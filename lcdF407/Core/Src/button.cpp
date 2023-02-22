/*
 * button.cpp
 *
 *  Created on: Jan 25, 2023
 *      Author: user
 */

#include "main.h"
#include "lcd_menu.h"
#include "gpio.h"
#include "usart.h"
#include "glcd.h"
#include "button.h"
#include "GlobalDataKeeper.h"

int button = 0, button_prev = 0;
int inputValueOLD, inputValue, inputValue_prev;
uint16_t rangeInput = 100;
uint32_t rangeInputTime=10;

int posX = 0;

void encoder_clear(uint8_t mode)
{
	posX=0;
	button = 0;
	button_prev = 0;


//	if(mode==1)
//	{
//		enc_state = default_state;
//		LCD_CharAt(0x90, 0, 0);
//	}
}

void button_moving_to_next_menu()
{
	int res = 0; // нужен для проверки подключения флешки
		int mode = 0; // нужен для сброса энкодера
		int y = 2;


		switch(selectedMenuItem->payload.menu_ptr) //прыгаем в .../делаем ...
			{
			case start_menu_ptr: // в главное меню
//				button_state = default_state;

				break;
			case stat_menu_ptr:// в запуск опыта
				//LCD_CharAt(0x90, 0, 0);
				//data->diameterPlateDIN=300;

				break;
			case diag_menu_ptr: //в DIN на песках
//				mode = 1;
//				proc_type = DIN_sand;
//				stepsDIN = stepsSands;
//				data->diaDIN = 300;
//				selectSwitch(selectedMenuItem->children.front()->next,0,1);

				break;
			case setting_menu_ptr: //в стандартный DIN
//				mode = 1;
//				proc_type = DIN_no_sand;
//				stepsDIN = stepsDIN1;

				break;
			}

		if(posX > 0) //на второй кнопке
			{
				Row* oldSelectedMenuItem = selectedMenuItem;
				selectedMenuItem = selectedMenuItem->children.back();
//				if(selectedMenuItem == oldSelectedMenuItem) //если пункт сохранить/запустить, то указывать будет сам на себя
//				{
//					res = USB__checkConnection();
//					if (res)
//						USB__saveCurrentSettings( );
//					if (selectedMenuItem->payload.menu_ptr == main_menu_ptr) // прыгаем из настроек
//						selectedMenuItem = selectedMenuItem -> parent;
//					else // иначе прыгаем в опыт
//						selectedMenuItem = *next(selectedMenuItem->children.begin(), 1);
//				}
			}
			else //это просто переход в меню
			{
				// проверка на отмену
				Row* oldSelectedMenuItem = selectedMenuItem;
				Row* menuItem = selectedMenuItem->children.back();
				if(menuItem == oldSelectedMenuItem) // это отмена, валим ребята
				{
					//enc_state = default_state;
					mode = 1;
				}

				selectedMenuItem = selectedMenuItem->children.front();
			}


			keyMenu(KEY_DOWN);//каждое подменю начинается со строки root, поэтому после перехода всегда приходится сдвигать

			menu_output(selectedMenuItem); //отрисовка меню
			// если в проверке прибора
//			if (selectedMenuItem->prev->payload.menu_ptr == test_sensor_menu_ptr|| // отдельная менюшка
//
//					//selectedMenuItem->prev->payload.callback == test_sensor_before_exp_ptr) // или менюшка перед опытом
//
//					selectedMenuItem->prev->payload.menu_ptr == test_sensor_before_exp_ptr) // или менюшка перед гильотиной
//			{
//				if (!res)
//					LCD_StringAt("ERR", 5, y);
//				else
//					LCD_StringAt("OK", 5, y);
//			}

			encoder_clear(mode);

}
int restimer=0;
void tik_callback(void)
{
//	enc1.tick();

	if((down_button==1)&&(HAL_GetTick()-restimer>300))
	{
		button--;
		down_button=0;
		restimer=HAL_GetTick();
	}
	if((up_button==1)&&(HAL_GetTick()-restimer>300))
	{
		up_button=0;
		button++;
		restimer=HAL_GetTick();
	}


}



int button_in_menu()
{
	int flag_input=0;
	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)== GPIO_PIN_SET){
		  if(flag_input==0)
		  		  {
		  HAL_UART_Transmit_IT(&huart5, (uint8_t*)"1\n", 3);
		  flag_input=1;
		  return 1;
		  }
	  }
	  else
		  flag_input=0;
		  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)== GPIO_PIN_SET){
			  if(flag_input==0)
			  		  {
			  HAL_UART_Transmit_IT(&huart5, (uint8_t*)"2\n", 3);
			  flag_input=1;
			  return 2;
			  }
		  }
		  else
			  flag_input=0;
		  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)== GPIO_PIN_SET){
			  if(flag_input==0)
			  		  {
			 HAL_UART_Transmit_IT(&huart5,(uint8_t*)"3\n", 3);
			  flag_input=1;
			  return 3;
			  }
		  }
		  else
			  flag_input=0;
		  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9)== GPIO_PIN_SET){
			  if(flag_input==0)
			 	  {
			 HAL_UART_Transmit_IT(&huart5, (uint8_t*)"4\n", 3);
			  flag_input=1;
			  return 4;
			  }
		  }
		  else
			  flag_input=0;
}

