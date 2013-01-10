// Jasper Desmadryl

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template<typename T>
class Set
{
private:
	std::vector<T> elements;
	static const int npos = -1; // when an element is not found, functions return this value
	void (*sort)(std::vector<T>&); // pointer to a function that takes a reference to a vector and sorts it

	int binarySearch(const T&) const;

public:
	Set(void (*sF)(std::vector<T>&));

	bool insert(const T&);
	bool remove(const T&);
	bool find(const T&) const;

	void print() const;

	int getNumElements() const;
};

// constructor takes a pointer to a sortfunction (callback function)
template<typename T>
Set<T>::Set(void (*sortFunction)(std::vector<T>&))
	: sort(sortFunction)
{
}

// do a binary search after elem
// return the index if it's found, -1 otherwise
template<typename T>
int Set<T>::binarySearch(const T& elem) const
{
	typename std::vector<T>::const_iterator pos = std::lower_bound(elements.begin(), elements.end(), elem);

	if (pos != elements.end() && *pos == elem)
		return pos - elements.begin();
	else
		return npos;
}

// insert an element if it's absent, sort after a successful insert
// return true if it was inserted, false otherwise (element already present)
template<typename T>
bool Set<T>::insert(const T& elem)
{
	int pos = binarySearch(elem);

	if (pos != npos) // already in set
		return false;

	elements.push_back(elem);
	sort(elements);
	return true;
}

// removes an element if it's present in the set
// return true if it was removed, false otherwise (element absent)
template<typename T>
bool Set<T>::remove(const T& elem)
{
	int pos = binarySearch(elem);

	if (pos != npos) // element found
	{
		elements.erase(elements.begin() + pos);
		return true;
	}

	return false;
}

// finds an element in the set with a binary search
// return true if it's found, false otherwise
template<typename T>
bool Set<T>::find(const T& elem) const
{
	return binarySearch(elem) != npos;
}

// print all the elements that are in the set separated by a space
template<typename T>
void Set<T>::print() const
{
	std::copy(elements.begin(), elements.end(), std::ostream_iterator<T>(std::cout, " "));
	std::cout << std::endl;
}

// return the number of elements in the set
template<typename T>
int Set<T>::getNumElements() const
{
	return elements.size();
}
