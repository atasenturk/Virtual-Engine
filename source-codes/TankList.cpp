/**
* @file TankList.cpp
* @author Ergün Altýndað (152120181083)
* @date 19.01.2022
* @brief Source file of TankList class.
*
*	This file includes all the implementations declared in the TankList header file.
*/
#include "TankList.h"
#include "engine.h"
#include <iostream>
#include "output.h"
Engine& e = Engine::Get();

TankList::TankList() {

}

/// updates the fuel quantity values from engine's connected tank list
void TankList::update_tanks() {
	for (int i = 0; i < tanks.size(); i++) {
		for (int j = 0; j < e.connectedTanks.size(); j++) {
			if (tanks[i].get_id() == e.connectedTanks[j]->get_id()) {
				tanks[i].set_fuel_quantity(e.connectedTanks[j]->get_fuel_quantity());
			}
		}
	}
}

void TankList::registerTanks()
{
	for (int i = 0; i < tanks.size(); i++)
	{
		e.registerObserver(&tanks[i]);
	}
}

void TankList::add_fuel_tank(double capacity) {
	Tank t(capacity);
	tanks.push_back(t);
}

void TankList::list_fuel_tanks() {
	if (tanks.size() < 1) {
		std::cout << "There isn't any tank!" << std::endl;
	}
	else {
		update_tanks(); // updating the tanks before printing info
		for (int i = 0; i < tanks.size(); i++) {
			tanks[i].get_info();
		}
	}
}

int TankList::find_tank(int id) {       // finds the tank in the tanks vector by id and returns its index
	for (int i = 0; i < tanks.size(); i++) { // iterate through all the tanks
		if (tanks[i].get_id() == id) {   // if the id of the tank equals given id
			return i;					// return index
		}
	}
	return -1;							// return -1 if the tank doesn't exist
}

void TankList::remove_fuel_tank(int id) {
	int index = find_tank(id);
	if (index != -1) {
		tanks.erase(tanks.begin() + index);                      // delete from the tanks vector
		std::cout << "Tank id: " << id << " removed" << std::endl;
		//this for loop deletes the tank from the connected tanks vector
		for (int i = 0; i < e.connectedTanks.size(); i++) {
			if (e.connectedTanks[i]->get_id() == id) {
				e.connectedTanks.erase(e.connectedTanks.begin() + i);
			}
		}
	}
	else
		std::cout << "There isn't any tank with id " << id << std::endl;
}

void TankList::break_fuel_tank(int id) {
	int index = find_tank(id);
	if (index != -1)
		tanks[index].set_broken(true);
	else
		std::cout << "There isn't any tank with id " << id << std::endl;
}

void TankList::repair_fuel_tank(int id) {
	int index = find_tank(id);
	if (index != -1)
		tanks[index].set_broken(false);
	else
		std::cout << "There isn't any tank with id " << id << std::endl;
}

void TankList::open_valve(int id) {
	int index = find_tank(id);
	if (index != -1) {
		if (!tanks[index].get_valve()) {
			tanks[index].set_valve(true);
			std::cout << "Tank " << id << " valve's opened" << std::endl;
		}
		else
			std::cout << "Tank " << id << " valve's is already opened" << std::endl;
	}
	else
		std::cout << "There isn't any tank with id " << id << std::endl;
}

void TankList::close_valve(int id) {
	int index = find_tank(id);
	if (index != -1) {
		if (tanks[index].get_valve()) {
			tanks[index].set_valve(false);
			std::cout << "Tank " << id << " valve's closed" << std::endl;
		}
		else
			std::cout << "Tank " << id << " valve's is already closed!" << std::endl;
	}
	else
		std::cout << "There isn't any tank with id " << id << std::endl;
}

