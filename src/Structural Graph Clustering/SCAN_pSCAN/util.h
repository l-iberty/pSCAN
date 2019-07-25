#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iostream>

template<typename T>
std::vector<T> operator+(const std::vector<T>& v, const T& x)
{
	std::vector<T> res = v;
	res.push_back(x);
	return res;
}

template<typename T>
std::vector<T> my_intersection(std::vector<T>& v1, std::vector<T>& v2)
{
	std::vector<T> res;
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());
#if 0
	size_t i = 0, j = 0;
	while (i < v1.size() && j < v2.size())
	{
		while (i < v1.size() && j < v2.size() && v1[i] < v2[j]) i++;
		while (i < v1.size() && j < v2.size() && v2[j] < v1[i]) j++;
		while (i < v1.size() && j < v2.size() && v1[i] == v2[j])
		{
			res.push_back(v1[i]);
			i++, j++;
		}
	}
#else
	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(res));
#endif
	return res;
}

template<typename T>
std::vector<T> my_union(std::vector<T>& v1, std::vector<T>& v2)
{
	std::vector<T> res(v1), diff;
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	// diff = v2 - v1
	std::set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), std::back_inserter(diff));
	res.insert(res.end(), diff.begin(), diff.end());

	return res;
}

bool bin_search(std::vector<int>& v, int x);

bool linear_search(std::vector<int>& v, int x);

void TEST_my_intersection();

void TEST_my_union();

void TEST_bin_search();

#endif /* UTIL_H */
