// Jasper Desmadryl

#include <iostream>
#include <fstream>

#include "LeftHand.h"
#include "RightHand.h"

using namespace std;

int freeLeftHand(LeftHand* lefties, int n, int &L, int& R);
void solveOneCase(LeftHand* lefties, RightHand* righties, int n);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Not enough arguments. Usage: ./testSMPHand [SMP file]" << endl;
        return 1;
    }

    ifstream fin(argv[1], ifstream::in);

    if (!fin)
    {
        cout << "File not found." << endl;
        return 1;
    }

	int numCases;
	fin >> numCases;

	while (numCases--)
	{
        int n;
		fin >> n;

        // read the preferences of the left hands
		LeftHand* lefties = new LeftHand[n];
		for (int i = 0; i < n; ++i)
		{
			int* prefs = new int[n];

			for (int j = 0; j < n; ++j)
				fin >> prefs[j];

			lefties[i].setPreferences(prefs, n);
		}

		// read the preferences of the right hands
		RightHand* righties = new RightHand[n];
		for (int i = 0; i < n; ++i)
		{
			int* prefs = new int[n];

			for (int j = 0; j < n; ++j)
				fin >> prefs[j];

			righties[i].setPreferences(prefs, n);
		}

		// solve the stable marriage problem
		solveOneCase(lefties, righties, n);

		// print the result
		for (int i = 0; i < n; ++i)
			cout << i + 1 << ' ' << lefties[i].getFiancee() + 1 << endl;

		// print an extra line after each case, except the last one
		if (numCases)
			cout << endl;

		// clean up
		delete[] lefties;
		delete[] righties;
	}

	return 0;
}

int freeLeftHand(LeftHand* lefties, int n, int &L, int& R)
{
	// find a free left hand and his current favorite right hand
	for (int i = 0; i < n; ++i)
	{
		if (lefties[i].isFree())
		{
			L = i;
			R = lefties[i].getNextFavoriteRight();

			return 1;
		}
	}

	return 0;
}

void solveOneCase(LeftHand* lefties, RightHand* righties, int n)
{
	int L, R;

	while (freeLeftHand(lefties, n, L, R))
	{
		// mark the right hand as chosen (we can only propose once)
		lefties[L].attemptToProposeFavorite();

		// if right hand is not free we can check if he prefers the new candidate left hand
		// otherwise he'll stay with his current left hand
		if (!righties[R].isFree())
		{
			if (righties[R].prefersNewLeft(L))
			{
				// right hand dumps current partner
				int exPartner = righties[R].getFiancee();
				lefties[exPartner].setFree();
			}
			else
				continue;
		}

		// L and R sittin' in a tree.. :)
		lefties[L].setEngaged(R);
		righties[R].setEngaged(L);
	}
}

