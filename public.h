#pragma once

#include <algorithm>
#include <vector>

using std::vector;
using std::sort;
using std::iterator;

//������ֽ����
struct paper
{
public:
	int value, color, code;
	//value��¼��С��colorΪ��ɫ��codeΪ����
	paper() = default;
	paper(int _value,int _color):
		value(_value),color(_color),code(value << 2 | color){}
	bool operator < (paper &p)const
	{
		return code < p.code;
/*
	�ȼ��ڣ�
		if(value == p.value)
			return color < p.color
		else
			return value < p.value
*/
	}
};

//������������
struct hand
{
private:
	//�ж�����
	void initalize()
	{
		sort(p, p + 3);
		biggest = p[2];//�����
		if (p[0].value == p[1].value - 1 && p[1].value == p[2].value - 1)
		{
			if (p[0].color == p[1].color && p[1].color == p[2].color)
				rk = 5;//ͬ��˳
			else
				rk = 3;//˳��
		}
		else if (p[0].value == p[1].value && p[1].value == p[2].value)
			rk = 4;//����
		else if (p[0].color == p[1].color && p[1].color == p[2].color)
			rk = 2;//ͬ��
		else if (p[0].value == p[1].value || p[1].value == p[2].value)
		{
			rk = 1;
			if (p[0].value == p[1].value)
			{
				biggest = p[1];
			}
		}
		else
			rk = 0;//��
	}
public:
	int rk;
	paper p[3];
	paper biggest;
	hand() = default;
	hand(paper _p0, paper _p1, paper _p2) 
	{
		p[0] = _p0;
		p[1] = _p1;
		p[2] = _p2;
		initalize();
	}
	hand(paper* itrp)
	{
		p[0] = *itrp;
		p[1] = *(itrp + 1);
		p[2] = *(itrp + 2);
		initalize();
	}
	hand(vector<paper>::iterator itrp)
	{
		p[0] = *itrp;
		p[1] = *(itrp + 1);
		p[2] = *(itrp + 2);
		initalize();
	}
	bool operator < (hand &h)const
	{
		if (rk == h.rk)
			return biggest < h.biggest;
		else
			return rk < h.rk;
		//���չ����ȱȽ����ͣ��ٱȽ������
	}
};


