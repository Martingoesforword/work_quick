#pragma once
#include "QWU_include.h" 
#include "QWU_enum.h"
#include "QWU_function.h"
 

struct stct_indepinfo
{ 
	string type;	 
	string name;
	string idname;
	string parentname; 
	bool isOnClick;
	string onclick_name;
	bool isOnToolTips;
	string ontooltips_name;
	bool isOnScrollChange;
	string onscrollchange_name;
	bool isOnMove;
	string onmove_name;
};

vector< stct_indepinfo> indeps; 

//parentconbinename为类似 （wnd_amusement_park_list） ,表示window树结构
void add_indep_control(string type, string id, string context_name, bool has_func = false, vector<string> func_list = {})
{
	string p = "";
	if (context_name.find_first_of("_") != string::npos) p = "_";

	stct_indepinfo indep;
	indep.type = analysis_ptr_type(type);
	indep.idname = id;
	indep.name = analysis_code_prefix(type) + formal_deleteFirstOne(context_name) + p + formal_deleteFirstOne(id);
	indep.parentname = "m_" + context_name;
	
	if (has_func)
	{
		for (size_t i = 0; i < func_list.size(); i++)
		{
			string func_type = func_list[i];

			if (func_type == H9D_HAS_ONCLICK)
			{
				indep.isOnClick = true;
				indep.onclick_name = "onBtn" + formal_toHump_deleteFirstOne(id);
			}
			else if (func_type == H9D_HAS_ONTOOOLTIPS)
			{
				indep.isOnToolTips = true;
				indep.ontooltips_name = "onTips" + formal_toHump_deleteFirstOne(id);
			}
			else if (func_type == H9D_HAS_ONMOVE)
			{
				indep.isOnMove = true;
				indep.onmove_name = "onMove" + formal_toHump_deleteFirstOne(id);
			}
			else if (func_type == H9D_HAS_ONSCROLLCHANGE)
			{
				indep.isOnScrollChange = true;
				indep.onscrollchange_name = "onScroll" + formal_toHump_deleteFirstOne(id);
			}
		} 
	}
	else
	{
		indep.isOnClick = false;
		indep.isOnScrollChange = false;
		indep.isOnToolTips = false;
	}
	
	indeps.push_back(indep);
	 
}

void print_memberdef(ofstream& out)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//实现将所有定义输出 
		out << "\t" << indeps[i].type << "   " << indeps[i].name << ";" << endl;
	}
}
void print_initdef(ofstream& out,string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//实现将所有初始化输出
		//类似InitControl(this, m_richedit_content, m_wnd, L"rt_tips");
		//InitControl(this, m_btn_close, m_wnd, L"btn_close", SetPressFunc(&CUIAmusementParkHelp::OnBtnClose));
		if (!indeps[i].isOnClick)
		{
			out << "\t" << "InitControl(this"
				<< ", " << indeps[i].name
				<< ", " << indeps[i].parentname
				<< ", " << "L\"" << indeps[i].idname << "\");"
				<< endl;
		}
		else
		{
			out << "\t" << "InitControl(this"
				<< ", " << indeps[i].name
				<< ", " << indeps[i].parentname
				<< ", " << "L\"" << indeps[i].idname << "\""
				<<", "<<"SetPressFunc(&"<<globleclassname<<"::"<<indeps[i].onclick_name<<"));"
				<< endl;
		}
	
		
	}
}
string get_onBtnFun_declare_without_semicolon(string onclick_name, string globleclassname)
{
	return "void " + globleclassname + "::" + onclick_name + "(H3D_CLIENT::IUIWnd* wnd)";
}
void print_onBtnFun_declare(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//实现将所有onbtn函数声明输出::不需要加结尾的分号，可重用于定义部分
		//类似void CUIAmusementParkHelp::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
		if (indeps[i].isOnClick)
		{
			out << "\t" << get_onBtnFun_declare_without_semicolon(indeps[i].onclick_name, globleclassname)<<";" << endl;
		}
	}
}
void print_onBtnFun_def(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//实现将所有onbtn函数声明输出::不需要加结尾的分号，可重用于定义部分
		//类似void CUIAmusementParkHelp::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
		if (indeps[i].isOnClick)
		{
			out << get_onBtnFun_declare_without_semicolon(indeps[i].onclick_name, globleclassname) << endl;
			out << "{" << endl;
			out << "\t" <<"//这里写下你的代码"<< endl;
			out << "}" << endl;
		}
	}
}


string get_onToolTips_declare_without_semicolon(string ontooltips_name, string globleclassname)
{
	return "void " + globleclassname + "::" + ontooltips_name + "(H3D_CLIENT::IUIWnd* wnd)";
}
void print_onToolTips_declare(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{ 
		if (indeps[i].isOnToolTips)
		{
			out << "\t" << get_onToolTips_declare_without_semicolon(indeps[i].ontooltips_name, globleclassname) << ";" << endl;
		}
	}
}
void print_onToolTips_def(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{ 
		if (indeps[i].isOnToolTips)
		{
			out << get_onBtnFun_declare_without_semicolon(indeps[i].ontooltips_name, globleclassname) << endl;
			out << "{" << endl;
			out << "\t" << "//这里写下你的代码" << endl;
			out << "}" << endl;
		}
	}
}
