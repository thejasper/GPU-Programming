#include <string>

#include "car.h"

class RaceCar : public Car
{
private:
    std::string engineType;

public:
    RaceCar(int numWheels, std::string color, std::string engineType);

    ~RaceCar();

    std::string getEngineType() const;

    void setEngineType(std::string engineType);
};
