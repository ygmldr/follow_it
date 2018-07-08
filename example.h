#pragma once

#include "public.h"

//你可以使用但不推荐你使用其他头文件
//因为我觉得好像没什么用emm...

#include <vector>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using std::vector;
using std::pair;
using std::make_pair;



namespace user_name//请以你的参赛名字命名该命名空间和你的头文件
{

/*
	如果你需要增添一些东西请注意：
		1.所有东西都放在命名空间内
		2.不要using namespace std,而应该和上面的形式一样
		3.注意不要重名
		4.玩的愉快
*/



	vector<int> money;//记录所有玩家的钱
	//注意，修改这个并不会改变你的钱
	//这只是给你看看的

	vector<pair<int, int>> used;//表示玩家们之前的操作
	//第一个参数为玩家id,第二个参数为操作
	//我们会在比赛结束时帮你清空这个vector


	const int my_id;
	//记录你自己的id

	//请不要试图修改上面三项数据,出bug后果自负(明明就是自己懒的备份

	hand inhand;
	int position;

	void initalize()
	{


	}//第一场比赛开始前会不带参数的运行此函数
	//也就是说你会有一点时间预处理

	void start(hand mine, int place)
	{
		inhand = mine;
		position = place;

		return;
	}//调用告诉你一轮游戏开始，你的手牌和位置

	int decision(int least)
	{

		return -1;
	}//传入你至少下多少注，你需要返回一个值，-1表示弃，或一个数表示跟的值，非法操作将视为你返回-1

	void end(bool win,int money)
	{

		return;
	}//调用本函数告诉你本回合结束，以及你的胜负,输赢多少（这是一个整数啊，不是绝对值）

}

