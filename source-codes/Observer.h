/**
* @file Observer.h
* @author Olçan Satýr (152120171109)
* @date 15.01.2022
* @brief Header of Observer class.
*
* This file includes all the declarations functions for Observer interface.
*/

#pragma once
#include <string>
using namespace std;

class Observer
{
public:

    /**
     * Update the state of this observer
     * @param message is message from the subject
     */
    virtual void update(string message) = 0;  // This function is a virtual void function.
};
