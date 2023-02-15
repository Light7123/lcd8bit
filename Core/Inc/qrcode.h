
#include "qrencode.h"
#include "main.h"
#include "glcd.h"
#include "lcd_menu.h"
#include "button.h"
#include <string>
#include "string.h"
#include "strings.h"
#include <iostream>

class QRcode
{
	private:
		//TFT_eSPI *tft;
		void render(int x, int y, int color);

	public:
		QRcode();
		void init();
		void create(string message);
};
