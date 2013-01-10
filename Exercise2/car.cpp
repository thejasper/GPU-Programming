#include <iostream>

#include "car.h"

using namespace std;

Car::Car(int numWheels, string color) :
    numWheels(numWheels), color(color)
{
    cout << "Car constructor is called" << endl;
}

Car::~Car()
{
    cout << "Car destructor is called" << endl;
}

int Car::getNumWheels() const
{
    return numWheels;
}

string Car::getColor() const
{
    return color;
}

void Car::setNumWheels(int n)
{
    numWheels = n;
}

void Car::setColor(std::string c)
{
    color = c;
}

string Car::getClassDescription() 
{
    return "Class to represent a car..";
}
