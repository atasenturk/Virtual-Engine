/**
* @file engine.cpp
* @author Ahmet Ata Þentürk (152120181120)
* @date 17.01.2022
* @brief Source file of engine class.
*
*	This file has method implementations for the engine class.
*/

#include "engine.h"
#include "ExternalTank.h"
#include "TankList.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "output.h"

Engine Engine::e_Instance;

Engine::Engine(bool status) :fuel_per_second(5.5),heat(0) {
	internalTank = new InternalTank;
	this->status = status;
	totalConsumedFuel = 0.0;
	health = 100;
}

void Engine::list_connected_tanks() const {
	if (connectedTanks.size() < 1) {				// if there is no tank print a message
		std::cout << "There isn't any connected tank!" << std::endl;
		Output::Get()->writeDatas("There isn't any connected tank!");
	}
	else {
		for (int i = 0; i < connectedTanks.size(); i++) {  // if there is 1 or more connected tank print info about tank(s).
			connectedTanks[i]->get_info();
		}
	}
}

double Engine::get_fuel_per_second() const {
	return fuel_per_second;
}

bool Engine::get_status() const {
	return status;
}

void Engine::start_engine() {
	if (connectedTanks.size() > 0 && health > 20) {
		status = true;
		std::cout << "Engine started!" << std::endl;
		Output::Get()->writeDatas("Engine started!");
		absorb_fuel(internalTank->get_capacity()); // when engine started fills internal tank
	}
	else {
		if (connectedTanks.size() == 0)
		{
			std::cout << "Engine cannot start! There should be at least 1 connected tank to the engine" << std::endl;
			Output::Get()->writeDatas("Engine cannot start! There should be at least 1 connected tank to the engine");
		}
		else if (health <= 20) {
			std::cout << "Engine cannot start! Engine health is equal or less than 20 percent. Please repair engine or change block of the engine!" << std::endl;
			Output::Get()->writeDatas("Engine cannot start! Engine health is equal or less than 20 percent. Please repair engine or change block of the engine!");
		}
	}
}

//absorb fuel method selects a random connected tank and absorbs fuel to engine's internal tank
void Engine::absorb_fuel(double amount) {
	srand(time(NULL));
	int connectedTankCount = connectedTanks.size(); // take connected tanks number
	int randomTank = rand() % connectedTankCount;	// create a random index between 0 and connected tanks number
	int count = 0; // to prevent an endless loop
	while (true) {
		if (connectedTanks[randomTank]->get_fuel_quantity() >= amount) {  // if random connected tank's fuel is more than the amount
			connectedTanks[randomTank]->take_fuel(amount);								// take fuel from the connected tank
			internalTank->add_fuel(amount);												// add fuel to the internal tank
			break;
		}
		else if (connectedTanks[randomTank]->get_fuel_quantity() < amount) { // if random connected tank has not enough fuel in it
			int newAmount = connectedTanks[randomTank]->get_fuel_quantity();  // new amount is all the fuel inside the random tank
			if (internalTank->get_capacity() - internalTank->get_fuel_quantity() >= newAmount) { // if internal tank has enough capacity
				connectedTanks[randomTank]->take_fuel(newAmount);		// take all the fuel inside the connected tank
				internalTank->add_fuel(newAmount);						// add to the internal tank
			}
		}

		randomTank = rand() % connectedTankCount;
		count++;
		if (count > connectedTankCount) { // if all of the connected tanks checked and none of them have enough fuel then exit the loop
			break;
		}
	}
}

void Engine::give_back_fuel() {
	if (internalTank->get_fuel_quantity() > 0) {				// if internal tank has fuel in it
		double min = connectedTanks[0]->get_fuel_quantity(); //represents the minimum fuel quantity
		int minIndex = 0;									// represents index of the tank which has minimum fuel in it
		for (int i = 0; i < connectedTanks.size(); i++) {
			if (connectedTanks[i]->get_fuel_quantity() < min) {  // if there is another tank which has less fuel
				min = connectedTanks[i]->get_fuel_quantity();   // update the minimum value
				minIndex = i;								   // set the current tank's index to minIndex variable
			}
		}
		connectedTanks[minIndex]->add_fuel(internalTank->get_fuel_quantity());  //give internal tank's all fuel to the connected tank with minimum fuel
		std::cout << internalTank->get_fuel_quantity() << " gave back to tank: " << connectedTanks[minIndex]->get_id() << std::endl;
		ostringstream os;
		os << internalTank->get_fuel_quantity() << " gave back to tank: " << connectedTanks[minIndex]->get_id();
		Output::Get()->writeDatas(os.str());
		internalTank->set_fuel_quantity(0);									  //set internal tank's fuel to 0 since its empty
	}
}