void button_input(void)
{
	//enc_state = value_input;
	//glcd_puts("I", 0, 0);

	if(selectedMenuItem->payload.menu_ptr==input_value_range10_ptr)
	{
		rangeInput=10; // ввод двухзначного значения
	}
	else
		if(selectedMenuItem->payload.menu_ptr==input_value_float)
		{
			rangeInput=1000;
		}
		else
			if(selectedMenuItem->payload.menu_ptr==input_value_float2)
			{
				rangeInput=100;
			}
			else
		{
			rangeInput=100; // ввод трехзначного значения
		}
	rangeInputTime=10;
	inputValue = *selectedMenuItem->payload.value;
	inputValueOLD = *selectedMenuItem->payload.value;
	//read_button_set_data(1,1,1,100,5);
}

uint8_t keyMenu(uint8_t param) {
	switch (param) {
	case 0:
		return 1;
	case KEY_LEFT: // Вернуться назад на одну менюшку (кнопка reset)
		if(selectedMenuItem -> parent) // если есть куда возвращаться
		{

			// Выводим старые данные
			selectedMenuItem = selectedMenuItem -> parent ->next;
			menu_output(selectedMenuItem);
			encoder_clear(1);
		}
		break;
	case KEY_DOWN: //  энкодер на одну строчку вниз
		if(selectedMenuItem!=selectedMenuItem->end()) // если снизу еще есть строчки
			if(selectedMenuItem -> next )
			{
				selectedMenuItem = selectedMenuItem -> next;
				return 1;
			}
		return 0;
	case KEY_UP:  // энкодер на одну строчку вверх
		if(selectedMenuItem -> prev -> payload.name!="root") // проверка выхода за пределы
			if(selectedMenuItem -> prev)
			{
				selectedMenuItem = selectedMenuItem -> prev;
				return 1;
			}
		return 0;
	case KEY_OK: // перейти на одну менюшку вперед или селектор ( кнопка ОК)
		//y = encoder;
		if(selectedMenuItem->payload.value != NULL)
					button_input(); //переход в состояние ввода числа





		if(selectedMenuItem->hasChildren())

			button_moving_to_next_menu();// переход на след. уровень меню
		return 1;
	}
	return 1;
}


void read_button(void)
{
	tik_callback();

	if(button > button_prev)//курсор на экране двинули вниз
	{
		if(selectedMenuItem -> payload.number_of_button) //если это строка с двумя кнпоками
		{
			glcd_puts(" ", posX, button_prev);
			//В строке с двумя кнопками длина кнопок разная
//			if(selectedMenuItem->payload.menu_ptr== main_menu_ptr)
//			{
//				posX = 9;
//			}
//			else
//			{
//				posX = 11;
//			}
			button = button_prev;
			glcd_puts("*", posX, button);
		}
		else if(button > 6 && selectedMenuItem -> next) // проверяем есть ли еще строки, нужно ли перерисовывать экран
		{
			keyMenu(KEY_DOWN);
			button = 0;
			menu_output(selectedMenuItem);
		}
		else if(!keyMenu(KEY_DOWN)) button--; //тут наконец-то его двигаем вниз и ограничиваем движение энкодера, если строк больше нет

	}
	else if(button < button_prev) //когда листаем меню вверх
	{
		if(posX > 0) //если это строка с двумя кнпоками
		{
			glcd_puts(" ", posX, button_prev);
			posX = 0;
			button = button_prev;
			glcd_puts("*", posX, button);
		}
//		else if(button < 0 && selectedMenuItem-> prev-> payload.name!="root" && selectedMenuItem -> prev) //если надо перерисовать экран вверх
//		{
//			//передвигаем экран на 4 позиции вверх и отрисовываем его, курсор рисуется на самой первой строке
//			button = 0;
//			button_prev = 0;
//
//			// Это норма, это для постраничной отрисовки меню
//			keyMenu(KEY_UP);
//			keyMenu(KEY_UP);
//			keyMenu(KEY_UP);
//			keyMenu(KEY_UP);
//
//
//			menu_output(selectedMenuItem);
//			selectedMenuItem = selectedMenuItem -> next;
//			button++;
//			selectedMenuItem = selectedMenuItem -> next;
//			button++;
//			selectedMenuItem = selectedMenuItem -> next;
//			button++;
//
//		}
		else if(!keyMenu(KEY_UP)) button = 0; //если стоим на первой строке и долбимся вверх
	}
	if (button != button_prev){ //костыль чтобы на прерываниях все было чики бамбони
		button < 0 ? button = 0 : button;
		glcd_puts(" ", posX, button_prev);
		glcd_puts("*", posX, button);

		button_prev = button;
	}
	if(reset_button==1)
	{
		keyMenu(KEY_LEFT);
		reset_button=0;

	}
	if(ok_button==1 && selectedMenuItem->payload.value == NULL) //заходим сюда, если надо переходить по менюхам, иначе все обрабатывается в колбеках
	{
		keyMenu(KEY_OK);
		posX=0;
		ok_button=0;

	}

}

