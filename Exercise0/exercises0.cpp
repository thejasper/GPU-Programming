#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

void increaseSalary(double& salary);
void allocateLastRow(char** multi);

int main()
{
    const int arraySize = 8;
    int array[arraySize] = {9, 8, 7, 6, 5};

    // write a for loop to go through and print the elements of the above array
    for (int i = 0; i < arraySize; ++i) {
        cout << array[i] << ' ';
    }
    cout << endl;


    // use the arrayPtr to loop through the array and print the array
    int *arrayPtr = array;
    for (int i = 0; i < arraySize; ++arrayPtr, ++i) {
        cout << *arrayPtr << ' ';
    }
    cout << endl;


    double monthlySalary = 1800.50;
    /* write a method called "increaseSalary" that takes monthlySalary
     * and increases it by 10% (multiplies by 1.1)
     * But make sure you pass monthlySalary by reference, not by value!
     */
    cout << "monthlySalary is " << monthlySalary;
    increaseSalary(monthlySalary);
    cout << " and now monthlySalary is " << monthlySalary << " and it should be " << 1980.55 << endl;


    // write a loop to change every character in myStr to upper case.  You can use toupper(char);
    char myStr[] = "I love the C++ language.";
    for (int i = 0; myStr[i]; ++i) {
        myStr[i] = toupper(myStr[i]);
    }
    cout << "myStr is now: " << myStr << endl;


    /*use the sizeof function that is built into C++ to print out the length of the myStr array.
      Make sure you do not just get the array's size in bytes! */
    int sz = sizeof(myStr) / sizeof(char) - 1; // -1 so the \0 isn't counted
    cout << "The length of myStr is: " << sz << endl;


    /* Create a vector of chars, and copy each element of the char array above into it.
     * Then create an iterator, and use it to go through the vector and count the number of times
     * that the character "E" occurs in the string.
     */
    int countE = 0;
    vector<char> myStrCopy(myStr, myStr + sz);
    for (vector<char>::const_iterator it = myStrCopy.begin(); it != myStrCopy.end(); ++it) {
        if (*it == 'E')
            ++countE;
    }
    cout << countE << " occurences of the letter 'E' in myStr" << endl;


    /* Create an array of integers using dynamic allocation (new).
     * Your array should be of length 10.  Print out the elements (without initializing them),
     * and then delete the memory you allocated.
     */
    int* myInts = new int[10];
    for (int i = 0; i < 10; ++i) {
        cout << myInts[i] << ' ';
    }
    cout << endl;
    delete[] myInts;


    /* Create a 2 dimensional array of characters using dynamic allocation.
     * Initialize the first row of the array to contain your first name, and the second row your last name.
     * Then pass that array to a function that you define that adds another row that contains "is cool."
     * Your initial array can be declared with 3 rows, but the function should allocate the last row.
     */
    char** multi = new char*[3];
    char firstname[] = "Jasper";
    char lastname[] = "Desmadryl";

    multi[0] = firstname;
    multi[1] = lastname;
    allocateLastRow(multi);

    // print and cleanup
    for (int i = 0; i < 3; ++i) {
        cout << multi[i] << endl;
    }
    delete[] multi;


    /* What is the difference between the following 2 declarations? */

    // this is a pointer that points to an integer or array of integers,
    // the address to which it points too can not be changed
    // int* const intPtr1;

    // this is a pointer to a constant int (or constant int array),
    // the address can be changed but the data that it points too not
    // const int* intPtr2;


    return 0;
}

void increaseSalary(double& salary)
{
    salary *= 1.1;
}

void allocateLastRow(char** multi)
{
    char lastLine[] = "is cool.";
    int sz = sizeof(lastLine) / sizeof(char);

    multi[2] = new char[sz];

    for (int i = 0; i < sz; ++i)
        multi[2][i] = lastLine[i];
}

