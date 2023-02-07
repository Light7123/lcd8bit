/*
 * GlobalDataKeeper.h
 *
 *  Created on: 3 февр. 2023 г.
 *      Author: user
 */

#ifndef INC_GLOBALDATAKEEPER_H_
#define INC_GLOBALDATAKEEPER_H_


#include "map"
#include "string"
#include "main.h"
#include "stm32f1xx_hal.h"
#include <vector>
using namespace std;


class GlobalDataKeeper {
public:
	GlobalDataKeeper(); 			// заполнение полей ниже дефолтными параметрами

	void create_map(void);			// создание карты для более удобных чтения/записи с флешки
	void map_to_data(void);


	// "Внешние" переменные. Их можно вводить, они выводятся на флешку
	int rashodomer;
	int ust1;
	int ust2;
	int ust3;
	int price_ob1;
	int price_ob2;
	int price_ob3;
	int price_cost1;
	int price_cost2;
	int price_cost3;
	map <string, int> global_var;	// map для хранения пар "человекопонятное_название - переменная"
};
typedef std::map<string, int> Mapa;


#endif /* INC_GLOBALDATAKEEPER_H_ */
