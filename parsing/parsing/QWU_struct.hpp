#pragma once
#include "QWU_include.h"
#include "QWU_function.h"


struct stct_window {
	string id;
	string res_id; 
	vector<stct_window> subs;
};

//加‘_def’的结构体表示中间的实体应该如何被定义出来，而并非是中间的实体的内容
//例如stct_item_def 表示item的‘定义’结构体，并不是item结构体
//比如item如果表示人的话，item_def结构体内容应该是
//1.定义人类语句中‘class person’中的‘person’字符串本身
//2.定义一个人实例语句‘person sjh’中的‘sjh’字符串本身
//综上所述，_def结构体中的必要元素是某种语言定义语句类似‘int a;’中的所有token[int,a]的类型[type,name];
struct stct_item_def {

	string type;
	string name;
	string layout_name;
}; 
struct stct_list_def
{
	int num;
	string name;
	string context_id;
	vector<stct_item_def> items;
	string index_name;
	string max_name;
	string control_array_name;
	string data_stct;
};


//全局变量
vector<stct_list_def> all_stcts;

//为name添加stct_前缀
//struct person---> struct stct_person
void format_stct_name(stct_list_def& dec12, string name);
void add_stct_def(stct_list_def& dec12, string name, vector<stct_item_def>& items, string context_id); 
//_tnum：前置\t的个数
void print_stct(ofstream& out, int _tnum);
//输出数据结构体
void print_stct_data(ofstream& out);

//改变样式 struct_friend --->  SFriendControl
string style_stct_name_ext1(string base_style);
//改变样式 struct_friend --->  struct_friend_control
string style_stct_name_ext2(string base_style);  
void print_stct_init_def(ofstream& out);

string get_max_name(string name);
string get_index_name(string name);
string get_control_array_name(string name);
 
void format_stct_name(stct_list_def& dec12, string name) {
	
	dec12.name = string(MEMBER_PREFIX)+ "list_"+ name; 
}
string style_stct_name_ext1(string base_style) {
	string base = STCT_PREFIX;
	int length = base.size();
	string result = STCT_PREFIX_SHORT;
	result += formal_toHump(base_style.substr(length, base_style.size())) ;
	return result+"Control";
}
string style_stct_name_ext2(string base_style) { 
	return base_style + "_control";
} 

