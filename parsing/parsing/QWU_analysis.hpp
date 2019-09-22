#pragma once
#include "QWU_include.h"
#include "QWU_xml.hpp"
#include "QWU_independent.hpp"
#include "QWU_function.h"
#include "QWU_struct.hpp"

//分析入口函数
void analysis_main(stct_window& window);

//将wnd_amusementPark和wnd_listTable合并为wnd_amusementPark_listTable
string conbine_context(string comeinParent, string nowWnd);

//判断window的子元素集合是否为空
bool isEmpty(stct_window& window);

//列表窗口需要分析出来结构体数组及其大小
//node表示当前的list窗口，parentconbinename表示wnd_amusementPark_list_person
void analysis_listWindow(stct_window& node, string context_id);

//分析整个窗口
void analysis_wnd(string parentconbinename, stct_window& node, bool isTop);
  


string conbine_context(string context_name, string nowWnd)
{
	if(context_name.empty()) return formal_deleteFirstOne(nowWnd);
	else return context_name +"_"+ formal_deleteFirstOne(nowWnd);
}

bool isEmpty(stct_window& window)
{
	return window.subs.empty();
}

void analysis_listWindow(stct_window& node, string context_id) 
{
	string parentconbinename = node.id;
	vector<stct_item_def> items;

	vector<stct_window>& cons = node.subs[0].subs;
	for (size_t i = 0; i < cons.size(); i++)
	{
		stct_item_def content;
		content.type = analysis_ptr_type( analysis_control_name(cons[i].id));
		content.name = cons[i].id;
		items.push_back(content);
	}

	//生成结构体定义列表
	add_list_vector(items, formal_saveLast(parentconbinename), node.subs.size(), context_id);
	//生成结构体
}

//分析整个窗口
void analysis_wnd(string context_name
	, stct_window& node, bool isTop)
{
	vector<stct_window>& subs = node.subs;
	 
	 
	for (size_t i = 0; i < subs.size(); i++)
	{
		string type = analysis_control_name(subs[i].id);

		if (type != "")
		{
			if (type == H9D_BTN_CLASS)
			{
				vector<string> func_list = { H9D_HAS_ONCLICK };

				if(isTop) add_indep_control(type, subs[i].id, "wnd", true, func_list);
				else add_indep_control(type, subs[i].id, context_name,true, func_list);
			}
			else if(type == H9D_SCR_CLASS)
			{
				vector<string> func_list = { H9D_HAS_ONSCROLLCHANGE };
				if (isTop) add_indep_control(type, subs[i].id, "wnd", true, func_list);
				else add_indep_control(type, subs[i].id, context_name, true, func_list);
			}
			else if(type != H9D_WND_CLASS)
			{
				if (isTop) add_indep_control(type, subs[i].id, "wnd");
				else add_indep_control(type, subs[i].id, context_name);
			}
			else 
			{
				if (isTop) add_indep_control(type, subs[i].id, "wnd");
				else add_indep_control(type, subs[i].id, context_name);

				//这里需要判断是列表窗口还是普通窗口
				//列表窗口类似wnd_list_persons
				if (is_listWnd(subs[i].id))
				{ 
					//列表窗口执行以下
					analysis_listWindow(subs[i],  conbine_context(context_name, subs[i].id) );
				}
				else
				{ 
					//普通窗口执行以下
					if (isTop) analysis_wnd(conbine_context("wnd", subs[i].id), subs[i], false);
					else analysis_wnd(conbine_context(context_name, subs[i].id), subs[i], false);
					

				}
			}
			 
		} 
	}
}

//分析入口函数
void analysis_main(stct_window& window)
{   
	//以下添加独立的窗口（非列表窗口）
	analysis_wnd(window.id, window, true);
	 
}