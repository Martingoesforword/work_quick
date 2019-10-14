#pragma once
#include "QWU_include.h"
#include "QWU_function.h"


struct stct_window {
	string id;
	string res_id; 
	vector<stct_window> subs;
};

//�ӡ�_def���Ľṹ���ʾ�м��ʵ��Ӧ����α�������������������м��ʵ�������
//����stct_item_def ��ʾitem�ġ����塯�ṹ�壬������item�ṹ��
//����item�����ʾ�˵Ļ���item_def�ṹ������Ӧ����
//1.������������С�class person���еġ�person���ַ�������
//2.����һ����ʵ����䡮person sjh���еġ�sjh���ַ�������
//����������_def�ṹ���еı�ҪԪ����ĳ�����Զ���������ơ�int a;���е�����token[int,a]������[type,name];
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


//ȫ�ֱ���
vector<stct_list_def> all_stcts;

//Ϊname���stct_ǰ׺
//struct person---> struct stct_person
void format_stct_name(stct_list_def& dec12, string name);
void add_stct_def(stct_list_def& dec12, string name, vector<stct_item_def>& items, string context_id); 
//_tnum��ǰ��\t�ĸ���
void print_stct(ofstream& out, int _tnum);
//������ݽṹ��
void print_stct_data(ofstream& out);

//�ı���ʽ struct_friend --->  SFriendControl
string style_stct_name_ext1(string base_style);
//�ı���ʽ struct_friend --->  struct_friend_control
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
		OUTPUT(1) << "struct" << DEFINE_SPACE + all_stcts[i].data_stct << endl;
		OUTPUT(1,START);
		{
			OUTPUT(2) << all_stcts[i].data_stct <<"()"<< endl;
			OUTPUT(2,START);
			{

			}
			OUTPUT(2,END);
			
		}
		OUTPUT(1,END);
	}
	OUTPUT(0, 1);
	{
		H3D_NOTICE____H3D_NOTICE
		OUTPUT(1) << "//�������ݽṹ��ʵ��" << endl;

	}
}
void print_stct(ofstream& out, int _tnum)
{ 
	OUTPUT(1) << "//�ṹ������ȶ���" << endl; 
	OUTPUT(1) << "enum" << endl;
	OUTPUT(1) << "{" << endl;
	 
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		if (i == 0)
		{

			OUTPUT(2) << all_stcts[i].max_name +
				" = " +
				to_string(all_stcts[i].num) + "," << endl; 
			 
		}
		else
		{
			OUTPUT(2) << ", "<<all_stcts[i].max_name +
				" = " +
				to_string(all_stcts[i].num) + "," << endl;
		 
		}
	}
	OUTPUT(1) << "}" << endl;
	  
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		OUTPUT(1) << "struct "+style_stct_name_ext1(all_stcts[i].name) << endl;
		 
		OUTPUT(1) << "{" << endl;
		

		auto items = all_stcts[i].items;  
		OUTPUT(2) << conbine_define("H3D_CLIENT::IUIWnd*", "wnd_item") << endl;
		for (size_t i = 0; i < items.size(); i++)
		{
			OUTPUT(2) << conbine_define(items[i].type, items[i].name) << endl;
		}
		
		OUTPUT(2) << "" << endl;
		OUTPUT(2) << style_stct_name_ext1(all_stcts[i].name) +"()" << endl;
		OUTPUT(2) << "{" << endl;
		OUTPUT(3) << "wnd_item = NULL;" << endl;
		for (size_t i = 0; i < items.size(); i++)
		{
			OUTPUT(3) << items[i].name + " = NULL;" << endl;
		}
		OUTPUT(2) << "};" << endl;
		OUTPUT(1) << "};" << endl;
		OUTPUT(1) << conbine_define(
			"int",
			all_stcts[i].index_name
		) << endl;
		OUTPUT(0) << "private:" << endl;    
		OUTPUT(1) << conbine_define(
			style_stct_name_ext1(all_stcts[i].name),
			all_stcts[i].control_array_name +"["+ all_stcts[i].max_name+"]"
		) << endl; 
	} 
}
void add_list_vector(vector< stct_item_def>& items, string name, int num, string context_id)
{
	stct_list_def dec;
	//�����ж�items  
	//��ʽ��vector
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
		OUTPUT(1) << "for (int i = 0; i < MAX_" << formal_allUp(def.name) << LIST_MAX_NAME_POSTFIX_STYLE<<"; i++)" << endl;
		OUTPUT(1) << "{" << endl;

		OUTPUT(2) << "InitControl(this, " << all_stcts[i].name << LIST_CONTROL_ARRAY_POSTFIX_STYLE <<"[i]" << "." << "wnd_item" << ", " << def.context_id <<", _tstring(L\"item\") + ItoStr(i)); " << endl;
		OUTPUT(2) << "H3D_CLIENT::IUIWnd* wnd_item = "+ all_stcts[i].control_array_name+"[i].wnd_item;" << endl;
		for (size_t j = 0; j < def.items.size(); j++)
		{
			stct_item_def item_def = def.items[j];
			OUTPUT(2) <<"InitControl(this, "<< all_stcts[i].name << LIST_CONTROL_ARRAY_POSTFIX_STYLE << "[i]"<<"." << item_def.name <<", "<< "wnd_item, L\""<< item_def.layout_name <<"\");"<<endl;

		}

		OUTPUT(1) << "}" << endl;
	}
}
 