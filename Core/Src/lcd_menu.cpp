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
#include "GlobalDataKeeper.h"
#include "button.h"

GlobalDataKeeper* data = new GlobalDataKeeper();

Row* selectedMenuItem;

Row* start_menu = new Row({"root"});
Row* stat_menu = new Row({"root"});
Row* diag_menu = new Row({"root"});
Row* setting_menu = new Row({"root"});
Row* peref_menu = new Row({"root"});
Row* prodaja_stat = new Row({"root"});
Row* beznal_stat = new Row({"root"});
Row* nal_stat = new Row({"root"});
Row* sbros_stat = new Row({"root"});
Row* data_stat = new Row({"root"});
Row* beznal_peref = new Row({"root"});
Row* oplata_qr = new Row({"root"});
Row* terminal = new Row({"root"});
Row* loyal = new Row({"root"});
Row* nal_peref = new Row({"root"});
Row* kupurpriem = new Row({"root"});
Row* test_button = new Row({"root"});
Row* modem_peref = new Row({"root"});
Row* rashirenie_peref = new Row({"root"});
Row* bak_peref = new Row({"root"});
Row* kalibrovka = new Row({"root"});
Row* ustirowka = new Row({"root"});
Row* price = new Row({"root"});
Row* price_obem = new Row({"root"});
Row* price_cena = new Row({"root"});
Row* setting_nal = new Row({"root"});
Row* setting_kupur = new Row({"root"});
Row* setting_rashir = new Row({"root"});
Row* bak_setting = new Row({"root"});
Row* zamena = new Row({"root"});
Row* data_zamen = new Row({"root"});
Row* data_zapr = new Row({"root"});
int str[80][14] = {
{145, 226, 160, 226, 168, 225, 226, 168, 170, 160, 300}, //1
{132, 168, 160, 163, 173, 174, 225, 226, 168, 170, 160, 300},  //2
{141, 160, 225, 226, 224, 174, 169, 170, 168, 300},  //3
{143, 224, 174, 164, 160, 166, 160, 300}, //4
{129, 165, 167, 173, 160, 171, 168, 231, 173, 235, 165, 300}, //5
{141, 160, 171, 168, 231, 173, 235, 165, 300}, //6
{145, 161, 224, 174, 225, 32, 145, 226, 160, 226, 300},  //7
{132, 160, 226, 160, 32, 167, 160, 175, 224, 160, 162, 170, 168, 300},  //8
{146, 165, 225, 226, 174, 162, 160, 239, 32, 300},  //9
{143, 165, 224, 168, 228, 165, 224, 168, 239, 300},  //10
{129, 165, 167, 173, 160, 171, 168, 231, 173, 235, 165, 300}, //11
{141, 160, 171, 168, 231, 173, 235, 165, 300},  //12
{146, 165, 225, 226, 32, 170, 173, 174, 175, 174, 170, 300},  //13
{140, 174, 164, 165, 172, 300},  //14
{143, 171, 160, 226, 235, 32, 224, 160, 225, 232, 168, 224, 46, 300},  //15
{138, 160, 171, 168, 161, 224, 174, 162, 170, 160, 300},  //16
{158, 225, 226, 168, 224, 174, 162, 170, 160, 300},  //17
{143, 224, 160, 169, 225, 45, 171, 168, 225, 226, 300},  //18
{141, 160, 171, 168, 231, 173, 235, 165, 300},  //19
{143, 171, 160, 226, 235, 32, 224, 160, 225, 232, 168, 224, 46, 300},  //20
{130, 174, 164, 160, 32, 32, 32, 32, 32, 32, 32, 48, 300},  //21
{145, 129, 143, 32, 32, 32, 32, 32, 32, 32, 32, 48, 300},  //22
{146, 165, 224, 172, 168, 173, 160, 171, 32, 32, 32, 48, 300},  //23
{139, 174, 239, 171, 236, 173, 174, 225, 226, 236, 32, 48, 300},  //24
{138, 227, 175, 238, 224, 174, 175, 224, 168, 165, 172, 300},  //25
{145, 161, 224, 174, 225, 168, 226, 236, 300},  //26
{145, 161, 224, 174, 225, 168, 226, 236, 300},  //27
{142, 175, 171, 160, 226, 160, 32, 175, 174, 32, 81, 82, 300},  //28
{146, 165, 224, 172, 168, 173, 160, 171, 300},  //29
{139, 174, 239, 171, 236, 173, 174, 225, 226, 236, 300},  //30
{145, 226, 160, 226, 227, 225, 32, 32, 32, 32, 79, 75, 300},  //31
{145, 226, 160, 226, 227, 225, 32, 32, 32, 32, 79, 75, 300},  //32
{140, 174, 164, 165, 171, 236, 32, 32, 32, 32, 32, 48, 300},  //33
{145, 226, 160, 226, 227, 225, 32, 32, 32, 32, 79, 75, 300},  //34
{138, 227, 175, 238, 224, 174, 175, 224, 168, 165, 172, 300},  //35
{145, 226, 160, 226, 227, 225, 32, 32, 32, 32, 79, 75, 300},  //36
{140, 174, 164, 165, 171, 236, 32, 32, 32, 32, 32, 48, 300},  //37
{32, 146, 165, 225, 226, 32, 170, 173, 174, 175, 174, 170, 300},  //38
{73, 77, 69, 73, 32, 32, 32, 32, 32, 32, 32, 48, 300},  //39
{73, 67, 67, 73, 68, 32, 32, 32, 32, 32, 32, 48, 300},  //40
{67, 83, 81, 32, 32, 32, 32, 32, 32, 32, 32, 48, 300},  //41
{67, 83, 80, 78, 32, 32, 32, 32, 32, 32, 32, 48, 300},  //42
{142, 231, 168, 225, 226, 170, 160, 47, 161, 160, 170, 300},  //43
{145, 226, 160, 226, 227, 225, 32, 32, 32, 32, 79, 75, 300},  //44
{144, 160, 225, 229, 174, 164, 300},  //45
{142, 161, 234, 165, 172, 32, 49, 300},  //46
{142, 161, 234, 165, 172, 32, 50, 300},  //47
{142, 161, 234, 165, 172, 32, 51, 300},  //48
{142, 161, 234, 165, 172, 300},  //49
{150, 165, 173, 160, 300},  //50
{142, 161, 234, 165, 172, 32, 49, 300},  //51
{142, 161, 234, 165, 172, 32, 50,300},  //52
{142, 161, 234, 165, 172, 32, 51, 300},  //53
{142, 161, 234, 165, 172, 32, 49,  300},  //54
{142, 161, 234, 165, 172, 32, 50, 300},  //55
{142, 161, 234, 165, 172, 32, 51, 300},  //56
{138, 227, 175, 238, 224, 174, 175, 224, 168, 165, 172, 300},  //57
{136, 173, 170, 32, 225, 173, 239, 226, 32, 225, 226, 165, 170, 300},  //58
{142, 231, 168, 225, 226, 170, 160, 47, 161, 160, 170, 300},  //59
{144, 165, 166, 168, 172, 32, 224, 160, 161, 174, 226, 235, 300},  //60
{135, 160, 175, 224, 160, 162, 47, 167, 160, 172, 165, 173, 160, 300},  //61
{132, 160, 226, 160, 32, 167, 160, 175, 224, 160, 162, 170, 168, 300},  //62
{130, 224, 227, 231, 173, 227, 238, 300},  //63
{128, 162, 226, 174, 172, 160, 226, 168, 231, 165, 225, 170, 168, 300},  //64
{132, 160, 226, 160, 32, 167, 160, 172, 165, 173, 235, 300},  //65
{130, 224, 227, 231, 173, 227, 238, 300},  //66
{128, 162, 226, 174, 172, 160, 226, 168, 231, 165, 225, 170, 168, 300},  //67
{53, 48, 32, 32, 32, 32, 32, 32, 32, 32, 32, 48, 300}, //68
{49, 48, 48, 32, 32, 32, 32, 32, 32, 32, 32, 48, 300}, //69
{50, 48, 48, 32, 32, 32, 32, 32, 32, 32, 32, 48, 300}, //70
{53, 48, 48, 32, 32, 32, 32, 32, 32, 32, 32, 48, 300}, //71
};
void menu_init()
{
	//������������������������������������������������������ ������������������������

	start_menu->addRow({"Статистика    ",1})->children.push_back(stat_menu);

	start_menu->addRow({"Diagnostika   ",2})->children.push_back(diag_menu);

	start_menu->addRow({"Nastroiki     ",3})->children.push_back(setting_menu);


	//������������������������������������������������������������
	stat_menu->parent=start_menu;
	stat_menu->addRow({"prodaja",4})->children.push_back(prodaja_stat);
		prodaja_stat->addRow({"Voda",21})->parent=stat_menu;
	stat_menu->addRow({"beznal",5})->children.push_back(beznal_stat);
		beznal_stat->addRow({"SBP",22})->parent=stat_menu;
		beznal_stat->addRow({"terminal",23})->parent=stat_menu;
		beznal_stat->addRow({"loyal",24})->parent=stat_menu;
	stat_menu->addRow({"nal",6})->children.push_back(nal_stat);
		nal_stat->addRow({"купюроприемник",25})->parent=stat_menu;
		nal_stat->addRow({"50",68})->parent=stat_menu;
		nal_stat->addRow({"100",69})->parent=stat_menu;
		nal_stat->addRow({"200",70})->parent=stat_menu;
		nal_stat->addRow({"500",71})->parent=stat_menu;
	stat_menu->addRow({"sbros_stat",7})->children.push_back(sbros_stat);
		sbros_stat->addRow({"sbros",26})->parent=stat_menu;
	stat_menu->addRow({"data zameni",8})->children.push_back(data_stat);
		data_stat->addRow({"sbros",27})->parent=stat_menu;

	//������������������������������������������������������������������
		diag_menu->parent=start_menu;
	diag_menu->addRow({"test pokupka",9})->parent=start_menu;
	diag_menu->addRow({"perefiriya",10})->children.push_back(peref_menu);
	peref_menu->parent=diag_menu;
	peref_menu->addRow({"Безнал",11})->children.push_back(beznal_peref);
		beznal_peref->parent=peref_menu;
		beznal_peref->addRow({"oplata qr",28})->children.push_back(oplata_qr);
			oplata_qr->addRow({"status",31})->parent=beznal_peref;
		beznal_peref->addRow({"terminal",29})->children.push_back(terminal);
			terminal->addRow({"status",32})->parent=beznal_peref;
			terminal->addRow({"model",33})->parent=beznal_peref;
		beznal_peref->addRow({"loyal",30})->children.push_back(loyal);
			loyal->addRow({"status",34})->parent=beznal_peref;
	peref_menu->addRow({"Наличные",12})->children.push_back(nal_peref);
		nal_peref->parent=peref_menu;
		nal_peref->addRow({"Купюроприемник",35})->children.push_back(kupurpriem);
			kupurpriem->addRow({"status",36})->parent=nal_peref;
			kupurpriem->addRow({"model",37})->parent=nal_peref;
	peref_menu->addRow({"Тест кнопок",13})->children.push_back(test_button);
		test_button->addRow({"тест",38})->parent=peref_menu;
	peref_menu->addRow({"Модем",14})->children.push_back(modem_peref);
		modem_peref->addRow({"imei",39})->parent=peref_menu;
		modem_peref->addRow({"iccid",40})->parent=peref_menu;
		modem_peref->addRow({"csq",41})->parent=peref_menu;
		modem_peref->addRow({"cspn",42})->parent=peref_menu;
	peref_menu->addRow({"Платы расширения",15})->children.push_back(rashirenie_peref);
		rashirenie_peref->parent=peref_menu;
		rashirenie_peref->addRow({"bak",43})->children.push_back(bak_peref);
			bak_peref->addRow({"status",44})->parent=rashirenie_peref;

	//������������������������������������������������������ ������������������������������������������������������������
	setting_menu->parent=start_menu;
	setting_menu->addRow({"kalibrovka",16})->children.push_back(kalibrovka);
		kalibrovka->addRow({"rashod",45,8*8,&data->rashodomer,button_input_value,zero_buttons,NULL,input_value_float})->parent=setting_menu;
	setting_menu->addRow({"ustirovka",17})->children.push_back(ustirowka);
		ustirowka->addRow({"obem 1",46,8*9,&data->ust1,button_input_value,zero_buttons,NULL,input_value_float2})->parent=setting_menu;
		ustirowka->addRow({"obem 2",47,8*9,&data->ust2,button_input_value,zero_buttons,NULL,input_value_float2})->parent=setting_menu;
		ustirowka->addRow({"obem 3",48,8*9,&data->ust3,button_input_value,zero_buttons,NULL,input_value_float2})->parent=setting_menu;
	setting_menu->addRow({"price",18})->children.push_back(price);
		price->parent=setting_menu;
		price->addRow({"obem",49})->children.push_back(price_obem);
			price_obem->addRow({"obem 1",51,8*9,&data->price_ob1,button_input_value,zero_buttons,NULL,input_value_float2})->parent=price;
			price_obem->addRow({"obem 2",52,8*9,&data->price_ob2,button_input_value,zero_buttons,NULL,input_value_float2})->parent=price;
			price_obem->addRow({"obem 3",53,8*9,&data->price_ob3,button_input_value,zero_buttons,NULL,input_value_float2})->parent=price;
		price->addRow({"cena",50})->children.push_back(price_cena);
			price_cena->addRow({"obem 1",54,8*9,&data->price_cost1,button_input_value,zero_buttons,NULL,input_value_float2})->parent=price;
			price_cena->addRow({"obem 2",55,8*9,&data->price_cost2,button_input_value,zero_buttons,NULL,input_value_float2})->parent=price;
			price_cena->addRow({"obem 3",56,8*9,&data->price_cost3,button_input_value,zero_buttons,NULL,input_value_float2})->parent=price;
	setting_menu->addRow({"nichnie",19})->children.push_back(setting_nal);
		setting_nal->parent=setting_menu;
		setting_nal->addRow({"kupur",57})->children.push_back(setting_kupur);
			setting_kupur->addRow({"inkas",58})->parent=setting_nal;
	setting_menu->addRow({"plat rashire",20})->children.push_back(setting_rashir);
		setting_rashir->parent=setting_menu;
		setting_rashir->addRow({"bak",59})->children.push_back(bak_setting);
			bak_setting->addRow({"rezhim",60})->parent=setting_rashir;
		setting_rashir->addRow({"zamena",61})->children.push_back(zamena);
			zamena->parent=setting_rashir;
			zamena->addRow({"data",62})->children.push_back(data_zapr);
				data_zapr->addRow({"manual",63})->parent=zamena;
				data_zapr->addRow({"auto",64})->parent=zamena;
			zamena->addRow({"data",65})->children.push_back(data_zamen);
				data_zamen->addRow({"manual",66})->parent=zamena;
				data_zamen->addRow({"auto",67})->parent=zamena;

}


