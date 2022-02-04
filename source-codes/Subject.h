/**
* @file Subject.h
* @author Olçan Satýr (152120171109)
* @date 15.01.2022
* @brief Header of Subject class.
*
* This file includes all the declarations functions for Subject interface.
*/

#pragma once
#include "Observer.h";

class Subject
{
public:

    /**
     * Register an observer
     * @param observer: the observer object to be registered
     */
    virtual void registerObserver(Observer* observer) = 0;

    /**
     * Unregister an observer
     * @param observer: the observer object to be unregistered
     */
    virtual void removeObserver(Observer* observer) = 0;

    /**
     * Notify all the registered observers when a change happens
     */
    virtual void notifyObservers() = 0;
};

#pragma once