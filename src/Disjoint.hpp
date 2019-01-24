#ifndef DISJOINT_H
#define DISJOINT_H
#include <vector>
class Disjoint
{
private:
	std::vector<int> id;
	std::vector<int> size;
public:
	Disjoint(int amount);
	int find_root(int p);
	bool areConnected(int p, int q);
	void connect(int p, int q);
};
#endif