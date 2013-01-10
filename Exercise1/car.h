#pragma once

#include <string>

class Car
{
private:
    int numWheels;
    std::string color;

public:
    Car(int numWheels, std::string color);

    int getNumWheels() const;

    std::string getColor() const;

    void setNumWheels(int n);

    void setColor(std::string c);

    static std::string getClassDescription();
};
