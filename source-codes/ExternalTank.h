/**
* @file ExternalTank.h
* @Author Aylin Unal 152120181117
* @date  19 Ocak 2022
* @brief  ExternalTank.h dosyasi
*
*/
#ifndef EXTERNALTANK_H_
#define EXTERNALTANK_H_

#include "tank.h"

class ExternalTank : public Tank
{
public:
	/**
	* @brief :	Yapici fonksiyon.
	*/
	ExternalTank();
	/**
	* @brief :	Yikici fonksiyon.
	*/
	~ExternalTank();
	/**
	* Bu fonksiyon, iki tankin fuel kapasitesinin toplami 55'den kucuk ise toplama islemini gerceklestirip, iki tankin toplamini baska bir tanka aktarir.
	* @param tank: Toplama isleminin yapilacagi ExternalTank nesnesi
	* @return: ExternalTank nesnesini dondurur.
	*/
	ExternalTank operator+(const ExternalTank& tank)
	{
		ExternalTank extTank;
		if (get_capacity() + tank.get_capacity() <= 55)
		{
			extTank.set_capacity(get_capacity() + tank.get_capacity());
		}
		return extTank;
	}

private:


};




#endif /* EXTERNALTANK_H_ */