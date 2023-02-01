/*
 * node_menu.h
 *
 *  Created on: 20 апр. 2020 г.
 *      Author: user
 */

#ifndef LCD_MENU_H_
#define LCD_MENU_H_

#define USER_SCHEME_SELECTOR 0
#define USER_PLATE_SELECTOR 1

#include "stm32f1xx_hal.h"
#include "list"
#include "map"
#include "iostream"
#include "vector"
#include "string"
#include "main.h"

#define NumofParam 7

using namespace std;

enum Menu_pointer
{
	//данное перечисление указателей показывает что нужно сделать или куда нужно перейти по нажатию кнопки OK
	start_menu_ptr,
	stat_menu_ptr,
	diag_menu_ptr,
	setting_menu_ptr


};
enum number_of_button
{
	two_buttons = 1,
	zero_buttons = 0,
};

class Selector
{
public:
	uint8_t IDselect; // порядковый номер ( ID) селектора
	uint8_t LenTypes; // количество вариантов
	uint8_t TypeNow; // Текущий вариант
	vector<string>  text;
public:
	Selector(vector<string>  text_)
	{
		text = text_;
		TypeNow=0;
	}

	Selector(vector<string>  text_,uint8_t IDselect_,uint8_t LenTypes_)
	{
		text = text_;
		IDselect=IDselect_;
		LenTypes=LenTypes_;
		TypeNow=0;
	}
};

//здесь указываем какую информацию мы можем хранить
struct Payload
{
	string name;
	int name_int;
	int lcd_data_position;
	int* value;
	void (*callback)() = nullptr;
	int number_of_button = zero_buttons;
	Selector  *selection;
	Menu_pointer menu_ptr;


};


class Row
{
public:
	Row* parent;
	list<Row*> children; //list дает возможность сортить подменю
	Row* next;
	Row* prev;
	Row* last; //конец списка
	Payload payload;
public:
	Row():
		parent(nullptr),children(),next(nullptr),prev(nullptr), last(this), payload()
	{
		//cout<<__PRETTY_FUNCTION__<<endl;
	}
	Row(const Payload& payload):
		parent(nullptr),children(),next(nullptr),prev(nullptr), last(this), payload(payload)
	{
		//cout<<__PRETTY_FUNCTION__<<endl;
	}
	Row(const Payload& payload, Row* parent_):
		parent(parent_),children(),next(nullptr),prev(nullptr), last(this), payload(payload)
	{
		//cout<<__PRETTY_FUNCTION__<<endl;
		if(parent)
			parent->children.push_back(this);
	}
	Row(const Payload& payload, Row* parent_, Row* left, Row* right=nullptr):
		parent(parent_), children(), next(right), prev(left),
		last(prev ? prev->last : (next ? next->last : this)),
		payload(payload)
	{
		//cout<<__PRETTY_FUNCTION__<<endl;
		if(parent)
			parent->children.push_back(this);

		if(prev)
			prev->next = this;

		if(next)
			next->prev = this;
	}
	//создать подменю
	Row* addChild(const Payload& payload)
	{
		//cout<<__PRETTY_FUNCTION__<<endl;
		Row* child = new Row(payload,this);
		return child;
	}
	Row* addNextRow(const Payload& payload)
	{
		//cout<<__PRETTY_FUNCTION__<<endl;
		Row* newRow = new Row(payload,parent,this,next);
		return newRow;
	}
	//создать строку в конце списка
	Row* addRow(const Payload& payload)
	{
		//cout<<__PRETTY_FUNCTION__<<endl;
		Row* newLast = last->addNextRow(payload); //новый хвост списка
		for(Row* row = this; row!=nullptr; row = row->prev)
		{
			row->last = newLast; //ставим новый хвост всем предыдущим строкам
		}
		for(Row* row = this; row!=nullptr; row = row->next)
		{
			row->last = newLast; //ставим нвоый хвост всем поседующим строкам
		}
		return newLast;
	}

	bool hasChildren() const
	{
		return !children.empty();
	}
	bool hasParent() const
	{
		return !children.empty();
	}
	//begin(). Сделано чисто для удобства обхода в цикле
	Row* begin()
	{
		return this;
	}
	Row* end() const
	{
		return nullptr;
	}
};

extern Row* selectedMenuItem;
extern Row* setting_menu;
extern Row* start_menu;
extern Row* stat_menu;
extern Row* diag_menu;

void default_settings(void);

void menu_init();
void menu_output(Row* row); // вывод отображаемого меню на экран
void startMenu(void); // начальный вывод меню
void menu_debug(Row* row); // вывод меню в отладочном режиме
void selectSwitch(Row* row, int y, int reset);


#endif /* LCD_MENU_H_ */
