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
	bool Isonclick;
	string onclickname;
};

vector< stct_indepinfo> indeps; 

//parentconbinename为类似 （wnd_amusement_park_list） ,表示window树结构
void add_indep_control(string type, string id,string context_name,bool has_func = false)
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
		indep.Isonclick = true;
		indep.onclickname = "onBtn" + formal_toHump_deleteFirstOne(id);
	}
	else
	{
		indep.Isonclick = false;
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
		if (!indeps[i].Isonclick)
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
				<<", "<<"SetPressFunc(&"<<globleclassname<<"::"<<indeps[i].onclickname<<"));"
				<< endl;
		}
	
		
	}
}
void print_onBtnFun_declare(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//实现将所有onbtn函数声明输出::不需要加结尾的分号，可重用于定义部分
		//类似void CUIAmusementParkHelp::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
		if (indeps[i].Isonclick)
		{
			out << "\t" << "void " << globleclassname << "::" << indeps[i].onclickname
				<< "(H3D_CLIENT::IUIWnd* wnd);" << endl;
		}
	}
}
void print_onBtnFun_def(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//实现将所有onbtn函数声明输出::不需要加结尾的分号，可重用于定义部分
		//类似void CUIAmusementParkHelp::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
		if (indeps[i].Isonclick)
		{
			out << "void " << globleclassname << "::" << indeps[i].onclickname
				<< "(H3D_CLIENT::IUIWnd* wnd)" << endl;
			out << "{" << endl;
			out << "\t" <<"//这里写下你的代码"<< endl;
			out << "}" << endl;
		}
	}
}
