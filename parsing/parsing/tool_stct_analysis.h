#pragma once
#include "tool_includeHelper.h"
#include "tool_xml_get.h"
#include "tool_indepcontrol.h"
#include "tool.h"
#include "tool_stct.h"



//�ж��Ƿ����б���
bool isListWnd(string name)
{
	if (name.substr(0, 8) == "wnd_list") return true;
	else return false;
}

//��wnd_amusementPark��wnd_listTable�ϲ�Ϊwnd_amusementPark_listTable
string conbineWndTree(string comeinParent, string nowWnd)
{
	return comeinParent + formalId(nowWnd);
}

bool isEmpty(stct_window& window)
{
	return window.cons.empty();
}

//�б�����Ҫ���������ṹ�����鼰���С
//node��ʾ��ǰ��list���ڣ�parentconbinename��ʾwnd_amusementPark_list_person
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

	//���ɽṹ�嶨���б�
	addlist(items, formalListName(parentconbinename), node.cons.size());
	//���ɽṹ��
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
				//������Ҫ�ж����б��ڻ�����ͨ����
				//�б�������wnd_list_persons
				if (isListWnd(xcons[i].id))
				{
					//�б���ִ������
					analysis_listWindow(conbineWndTree(parentconbinename, xcons[i].id), xcons[i]);
				}
				else
				{
					//��ͨ����ִ������
					analysis_indep(conbineWndTree(parentconbinename, xcons[i].id), xcons[i]);
				}
				

			}
		} 
	}
}

//���������ؼ�
void analysis_stct_window_indep(stct_window& window)
{
	string comeinParent = window.id;
	//���㴰�����������ʱ�����

	//������Ӷ����Ĵ��ڣ����б�
	analysis_indep(comeinParent, window);
	 
}