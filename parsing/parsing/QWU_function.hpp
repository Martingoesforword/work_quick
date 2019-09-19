#pragma once
#include "QWU_include.h"
#include "QWU_enum.h"

//判断是否是列表窗口
bool isListWnd(string name)
{
	if (name.length > 8 && name.substr(0, 8) == "wnd_list") return true;
	else return false;
} 
 //根据前缀获得控件名
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


//根据控件名获得指针定义类型名
string analysis_ptr_type(string id)
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

//将类似wnd_amusement_park转化为AmusementPark
//要求：结尾不可为_
string formalFirstUpDeleteOne(string hname)
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
		}
	}
	return two;
}

//将类似wnd_amusement_park转化为WND_AMUSEMENT_PARK
//要求：结尾不可为_
string formalAllUp(string hname)
{
	string one = hname;
	string two = "";
	for (int i = 0; i < one.size(); i++)
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

//将类似wnd_amusement_park转化为WndAmusementPark
//要求：结尾不可为_
string formalFirstUp(string hname)
{
	string one = hname;
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
		}
	}
	return two;
}

//实现
//将类似btn_close转化为close
string formalDeleteOne(string id)
{
	if (id.empty()) return "";
	string ret = id.substr(id.find_first_of("_") + 1, id.size());
	return ret;
}

//取_最后一个的后面部分
//类似wnd_list_person 取到person
string formalListName(string id)
{
	return id.substr(id.find_last_of("_") + 1, id.size());
}