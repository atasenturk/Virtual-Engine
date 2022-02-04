/**
* @file TankList.h
* @author Ergün Altýndað(152120181083)
* @date 19.01.2022
* @brief Header of TankList class.
*
*This file includes all the declarations of member variables and functions for TankList class.
*/
#ifndef TANKLIST_H_
#define TANKLIST_H_
#include "tank.h"
#include <vector>
#include <string>
#include <string.h>
#include <sstream>

//!The TankList class is the class that contains the and functions such as adding gasoline, etc., where we adjust the properties of the tanks.
/*!
 * It allows adding and removing tanks by adjusting the properties of tanks.
*/
class TankList {
private:
	std::vector<Tank> tanks;
public:
	/**Constructor for TankList class
	*/
	TankList();
	/** This function is used to add gasoline to the tank.
	* @param doblue gets the amount of petrol to add
	*/
	void add_fuel_tank(double = 100);
	/** This function is used to list tanks.
	*/
	void list_fuel_tanks();
	/** This function allows tanks used to remove from the list.
	* @param int gets the id of the tank to be deleted
	*/
	void remove_fuel_tank(int);
	/** This function allows tanks used to remove from the list.
	* @param int gets the id of the tank to be break
	*/
	void break_fuel_tank(int);
	/** This function allows tanks used for repair.
	* @param int gets the id of the tank to be repair
	*/
	void repair_fuel_tank(int);
	/** This function is used to open the valve of the tanks.
	* @param the int valve gets the id of the tank to be opened
	*/
	void open_valve(int);
	/** This function is used to close the valve of the tanks.
	* @param the int valve gets the id of the tank to be closed
	*/
	void close_valve(int);

	/** This function is used to connect the tank.
	* @param int connect the id of the tank to connect to
	*/
	void connect_fuel_tank_to_engine(int);
	/** This function is used to disconnect the tank.
	* @param int disconnect the id of the tank to connect to
	*/
	void disconnect_fuel_tank_from_engine(int);
	/** This function is used to print the fuel_tank count.
	*/
	void print_fuel_tank_count() const;
	/** This function is used to print the fuel_tank quantity.
	*/
	void print_total_fuel_quantity();
	/** This function is used to find out the tank status.
	* @param int gets the id of the tank whose status is to be learned
	*/
	void print_tank_info(int);
	/** This function is used to refuel the tank.
	*@param int gets the ID of the tank to refuel
	*@param double gets the amount of fuel of the tank to refuel
	*/
	void fill_tank(int, double);

	/** This function is used to refuel between tanks
	* @param int,int,int gets the ids of the tanks that are refueled.
	*/
	void sum_operator(int tank1, int tank2, int tank3);

	/** This function is used to find the tank.
	* @param int,int,int gets the ids of the tanks that are refueled.
	*/
	int find_tank(int);
	/** This function is used to update the tank.
	*/
	void update_tanks();
	/** This function is used to register the tank.
	*/
	void registerTanks();
};

#endif /* TANKLIST_H_ */