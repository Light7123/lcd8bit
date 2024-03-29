/*
 * button.h
 *
 *  Created on: Jan 25, 2023
 *      Author: user
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

void button_moving_to_next_menu();
int button_in_menu();
uint8_t keyMenu(uint8_t param);
void read_button(void);
uint16_t read_button_set_data(uint8_t x, uint8_t y, int rangeMAX,int rangeMIN, uint8_t setNum);
void button_input_value();


#define KEY_UP				1
#define KEY_DOWN			2
#define KEY_RIGHT			3
#define KEY_LEFT			4
#define KEY_OK				5

#endif /* INC_BUTTON_H_ */
