#pragma once
#include "QWU_include.h"
#include "QWU_xml.hpp"
#include "QWU_independent.hpp"
#include "QWU_function.h"
#include "QWU_struct.h"

//分析入口函数
void analysis_main(stct_window& window);

//将wnd_amusementPark和wnd_listTable合并为wnd_amusementPark_listTable
string conbineWndTree(string comeinParent, string nowWnd);

//判断window的子元素集合是否为空
bool isEmpty(stct_window& window);

//列表窗口需要分析出来结构体数组及其大小
//node表示当前的list窗口，parentconbinename表示wnd_amusementPark_list_person
void analysis_listWindow(string parentconbinename, stct_window& node);

//分析整个窗口
void analysis_wnd(string parentconbinename, stct_window& node);
  


string conbineWndTree(string comeinParent, string nowWnd)
{
	if(comeinParent.empty()) return formal_deleteFirstOne(nowWnd);
	else return comeinParent +"_"+ formal_deleteFirstOne(nowWnd);
}

bool isEmpty(stct_window& window)
{
	return window.cons.empty();
}

void analysis_listWindow(string parentconbinename
	, stct_window& node) 
{
	vector<stct_item_def> items;

	vector<stct_window>& cons = node.cons[0].cons;
	for (size_t i = 0; i < cons.size(); i++)
	{
		stct_item_def content;
		content.type = analysis_ptr_type( analysis_control_name(cons[i].id));
		content.name = cons[i].id;
		items.push_back(content);
	}

	//生成结构体定义列表
	add_list_vector(items, formal_saveLast(parentconbinename), node.cons.size());
	//生成结构体
}

//分析整个窗口
void analysis_wnd(string parentconbinename
	, stct_window& node)
{
	vector<stct_window>& xcons = node.cons;


	for (size_t i = 0; i < xcons.size(); i++)
	{
		string type = analysis_control_name(xcons[i].id);

		if (type != "")
		{
			if (type == H9D_BTN_CLASS)
			{
				add_indep_control(type, xcons[i].id, parentconbinename,true);
			}
			else if(type != H9D_WND_CLASS)
			{
				add_indep_control(type, xcons[i].id, parentconbinename); 
			}
			else 
			{
				//这里需要判断是列表窗口还是普通窗口
				//列表窗口类似wnd_list_persons
				if (is_listWnd(xcons[i].id))
				{
					add_indep_control(type, xcons[i].id, parentconbinename);
					//列表窗口执行以下
					analysis_listWindow(xcons[i].id, xcons[i]);
					
				}
				else
				{
					add_indep_control(type, xcons[i].id, parentconbinename);
					//普通窗口执行以下
					analysis_wnd(conbineWndTree(parentconbinename, xcons[i].id), xcons[i]);

				}
			}
			 
		} 
	}
}

//分析入口函数
void analysis_main(stct_window& window)
{ 
	//顶层窗口在最终输出时再添加

	//以下添加独立的窗口（非列表）
	analysis_wnd(window.id, window);
	 
}