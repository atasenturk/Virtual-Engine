/**
* @file output.cpp
* @Author Aylin Unal 152120181117
* @date  19 Ocak 2022
* @brief  output.cpp dosyasi
*
*  Bu sinif, dosyalama islemini gerceklestirir.
*/
#include "output.h"
#include <iostream>
#include <fstream>
Output* Output::Instance = NULL;

Output* Output::Get()
{
	if (Instance == NULL) {
		Instance = new Output();
	}
	return Instance;
}

void Output::writeDatas(string str) {
	file << str << endl;
}

void Output::openFile()
{
	file.open(fileName, ios::out);
	if (!file.is_open())
	{
		cout << "Error opening output file <" << fileName << ">" << endl;
	}
	else cout << "Output file is successfully opened!" << endl;
}

void Output::setFilename(string filename)
{
	this->fileName = filename;
}