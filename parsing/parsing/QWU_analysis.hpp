#pragma once
#include "QWU_include.h"
#include "QWU_xml.hpp"
#include "QWU_independent.hpp"
#include "QWU_function.h"
#include "QWU_struct.h"

//������ں���
void analysis_main(stct_window& window);

//��wnd_amusementPark��wnd_listTable�ϲ�Ϊwnd_amusementPark_listTable
string conbineWndTree(string comeinParent, string nowWnd);

//�ж�window����Ԫ�ؼ����Ƿ�Ϊ��
bool isEmpty(stct_window& window);

//�б�����Ҫ���������ṹ�����鼰���С
//node��ʾ��ǰ��list���ڣ�parentconbinename��ʾwnd_amusementPark_list_person
void analysis_listWindow(string parentconbinename, stct_window& node);

//������������
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

	//���ɽṹ�嶨���б�
	add_list_vector(items, formal_saveLast(parentconbinename), node.cons.size());
	//���ɽṹ��
}

//������������
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
				//������Ҫ�ж����б��ڻ�����ͨ����
				//�б�������wnd_list_persons
				if (is_listWnd(xcons[i].id))
				{
					add_indep_control(type, xcons[i].id, parentconbinename);
					//�б���ִ������
					analysis_listWindow(xcons[i].id, xcons[i]);
					
				}
				else
				{
					add_indep_control(type, xcons[i].id, parentconbinename);
					//��ͨ����ִ������
					analysis_wnd(conbineWndTree(parentconbinename, xcons[i].id), xcons[i]);

				}
			}
			 
		} 
	}
}

//������ں���
void analysis_main(stct_window& window)
{ 
	//���㴰�����������ʱ�����

	//������Ӷ����Ĵ��ڣ����б�
	analysis_wnd(window.id, window);
	 
}