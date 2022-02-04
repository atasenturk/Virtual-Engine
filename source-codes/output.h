/**
* @file output.h
* @Author Aylin Unal 152120181117
* @date  19 Ocak 2022
* @brief  output.h dosyasi
*
*/
#pragma once
#include <string>
#include <fstream>
using namespace std;
class Output
{
private:
	ofstream file;
	string fileName;
	static Output* Instance;
public:
	/**
	* @brief :	Yapici fonksiyon.
	*/
	Output() {}
	/**
	* Bu fonksiyon, Instance nesnesini dondurur.
	* @return: Dondurulecek Output nesnesi
	*/
	static Output* Get();
	/**
	* Bu fonksiyon, fileName degiskenine deger atamasý yapar.
	* @param filename: Dosyalama isleminin yapilacagi dosyanin adini tutan degisken.
	*/
	void setFilename(string filename);
	/**
	* Bu fonksiyon, dosyaya verileri yazar.
	* @param str: Dosyaya yazilacak verileri tutan degisken.
	*/
	void writeDatas(string);
	/**
	* Bu fonksiyon, dosyalama isleminin yapilacagi dosyayi acar.
	*/
	void openFile();

};