//void button_input(void)
//{
//	enc_state = value_input;
//
//	if(selectedMenuItem->payload.menu_ptr==input_value_range10_ptr)
//	{
//		rangeInput=10; // ввод двухзначного значения
//	}
//	else
//		if(selectedMenuItem->payload.menu_ptr==input_value_float)
//		{
//			rangeInput=1000;
//		}
//		else
//		{
//			rangeInput=100; // ввод трехзначного значения
//		}
//	rangeInputTime=10;
//	inputValue = *selectedMenuItem->payload.value;
//	inputValueOLD = *selectedMenuItem->payload.value;
//}
uint8_t setNum = 3;
void button_input_value()
{
	//enc_state = value_input;

	if(ok_button==1){
		ok_button = 0;
		while(1)
		{
			int rangeMAX = 999, rangeMIN = 0;

			if (selectedMenuItem->payload.value == &data->rashodomer) //если ввод шагов, то диапозон от 0 до 10
				(rangeMAX = 10000, rangeMIN = 0, setNum = 6);
			else if (selectedMenuItem->payload.value == &data->price_cost1||selectedMenuItem->payload.value == &data->price_cost2||selectedMenuItem->payload.value == &data->price_cost3
					||selectedMenuItem->payload.value == &data->price_ob1||selectedMenuItem->payload.value == &data->price_ob2||selectedMenuItem->payload.value == &data->price_ob3||
					selectedMenuItem->payload.value == &data->ust1||selectedMenuItem->payload.value == &data->ust2||selectedMenuItem->payload.value == &data->ust3)
				(rangeMAX = 999, rangeMIN = 0, setNum = 5);

				inputValue = *selectedMenuItem->payload.value;
				inputValueOLD = *selectedMenuItem->payload.value;
			*selectedMenuItem->payload.value = read_button_set_data(selectedMenuItem->payload.lcd_data_position, button, rangeMAX, rangeMIN, setNum);
			if((ok_button && rangeInput <= 1 ) || reset_button)
			{
				ok_button = 0;
				reset_button = 0;
				rangeInput = 100;
				//enc_state = default_state;
				break;
			}
		}
	}

}

uint16_t read_button_set_data(uint8_t x, uint8_t y, int rangeMAX,int rangeMIN, uint8_t setNum)
{
	char ch[40];
	//button.tick();
	//glcd_puts("Z", 0, 0);

	if(up_button==1)
	{
		inputValue+=rangeInput;
		up_button = 0;
		//glcd_puts("+", 0, 0);

	}
	if(down_button==1 )
	{
		//enc1.tick();
		//glcd_puts("-", 0, 0);

		inputValue -=rangeInput;
		down_button = 0;
	}




	if(inputValue < rangeMIN)
		inputValue=rangeMIN;
	if(inputValue > rangeMAX) inputValue=rangeMAX;

	if(inputValue != inputValue_prev)
	{
		inputValue_prev = inputValue;

		if(setNum==4)
		{
			sprintf(ch,"[%04d]",inputValue);
		} else if(setNum ==3)
		{
			sprintf(ch,"[%03d]",inputValue);
		}else if(setNum == 2)
		{
			sprintf(ch,"[%02d]",inputValue);
		}
		else if(setNum==5)
		{
			sprintf(ch, "[%02d.%01d]", inputValue/10,inputValue%10);
		}
		else if(setNum==6)
				{
					sprintf(ch, "[%01d.%03d]", inputValue/1000,inputValue%1000);
				}
		glcd_puts(ch, x, y);

	}
	if(ok_button==1 && rangeInput > 1)
	{
		rangeInput /= 10;
		ok_button = 0;
	}

	if(reset_button )
	{
//		//Костыль чтобы ливнуть из другого костыля
//		if(manual_mode_func==3)
//		{
//			manual_mode_func=1;
//		}
//		else
//		{

			*selectedMenuItem->payload.value = inputValueOLD;
			inputValue_prev = inputValue = inputValueOLD;
			if(setNum==4)
			{
				sprintf(ch,"[%04d]",inputValueOLD);
			}else if(setNum ==3)
			{
				sprintf(ch,"[%03d]",inputValueOLD);
			}else if(setNum == 2)
			{
				sprintf(ch,"[%02d]",inputValueOLD);
			}
			else if(setNum==5)
			{
				sprintf(ch, "[%02d.%1d]", inputValue/10,inputValue%10);
			}
			else if(setNum==6)
					{
						sprintf(ch, "[%01d.%03d]", inputValue/1000,inputValue%1000);
					}

			glcd_puts(ch, x, y);

//			if(enc_state == value_input)
//			{
//				enc_state = default_state;
//			}
		//}


	}
	inputValue_prev = 0;

	return inputValue;
}
