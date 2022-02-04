/**
* @file input.h
* @author Ahmet Ata Þentürk (152120181120)
* @date 18.01.2022
* @brief Header file of input class.
*
*	This file includes all the declarations of functions for input class.
*/

#ifndef INPUT
#define INPUT

#include <iostream>
#include <vector> 
#include <string.h>
#include <string>
#include <fstream>
#include "TankList.h"
#include "engine.h"
#include <sstream>

using namespace std;
class Input
{
public:
	/** Class function for reading line commands from text file and it calls the classes that is required.
	* @param filename is the filename that entered from terminal.
	*/
	void readInputs(string filename);

	/** If command takes value, that function return true.
	* @param str is the line string. Every line is analyzed whether include value or not.
	*/
	bool isStringNeedValue(string str);

	/** That function tokenize the string with the given delimiter.
	* @param str is the line string.
	* @param delim is the delimiter that tokenizes the string.
	* @param out is the output after tokenizing.
	*/
	void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);

	/** That function removes the spaces in the string that is given.
	* @param s is string that is wanted to removing spaces.
	*/
	string remove_spaces(const string& s);

	/** Returns the value that how many value does the command takes.
	* @param str is the string line.
	* @return the parameter count in the command.
	*/
	int howManyParameterDoesCommandTake(string str);
};
#endif