#include "util.h"
#include <cassert>

bool bin_search(std::vector<int>& v, int x)
{
	int left = 0, right = v.size() - 1, mid = -1;
	while (left <= right)
	{
		mid = (left + right) >> 1;
		if (v[mid] == x) break;
		else if (x > v[mid]) left = mid + 1;
		else right = mid - 1;
	}
	if (mid >= 0 && mid < v.size() && v[mid] == x) return true;
	return false;
}

bool linear_search(std::vector<int>& v, int x)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == x) return true;
	}
	return false;
}

void TEST_my_intersection()
{
	std::vector<int> v1, v2, res;

	v1 = { 1 };
	v2 = {};
	res = my_intersection(v1, v2);
	std::cout << "TEST-1 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1 };
	v2 = { 1 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-2 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1 };
	v2 = { 2 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-3 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1 };
	v2 = { 1, 2 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-4 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2 };
	v2 = { 1 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-5 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2 };
	v2 = { 1, 2 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-6 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 4, 6, 10 };
	v2 = { 1, 2, 4, 6, 10 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-7 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 4, 6, 10 };
	v2 = { 1, 2, 3, 4, 6, 10 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-8 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 4, 6, 10 };
	v2 = { 3, 4, 5, 6, 12 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-9 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 10, 2, 4, 16, 10 };
	v2 = { 3, 14, 4, 10, 5, 4, 6, 10, 12 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-10 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 1, 2 };
	v2 = { 2, 2, 2, 1, 2, 1 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-11 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 1 };
	v2 = { 1, 1 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-12 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 3, 5 };
	v2 = { 1, 2, 3, 4 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-13 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 3, 5 };
	v2 = { 5, 7, 8, 10 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-14 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 3, 5 };
	v2 = { 6, 7, 8, 10 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-15 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 2, 2, 2, 3, 5, 6, 10 };
	v2 = { 1, 2, 3, 5 };
	res = my_intersection(v1, v2);
	std::cout << "TEST-16 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;
}

void TEST_my_union()
{
	std::vector<int> v1, v2, res;

	v1 = { 1 };
	v2 = {};
	res = my_union(v1, v2);
	std::cout << "TEST-1 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1 };
	v2 = { 1 };
	res = my_union(v1, v2);
	std::cout << "TEST-2 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1 };
	v2 = { 2 };
	res = my_union(v1, v2);
	std::cout << "TEST-3 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1 };
	v2 = { 1, 2 };
	res = my_union(v1, v2);
	std::cout << "TEST-4 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2 };
	v2 = { 1 };
	res = my_union(v1, v2);
	std::cout << "TEST-5 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2 };
	v2 = { 1, 2 };
	res = my_union(v1, v2);
	std::cout << "TEST-6 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 4, 6, 10 };
	v2 = { 1, 2, 4, 6, 10 };
	res = my_union(v1, v2);
	std::cout << "TEST-7 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 4, 6, 10 };
	v2 = { 1, 2, 3, 4, 6, 10 };
	res = my_union(v1, v2);
	std::cout << "TEST-8 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 4, 6, 10 };
	v2 = { 3, 4, 5, 6, 12 };
	res = my_union(v1, v2);
	std::cout << "TEST-9 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 10, 2, 4, 16, 10 };
	v2 = { 3, 14, 4, 10, 5, 4, 6, 10, 12 };
	res = my_union(v1, v2);
	std::cout << "TEST-10 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 1, 2 };
	v2 = { 2, 2, 2, 1, 2, 1 };
	res = my_union(v1, v2);
	std::cout << "TEST-11 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 1 };
	v2 = { 1, 1 };
	res = my_union(v1, v2);
	std::cout << "TEST-12 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 3, 5 };
	v2 = { 1, 2, 3, 4 };
	res = my_union(v1, v2);
	std::cout << "TEST-13 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 3, 5 };
	v2 = { 5, 7, 8, 10 };
	res = my_union(v1, v2);
	std::cout << "TEST-14 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 1, 2, 3, 5 };
	v2 = { 6, 7, 8, 10 };
	res = my_union(v1, v2);
	std::cout << "TEST-15 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;

	v1 = { 2, 2, 2, 3, 5, 6, 10 };
	v2 = { 1, 2, 3, 5 };
	res = my_union(v1, v2);
	std::cout << "TEST-16 ";
	for (int i : res) std::cout << i << " ";
	std::cout << std::endl;
}

void TEST_bin_search()
{
#if 0
	std::vector<int> v;

	std::cout << "TEST-1\n";
	for (int i : v) std::cout << bin_search(v, i) << " ";
	std::cout << "\n";

	v = { 1 };
	std::cout << "TEST-2\n";
	for (int i : v) std::cout << bin_search(v, i) << " ";
	std::cout << "\n";

	v = { 1, 1 };
	std::cout << "TEST-3\n";
	for (int i : v) std::cout << bin_search(v, i) << " ";
	std::cout << "\n";

	v = { 1, 2 };
	std::cout << "TEST-4\n";
	for (int i : v) std::cout << bin_search(v, i) << " ";
	std::cout << "\n";

	v = { 0, 1, 2 };
	std::cout << "TEST-5\n";
	for (int i : v) std::cout << bin_search(v, i) << " ";
	std::cout << "\n";

	v = { 0, 0, 1, 1, 2, 2 };
	std::cout << "TEST-6\n";
	for (int i : v) std::cout << bin_search(v, i) << " ";
	std::cout << "\n";

	v = { 1, 2, 2, 4, 5, 6, 10, 12, 14 };
	std::cout << "TEST-7\n";
	for (int i : v) std::cout << bin_search(v, i) << " ";
	std::cout << bin_search(v, 9) << " ";
	std::cout << bin_search(v, 15) << " ";
	std::cout << bin_search(v, -15);
	std::cout << "\n";
#endif
}