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
class ListUpdate
{
private:
	control_struct* cons;
	int length;
	vector< data_struct>& datas;
	int control_index;
	void(*func)(control_struct, data_struct);
	I_ScrollBar_Adv* scr;
public:
	ListUpdate(int cons_length, I_ScrollBar_Adv* scrs, control_struct* conss, vector<data_struct>& datass, void(*funcc)(control_struct, data_struct))
		:cons(conss), datas(datass), func(funcc), control_index(0), scr(scrs), length(cons_length)
	{

	}
	void update()
	{
		for (int i = 0; i < length; i++)
		{
			cons[i].m_wnd_item->ShowWindow(false);
		}

		//滚动条m_scr_content_friend刷新
		int maxPageNum = (datas.size() + length) / length;
		if (maxPageNum == 1 || maxPageNum == 0) scr->ShowWindow(false);
		else scr->ShowWindow(true);

		//列表m_s_friend_control_arr刷新
		auto pos = datas.begin();
		std::advance(pos, control_index);

		for (int i = 0; pos != datas.end() && i < length; ++pos)
		{
			func(cons[i], datas[control_index + i]);
			i++;
		}
	}

};


