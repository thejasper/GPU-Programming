#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#define HARD_CODED_PATH

// Jasper Desmadryl

/* Why is the array passed to max_frequency const?
 * The function max_frequency doesn't need to modify the array to calculate the
 * most frequent character in it. Just like in object oriented programming it's
 * good practice to restrict access. It's also some kind of implicit documentation.
 *
 * Why is the array passed to rotate not const?
 * The return type of rotate is void so the only way to give back the result to the
 * caller is by modifying the argument. That wouldn't be possible if it's const.
 *
 * Why do we not necessarily have to pass the array's length to the 2 functions?
 * After the last character in the array there's a 0 character. You can process each
 * character one at a time and stop when you hit the end ('\0'). Passing the length would
 * require a little bit more memory.
 *
 * What is one thing that is different between strings and char arrays?
 * A string is an stl container that wraps a char array and provides a lot of
 * functionality so it's easier to use. A char array is just some sequence of characters
 * in a continuous block of memory, nothing more.
 */

using namespace std;

/* This function takes a character array, and finds the alphabetic character
 * that occurs the most frequently (ignoring case) and returns it
 */
char max_frequency(const char str[]);

/* This function takes a character array and a rotation distance,
 * and changes each alphabetical character in the array by the rotation distance
 */
void rotate(char str[], int rot_dist);

int main(int argc, char* argv[])
{
#ifdef HARD_CODED_PATH
	argv[1] = (char*)"C:\\Users\\Jasper\\Dropbox\\School\\Masterjaar\\Eerste semester\\GPU programmering\\Assignment0\\Neruda.in"; // The path to the encrypted file
#else
    if (argc < 2)
    {
        cout << "Not enough arguments. Usage: ./decipherA1 [encrypted file]" << endl;
        return 1;
    }
#endif

    ifstream input(argv[1], ios::in);

    if (!input)
    {
        cout << "File not found." << endl;
        return 1;
    }

    // Read the contents of the file in one big string
    string line, text;
    while (getline(input, line))
        text += line + '\n';

    // Convert the text to a char array to match the given function prototypes
    char* cipher = (char*)text.c_str();

    // We know the text is encrypted by shifting every letter a constant number of places
    // The shift is calculated assuming the letter e is the most frequent one in the text
    int shift = max_frequency(cipher) - 'e';

    // Shift every alphabetic character in cipher and print the result
    rotate(cipher, shift);
    cout << cipher;

    return 0;
}

char max_frequency(const char str[])
{
    int freq[26] = {};

    for (int i = 0; str[i]; ++i)
    {
        if (!isalpha(str[i]))
            continue;

        int normalized = tolower(str[i]) - 'a';
        ++freq[normalized];
    }

    // Store the index i where freq[i] has the highest count
    int index_max = max_element(freq, freq + 26) - freq;

    return index_max + 'a';
}

void rotate(char str[], int rot_dist)
{
    for (int i = 0; str[i]; ++i)
    {
        if (!isalpha(str[i]))
            continue;

        // Normalize character
        char offset = isupper(str[i]) ? 'A' : 'a';
        char normalized = str[i] - offset;

        // Shift the character and make sure it's in [0, 26[
        char decrypted = (normalized - rot_dist + 26) % 26;

        // Store the result as a alfabethical character
        str[i] = decrypted + offset;
    }
}

