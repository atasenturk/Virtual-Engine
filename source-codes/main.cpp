/**
* @file main.cpp
* @author Olçan Satýr (152120171109)
* @date 15.01.2022
* @brief Main class.
*
* This file is the main file containing all the classes.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include "TankList.h"
#include "engine.h"
#include "input.h"
#include "output.h"
#include "ExternalTank.h"
#include "InternalTank.h"
using namespace std;
void Test(string inputFile, string outputFile);

int main(int argc, char* argv[]) /// files taking from command line
{
	if (argc > 1)
	{
		string inputFilename = argv[1];
		string outputFilename = argv[2];
		Test(inputFilename,outputFilename);
	}
	else
	{
		cout << "An input and output file name must be entered.";
	}
}


void Test(string inputFile, string outputFile)
{
	Input inputs;
	Output::Get()->setFilename(outputFile);
	Output::Get()->openFile();
	inputs.readInputs(inputFile);
}


//int main()
//{
//	string inputFilename = "input3.txt";
//	string outputFilename = "output.txt";
//
//
//	Test(inputFilename, outputFilename);
//
//}