// Jasper Desmadryl

#include "Hand.h"

class LeftHand : public Hand
{
private:
	int nextToProposeToo;

public:
	LeftHand();

	int getNextFavoriteRight() const;
	void attemptToProposeFavorite();
};
