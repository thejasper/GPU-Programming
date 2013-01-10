// Jasper Desmadryl

#include "Hand.h"

Hand::Hand() : free(true)
{
}

Hand::~Hand()
{
	delete[] preferences;
}

void Hand::setEngaged(int with)
{
	engagedWith = with;
	free = false;
}

void Hand::setPreferences(int* prefs, int n)
{
	preferences = prefs;
	numPrefs = n;

	// everything - 1 so we can use them as indices
	for (int i = 0; i < numPrefs; ++i)
		--preferences[i];
}
