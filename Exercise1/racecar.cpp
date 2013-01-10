#include "racecar.h"

using namespace std;

RaceCar::RaceCar(int numWheels, string color, string engineType)
    :Car(numWheels, color), engineType(engineType)
{
}

string RaceCar::getEngineType() const
{
    return engineType;
}

void RaceCar::setEngineType(string engineType)
{
    this->engineType = engineType;
}

