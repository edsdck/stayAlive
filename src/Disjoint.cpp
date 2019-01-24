#include "Disjoint.hpp"

Disjoint::Disjoint(int amount)
{
	id.reserve(amount);
	for (int i = 0; i < amount; i++)
	{
		id.push_back(i);
	}
	size.resize(amount, 1);
}

int Disjoint::find_root(int p)
{
	int root = p;
	while (root != id[root])
	{
		root = id[root]; //[root = 5 id[root] = 6], [root = 6 id[root] = 7]; [root = 7 id[root] = 7];
	}
	while (p != root) //path compression
	{
		int next = id[p];
		id[p] = root;
		p = next;
	}
	return root;
}

bool Disjoint::areConnected(int p, int q)
{
	return find_root(p) == find_root(q);
}

void Disjoint::connect(int p, int q)
{
	int root1 = find_root(p);
	int root2 = find_root(q);
	if (size[root1] > size[root2])
	{
		size[root1] += size[root2];
		id[root2] = id[root1];
	}
	else
	{
		size[root2] += size[root1];
		id[root1] = id[root2];
	}
}