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
	string list_name;
	string list_index_name;
	string list_refreshENUM_name;
	string list_refreshfunc_name;
	string list_control_arr_name;
	string list_data_arr_name;
	string max_name;

	bool isOnMove = false;
	string onmove_name;
};

vector< stct_indepinfo> indeps; 

//获取列表名
string find_list_name(vector< stct_window>& subs, string context_name);


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

			if (func_type == H3D_HAS_ONCLICK)
			{
				indep.isOnClick = true;
				indep.onclick_name = "onBtn" + formal_toHump_deleteFirstOne(id);
			}
			else if (func_type == H3D_HAS_ONTOOOLTIPS)
			{
				indep.isOnToolTips = true;
				indep.ontooltips_name = "onTips" + formal_toHump_deleteFirstOne(id);
			}
			else if (func_type == H3D_HAS_ONMOVE)
			{
				indep.isOnMove = true;
				indep.onmove_name = "onMove" + formal_toHump_deleteFirstOne(id);
			}
			else if (func_type == H3D_HAS_ONSCROLLCHANGE)
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
string find_list_scroll_name(vector< stct_window>& subs, string context_name)
{
	for (size_t i = 0; i < subs.size(); i++)
	{
		if (analysis_control_name(subs[i].id) == H3D_SCR_CLASS)
		{
			return conbine_context(context_name, subs[i].id);
		}
	}
	return "";
}
string find_list_index_name(vector< stct_window>& subs, string context_name) {
	//改变样式 m_wnd_content_friend --->  m_struct_friend_control_index
	string gdfgfdgdfg = find_list_name(subs, context_name);
	return string("m_struct_") + gdfgfdgdfg.substr(gdfgfdgdfg.find_last_of("_") + 1, gdfgfdgdfg.size()) + "_control_index";
} 
string find_list_refreshENUM_name(vector< stct_window>& subs, string context_name)
{
	
	string gdfgfdgdfg = find_list_name(subs, context_name);
	return formal_allUp(gdfgfdgdfg.substr(gdfgfdgdfg.find_last_of("_") + 1, gdfgfdgdfg.size()))  + "_LIST_RF";
}
string find_list_refreshfunction_name(vector< stct_window>& subs, string context_name)
{

	string gdfgfdgdfg = find_list_name(subs, context_name);
	return "refreshUI" + formal_toHump(gdfgfdgdfg.substr(gdfgfdgdfg.find_last_of("_") + 1, gdfgfdgdfg.size()))+"List";
}
string find_list_name(vector< stct_window>& subs, string context_name)
{
	for (size_t i = 0; i < subs.size(); i++)
	{
		if (is_listWnd(subs[i].id))
		{
			return conbine_context(context_name, subs[i].id);
		}
	}
	return "";
}
string find_max_name(vector< stct_window>& subs, string context_name)
{
	//这里的实现还有问题
	return "MAX_"+ formal_allUp(STCT_PREFIX) + formal_allUp(context_name) + "_NUM";
}
void add_unindep_scroll_control(string type, vector< stct_window>& subs, string context_name, vector<string> func_list = {})
{
	string p = "";
	if (context_name.find_first_of("_") != string::npos) p = "_";

	stct_indepinfo indep;
	indep.type = analysis_ptr_type(type);
	indep.idname = find_list_scroll_name(subs, context_name);
	indep.list_name = "m_"+find_list_name(subs, context_name);
	indep.list_index_name = find_list_index_name(subs, context_name);
	indep.list_refreshENUM_name = find_list_refreshENUM_name(subs, context_name);
	indep.list_refreshfunc_name = find_list_refreshfunction_name(subs, context_name);
	indep.max_name = find_max_name(subs, context_name);
	indep.name = "m_" + find_list_scroll_name(subs, context_name);
	indep.parentname = "m_" + context_name;

	indep.isOnScrollChange = true;
	indep.isOnClick = false;
	indep.isOnToolTips = false;
	indep.isOnMove = false;

	indep.onscrollchange_name = "onScroll" + formal_toHump(find_list_scroll_name(subs, context_name));
	
	
	 

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
	static int hadOutputComment = false;
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//实现将所有onbtn函数声明输出::不需要加结尾的分号，可重用于定义部分
		//类似void CUIAmusementParkHelp::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
		if (!hadOutputComment)
		{
			out_with_tnum("//on函数是H3DAPI中的函数，其本质是Data更新函数，需要调用相关数据更新函数进行修改",
				out,
				1);
			hadOutputComment = true;
		}
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
			out << "\t" << "//这里写下你的代码" << endl;
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
void print_onScroll_def_with_refresh(ofstream& out, string globleclassname)
{
	H3D_NOTICE____H3D_NOTICE
	for (size_t i = 0; i < indeps.size(); i++)
	{
		if (indeps[i].isOnScrollChange)
		{
			OUTWITH_0000000000000_Tab << "void " << globleclassname << "::" <<get_onScroll_declare_without_semicolon(indeps[i].onscrollchange_name) << endl;
			OUTWITH_0000000000000_Tab << "{" << endl;
			
			OUTWITH_0000000000000_Tab << globleclassname << "* pthis = static_cast<" << globleclassname << "*>(ptrThis);" << endl;
			OUTWITH_0000000000000_Tab << "\tif(!pthis){ return; }" << endl;
			OUTWITH_0000000000000_Tab << "\tpthis->getClientHall()->GetUIHall()->RefreshScrollBarPos(pthis->" << indeps[i].name << ", mode, pos, pthis->"
				<< indeps[i].list_index_name << ", pthis->" << indeps[i].list_name << ".size(), " << indeps[i].max_name << ");" << endl;
			OUTWITH_0000000000000_Tab << "\tpthis->"<<"refreshUI("+ indeps[i].list_refreshENUM_name +"); "<< endl;
			OUTWITH_0000000000000_Tab << "}" << endl;

			OUTWITH_0000000000000_Tab << "void " << globleclassname << "::" << indeps[i].list_refreshfunc_name<<"()" << endl;
			OUTWITH_0000000000000_Tab << "{" << endl; 
			OUTWITH_1111111111_Tab << "//update函数必须首先隐藏负责的界面" << endl;
			OUTWITH_1111111111_Tab << "for (int i = 0; i < "+indeps[i].max_name+"; i++)" << endl;
			OUTWITH_1111111111_Tab << "{" << endl;
			OUTWITH_2222222_Tab << indeps[i].list_control_arr_name+"[i].m_wnd_item->ShowWindow(false);" << endl;
			OUTWITH_1111111111_Tab << "}" << endl;
			OUTWITH_1111111111_Tab << indeps[i].name<<"->ShowWindow(false);" << endl;

			OUTWITH_1NewLINE
			OUTWITH_1111111111_Tab << "//滚动条m_scr_content_friend刷新" << endl;
			OUTWITH_1111111111_Tab << "int maxPageNum = ("<< indeps[i].list_data_arr_name<<".size() + "<< indeps[i].max_name<<" - 1) / "<< indeps[i].max_name <<";"<< endl;
			OUTWITH_1111111111_Tab << "if (maxPageNum == 1 || maxPageNum == 0) " + indeps[i].list_name + "->ShowWindow(false);" << endl;
			OUTWITH_1111111111_Tab << "else "+ indeps[i].list_name +"->ShowWindow(true);" << endl;
			OUTWITH_1NewLINE
			OUTWITH_1111111111_Tab << "//列表m_s_friend_control_arr刷新" << endl;
			OUTWITH_1111111111_Tab << "vector<" << "SFiendData" << ">::iterator  pos = " + indeps[i].list_data_arr_name + ".begin();" << endl;
			OUTWITH_1111111111_Tab << "std::advance(pos, "+ indeps[i].list_index_name+");" << endl;
			 
			OUTWITH_1111111111_Tab << "for (int i = 0; pos != "+ indeps[i].list_data_arr_name +".end() && i < "+indeps[i].max_name+"; ++pos)" << endl;
	 
			OUTWITH_1111111111_Tab << "{" << endl;
			OUTWITH_2222222_Tab << endl;
			OUTWITH_2222222_Tab << "//列表m_s_friend_control_arr内部wnd_item刷新" << endl;
			OUTWITH_2222222_Tab << indeps[i].list_control_arr_name+"[i].m_wnd_item->ShowWindow(true);  "<<endl;
			OUTWITH_2222222_Tab << "i++;" << endl;
			OUTWITH_1111111111_Tab << "}" << endl;
			OUTWITH_0000000000000_Tab << "}" << endl;
			 
		}
	}
}
