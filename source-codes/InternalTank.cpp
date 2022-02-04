/**
* @file InternalTank.cpp
* @Author Aylin Unal 152120181117
* @date  19 Ocak 2022
* @brief  InternalTank.cpp dosyasi
*
*  Tank sinifindan miras alýnmýs ic tank sinifi.
*/
#include <iostream>
#include "InternalTank.h"

InternalTank::InternalTank()
{
	capacity = 55.0;
	this->fuel_quantity = fuel_quantity;
	broken = false;  /*!< Yeni eklenen tank baslangicta broken degil */
	valve = false;	  /*!< Yeni eklenen tank nesnesinin vanasi baslangicta kapali */
	counter++;
}

InternalTank::~InternalTank()
{
}