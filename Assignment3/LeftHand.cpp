// Jasper Desmadryl

#include "LeftHand.h"

LeftHand::LeftHand() : nextToProposeToo(0)
{
}

int LeftHand::getNextFavoriteRight() const
{
	if (nextToProposeToo == numPrefs) // nobody left to propose too
		return Hand::npos;
	else
		return preferences[nextToProposeToo];
}

void LeftHand::attemptToProposeFavorite()
{
	// left hand can only propose once to each right hand
	// so at an attempt we move to the next favorite right hand
	++nextToProposeToo;
}