void TankList::connect_fuel_tank_to_engine(int id) {
	int index = find_tank(id);
	bool isAlreadyConnected = false;

	if (index != -1) {
		for (int i = 0; i < e.connectedTanks.size(); i++) {			// iterates through the connected tanks and check whether the tank with given id is already connected
			if (e.connectedTanks[i]->get_id() == tanks[index].get_id())
				isAlreadyConnected = true;
		}

		if (tanks[index].get_broken()) {
			std::cout << "The tank " << id << " is broken cannot connect to engine!" << std::endl; // if the tank is broken cannot connect to the engine
		}
		else if (!tanks[index].get_valve()) {
			std::cout << "The tank " << id << " valve is closed cannot connect to engine!" << std::endl; // if the valve is closed cannot connect the engine
		}
		else if (isAlreadyConnected) {
			std::cout << "The tank " << id << " is already connected to engine!" << std::endl;
		}
		else {
			e.connectedTanks.push_back(&tanks[index]);
			std::cout << "Tank id: " << tanks[index].get_id() << " connected to the engine!" << std::endl;	// add to the connected tanks vector
		}
	}
	else
		std::cout << "There isn't any tank with id " << id << std::endl;
}

void TankList::disconnect_fuel_tank_from_engine(int id) {
	int index = find_tank(id);
	bool isConnected = false;

	if (index != -1) {
		for (int i = 0; i < e.connectedTanks.size(); i++) {			// iterates through the connected tanks and check whether the tank with given id is connected
			if (e.connectedTanks[i]->get_id() == tanks[index].get_id())
				isConnected = true;
		}

		if (isConnected) {
			e.connectedTanks.erase(e.connectedTanks.begin() + index);		// deletes the tank from the connected tanks vector
			std::cout << "Tank id: " << e.connectedTanks[index]->get_id() << " disconnected from engine!" << std::endl;
		}
		else
			std::cout << "Tank id: " << id << " is not connected to engine!" << std::endl;
	}
	else
		std::cout << "There isn't any tank with id " << id << std::endl;
}

void TankList::print_fuel_tank_count() const {  // could return the count or print directly
	std::cout << "There are " << tanks.size() << " tanks." << std::endl;
}

void TankList::print_total_fuel_quantity() {
	update_tanks();
	double total = 0.0;
	for (int i = 0; i < tanks.size(); i++) {
		total += tanks[i].get_fuel_quantity();
	}

	std::string output;
	std::ostringstream os;
	os << "Total fuel quantity :" << total;
	output = os.str();

}

void TankList::print_tank_info(int id) {
	update_tanks();
	int index = find_tank(id);
	if (index != -1) {
		tanks[index].get_info();
	}
	else
		std::cout << "There isn't any tank with id " << id << std::endl;
}

void TankList::fill_tank(int id, double quantity) {

	for (int i = 0; i < tanks.size(); i++) {
		if (tanks[i].get_id() == id) {
			if (tanks[i].get_capacity() >= quantity + tanks[i].get_fuel_quantity()) {
				tanks[i].add_fuel(quantity);
				std::cout << "Tank " << id << " is filled: " << quantity << std::endl;
			}
			else
				std::cout << "Not enough capacity in the tank " << id << std::endl;
		}
	}

	for (int i = 0; i < e.connectedTanks.size(); i++) { // to find the tank in the connected tanks.
		if (e.connectedTanks[i]->get_id() == id && e.connectedTanks[i]->get_capacity() >= quantity + e.connectedTanks[i]->get_fuel_quantity()) {
			e.connectedTanks[i]->add_fuel(quantity);
		}
	}
}

void TankList::sum_operator(int tank1, int tank2, int tank3)
{
	if (tanks[tank1].get_valve() == true && tanks[tank2].get_valve() == true && tanks[tank3].get_valve() == true) {
		tanks[tank1].set_fuel_quantity(tanks[tank2].get_fuel_quantity() + tanks[tank3].get_fuel_quantity());
		remove_fuel_tank(tank2);
		remove_fuel_tank(tank3);
		cout << "Fuels of " << tank2 << " and " << tank3 << " has transferred to " << tank1 << ". Also " << tank2 << " and " << tank3 << " has deleted" << endl;
	}
	else {
		cout << "The tanks you are trying to sum, valves must be open" << endl;
	}
}

