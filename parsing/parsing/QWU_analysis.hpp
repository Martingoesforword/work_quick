#pragma once
#include "QWU_include.h"
#include "QWU_xml.hpp"
#include "QWU_independent.hpp"
#include "QWU_function.h"
#include "QWU_struct.hpp"

//������ں���
void analysis_main(stct_window& window);


//�ж�window����Ԫ�ؼ����Ƿ�Ϊ��
bool isEmpty(stct_window& window);

//�б�����Ҫ���������ṹ�����鼰���С
//node��ʾ��ǰ��list���ڣ�parentconbinename��ʾwnd_amusementPark_list_person
void analysis_listWindow(stct_window& node, string context_id);

//������������
void analysis_wnd(string parentconbinename, stct_window& node, bool isTop);
  



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

	//���ɽṹ�嶨���б�
	add_list_vector(items, formal_saveLast(parentconbinename), node.subs.size(), context_id);
	//���ɽṹ��
}

//������������
void analysis_wnd(string context_name
	, stct_window& node, bool isTop)
{
	vector<stct_window>& subs = node.subs;
	 
	 
	for (size_t i = 0; i < subs.size(); i++)
	{
		string type = analysis_control_name(subs[i].id);

		if (type != "")
		{
			if (type == H3D_BTN_CLASS)
			{
				vector<string> func_list = { H3D_HAS_ONCLICK };

				if(isTop) add_indep_control(type, subs[i].id, "stateWnd", true, func_list);
				else add_indep_control(type, subs[i].id, context_name,true, func_list);
			}
			else if(type == H3D_SCR_CLASS)
			{
				vector<string> func_list = { H3D_HAS_ONSCROLLCHANGE };
				if (isTop) add_indep_control(type, subs[i].id, "stateWnd", true, func_list);
				else add_unindep_scroll_control(type, subs, context_name,func_list);
			}
			else if(type != H3D_WND_CLASS)
			{
				if (isTop) add_indep_control(type, subs[i].id, "stateWnd");
				else add_indep_control(type, subs[i].id, context_name);
			}
			else 
			{
				if (isTop) add_indep_control(type, subs[i].id, "stateWnd");
				else add_indep_control(type, subs[i].id, context_name);

				//������Ҫ�ж����б��ڻ�����ͨ����
				//�б�������wnd_list_persons
				if (is_listWnd(subs[i].id))
				{ 
					//�б���ִ������
					analysis_listWindow(subs[i],  conbine_context(context_name, subs[i].id) );
				}
				else
				{ 
					//��ͨ����ִ������
					if (isTop) analysis_wnd(conbine_context("wnd", subs[i].id), subs[i], false);
					else analysis_wnd(conbine_context(context_name, subs[i].id), subs[i], false);
					

				}
			}
			 
		} 
	}
}

//������ں���
void analysis_main(stct_window& window)
{   
	//������Ӷ����Ĵ��ڣ����б��ڣ�
	analysis_wnd(window.id, window, true);
	 
}