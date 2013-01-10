#include <string>

// Jasper Desmadryl

static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date
{
private:
	int day, month, year;

	void initObject(int d = 1, int m = 1, int y = 1900);
	bool isLeapYear(int year);
	void parseDate(std::string s);
	int toInt(std::string s, int from, int to);

public:
	Date();
	Date(int d, int m, int y);
	Date(Date const &d);
	Date(std::string s);

	~Date();

	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }

	bool setDay(int d);
	bool setMonth(int m);
	bool setYear(int y);
	bool setDate(int d, int m, int y);

	bool equals(Date const &date) const;

	void readDate();
	void displayDate() const;

	void add(int n);
	void sub(int n);
	int difference(Date const & date) const;
};

