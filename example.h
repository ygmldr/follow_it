#pragma once

#include "public.h"

//�����ʹ�õ����Ƽ���ʹ������ͷ�ļ�
//��Ϊ�Ҿ��ú���ûʲô��emm...

#include <vector>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using std::vector;
using std::pair;
using std::make_pair;



namespace user_name//������Ĳ������������������ռ�����ͷ�ļ�
{

/*
	�������Ҫ����һЩ������ע�⣺
		1.���ж��������������ռ���
		2.��Ҫusing namespace std,��Ӧ�ú��������ʽһ��
		3.ע�ⲻҪ����
		4.������
*/



	vector<int> money;//��¼������ҵ�Ǯ
	//ע�⣬�޸����������ı����Ǯ
	//��ֻ�Ǹ��㿴����

	vector<pair<int, int>> used;//��ʾ�����֮ǰ�Ĳ���
	//��һ������Ϊ���id,�ڶ�������Ϊ����
	//���ǻ��ڱ�������ʱ����������vector


	const int my_id;
	//��¼���Լ���id

	//�벻Ҫ��ͼ�޸�������������,��bug����Ը�(���������Լ����ı���

	hand inhand;
	int position;

	void initalize()
	{


	}//��һ��������ʼǰ�᲻�����������д˺���
	//Ҳ����˵�����һ��ʱ��Ԥ����

	void start(hand mine, int place)
	{
		inhand = mine;
		position = place;

		return;
	}//���ø�����һ����Ϸ��ʼ��������ƺ�λ��

	int decision(int least)
	{

		return -1;
	}//�����������¶���ע������Ҫ����һ��ֵ��-1��ʾ������һ������ʾ����ֵ���Ƿ���������Ϊ�㷵��-1

	void end(bool win,int money)
	{

		return;
	}//���ñ����������㱾�غϽ������Լ����ʤ��,��Ӯ���٣�����һ�������������Ǿ���ֵ��

}

