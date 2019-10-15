#pragma once
#include <vector>
#include <string>
#include "ui.h"

using namespace std;
class view_base
{
public:
	IUIWnd*   m_wnd_item;
};
template<typename control_struct, typename data_struct>
class ScrollAgent
{
private:
	vector< control_struct>& cons;
	vector< data_struct>& datas;
	void(*func)(control_struct, data_struct);
	I_ScrollBar_Adv* scr;

	int control_index;
public:
	ScrollAgent(I_ScrollBar_Adv* scrs, vector< control_struct>& conss, vector<data_struct>& datass, void(*funcc)(control_struct, data_struct))
		:cons(conss), datas(datass), func(funcc), control_index(0), scr(scrs) {}
	void update()
	{
		for (int i = 0; i < cons.size(); i++)
		{
			cons[i].m_wnd_item->ShowWindow(false);
		}

		//滚动条m_scr_content_friend刷新
		int maxPageNum = (datas.size() + cons.size() - 1) / cons.size();
		if (maxPageNum == 1 || maxPageNum == 0) scr->ShowWindow(false);
		else scr->ShowWindow(true);

		//列表m_s_friend_control_arr刷新
		auto pos = datas.begin();
		std::advance(pos, control_index);

		for (int i = 0; pos != datas.end() && i < control_index; ++pos)
		{
			func(cons[i], datas[control_index + i]);
			i++;
		}
	}
	void reset()
	{
		control_index = 0;
	}
	void review()
	{
		control_index = 0;
	}
};