int hz=0;
void menu_output(Row* row)
{
	glcd_clear_all();
	char ch[60];
	char ch1[60];
	glcd_puts("*", 0, 0);


	for(int i=0;i<8;i+=1) //������������������������������������������������������������ ������������������������������ ������������ ������������������������������������������
	{
		sprintf(ch, "%s", row->payload.name.c_str());
		int a=row->payload.name_int;
		int test[14];
		for(int i=0;i<14;i++)
		{
			test[i]=str[row->payload.name_int-1][i];
		}
		glcd_int_puts(test, 10, i);
		int value=*row->payload.value;
		uint8_t setNum;
		if (selectedMenuItem->payload.value == &data->rashodomer) //если ввод шагов, то диапозон от 0 до 10
						(setNum = 6);
					else if (selectedMenuItem->payload.value == &data->price_cost1||selectedMenuItem->payload.value == &data->price_cost2||selectedMenuItem->payload.value == &data->price_cost3
							||selectedMenuItem->payload.value == &data->price_ob1||selectedMenuItem->payload.value == &data->price_ob2||selectedMenuItem->payload.value == &data->price_ob3||
							selectedMenuItem->payload.value == &data->ust1||selectedMenuItem->payload.value == &data->ust2||selectedMenuItem->payload.value == &data->ust3)
						(setNum = 5);
		if(row->payload.value!=NULL)
		{
			if(setNum==4)
			{
				sprintf(ch1,"[%04d]", value);
			} else if(setNum ==3)
			{
				sprintf(ch1,"[%03d]", value);
			}else if(setNum == 2)
			{
				sprintf(ch1,"[%02d]", value);
			}
			else if(setNum==5)
			{
				sprintf(ch1, "[%02d.%01d]", value/10,value%10);
			}
			else if(setNum==6)
					{
						sprintf(ch1,"[%01d.%03d]",  value/1000, value%1000);
					}
			glcd_puts(ch1, row->payload.lcd_data_position, i);
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
