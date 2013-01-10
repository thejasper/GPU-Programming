#include <iostream>
#include <vector>

#include "car.h"
#include "racecar.h"

using namespace std;

int main()
{
    //The following 2 questions are from exercises1.  We extend upon them in these exercises.
    /*Write a class definition for a car, with a few member variables, and some
      getter and setter methods for those member variables. Then, here in main, create
      an instance of that class, and call its methods.*/
    /*Think of a possible class that could be derived from your car class.
      What would its member variables be? */
    // See Exercise 1
    /* EXERCISES 2 */
    /*Write a class that is derived from your Car class.  Put a print statement in both the
      Car and the derived class' constructors and destructors.  Then create an instance of
      the derived class and see the order that constructors get called. */
    {
        RaceCar raceCar(4, "Blue", "8 cilinder motor");
        /*What is the size in bytes of your derived class? */
        cout << endl << "Size of racecar is " << sizeof(raceCar) << " bytes" << endl << endl;
    }

    {
        Car car(4, "Red");
        cout << endl << "Size of a normal car is " << sizeof(car) << " bytes" << endl;
    }
    return 0;
}

