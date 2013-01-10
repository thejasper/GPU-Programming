// Jasper Desmadryl

#pragma once

class Hand
{
private:
	// all references to other hands can be done by index, no copying required
    // derived classes seem to be affected by these definitions
	Hand(const Hand& hand);
	Hand operator=(const Hand& hand);

protected:
	bool free;
	int engagedWith;
	int numPrefs;
	int* preferences;

public:
	static const int npos = -1; // represents the index of a non valid hand

	Hand();

	~Hand();

	bool isFree() const { return free; }
	void setFree() { free = true; }

	int getFiancee() const { return engagedWith; }
	void setEngaged(int with);

	void setPreferences(int* prefs, int n);
};
