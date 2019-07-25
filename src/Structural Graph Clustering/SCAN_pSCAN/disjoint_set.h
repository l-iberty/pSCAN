#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

class DisjointSet
{
private:
	int *mRoots;
	int mSize;
public:
	DisjointSet(int size);
	~DisjointSet();
	int Find(int x);
	int Union(int x, int y);
	int GetSetSize(int x);
	inline int GetSize() { return mSize; }
	inline int* GetRoots() { return mRoots; }
	void DispRoots();
};

#endif /* DISJOINT_SET_H */