// wait method burns fuel from the internal tank
void Engine::wait(int seconds) {
	double fuelToConsume = seconds * fuel_per_second;
	if (status) {    //if the engine is running
		if (fuelToConsume > internalTank->get_fuel_quantity()) { // if internal tank doesnt have enough fuel in it
			absorb_fuel(internalTank->get_capacity() - internalTank->get_fuel_quantity()); // call absorb fuel method to fill the internal tank
		}

		internalTank->take_fuel(fuelToConsume);	// decrease the fuel quantity of the internal tank
		totalConsumedFuel += fuelToConsume;		// add consumed value to total consumed attribute


		if (internalTank->get_fuel_quantity() < 20)   // after consuming fuel from internal tank if the fuel is less than 20
			absorb_fuel(internalTank->get_capacity() - internalTank->get_fuel_quantity()); //call absorb fuel method to fill the internal tank
		for (int i = 0; i < seconds; i++)
		{
			if (heat > 90) heat--;
			else heat++;
			if (heat > 130.0) {
				if (health <= 20) {
					stop_engine();
				}
				else health -= (health / 100);
			}
		}
		
	}
	else {
		std::cout << "engine is not running!" << std::endl;
		Output::Get()->writeDatas("Engine is not running!");
		for (int i = 0; i < seconds; i++)
		{
			if (heat > 20)
			{
				heat--;
			}
		}
		
	}

	
	
	std::cout << "Heat of the engine : " << heat << " and the health of the engine : " << health << std::endl;
	ostringstream os;
	os << "Heat of the engine : " << heat << " and the health of the engine : " << health << std::endl;
	Output::Get()->writeDatas(os.str());
	
}

void Engine::full_throttle(int seconds)
{
	fuel_per_second *= 5;
	double fuelToConsume = seconds * fuel_per_second;
	if (status) {    //if the engine is running
		if (fuelToConsume > internalTank->get_fuel_quantity()) { // if internal tank doesnt have enough fuel in it
			absorb_fuel(internalTank->get_capacity() - internalTank->get_fuel_quantity()); // call absorb fuel method to fill the internal tank
		}

		internalTank->take_fuel(fuelToConsume);	// decrease the fuel quantity of the internal tank
		totalConsumedFuel += fuelToConsume;		// add consumed value to total consumed attribute


		if (internalTank->get_fuel_quantity() < 20)   // after consuming fuel from internal tank if the fuel is less than 20
			absorb_fuel(internalTank->get_capacity() - internalTank->get_fuel_quantity()); //call absorb fuel method to fill the internal tank
		for (int i = 0; i < seconds; i++)
		{
			heat += 5;
			if (heat < 90) health -= ((health * 1) / 100);
		}
	}
	else {
		std::cout << "engine is not running!" << std::endl;
		Output::Get()->writeDatas("engine is not running!");
		for (int i = 0; i < seconds; i++) {
			if (heat > 20) {
				heat--;
			}
		}
	}
	fuel_per_second /= 5;
	std::cout << "Heat of the engine : " << heat << " and the health of the engine : " << health;
	ostringstream os;
	os << "Heat of the engine : " << heat << " and the health of the engine : " << health;
	Output::Get()->writeDatas(os.str());
}

void Engine::repair_engine()
{
	if (!status) {
		if (health > 1.00) {
			health = 100;
		}
	}
}

void Engine::change_engine_block()
{
	if (!status) {
		totalConsumedFuel = 0.0;
		health = 100;
		heat = 0;
	}
}

void Engine::print_total_consumed_fuel_quantity() const {
	std::cout << "Total consumed fuel: " << totalConsumedFuel << std::endl;
	ostringstream os;
	os << "Total consumed fuel: " << totalConsumedFuel;
	Output::Get()->writeDatas(os.str());
}

void Engine::stop_engine() {
	setState("Engine: Simulation stopped");
	notifyObservers();
	give_back_fuel();
	status = false;
}

void Engine::stop_simulation() {
	Output::Get()->writeDatas("Engine: Simulation stopped");
	setState("Simulation stopped");
	exit(0);
}


void Engine::registerObserver(Observer* observer)
{
	observers.push_back(observer);
}

void Engine::removeObserver(Observer* observer)
{
	// find the observer
	auto iterator = std::find(observers.begin(), observers.end(), observer);

	if (iterator != observers.end()) { // observer found
		observers.erase(iterator); // remove the observer
	}
}

void Engine::notifyObservers()
{
	std::vector<Observer*>::iterator iterator = observers.begin();

	while (iterator != observers.end()) {
		cout << message << endl;
		(*iterator)->update(message);
		++iterator;
	}
}

void Engine::setState(string message)
{
	this->message = message;
	notifyObservers();
}



