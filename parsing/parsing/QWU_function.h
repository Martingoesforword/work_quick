#pragma once
#include "QWU_include.h"
#include "QWU_enum.h"
//�ж��Ƿ����б��� ����wnd_list_XXXX��ʽ
bool is_listWnd(string name);

//����ǰ׺��ÿؼ��� st_title -> StaticText
string analysis_control_name(string id);

//���ݿؼ������ָ�붨�������� StaticText-> H3D_CLIENT::IUIStaticText*
string analysis_ptr_type(string id);

//���ݿؼ������ָ�붨��������������ǰ׺ StaticText-> st
string analysis_code_prefix(string id);

//������wnd_amusement_park -> AmusementPark
//Ҫ�󣺽�β����Ϊ_
string formal_toHump_deleteFirstOne(string hname);

//������wnd_amusement_park -> WND_AMUSEMENT_PARK
//Ҫ�󣺽�β����Ϊ_
string formal_allUp(string hname);

//������wnd_amusement_park -> WndAmusementPark
//Ҫ�󣺽�β����Ϊ_
string formal_toHump(string hname);

//������btn_close -> close
string formal_deleteFirstOne(string id);

//ȡ_���һ���ĺ��沿��
//����wnd_list_person -> person
string formal_saveLast(string id);
 
bool is_listWnd(string name)
{
	if (name.length() > 8 && name.substr(0, 8) == "wnd_list") return true;
	else return false;
} 

string analysis_control_name(string id)
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
 
string analysis_ptr_type(string id)
{ 
	if (id == H9D_BTN_CLASS) return H9D_BTN;
	if (id == H9D_WND_CLASS) return H9D_WND;
	if (id == H9D_ST_CLASS) return H9D_ST;
	if (id == H9D_SCR_CLASS) return H9D_SCR;
	if (id == H9D_IMG_CLASS) return H9D_IMG;
	if (id == H9D_CHK_CLASS) return H9D_CHK;
	if (id == H9D_EDBX_CLASS) return H9D_EDBX;
	if (id == H9D_EFCT_CLASS) return H9D_EFCT;
	if (id == H9D_PRCCBR_CLASS) return H9D_PRCCBR;
	return "";
}

string analysis_code_prefix(string id)
{
	if (id == H9D_BTN_CLASS) return H9D_BTN_CODE;
	if (id == H9D_WND_CLASS) return H9D_WND_CODE;
	if (id == H9D_ST_CLASS) return H9D_ST_CODE;
	if (id == H9D_SCR_CLASS) return H9D_SCR_CODE;
	if (id == H9D_IMG_CLASS) return H9D_IMG_CODE;
	if (id == H9D_CHK_CLASS) return H9D_CHK_CODE;
	if (id == H9D_EDBX_CLASS) return H9D_EDBX_CODE;
	if (id == H9D_EFCT_CLASS) return H9D_EFCT_CODE;
	if (id == H9D_PRCCBR_CLASS) return H9D_PRCCBR_CODE;
	return "";
}



string formal_toHump_deleteFirstOne(string hname)
{
	string right_str = formal_deleteFirstOne(hname);
	string result = formal_toHump(right_str);
	 
	return result;
} 

string formal_allUp(string hname)
{
	string one = hname;
	string two = "";
	for (size_t i = 0; i < one.size(); i++)
	{
		if (one[i] != '_')
		{
			two.push_back(one[i]-32);
		} 
		else
		{
			two.push_back(one[i]);
		}
	}
	return two;
}
 
string formal_toHump(string hname)
{
	string one = hname;
	string two = "";
	two.push_back(one[0] - 32);
	for (size_t i = 1; i < one.size(); i++)
	{
		if (one[i] != '_')
		{
			two.push_back(one[i]);
		}
		else
		{
			i += 1;
			two.push_back(one[i] - 32);
		}
	}
	return two;
}
 
string formal_deleteFirstOne(string id)
{
	if (id.empty()) return "";
	if (id.find_first_of("_") == string::npos) return "";
	string ret = id.substr(id.find_first_of("_") + 1, id.size());
	return ret;
}
 
string formal_saveLast(string id)
{
	return id.substr(id.find_last_of("_") + 1, id.size());
}