
#include "qrcode.h"
#include "qrencode.h"
#include "main.h"
#include "glcd.h"
#include "lcd_menu.h"
#include "button.h"
#include <string>
#include "string.h"
#include "strings.h"
#include <iostream>

using namespace std;


int offsetsX;
int offsetsY;
int screenwidth;
int screenheight;
int multiply=2;

QRcode::QRcode(){

}

void QRcode::init(){
    //((TFT_eSPI *)tft)->init();
    screenwidth =128;
    screenheight = 64;
    //tft->setRotation(1);
    //tft->fillScreen(TFT_WHITE);
    int min = screenwidth;
    if (screenheight<screenwidth)
      min = screenheight;
    multiply = min/WD;
    offsetsX = (screenwidth-(WD*multiply))/2;
    offsetsY = (screenheight-(WD*multiply))/2;

}

void QRcode::render(int x, int y, int color){
  x=(x*multiply)+offsetsX;
  y=(y*multiply)+offsetsY;
  if(color==1) {
    glcd_puts_point(x,y,1);
    if (multiply>1) {
    	 glcd_puts_point(x+1,y,1);
    	 glcd_puts_point(x+1,y+1,1);
    	 glcd_puts_point(x,y+1,1);
    }
  }
  else {
	  //glcd_clear_here(x, x, y, y);
    if (multiply>1) {
    	//glcd_clear_here(x+1,x+1,y,y);
    	//glcd_clear_here(x+1,x+1,y+1,y+1);
    	//glcd_clear_here(x,x,y+1,y+1);
    }
  }
}

void QRcode::create(string message) {
  // create QR code
  glcd_clear_all();
 // message.toCharArray((char *)strinbuf,260);
  strcpy((char *)strinbuf,message.c_str());
  qrencode();
  // print QR Code
  for (int x = 0; x < WD; x+=2) {
    for (int y = 0; y < WD; y++) {
      if ( QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // black square on top of black square
        render(x, y, 1);
        render((x+1), y, 1);
      }
      if (!QRBIT(x,y) &&  QRBIT((x+1),y)) {
        // white square on top of black square
        render(x, y, 0);
        render((x+1), y, 1);
      }
      if ( QRBIT(x,y) && !QRBIT((x+1),y)) {
        // black square on top of white square
        render(x, y, 1);
        render((x+1), y, 0);
      }
      if (!QRBIT(x,y) && !QRBIT((x+1),y)) {
        // white square on top of white square
        render(x, y, 0);
        render((x+1), y, 0);
      }
    }
  }
}
