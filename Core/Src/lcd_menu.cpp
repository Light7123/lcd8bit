/*
 * lcd_menu.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: user
 */
#include "lcd_menu.h"
#include "glcd.h"
#include "main.h"
#include "string.h"

Row* selectedMenuItem;

Row* start_menu			= new Row({"root"});
Row* stat_menu			= new Row({"root"});
Row* diag_menu			= new Row({"root"});
Row* setting_menu			= new Row({"root"});
Row* peref_menu =  new Row({"root"});
int str1[11]={145, 226, 160, 226, 168, 225, 226, 168, 170, 160, 300};
int str2[12]={132, 168, 160, 163, 173, 174, 225, 226, 168, 170, 160, 300};
int str3[14]={141, 160, 225, 226, 224, 174, 169, 170, 168, 300};
int str4[14]={143, 224, 174, 164, 160, 166, 160, 300};
int str5[14]={129, 165, 167, 173, 160, 171, 168, 231, 173, 235, 165, 300};
int str6[14]={141, 160, 171, 168, 231, 173, 235, 165, 300};
int str7[14]={145, 161, 224, 174, 225, 32, 145, 226, 160, 226, 300};
int str8[14]={132, 160, 226, 160, 32, 167, 160, 175, 224, 160, 162, 170, 168, 300};
int str9[14]={146, 165, 225, 226, 174, 162, 160, 239, 32, 300};
int str10[14]={143, 165, 224, 165, 228, 165, 224, 168, 239, 300};
int str11[14]={129, 165, 167, 173, 160, 171, 168, 231, 173, 235, 165, 300};
int str12[14]={141, 160, 171, 168, 231, 173, 235, 165, 300};
int str13[14]={146, 165, 225, 226, 32, 170, 173, 174, 175, 174, 170, 300};
int str14[14]={140, 174, 164, 165, 172, 300};
int str15[14]={143, 171, 160, 226, 235, 32, 224, 160, 225, 232, 168, 224, 46, 300};
int str16[14]={138, 160, 171, 168, 161, 224, 174, 162, 170, 160, 300};
int str17[14]={158, 225, 226, 168, 224, 174, 162, 170, 160, 300};
int str18[14]={143, 224, 160, 169, 225, 45, 171, 168, 225, 226, 300};
int str19[14]={141, 160, 171, 168, 231, 173, 235, 165, 300};
int str20[14]={143, 171, 160, 226, 235, 32, 224, 160, 225, 232, 168, 224, 46, 300};
void menu_init()
{
	//������������������������������������������������������ ������������������������

	start_menu->addRow({"Статистика    ",1})->children.push_back(stat_menu);

	start_menu->addRow({"Diagnostika   ",2})->children.push_back(diag_menu);

	start_menu->addRow({"Nastroiki     ",3})->children.push_back(setting_menu);


	//������������������������������������������������������������
	stat_menu->addRow({"prodaja",4})->parent=start_menu;
	stat_menu->addRow({"beznal",5})->parent=start_menu;
	stat_menu->addRow({"nal",6})->parent=start_menu;
	stat_menu->addRow({"sbros_stat",7})->parent=start_menu;
	stat_menu->addRow({"data zameni",8})->parent=start_menu;

	//������������������������������������������������������������������
	diag_menu->addRow({"test pokupka",9})->parent=start_menu;
	diag_menu->addRow({"perefiriya",10})->children.push_back(peref_menu);

	peref_menu->addRow({"Безнал",11})->parent=diag_menu;
	peref_menu->addRow({"Наличные",12})->parent=diag_menu;
	peref_menu->addRow({"Тест кнопок",13})->parent=diag_menu;
	peref_menu->addRow({"Модем",14})->parent=diag_menu;
	peref_menu->addRow({"Платы расширения",15})->parent=diag_menu;

	//������������������������������������������������������ ������������������������������������������������������������
	setting_menu->addRow({"kalibrovka",16})->parent=start_menu;
	setting_menu->addRow({"ustirovka",17})->parent=start_menu;
	setting_menu->addRow({"price",18})->parent=start_menu;
	setting_menu->addRow({"nichnie",19})->parent=start_menu;
	setting_menu->addRow({"plat rashire",20})->parent=start_menu;


}


