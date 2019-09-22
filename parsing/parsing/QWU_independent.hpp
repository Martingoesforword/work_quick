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
	bool isOnClick = false;
	string onclick_name;
	bool isOnToolTips = false;
	string ontooltips_name;
	bool isOnScrollChange = false;
	string onscrollchange_name;
	bool isOnMove = false;
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
		indep.isOnMove = false;
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
		if (indeps[i].isOnClick)
		{
			out << "\t" << "InitControl(this"
				<< ", " << indeps[i].name
				<< ", " << indeps[i].parentname
				<< ", " << "L\"" << indeps[i].idname << "\""
				<< ", " << "SetPressFunc(&" << globleclassname << "::" << indeps[i].onclick_name << "));"
				<< endl; 
		}
		else
		{
			out << "\t" << "InitControl(this"
				<< ", " << indeps[i].name
				<< ", " << indeps[i].parentname
				<< ", " << "L\"" << indeps[i].idname << "\");"
				<< endl;

			if (indeps[i].isOnScrollChange)
			{
				out << "\t" << indeps[i].name
					<< "->" << "SetPosFunEx("
					<< indeps[i].onscrollchange_name
					<< ", " << "this);"
					<< endl;
				out << "\t" << indeps[i].name
					<< "->" << "SetPos(0);"
					<< endl;
			}  
		}
		
	
		
	}
}
string get_onBtnFun_declare_without_semicolon(string onclick_name, string globleclassname)
{
	if(globleclassname.empty())
		return  onclick_name + "(H3D_CLIENT::IUIWnd* wnd)";
	return onclick_name + "(H3D_CLIENT::IUIWnd* wnd)";
}
void print_onBtnFun_declare(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//实现将所有onbtn函数声明输出::不需要加结尾的分号，可重用于定义部分
		//类似void CUIAmusementParkHelp::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
		if (indeps[i].isOnClick)
		{
			out << "\t"<<"void " << get_onBtnFun_declare_without_semicolon(indeps[i].onclick_name, globleclassname)<<";" << endl;
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
			out << "void " << globleclassname <<"::"<< get_onBtnFun_declare_without_semicolon(indeps[i].onclick_name, globleclassname) << endl;
			out << "{" << endl;
			out << "\t" <<"//这里写下你的代码"<< endl;
			out << "}" << endl;
		}
	}
}


string get_onToolTips_declare_without_semicolon(string ontooltips_name, string globleclassname)
{
	if(globleclassname.empty())
		return  ontooltips_name + "(H3D_CLIENT::IUIWnd* wnd)";
	return  ontooltips_name + "(H3D_CLIENT::IUIWnd* wnd)";
}
void print_onToolTips_declare(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{ 
		if (indeps[i].isOnToolTips)
		{
			out << "\tvoid" << get_onToolTips_declare_without_semicolon(indeps[i].ontooltips_name, globleclassname) << ";" << endl;
		}
	}
}
void print_onToolTips_def(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{ 
		if (indeps[i].isOnToolTips)
		{
			out << "void " << globleclassname << "::"<<get_onBtnFun_declare_without_semicolon(indeps[i].ontooltips_name, globleclassname) << endl;
			out << "{" << endl;
			out << "\t" << "//这里写下你的代码" << endl;
			out << "}" << endl;
		}
	}
}
string get_onScroll_declare_without_semicolon(string onscroll_name)
{
	 
	return  onscroll_name + "(H3D_CLIENT::IUIWnd* wnd, int mode, int pos, void* ptrThis)";
	 
}
void print_onScroll_declare(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		if (indeps[i].isOnScrollChange)
		{
			out << "\tstatic void " << get_onScroll_declare_without_semicolon(indeps[i].onscrollchange_name) << ";" << endl;
		}
	}
}
void print_onScroll_def(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		if (indeps[i].isOnScrollChange)
		{
			out << "void " << globleclassname << "::" <<get_onScroll_declare_without_semicolon(indeps[i].onscrollchange_name) << endl;
			out << "{" << endl;
			
			out << "\tCUI" << globleclassname << "* pthis = static_cast<" << globleclassname << "*>(ptrThis);" << endl;
			out << "\tif(!pthis){ return; }" << endl;
			out << "\tpthis->getClientHall()->GetUIHall()->RefreshScrollBarPos(pthis->" << indeps[i].name << ", mode, pos, pthis->m_list_start" << ", pthis->" << "m_listContentDataArray.size(), MAX_LIST_CONTENT_CONTROL_SIZE);" << endl;
			out << "\tpthis->RefreshList(); "<< endl;
			out << "}" << endl;
		}
	}
}
