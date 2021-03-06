#pragma once
#include "QWU_include.h"
#include "QWU_enum.h" 
#include <stdarg.h>

 
class print_notice {
private:

	ofstream& out;
public:
	static int NUM;
	print_notice(ofstream& out) :out(out)
	{
		OUTPUT(0, 1);
		OUTPUT(0,) << "<<<<<<<< 请添加、修改代码 <<<<<<<< NO."<< NUM << endl;
	}
	~print_notice()
	{ 
		OUTPUT(0, ) << "========  请添加、修改代码  ======== NO." << NUM << "\n"<<endl;
		NUM++;
	} 
};
int print_notice::NUM = 1;
//判断是否是列表窗口 类似wnd_list_XXXX格式
bool is_listWnd(string name);

//根据前缀获得控件名 st_title -> StaticText
string analysis_control_name(string id);

//根据控件名获得指针定义类型名 StaticText-> H3D_CLIENT::IUIStaticText*
string analysis_ptr_type(string id);

//根据控件名获得指针定义类型名程序用前缀 StaticText-> st
string analysis_code_prefix(string id);

//将类似wnd_amusement_park -> AmusementPark
//要求：结尾不可为_
string formal_toHump_deleteFirstOne(string hname);

//将类似wnd_amusement_park -> WND_AMUSEMENT_PARK
//要求：结尾不可为_
string formal_allUp(string hname);

//将类似wnd_amusement_park -> WndAmusementPark
//要求：结尾不可为_
string formal_toHump(string hname);

//将类似btn_close -> close
string formal_deleteFirstOne(string id);

//取_最后一个的后面部分
//类似wnd_list_person -> person
string formal_saveLast(string id);

//将wnd_amusementPark和wnd_listTable合并为wnd_amusementPark_listTable
string conbine_context(string comeinParent, string nowWnd);

//将wnd_amusementPark和btn_close合并为btn_amusementPark_close
string conbine_context_not_wnd(string comeinParent, string nowWnd);
 

//获得一个定义语句
string conbine_define(string type_name, string name);

bool is_listWnd(string name)
{
	if (name.length() > 8 && name.substr(0, 8) == "wnd_list") return true;
	else return false;
} 

string analysis_control_name(string id)
{ 
	string before = id.substr(0, id.find_first_of("_"));
	if (before == H3D_BTN_PREFIX) return H3D_BTN_CLASS;
	if (before == H3D_WND_PREFIX) return H3D_WND_CLASS;
	if (before == H3D_ST_PREFIX) return H3D_ST_CLASS;
	if (before == H3D_SCR_PREFIX) return H3D_SCR_CLASS;
	if (before == H3D_IMG_PREFIX) return H3D_IMG_CLASS;
	if (before == H3D_CHK_PREFIX) return H3D_CHK_CLASS;
	if (before == H3D_EDBX_PREFIX) return H3D_EDBX_CLASS;
	if (before == H3D_EFCT_PREFIX) return H3D_EFCT_CLASS;
	if (before == H3D_PRCCBR_PREFIX) return H3D_PRCCBR_CLASS;
	return "";
}

string conbine_context(string context_name, string nowWnd)
{
	if (context_name.empty()) return formal_deleteFirstOne(nowWnd);
	else return context_name + "_" + formal_deleteFirstOne(nowWnd);
}
string conbine_context_not_wnd(string context_name, string nowWnd)
{
	if (context_name.empty()) return formal_deleteFirstOne(context_name);
	else return nowWnd + "_" + formal_deleteFirstOne(context_name);
} 
string analysis_ptr_type(string id)
{ 
	if (id == H3D_BTN_CLASS) return H3D_BTN;
	if (id == H3D_WND_CLASS) return H3D_WND;
	if (id == H3D_ST_CLASS) return H3D_ST;
	if (id == H3D_SCR_CLASS) return H3D_SCR;
	if (id == H3D_IMG_CLASS) return H3D_IMG;
	if (id == H3D_CHK_CLASS) return H3D_CHK;
	if (id == H3D_EDBX_CLASS) return H3D_EDBX;
	if (id == H3D_EFCT_CLASS) return H3D_EFCT;
	if (id == H3D_PRCCBR_CLASS) return H3D_PRCCBR;
	return "";
}

string analysis_code_prefix(string id)
{
	if (id == H3D_BTN_CLASS) return H3D_BTN_CODE;
	if (id == H3D_WND_CLASS) return H3D_WND_CODE;
	if (id == H3D_ST_CLASS) return H3D_ST_CODE;
	if (id == H3D_SCR_CLASS) return H3D_SCR_CODE;
	if (id == H3D_IMG_CLASS) return H3D_IMG_CODE;
	if (id == H3D_CHK_CLASS) return H3D_CHK_CODE;
	if (id == H3D_EDBX_CLASS) return H3D_EDBX_CODE;
	if (id == H3D_EFCT_CLASS) return H3D_EFCT_CODE;
	if (id == H3D_PRCCBR_CLASS) return H3D_PRCCBR_CODE;
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
 
string conbine_define(string type_name, string name)
{
	return type_name + DEFINE_SPACE + name+";";
}
 
string conbine_func_define_call(string name)
{
	string res = name + "()"; 

	return res;

}
string conbine_func_define_call(string name, string parameter1,...)
{
	string res = name + "(";

	va_list arg_ptr;
	 
	string tempValue;
	 
	res += parameter1;
	return res;
	va_start(arg_ptr, parameter1);
	do
	{ 
		tempValue = va_arg(arg_ptr, string);  
		res += PARAMETER_DIVIDE_STYLE+ tempValue;
	} while (1);

	va_end(arg_ptr);
	res += ")";
	return res;
		 
}