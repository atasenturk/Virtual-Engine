/**
* @file tank.cpp
* @author Ergün Altýndað (152120181083)
* @date 19.01.2022
* @brief Source file of tank class.
*
*	This file includes all the implementations declared in the tank header file.
*/#include "tank.h"
#include <iostream>

int Tank::counter = 0;

Tank::Tank(double capacity, double fuel_quantity) : id(counter++) {
	this->capacity = capacity;
	this->fuel_quantity = fuel_quantity;
	broken = false;  /// new tank is not broken by default
	valve = false;	 /// new tanks valve is closed by default
}

Tank::Tank(const Tank& tank) {
	id = tank.id;
	capacity = tank.capacity;
	fuel_quantity = tank.fuel_quantity;
	broken = tank.broken;
	valve = tank.valve;
}

Tank::~Tank() {

}

int Tank::get_id() const {
	return id;
}

double Tank::get_capacity() const {
	return capacity;
}

void Tank::set_capacity(double capacity) {
	this->capacity = capacity;
}

bool Tank::get_broken() const {
	return broken;
}

void Tank::set_broken(bool value) {
	broken = value;
}

bool Tank::get_valve() const {
	return valve;
}

void Tank::set_valve(bool isOpen) {
	valve = isOpen;
}

double Tank::get_fuel_quantity() const {
	return fuel_quantity;
}

void Tank::set_fuel_quantity(double quantity) {
	if (quantity <= capacity) {
		fuel_quantity = quantity;
	}
	else {
		fuel_quantity = capacity;
	}
}

void Tank::add_fuel(double amount) {
	if (amount + fuel_quantity <= capacity) {
		fuel_quantity += amount;
	}
	else {
		if (id == 0)
		{
			std::cout << "Internal tank doesnt have enough capacity!" << std::endl;
		}
		else std::cout << "Tank " << id << " doesnt have enough capacity!" << std::endl;
	}
}

void Tank::take_fuel(double amount) {
	if (amount <= fuel_quantity) {
		fuel_quantity -= amount;
	}
	else {
		if (id == 0) std::cout << "Internal tank doesnt have enough fuel!" << std::endl;
		else std::cout << "Tank " << id << " doesnt have enough fuel!" << std::endl;
	}
}

void Tank::get_info() const {
	std::cout << "Tank id: " << id << " capacity: " << capacity << " fuel quantity: " << fuel_quantity << " broken: " << broken << " valve: " << valve << std::endl;
}


void Tank::update(string message)
{
	ostringstream os;
	os << "Tank " << id - 1 << ": " << message << "\nValve " << id - 1 << ": " << message;
	Output::Get()->writeDatas(os.str());
}



