// Jasper Desmadryl

// Give one reason why your quicksort method should be implemented outside of your Set class, and one reason it should be implemented within your Set class.
// -> Outside the set class: There exist a lot of sorting algorithms and sometimes a generic one is not desired.
//    If we allow the user to select his own sorting function, he can use whatever algorithm seems appropriate.
// -> Inside the set class: The class is now self-contained. There are no dependencies to worry about and
//    you can use the class immediately.
// Note: Both approaches have their benefits. We could take the best of both worlds by providing a default sorting method and
//       providing a function to change it.

// What is the running time of your quicksort method?
// U probably don't expect a deep analysis of quicksort so I'll assume the running times are known.
// The worst case running time is O(n^2) and the average running time is O(n*logn)
// The pivot (the element around which the partition is done) plays an important role in the running time of quicksort.
// When you always take the first item or the last item (like I do) as pivot, it will perform very badly on sorted sequences.
// A better method is to randomize the item that is picked as pivot (there exist some other methods too).
// By using a randomized version of quicksort it will perform very good on average.

// Is a vector a good choice for the best way to store elements in your set? Why or why not?
// No, It's expensive to insert and delete items. These operations take lineair time on average because
// you always have to shift the elements in the vector to make place (before insert) or to fill a gap (after delete).
// We could do better with a balanced binary tree (insert, delete, find in O(logn)), or 
// a hashtable (insert, delete, find in constant amortized time), or something else.

// If you were giving this Set class to a customer who was paying money for it, how thorough would your test class have to be for you to be satisfied it works?
// Very thorough. Preferably there should be automated tests (like with my date class) that test the class thoroughly.
// Because it's a template class it should also be tested with several instantiations.
// It's quite possible that all tests pass with a Set<int> class but fail with a Set<float> class.
// Your find function could fail when it compares floats with the equality operator '==' because of the inaccuracy.
// Something like abs(f1 - f2) < epsilon should be used (epsilon is some small value).

// Implement another sorting technique that you like and compare it (in words) to quicksort.
// I chose gnomesort because I like the idea behind it. It uses the same principle as insertion sort
// but places the element in the right spot with repeated swaps instead of just one.
// This results in compact code that sometimes runs fast.. It runs in O(n) on sorted sequences and has an average and
// worst case running time of O(n^2).


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Set.h"

using namespace std;

// format output for tests
template<typename T> void prettyPrint(string msg, Set<T> set, string expected);
void prettyPrint(string msg, int received, int expected);

// lineair time insertion of last element
template<typename T> void putLastElementInPlace(vector<T>& v);

// quicksort
template<typename T> int partition(vector<T>& v, int left, int right);
template<typename T> void quicksort(vector<T>& v, int left, int right);
template<typename T> void quickSortWrap(vector<T>& v);

// gnomesort
template<typename T> void gnomeSort(vector<T>& v);

int main()
{
	// constructor takes a pointer to the sorting method
	Set<int> set(&gnomeSort); // or &putLastElementInPlace, or &quickSortWrap

	// insert tests
	cout << "Insert tests..." << endl;
	cout << "---------------" << endl << endl;

	for (int i = 5; i > 0; --i) set.insert(i);
	prettyPrint("Initial insert in reverse order", set, "1 2 3 4 5");

	set.insert(0);
	prettyPrint("Insert front", set, "0 1 2 3 4 5");

	int ret = set.insert(-1);
	prettyPrint("Insert negative", set, "-1 0 1 2 3 4 5");
	prettyPrint("Return value unique", ret, true);

	ret = set.insert(5);
	prettyPrint("Insert duplicate", set, "-1 0 1 2 3 4 5");
	prettyPrint("Return value duplicate", ret, false);

	// remove tests
	cout << "Remove tests..." << endl;
	cout << "---------------" << endl << endl;

	for (int i = 0; i < 5; i += 2) set.remove(i);
	prettyPrint("Remove even numbers", set, "-1 1 3 5");

	ret = set.remove(-1);
	prettyPrint("Remove the negative number", set, "1 3 5");
	prettyPrint("Return value if it exists", ret, true);

	ret = set.remove(0);
	prettyPrint("Remove value that does not exist", set, "1 3 5");
	prettyPrint("Return value if it does not exist", ret, false);

	// find tests
	cout << "Find tests..." << endl;
	cout << "---------------" << endl << endl;

	ret = set.find(1);
	prettyPrint("Return value of successful search", ret, true);
	ret = set.find(0);
	prettyPrint("Return value of unsuccessful search", ret, false);

	// count tests
	cout << "Count tests..." << endl;
	cout << "---------------" << endl << endl;

	ret = set.getNumElements();
	prettyPrint("Number of elements", ret, 3);

	set.remove(1); set.remove(3); set.remove(5);
	ret = set.getNumElements();
	prettyPrint("Number of elements empty set", ret, 0);

	cout << "Please check if the first line matches the second one in each test case" << endl;

	return 0;
}

// 2 helper functions to print the result of the test cases
template<typename T>
void prettyPrint(string msg, Set<T> set, string expected)
{
	cout << msg << endl;
	set.print();
	cout << expected << endl << endl;
}

void prettyPrint(string msg, int received, int expected)
{
	cout << msg << endl;
	cout << received << endl;
	cout << expected << endl << endl;
}

// this puts the last inserted element element (at the back) in place
// by 'sifting' it down until it's on the right position
// this avoids resorting the whole array
template <typename T>
void putLastElementInPlace(vector<T>& v)
{
	for (int i = v.size() - 1; i > 0; --i)
	{
		if (v[i] < v[i-1])
			swap(v[i], v[i-1]);
		else
			break;
	}
}

// a subroutine used by quicksort (I used the pseudocode on wikipedia as inspiration)
// this 'splits' the vector in two parts: a part where the elements are smaller than
// the pivot and a part where they are bigger
template<typename T>
int partition(vector<T>& v, int left, int right)
{
	int pivotValue = v[right];
	int storeIndex = left;

	for (int i = left; i < right; ++i)
	{
		if (v[i] < pivotValue)
		{
			swap(v[i], v[storeIndex]);
			++storeIndex;
		}
	}

	swap(v[storeIndex], v[right]); //put pivot into place
	return storeIndex;
}

// recursively sort the vector using the quicksort method
template<typename T>
void quicksort(vector<T>& v, int left, int right)
{
	if (left >= right)
		return;

	int pivotIndex = partition(v, left, right);

	// sort left and right parts, pivot is always on it's place after the partition
	quicksort(v, left, pivotIndex - 1);
	quicksort(v, pivotIndex + 1, right);
}

// this wraps the quicksort method so it can be used by the Set class
template<typename T>
void quickSortWrap(vector<T>& v)
{
	quicksort(v, 0, v.size() - 1);
}

// an extra sorting method (explanation in the questions)
template<typename T>
void gnomeSort(vector<T>& v)
{
	unsigned int i = 1;
	while (i < v.size())
	{
		if (v[i-1] <= v[i])
			++i;
		else
		{
			swap(v[i], v[i-1]);
			if (i > 1) --i;
		}
	}
}
