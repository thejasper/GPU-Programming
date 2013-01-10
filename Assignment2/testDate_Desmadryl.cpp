#include <iostream>
#include <string>

#include "Date_Desmadryl.h"

// Jasper Desmadryl

using namespace std;

static int numPassed = 0;
static int numFailed = 0;

void dateTestEqual(string subj, Date act, Date exp);
void dateTestEqual(string subj, int act, int exp);

int main()
{
	Date defaultDate(1, 1, 1900);
	Date today(10, 10, 2012);

	// constructor tests
	dateTestEqual("Default constructor", Date(), Date(1, 1, 1900));
	dateTestEqual("Normal constructor", Date(10, 10, 2012), today);
	dateTestEqual("Constructor with year out of range", Date(10, 10, 1899), defaultDate);
	dateTestEqual("Constructor with month out of range", Date(10, 13, 1900), defaultDate);
	dateTestEqual("Constructor with day out of range", Date(32, 10, 1900), defaultDate);
	dateTestEqual("Copy constructor", Date(today), today);

	// getters and setters
	dateTestEqual("GetYear method", today.getYear(), 2012);
	dateTestEqual("GetMonth method", today.getMonth(), 10);
	dateTestEqual("GetDay method", today.getDay(), 10);

	Date someDate;
	dateTestEqual("SetYear method out of range", today.setYear(1800), false);
	dateTestEqual("SetMonth method out of range", today.setMonth(0), false);
	dateTestEqual("SetDay method out of range", today.setDay(0), false);

	bool yearSuccess = someDate.setYear(2099);
	bool monthSuccess = someDate.setMonth(9);
	bool daySuccuess = someDate.setDay(30);
	dateTestEqual("GetYear method after setYear", someDate.getYear(), 2099);
	dateTestEqual("GetMonth method after setMonth", someDate.getMonth(), 9);
	dateTestEqual("GetDay method after setDay", someDate.getDay(), 30);
	dateTestEqual("Return value of getYear after legal set", yearSuccess, true);
	dateTestEqual("Return value of getMonth after legal set", monthSuccess, true);
	dateTestEqual("Return value of getDay after legal set", daySuccuess, true);

	bool setDateSuccess = someDate.setDate(29, 2, 2004);
	dateTestEqual("Return value of setDate after legal set", setDateSuccess, true);
	bool setDateFail = someDate.setDate(29, 2, 2001);
	dateTestEqual("Return value of setDate after illegal set", setDateFail, false);

	// equal function
	Date date1(28, 2, 2100), date2(28, 2, 2100);
	dateTestEqual("Return value of equals when they are the same", date1.equals(date2), true);
	date1.setMonth(date1.getMonth() - 1);
	dateTestEqual("Return value of equals when they are not the same", date1.equals(date2), false);

	// add function
	Date testAdd(1, 1, 2010);
	testAdd.sub(-365*2);
	dateTestEqual("Date add test 1", testAdd, Date(1, 1, 2012));
	testAdd.add(31 + 29);
	dateTestEqual("Date add test 2", testAdd, Date(1, 3, 2012));
	testAdd.add(200000);
	dateTestEqual("Date add test 3", testAdd, Date(30, 9, 2559));
    testAdd.setDate(29, 2, 1992);
    testAdd.add(365);
	dateTestEqual("Date add test 4", testAdd, Date(28, 2, 1993));

	// subtract function
	Date testSub(1, 1, 2010);
	testSub.sub(1);
	dateTestEqual("Date sub test 1", testSub, Date(31, 12, 2009));
	testSub.sub(365 * 2 + 1);
	dateTestEqual("Date sub test 2", testSub, Date(31, 12, 2007));
	testSub.sub(200000);
	dateTestEqual("Date sub test 3 (was there an error printed?)", testSub, Date(1, 1, 1900));

	// difference
	Date testDifference1(1, 1, 2010), testDifference2(1, 1, 2010);
	dateTestEqual("Date difference test 1", testDifference1.difference(testDifference2), 0);
	testDifference2.add(2000);
	dateTestEqual("Date difference test 1", testDifference1.difference(testDifference2), 2000);
	testDifference1.add(4000);
	dateTestEqual("Date difference test 1", testDifference1.difference(testDifference2), -2000);

	// string constructor
	dateTestEqual("String constructor test 1", Date("10/10/2012"), today);
	dateTestEqual("String constructor test 2", Date("10/10/1800"), defaultDate);
	dateTestEqual("String constructor test 3", Date("blabla"), defaultDate);
	dateTestEqual("String constructor test 4", Date("10/a3/2012"), defaultDate);
	dateTestEqual("String constructor test 5", Date("10-03-2012"), defaultDate);

	cout << endl << "Passed: " << numPassed << ", failed: " << numFailed << endl;

	// test the readdate function
	Date newDate;
	cout << endl << "Enter a date (format dd/mm/yyyy): ";
	newDate.readDate();
	cout << endl << "You entered this date: ";
	newDate.displayDate();
	cout << endl;

	return 0;
}

void dateTestEqual(string subj, Date act, Date exp)
{
	bool ok = exp.equals(act);
	cout << (ok ? "[PASS]" : "[FAIL]") << ' ' << subj;

	if (!ok)
	{
		cout << endl << "  Expected: ";
		exp.displayDate();
		cout << ", received: ";
		act.displayDate();
	}
	cout << endl;

	numPassed += ok;
	numFailed += !ok;
}

void dateTestEqual(string subj, int act, int exp)
{
	bool ok = (exp == act);
	cout << (ok ? "[PASS]" : "[FAIL]") << ' ' << subj;

	if (!ok)
	{
		cout << endl << "  Expected: " << exp << ", received: " << act;
	}
	cout << endl;

	numPassed += ok;
	numFailed += !ok;
}
