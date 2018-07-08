#pragma once

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <queue>
#include <string>
#include <algorithm>

using std::queue;
using std::ifstream;
using std::ofstream;
using std::string;
using std::swap;
using std::iterator;

bool Lock(false);

class Rander
{
private:
	unsigned int lenth, range;
	ifstream in;
	ofstream out;
	queue<int> num;
public:
	Rander(int _len,int _range):lenth(_len),range(_range)
	{
		out.open("setlen.ini");
		out << lenth << endl;
		out << range << endl;
		out.close();
		apply();
	}
	void reset(int _len, int _range)
	{
		while (!num.empty())num.pop();
		lenth = _len;
		range = _range;
		out.open("setlen.ini");
		out << lenth << endl;
		out << range << endl;
		out.close();
		apply();
	}
	void apply()
	{
		while (Lock);
		Lock = true;
		system("python rand.py > randnum.txt");
		in.open("randnum.txt");
		for (unsigned int i(1); i <= lenth && !in.eof(); ++i)
		{
			int tmp;
			in >> tmp;
			num.push(tmp);
		}
		Lock = false;
	}
	int front()
	{
		if (num.empty())
		{
			apply();
		}
		int tmp = num.front();
		num.pop();
		return tmp;
	}
	double Random()
	{
		return front() * 1.0 / range;
	}
	int randint(int l,int r)
	{
		return floor(Random() * (r - l)) + l;
	}
	template<typename T>
	void shuffle(T *l, T *r)
	{
		int len = r - l;
		if (len <= 1)return;
		for (T *_itr(l); _itr != r; ++_itr)
		{
			swap(_itr, l + randint(0, len));
		}
	}
	template<typename T>
	void shuffle(vector<T> &v)
	{
		int len = v.size();
		for (int i(0); i < len; ++i)
		{
			int to = randint(0, len);
			swap(v[i], v[to]);
		}
	}
};

