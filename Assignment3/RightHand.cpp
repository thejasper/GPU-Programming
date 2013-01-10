// Jasper Desmadryl

#include "RightHand.h"

bool RightHand::prefersNewLeft(int newLeft) const
{
	// whatever comes first as preference determines the answer
	for (int i = 0; i < numPrefs; ++i)
	{
		if (preferences[i] == newLeft)
			return true;
		if (preferences[i] == engagedWith)
			return false;
	}

	// it's impossible to reach this line because
	// the preference will always be found
	return false;
}
