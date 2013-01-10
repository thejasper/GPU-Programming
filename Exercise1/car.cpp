#include "car.h"

using namespace std;

Car::Car(int numWheels, string color) :
    numWheels(numWheels), color(color)
{
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
