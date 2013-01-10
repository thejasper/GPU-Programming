#include <iostream>
#include <string>
#include <cctype>

#include "Date_Desmadryl.h"

// Jasper Desmadryl

using namespace std;

Date::Date()
{
	initObject();
}

Date::Date(int d, int m, int y)
{
	initObject(d, m, y);
}

Date::Date(Date const &d)
{
	initObject(d.day, d.month, d.year);
}

Date::Date(string s)
{
	parseDate(s);
}

Date::~Date()
{
}

void Date::initObject(int d, int m, int y)
{
	// whenever one of the variables is out of range, set the date as 1/1/1900
	if (!setYear(y) || !setMonth(m) || !setDay(d))
	{
		day = 1;
		month = 1;
		year = 1900;
	}
}

bool Date::isLeapYear(int year)
{
	if (year % 4 == 0) // normal rule
	{
		if (year % 100 == 0 && year % 400 != 0) // the edge case
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

int Date::toInt(string s, int from, int to)
{
	int result = 0;

	for (int i = from; i <= to; ++i)
	{
		int digit = s[i] - '0';
		result = result * 10 + digit;
	}

	return result;
}

// this method accepts datestrings in the format 01/01/1900
// it would look better with the use of a regural expression
void Date::parseDate(string s)
{
	bool error = false;
	string correctExample = "01/01/1900";

	// check if length is the same
	if (s.length() != correctExample.length())
	{
		error = true;
	}

	for (int i = 0; i < (int)s.length() && !error; ++i)
	{
		// check if there's a slash on position 2 and 5
		if (i == 2 || i == 5)
		{
			if (s[i] != '/')
			{
				error = true;
			}
		}
		else if (!isdigit(s[i])) // other positions must contain a digit
		{
			error = true;
		}
	}

	// try to initialise the object, there will be an error if there's a parameter out of range
	if (!error && (!setYear(toInt(s, 6, 9)) || !setMonth(toInt(s, 3, 4)) || !setDay(toInt(s, 0, 1))))
	{
		error = true;
	}

	if (error)
	{
		cout << "Make sure the date is in this format: 01/01/1900" << endl;
		initObject();
	}
}

bool Date::setDay(int d)
{
	// daysInMonth[i] contains the number of days of month i+1 in a normal year
	// so januari (the 1st month) contains daysInMonth[0] days
	// add one day to the number of days if it's a leap year and we are februari
	if (d < 1 || d > daysInMonth[month - 1] + (month == 2 && isLeapYear(year)))
	{
		return false;
	}

	day = d;
	return true;
}

bool Date::setMonth(int m)
{
	if (m < 1 || m > 12)
	{
		return false;
	}

	month = m;
	return true;
}

bool Date::setYear(int y)
{
	if (y < 1900)
	{
		return false;
	}

	year = y;
	return true;
}

bool Date::setDate(int d, int m, int y)
{
	// try to set the date
	// if something is not correct, revert the changes
	int currD = day;
	int currM = month;
	int currY = year;
	bool correct = setYear(y) && setMonth(m) && setDay(d);

	if (!correct)
	{
		day = currD;
		month = currM;
		year = currY;
	}

	return correct;
}

bool Date::equals(Date const &date) const
{
	return day == date.day &&
		   month == date.month &&
		   year == date.year;
}

void Date::readDate()
{
	string s;
	cin >> s;
	parseDate(s);
}

void Date::displayDate() const
{
	cout << day << "/" << month << "/" << year;
}

void Date::add(int n)
{
	if (n < 0)
	{
		sub(-n);
		return;
	}

	// this runs in O(n).. When there's time, a better method should be implemented
	while (n--)
	{
		// number of days in the current month
		int currMonthDays = daysInMonth[month - 1] + (month == 2 && isLeapYear(year));

		// no new month is started so just add one day
		if (day + 1 <= currMonthDays)
		{
			++day;
			continue;
		}

		day = 1;

		// no new year is started so just add one month
		if (month + 1 <= 12)
		{
			++month;
			continue;
		}

		month = 1;
		++year;
	}
}

void Date::sub(int n)
{
	if (n < 0)
	{
		add(-n);
		return;
	}

	// this runs in O(n).. When there's time, a better method should be implemented
	while (n--)
	{
		if (equals(Date(1, 1, 1900)))
		{
			cout << "Result must be after 1/1/1900" << endl;
			break;
		}

		// still in the same month
		if (day - 1 >= 1)
		{
			--day;
			continue;
		}

		// calculate index previous month and make sure it's in [1, 12]
		int prevMonthIndex = (month - 1 - 1 + 12) % 12;
		// number of days in the previous month
		int previousMonthDays = daysInMonth[prevMonthIndex] + (prevMonthIndex == 1 && isLeapYear(year));
		day = previousMonthDays;

		// still in the same year
		if (prevMonthIndex != 11)
		{
			--month;
			continue;
		}

		month = prevMonthIndex + 1;
		--year;
	}
}

int Date::difference(Date const &date) const
{
	int n = 0, direction = 1;
	Date copy(*this);

	if (date.year > year && date.month > month && date.day > day) // parameter date after this object
	{
		direction = 1; // result will be postive
	}
	else
	{
		direction = -1; // result will be negative
	}

	while (!copy.equals(date))
	{
		++n;
		copy.add(direction);
	}

	return n * direction;
}
