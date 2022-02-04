/**
* @file Tank.h
* @author Ergün Altýndað(152120181083)
* @date 19.01.2022
* @brief Header of Tank class.
*
*This file includes all the declarations of member variables and functions for Tank class.
*/
#ifndef TANK_H_
#define TANK_H_
#include <iostream>
#include "Observer.h"
#include "output.h"
#include <sstream>
using namespace std;

//!Tank class is the class that contains the functions we use to add tanksand set their properties.
/*!
 * It provides the possibility to add tanks by adjusting the properties of the tanks.
*/

class Tank : public Observer
{
protected:
	static int counter;  ///to auto increment the id's
	int id;
	double capacity;
	bool broken;
	bool valve;
	double fuel_quantity;
public:

	/**	Constructor for Tank class.
	* @param double gets the capacity of the tank to add
	*@param double gets the fuel_quantity of the tank to add
	*/
	explicit Tank(double capacity = 100, double fuel_quantity = 0);
	/**Copy constructor	 for Tank class.
	* @param double gets the Tank object
	*/
	Tank(const Tank&);
	/**Destructor for Tank class.
	*/
	~Tank();

	/**
	*This function is used to get the id of the tank.
	* @return int gets the Tank id
	*/
	int get_id() const;
	/**
	*This function is used to get the capacity of the tank.
	* @return double gets the Tank capacity
	*/
	double get_capacity() const;
	/**
	*This function is used to set the capacity of the tank.
	* @param double gets the Tank capacity
	*/
	void set_capacity(double);
	/**
	*This function is used to get the tank broken status.
	* @return bool gets the Tank broken
	*/
	bool get_broken() const;
	/**
	*This function is used to set the tank broken status.
	* @param bool gets the Tank broken
	*/
	void set_broken(bool);
	/**
	*This function is used to get the valve status of the tank.
	* @return bool  gets the status of the tank valve
	*/
	bool get_valve() const;
	/**
	*This function is used to set the valve status of the tank.
	* @param bool  sets the status of the tank valve
	*/
	void set_valve(bool);
	/**
	*This function is used to get the fuel quantity of the tank.
	* @return double, gets the amount of fuel from the tank
	*/

	double get_fuel_quantity() const;
	/**
	*This function is used to set the fuel quantity of the tank.
	* @param double, sets the amount of fuel from the tank
	*/
	void set_fuel_quantity(double);
	/**
	*This function is used to add fuel to the tank.
	* @param double gets the fuel quantity
	*/

	void add_fuel(double);
	/**
	*This function is used to take fuel to the tank.
	* @param double gets the fuel quantity
	*/
	void take_fuel(double);
	/**
	*This function is used to get the status of the tank.
	*/
	void get_info() const;

	/** Notifies the tank about engine and reacts to that change
	* @param message is tank's message to the change in the engine class
	*/
	virtual void update(string) override;
};

#endif /* TANK_H_ */