int hz=0;
void menu_output(Row* row)
{
	glcd_clear_all();
	char ch[60];
	glcd_puts("*", 0, 0);


	for(int i=0;i<8;i+=1) //������������������������������������������������������������ ������������������������������ ������������ ������������������������������������������
	{
		sprintf(ch, "%s", row->payload.name.c_str());
		int test[50];

		switch (row->payload.name_int) {
			case 1:
				glcd_int_puts(str1, 10, i);
				break;
			case 2:
				glcd_int_puts(str2, 10, i);
							break;
			case 3:
				glcd_int_puts(str3, 10, i);
				break;
			case 4:
							glcd_int_puts(str4, 10, i);
							break;
			case 5:
							glcd_int_puts(str5, 10, i);
							break;
			case 6:
							glcd_int_puts(str6, 10, i);
							break;
			case 7:
							glcd_int_puts(str7, 10, i);
							break;
			case 8:
							glcd_int_puts(str8, 10, i);
							break;
			case 9:
							glcd_int_puts(str9, 10, i);
							break;
			case 10:
							glcd_int_puts(str10, 10, i);
							break;
			case 11:
							glcd_int_puts(str11, 10, i);
							break;
			case 12:
							glcd_int_puts(str12, 10, i);
							break;
			case 13:
							glcd_int_puts(str13, 10, i);
							break;
			case 14:
							glcd_int_puts(str14, 10, i);
							break;
			case 15:
							glcd_int_puts(str15, 10, i);
							break;
			case 16:
							glcd_int_puts(str16, 10, i);
							break;
			case 17:
							glcd_int_puts(str17, 10, i);
							break;
			case 18:
							glcd_int_puts(str18, 10, i);
							break;
			case 19:
							glcd_int_puts(str19, 10, i);
							break;
			case 20:
							glcd_int_puts(str20, 10, i);

							break;
		}



//		if(row->payload.value != NULL)
//		{
//			if(row->payload.callback == input_value_date_ptr || row->payload.callback == input_value_time_ptr)
//			{
//				sprintf(ch,"%02d.%02d.%02d",(uint8_t)(*row->payload.value>>16),(uint8_t)(*row->payload.value>>8),(uint8_t)(*row->payload.value));
//
//			}
//			else if(row->payload.callback == input_value_range10_ptr)
//			{
//				sprintf(ch,"%02d",*row->payload.value);
//			}
//			else  if(row->payload.selection == NULL)
//			{
//				sprintf(ch,"%03d",*row->payload.value);
//			}
//			glcd_puts(ch, row->payload.lcd_data_position, i);
//		}
		if(row->payload.selection != NULL)
		{
			string str = row->payload.selection->text[row->payload.selection->TypeNow];
			sprintf(ch, "%s", str.c_str()); //������������������������������ ������������������������������������������ ������������������������������������ ������������ ������������������������������������������������

			glcd_puts(ch, row->payload.lcd_data_position, i);
		}

		if(row->next)
			row = row->next;
		else
			break;
	}


}
void startMenu(void) {
	selectedMenuItem = start_menu -> next;
	menu_output(selectedMenuItem);
	glcd_puts("*", 0, 0);//������������������������������������������������������ ������������������������������������������ ������������ 1������ ������������������������������������
}

void menu_debug(Row* row)
{
	//������������������������������ ������ ������������������, ������������ ������������������ ������������������������������ ������������������������������������������������
	std::cout<<std::endl<<"Menu rows: "<<std::endl;
	for(; row/*!=nullptr*/; row = row->next)
	{
		std::cout<<"- "<<row->payload.name<<std::endl;
		if(row->hasChildren())
		{
			auto submenu3 = row->children.front();
			for(auto row2 = submenu3->begin(); row2!=submenu3->end(); row2 = row2->next)
			{
				std::cout<<"--- "<<row2->payload.name<<std::endl;
			}
		}
	}
}


void selectSwitch(Row* row, int y, int reset)
{
	char ch[40];
	if(row->payload.selection != NULL) // ������������������������������ ������������������������������������������������������ ������������������������������������������������������������
	{
		if(row->payload.selection->TypeNow < row->payload.selection->LenTypes-1 && !reset)
		{
			row->payload.selection->TypeNow++;
		}
		else row->payload.selection->TypeNow=0;

		sprintf(ch, "%s", row->payload.selection->text[row->payload.selection->TypeNow].c_str());
		glcd_puts(ch, row->payload.lcd_data_position, y);
	}
}
