#pragma once


#include "player.h"
#include "public.h"
#include "random.h"

#include <vector>
using std::vector;
using std::iterator;

/*--------7.8 beta 完成--------*/

class Game
{
private:
	vector<Player*> players;
	vector<Player*> Losers;
	vector<paper> papers;
	vector<vector<int>> events;//0表示退出
	int num;
	int moneypool;
	Rander *r;
	const int first_in;
public:
	vector<int> money;
	Game(int _num) :num(_num),first_in(3)
	{
		r = new Rander(65536,131072);
		players.reserve(num);
		money.reserve(num);
		papers.reserve(52);
		for (int i(0); i < 13; ++i)
		{
			for (int j(0); j < 4; ++j)
			{
				papers.push_back(paper(i,j));
			}
		}
		for (int i(0); i < num; ++i)
		{
			money.push_back(10000);
			events.push_back(vector<int>());
		}
	}
	void add_player(
		void(*_initalize)(), void(*_start)(hand, int), int(*_decision)(int), void(*_end)(bool,int),
		int &_id, vector<int> &_money, vector<pair<int, int>> &_used
	)
	{
		players.push_back(new Player(_initalize,_start,_decision,_end,_id,_money,_used));
	}//player的构造函数自动执行init

	int get_id(vector<Player*>::iterator itr)
	{
		return (*itr)->pro_id;
	}

	void Eliminate()
	{
		for (int i(0); i < num; ++i)
		{
			for (vector<Player*>::iterator itr(players.begin()); itr != players.end(); ++itr)
			{
				if (money[get_id(itr)] < first_in)
				{
					players.erase(itr);
					Losers.push_back(*itr);
					events[get_id(itr)].push_back(0);
					break;
				}
			}
		}
	}

	bool start()
	{
		if (players.size() < 2)
		{
			return false;
		}//只剩一人，比赛结束
		GameBegin();
		int people_left = players.size();
		int atleast = first_in;
		moneypool = people_left * first_in;
		for (int i(1); i <= people_left; ++i)
		{
			if (Round(atleast))break;
		}//满足进行人数轮游戏
		ended(Find_Winner());
		return true;
	}

	void GameBegin()
	{
		r->shuffle(players);
		r->shuffle(papers);
		for (int i(0);i < players.size();++i)
		{
			players[i]->now = hand(papers.begin() + i * 3);
			players[i]->position = i;
			players[i]->thr = false;
			players[i]->gamestart();
		}//发牌
		for (vector<Player*>::iterator itr(players.begin()); itr != players.end(); ++itr)
		{
			money[get_id(itr)] -= first_in;
			events[get_id(itr)].back() -= first_in;
		}//记录
	}

	bool Round(int &least)
	{
		int lefts(0);
		for (vector<Player*>::iterator itr(players.begin()); itr != players.end(); ++itr)
		{
			lefts += !(*itr)->thr;
		}
		if (lefts < 2)
			return true;
		//只剩1人
		for (vector<Player*>::iterator itr(players.begin()); itr != players.end(); ++itr)
		{
			if (!(*itr)->thr)
			{
				int tmp = (*itr)->gamegoing(least);
				if (tmp == -1)
				{
					(*itr)->thr = true;
				}
				else
				{
					if (tmp < least && tmp == money[get_id(itr)])
					{
						events[get_id(itr)].back() -= tmp;
						money[get_id(itr)] -= tmp;
						return true;//无法支付
					}
					if (tmp < least || tmp > least + first_in || tmp > money[get_id(itr)])
					{
						(*itr)->thr = true;
					}//进行非法操作
					else
					{
						events[get_id(itr)].back() -= tmp;
						money[get_id(itr)] -= tmp;
						least = tmp;
					}
				}
			}
		}
		return false;
	}//满足只剩一人或有人无法下注时return true

	int Find_Winner()
	{
		vector<Settlement> settlements;
		for (vector<Player*>::iterator itr(players.begin()); itr != players.end(); ++itr)
		{
			if(!(*itr)->thr)
				settlements.push_back(Settlement(*itr));
		}
		sort(settlements.begin(), settlements.end());
		return settlements.back().id;
	}

	void ended(int winner)
	{
		for (vector<Player*>::iterator itr(players.begin()); itr != players.end(); ++itr)
		{
			if (get_id(itr) == winner)
			{
				money[get_id(itr)] += moneypool;
				events[get_id(itr)].back() += moneypool;
			}
		}
		for (vector<Player*>::iterator itr(players.begin()); itr != players.end(); ++itr)
		{
			if (get_id(itr) == winner)
			{
				(*itr)->gameend(true, events[get_id(itr)].back());
			}
			else
			{
				(*itr)->gameend(false, events[get_id(itr)].back());
			}
		}
		Eliminate();//赛后淘汰
	}

};
