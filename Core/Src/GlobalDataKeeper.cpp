#include "GlobalDataKeeper.h"

GlobalDataKeeper::GlobalDataKeeper() {

	rashodomer=12;
	ust1=50;
	ust2=100;
	ust3=189;
	price_ob1=50;
	price_ob2=100;
	price_ob3=189;
	price_cost1=10;
	price_cost2=10;
	price_cost3=10;
	create_map();
}
void GlobalDataKeeper::create_map(){
	global_var.clear();
	global_var.insert(Mapa::value_type("rashodeomer:",rashodomer));
	global_var.insert(Mapa::value_type("ust1:",ust1));
	global_var.insert(Mapa::value_type("ust2:",ust2));
	global_var.insert(Mapa::value_type("ust3:",ust3));
	global_var.insert(Mapa::value_type("price ob1:",price_ob1));
	global_var.insert(Mapa::value_type("price ob2:",price_ob2));
	global_var.insert(Mapa::value_type("price ob3:",price_ob3));
	global_var.insert(Mapa::value_type("price cost 1:",price_cost1));
	global_var.insert(Mapa::value_type("price cost 2:",price_cost2));
	global_var.insert(Mapa::value_type("price cost 2:",price_cost3));
}
void GlobalDataKeeper::map_to_data(void)
{
	rashodomer = global_var["rashodomer:"];
	ust1=global_var["ust1:"];
	ust2=global_var["ust2:"];
	ust3=global_var["ust3:"];
	price_ob1=global_var["price ob1:"];
	price_ob2=global_var["price ob2:"];
	price_ob3=global_var["price ob3:"];
	price_cost1=global_var["price cost1:"];
	price_cost2=global_var["price cost2:"];
	price_cost3=global_var["price cost3:"];
}
