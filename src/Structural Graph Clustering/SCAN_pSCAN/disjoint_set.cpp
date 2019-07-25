﻿#include <iostream>
#include "disjoint_set.h"

DisjointSet::DisjointSet(int size)
{
	mRoots = new int[size];
	mSize = size;
	// 初始时, 每个元素都是一个独立的集合
	for (int i = 0; i < mSize; i++)
	{
		mRoots[i] = -1;
	}
}

DisjointSet::~DisjointSet()
{
	delete[] mRoots;
}

// 返回 x 所在集合的名字, 不存在则返回(-1)
// x 的合法取值范围: [0, mSize-1]
int DisjointSet::Find(int x)
{
	if (x < 0 || x >= mSize)
	{
		return -1;
	}
	// mRoots[x] < 0 说明 x 就是根, 就是集合的名字;
	// 且 mRoots[x] 的绝对值等于该集合中的元素个数.
	while (mRoots[x] >= 0)
	{
		x = mRoots[x];
	}
	return x;
}

// 将 y 所在的集合合并到 x 所在的集合, 要求两个集合不相交
// 返回新集合的名字, 失败则返回(-1)
int DisjointSet::Union(int x, int y)
{
	int Root_x = Find(x);
	int Root_y = Find(y);

	if (Root_x == -1 || Root_y == -1) // x/y not found
	{
		return -1;
	}
	if (Root_x == Root_y) // x 与 y 属于同一个集合
	{
		return -1;
	}

	mRoots[Root_x] += mRoots[Root_y];
	mRoots[Root_y] = Root_x;
	return Root_x;
}

// 返回 x 所在集合中的元素个数, 失败则返回(-1)
int DisjointSet::GetSetSize(int x)
{
	int Root = Find(x);
	if (Root == -1) // Not found
	{
		return -1;
	}
	return -mRoots[Root];
}

void DisjointSet::DispRoots()
{
	for (int i = 0; i < mSize; i++)
	{
		std::cout << i << " - " << mRoots[i] << "\n";
	}
	std::cout << std::endl;
}
