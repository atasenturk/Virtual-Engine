/**
* @file input.cpp
* @author Ahmet Ata Þentürk (152120181120)
* @date 18.01.2022
* @brief Source file of input class.
*
*	This file has method implementations for the input class.
*/

#include "input.h"
#include "Observer.h"

void Input::readInputs(string filename)
{
    TankList t;
    int pos;
    string delimiter = ";";
    string line;
    vector<string> lines;
    ifstream inputFile;
    inputFile.open(filename);
    int i;
    
    if (!inputFile)
    {
        cout << "Error opening the file" << endl;
    }
    while (getline(inputFile, line)) { /// Reading file line by line.
        if (line.find(delimiter) != -1) { /// ";" Read line until delimiter.
            pos = line.find(delimiter);
            lines.push_back(line.substr(0, pos));
            line = line.substr(pos + delimiter.length());
        }
    }
    for (int i = 0; i < lines.size(); i++) { /// Pushing the elements into the array.
        if (isspace(lines[i].at(0)))
            lines[i] = lines[i].substr(1);
        lines[i] += ";";
    }


    Engine& e = Engine::Get();
    double doubleValue;
    string temp;
    int sizeoftemp;
    string cmnd;
    for (i = 0; i < lines.size(); i++)
    {
        temp = lines[i];
        vector<string> out;
        vector<string> output;

        /// Each command takes 1 second. So, for every loop, wait function is called. (If wait function does not parameter, second will be "1".)
        e.wait();

        if (isStringNeedValue(temp) == true)   /// Is string need value? If it is, return true.
        {
            /// How many parameter does command take?
            int parameterCount = howManyParameterDoesCommandTake(temp);
            double parameterArray[100];

            /// If string needs value more than one.
            /// There is only one command that takes two parameter. But in the coming weeks, there might be more than one.
            /// Also in the coming weeks, there might be functions that takes more than two or much more.
            if (parameterCount > 1)
            {
                /// Tokenizing the string with ";".
                tokenize(temp, ';', output);
                temp = output[0];
                /// Tokenizing the string with " ".
                tokenize(temp, ' ', out);
                cmnd = out[0];

                pos = temp.find(" "); /// Substr the string after blank (" ").
                temp = temp.substr(pos + 1);

                /// We use string stream to split every value in the command.
                istringstream iss(temp);
                string allValues;
                int j = 0;

                /// Splitting string to the double values.
                while (getline(iss, allValues, ' '))
                {
                    doubleValue = atof(allValues.c_str());
                    parameterArray[j] = doubleValue;
                    /// All values are in parameterArray
                    j++;
                }

                /// Comparing the command names and calling the functions.
                if (cmnd == "fill_tank")
                {
                    t.fill_tank(parameterArray[0], parameterArray[1]);
                }

                if (cmnd == "sum_operator")
                {
                    t.sum_operator(parameterArray[0], parameterArray[1], parameterArray[2]);
                }

            }

            /// If string needs only one value.
            else
            {
                /// Take the command only.
                tokenize(temp, ' ', out);
                cmnd = out[0];

                /// Removing the blank(it is the last char) from the command string.
                cmnd = remove_spaces(cmnd);

                ///  Finding only value in the string line.
                pos = temp.find(" "); /// Substr the string after blank (" ").
                string value = temp.substr(pos + 1);
                tokenize(value, ';', output);  /// Tokenizing the substred string with ";".
                value = output[0];

                /// Converting string value to the double value.
                doubleValue = atof(value.c_str());

                /// Comparing the command names and calling the functions.
                if (cmnd == "absorb_fuel")
                {
                    e.absorb_fuel(doubleValue);
                }
                else if (cmnd == "add_fuel_tank")
                {
                    t.add_fuel_tank(doubleValue);
                }
                else if (cmnd == "remove_fuel_tank")
                {
                    t.remove_fuel_tank(doubleValue);
                }
                else if (cmnd == "connect_fuel_tank_to_engine")
                {
                    t.connect_fuel_tank_to_engine(doubleValue);
                }
                else if (cmnd == "disconnect_fuel_tank_from_engine")
                {
                    t.disconnect_fuel_tank_from_engine(doubleValue);
                }
                else if (cmnd == "open_valve")
                {
                    t.open_valve(doubleValue);
                }
                else if (cmnd == "close_valve")
                {
                    t.close_valve(doubleValue);
                }
                else if (cmnd == "break_fuel_tank")
                {
                    t.break_fuel_tank(doubleValue);
                }
                else if (cmnd == "repair_fuel_tank")
                {
                    t.repair_fuel_tank(doubleValue);
                }
                else if (cmnd == "add_fuel_tank")
                {
                    t.add_fuel_tank(doubleValue);
                }
                else if (cmnd == "wait")
                {
                    e.wait(doubleValue);
                }
                else if (cmnd == "print_tank_info")
                {
                    t.print_tank_info(doubleValue);
                }
                else if (cmnd == "full_throttle")
                {
                    e.full_throttle(doubleValue);
                }
            }
    }

        /// If string does not take parameter.
        else
        {
            tokenize(temp, ';', out);
            cmnd = out[0];
            if (cmnd == "start_engine")
            {
                e.start_engine();
            }
            else if (cmnd == "stop_engine")
            {
                e.stop_engine();
            }
            else if (cmnd == "list_fuel_tanks")
            {
                t.list_fuel_tanks();
            }
            else if (cmnd == "stop_simulation")
            {
                t.registerTanks();
                e.stop_simulation();
            }
            else if (cmnd == "print_fuel_tank_count")
            {
                t.print_fuel_tank_count();
            }
            else if (cmnd == "list_connected_tanks")
            {
                e.list_connected_tanks();
            }
            else if (cmnd == "print_total_fuel_quantity")
            {
                t.print_total_fuel_quantity();
            }
            else if (cmnd == "print_total_consumed_fuel_quantity")
            {
                e.print_total_consumed_fuel_quantity();
            }
            else if (cmnd == "give_back_fuel")
            {
                e.give_back_fuel();
            }
            else if (cmnd == "change_engine_block")
            {
                e.change_engine_block();
            }
            else if (cmnd == "repair_engine")
            {
                e.repair_engine();
            }

        }
    }
   
    inputFile.close(); /// close input file
}


string Input::remove_spaces(const string& s)
{
    /// Removing spaces and returning string without spaces.
    int last = s.size() - 1;
    while (last >= 0 && s[last] == ' ') /// Last index will be reduced by the number of blank spaces.
        --last;
    return s.substr(0, last + 1);
}


void Input::tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
    /// Tokenizing the string.
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}


bool Input::isStringNeedValue(string str)
{
    /// If string need value (there is a number in the line string), returns true.
    for (int i = 0; i < str.size(); i++)
    {
        /// Numbers are located between 48 and 57 in ASCII tables.
        if (48 <= (int)str[i] && (int)str[i] <= 57)
        {
            return true;
        }
    }
    return false;
}

int Input::howManyParameterDoesCommandTake(string str)
{
    int count = 0;
    istringstream iss(str);
    vector<string> result;

    /// Splitting string with blanks and count how many char arrays in the string.
    for (str; iss >> str; )
    {
        result.push_back(str);
        count++;
    }
    /// Command name is also counted. So, function return count-1. It means command name is not counted.
    return count - 1;
}