void add_stct_def(stct_list_def& dec12, string name, vector<stct_item_def>& items, string context_id)
{
	format_stct_name(dec12, name);
	dec12.items = items;
	dec12.context_id = context_id;
	dec12.index_name = get_index_name(name);
	dec12.max_name = get_max_name(name);
	dec12.control_array_name = get_control_array_name(name); 
	dec12.data_stct = STCT_PREFIX_SHORT + formal_toHump(name)  + string("Data");
}
string get_index_name(string name)
{
	return MEMBER_PREFIX + string("list_") + name + LIST_INDEX_NAME_POSTFIX_STYLE;
}
string get_control_array_name(string name)
{
	return MEMBER_PREFIX + string("list_")+name + LIST_CONTROL_ARRAY_POSTFIX_STYLE;
}
string get_max_name(string name)
{
	return "MAX_LIST_" + formal_allUp(name) + LIST_MAX_NAME_POSTFIX_STYLE;
}
void print_stct_data(ofstream& out)
{
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		OUTWITH_11_Tab << "struct" << DEFINE_SPACE + all_stcts[i].data_stct << endl;
		OUTWITH_11GG_Tab_Over
		{
			OUTWITH_22_Tab << all_stcts[i].data_stct <<"()"<< endl;
			OUTWITH_22GG_Tab_Over
			{

			}
			OUTWITH_22YY_Tab_Over
			
		}
		OUTWITH_11YY_Tab_Over
	}
	OUTWITH_11_NewLINE
	{
		H3D_NOTICE____H3D_NOTICE
		OUTWITH_11_Tab << "//生成数据结构体实例" << endl;

	}
}
void print_stct(ofstream& out, int _tnum)
{ 
	OUTWITH_11_Tab << "//结构体最大宽度定义" << endl; 
	OUTWITH_11_Tab << "enum" << endl;
	OUTWITH_11_Tab << "{" << endl;
	 
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		if (i == 0)
		{

			OUTWITH_22_Tab << all_stcts[i].max_name +
				" = " +
				to_string(all_stcts[i].num) + "," << endl; 
			 
		}
		else
		{
			OUTWITH_22_Tab << ", "<<all_stcts[i].max_name +
				" = " +
				to_string(all_stcts[i].num) + "," << endl;
		 
		}
	}
	OUTWITH_11_Tab << "}" << endl;
	  
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		OUTWITH_11_Tab << "struct "+style_stct_name_ext1(all_stcts[i].name) << endl;
		 
		OUTWITH_11_Tab << "{" << endl;
		

		auto items = all_stcts[i].items;  
		OUTWITH_22_Tab << conbine_define("H3D_CLIENT::IUIWnd*", "wnd_item") << endl; 
		for (size_t i = 0; i < items.size(); i++)
		{
			OUTWITH_22_Tab << conbine_define(items[i].type, items[i].name) << endl;
		}
		
		OUTWITH_22_Tab << "" << endl;
		OUTWITH_22_Tab << style_stct_name_ext1(all_stcts[i].name) +"()" << endl;
		OUTWITH_22_Tab << "{" << endl;
		OUTWITH_33_Tab << "wnd_item = NULL;" << endl;  
		for (size_t i = 0; i < items.size(); i++)
		{
			OUTWITH_33_Tab << items[i].name + " = NULL;" << endl; 
		}
		OUTWITH_22_Tab << "};" << endl;
		OUTWITH_11_Tab << "};" << endl;
		OUTWITH_11_Tab << conbine_define(
			"int",
			all_stcts[i].index_name
		) << endl;
		OUTWITH_00_Tab << "private:" << endl;    
		OUTWITH_11_Tab << conbine_define(
			style_stct_name_ext1(all_stcts[i].name),
			all_stcts[i].control_array_name +"["+ all_stcts[i].max_name+"]"
		) << endl; 
	} 
}
void add_list_vector(vector< stct_item_def>& items, string name, int num, string context_id)
{
	stct_list_def dec;
	//类型判断items  
	//格式化vector
	add_stct_def(dec, name, items, context_id);
	dec.num = num;
	all_stcts.push_back(dec);
}

void print_stct_init_def(ofstream& out)
{
	H3D_NOTICE____H3D_NOTICE
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		stct_list_def def = all_stcts[i];
		OUTWITH_11_Tab << "for (int i = 0; i < MAX_" << formal_allUp(def.name) << LIST_MAX_NAME_POSTFIX_STYLE<<"; i++)" << endl;
		OUTWITH_11_Tab << "{" << endl;

		OUTWITH_22_Tab << "InitControl(this, " << all_stcts[i].name << LIST_CONTROL_ARRAY_POSTFIX_STYLE <<"[i]" << "." << "wnd_item" << ", " << def.context_id <<", _tstring(L\"item\") + ItoStr(i)); " << endl;
		OUTWITH_22_Tab << "H3D_CLIENT::IUIWnd* wnd_item = "+ all_stcts[i].control_array_name+"[i].wnd_item;" << endl;
		for (size_t j = 0; j < def.items.size(); j++)
		{
			stct_item_def item_def = def.items[j];
			OUTWITH_22_Tab <<"InitControl(this, "<< all_stcts[i].name << LIST_CONTROL_ARRAY_POSTFIX_STYLE << "[i]"<<"." << item_def.name <<", "<< "wnd_item, L\""<< item_def.layout_name <<"\");"<<endl;

		}

		OUTWITH_11_Tab << "}" << endl;
	}
}
 