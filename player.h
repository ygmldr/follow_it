#pragma once

#include <vector>
#include <utility>
#include "public.h"

using std::vector;
using std::pair;
using std::make_pair;

int givenid(0);

struct Player
{

public:

	int &id;
	vector<int> &money;
	vector<pair<int, int>> &used;
	int pro_id;

	void(*initalize)();
	void(*start)(hand, int);
	int(*decision)(int);
	void(*end)(bool,int);

	hand now;
	int position;
	bool thr;

	//指向玩家的操作
	
	Player() = default;

	Player(
		void (*_initalize)(),void (*_start)(hand,int),int (*_decision)(int),void (*_end)(bool,int),
		int &_id,vector<int> &_money,vector<pair<int,int>> &_used
	):
		initalize(_initalize),start(_start),decision(_decision),end(_end),
		id(_id),money(_money),used(_used)
	{
		initalize();
		money.clear();
		used.clear();

		id = givenid;
		pro_id = id;
		givenid++;

	}

	void gamestart()
	{
		used.clear();
		start(now, position);
	}

	int gamegoing(int least)
	{
		return decision(least);
	}

	void gameend(bool win,int money)
	{
		used.clear();
		end(win,money);
	}

};

struct Settlement
{
public:
	hand in;
	int id;
	Settlement(Player *t):in(t->now),id(t->pro_id){}
	bool operator < (Settlement &s)const
	{
		return in < s.in;
	}
};
