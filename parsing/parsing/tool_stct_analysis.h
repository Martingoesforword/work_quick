#pragma once
#include "tool_includeHelper.h"
#include "tool_xml_get.h"
#include "tool_indepcontrol.h"
#include "tool.h"
#include "tool_stct.h"



//判断是否是列表窗口
bool isListWnd(string name)
{
	if (name.substr(0, 8) == "wnd_list") return true;
	else return false;
}

//将wnd_amusementPark和wnd_listTable合并为wnd_amusementPark_listTable
string conbineWndTree(string comeinParent, string nowWnd)
{
	return comeinParent + formalId(nowWnd);
}

bool isEmpty(stct_window& window)
{
	return window.cons.empty();
}

//列表窗口需要分析出来结构体数组及其大小
//node表示当前的list窗口，parentconbinename表示wnd_amusementPark_list_person
void analysis_listWindow(string parentconbinename
	, stct_window& node) 
{
	vector<stct_item> items;

	vector<stct_window>& cons = node.cons[0].cons;
	for (size_t i = 0; i < cons.size(); i++)
	{
		stct_item content;
		content.type = returnOutputType( returnType(cons[i].id));
		content.name = cons[i].id;
		items.push_back(content);
	}

	//生成结构体定义列表
	addlist(items, formalListName(parentconbinename), node.cons.size());
	//生成结构体
}

void analysis_indep(string parentconbinename
	, stct_window& node)
{
	vector<stct_window>& xcons = node.cons;
	for (size_t i = 0; i < xcons.size(); i++)
	{
		string type = returnType(xcons[i].id);

		if (type != "")
		{
			add(type, xcons[i].id, parentconbinename);
			if (type == H9D_WND_CLASS)
			{ 
				//这里需要判断是列表窗口还是普通窗口
				//列表窗口类似wnd_list_persons
				if (isListWnd(xcons[i].id))
				{
					//列表窗口执行以下
					analysis_listWindow(conbineWndTree(parentconbinename, xcons[i].id), xcons[i]);
				}
				else
				{
					//普通窗口执行以下
					analysis_indep(conbineWndTree(parentconbinename, xcons[i].id), xcons[i]);
				}
				

			}
		} 
	}
}

//分析独立控件
void analysis_stct_window_indep(stct_window& window)
{
	string comeinParent = window.id;
	//顶层窗口在最终输出时再添加

	//以下添加独立的窗口（非列表）
	analysis_indep(comeinParent, window);
	 
}