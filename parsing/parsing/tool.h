#pragma once
#include "tool_includeHelper.h"
#include "tool_staticText.h"

// id:list_XXXX
bool is_list_token(string name) {
	if (name.size() > 4 
		&&name[0] == 'l'
		&& name[1] == 'i'
		&& name[2] == 's'
		&& name[3] == 't'
		)
		return true;
	else return false;
}
// button --- id:btnF__XXXX
bool is_callback_fun_token(string name) {
	if (name.size() > 4 
		&& name[0] == 'b'
		&& name[1] == 't'
		&& name[2] == 'b'
		&& name[3] == 'F'
		)
		return true;
	else return false;
}

string returnType(string id)
{
	string before = id.substr(0, id.find_first_of("_"));
	if (before == H9D_BTN_PREFIX) return H9D_BTN_CLASS;
	if (before == H9D_WND_PREFIX) return H9D_WND_CLASS;
	if (before == H9D_ST_PREFIX) return H9D_ST_CLASS;
	if (before == H9D_SCR_PREFIX) return H9D_SCR_CLASS;
	if (before == H9D_IMG_PREFIX) return H9D_IMG_CLASS;
	if (before == H9D_CHK_PREFIX) return H9D_CHK_CLASS;
	if (before == H9D_EDBX_PREFIX) return H9D_EDBX_CLASS;
	if (before == H9D_EFCT_PREFIX) return H9D_EFCT_CLASS;
	if (before == H9D_PRCCBR_PREFIX) return H9D_PRCCBR_CLASS;
	return "";
}

string returnOutputType(string id)
{
	string before = id.substr(0, id.find_first_of("_"));
	if (before == H9D_BTN_CLASS) return H9D_BTN;
	if (before == H9D_WND_CLASS) return H9D_WND;
	if (before == H9D_ST_CLASS) return H9D_ST;
	if (before == H9D_SCR_CLASS) return H9D_SCR;
	if (before == H9D_IMG_CLASS) return H9D_IMG;
	if (before == H9D_CHK_CLASS) return H9D_CHK;
	if (before == H9D_EDBX_CLASS) return H9D_EDBX;
	if (before == H9D_EFCT_CLASS) return H9D_EFCT;
	if (before == H9D_PRCCBR_CLASS) return H9D_PRCCBR;
	return "";
}

//������wnd_amusement_parkת��ΪUIAmusementPark
//Ҫ�󣺽�β����Ϊ_
string formalIfdef(string hname)
{
	string one = hname.substr(hname.find_first_of("_"), hname.size());
	string two = "";
	for (int i = 0; i < one.size(); i++)
	{
		if (one[i] != '_')
		{
			two.push_back(one[i]);
		}
		else
		{
			i += 1;
			two.push_back(one[i] - 32);
			i += 1;
		}
	}
	return two;
}

//ʵ��
//������btn_closeת��Ϊclose
string formalId(string id)
{
	string ret = id.substr(id.find_first_of("_") + 1, id.size());
	return ret;
}

//ȡ_���һ���ĺ��沿��
//����wnd_list_person ȡ��person
string formalListName(string id)
{
	return id.substr(id.find_last_of("_") + 1, id.size());
}