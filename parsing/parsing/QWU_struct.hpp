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
};
struct stct_list_def
{
	int num;
	string name;
	string context_id;
	vector<stct_item_def> items;

};


//ȫ�ֱ���
vector<stct_list_def> all_stcts;

//Ϊname���stct_ǰ׺
//struct person---> struct stct_person
void format_stct_name(stct_list_def& dec12, string name);
void add_stct_def(stct_list_def& dec12, string name, vector<stct_item_def>& items, string context_id);
//_tnum��ǰ��\t�ĸ���
void print_stct(ofstream& out, int _tnum);

//�ı���ʽ struct_friend --->  SFriendControl
string style_stct_name_ext1(string base_style);
//�ı���ʽ struct_friend --->  struct_friend_control
string style_stct_name_ext2(string base_style);  
void print_stct_init_def(ofstream& out);


void format_stct_name(stct_list_def& dec12, string name) {
	dec12.name = STCT_PREFIX;
	dec12.name.append(name);
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
}
void print_stct(ofstream& out, int _tnum)
{ 
	out_with_tnum("//�ṹ������ȶ���", 
		out, _tnum);
	out_with_tnum("enum", 
		out, _tnum);
	out_with_tnum("{", 
		out, _tnum);
	 
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		if (i == 0)
		{
			out_with_tnum("\tMAX_"+
				formal_allUp(all_stcts[i].name)+
				"_CONTROL_NUM"+
				" = "+
				to_string(all_stcts[i].num) , 
				out, _tnum);
			 
		}
		else
		{
			out_with_tnum("\t, MAX_" +
				formal_allUp(all_stcts[i].name) +
				"_CONTROL_NUM" +
				" = " +
				to_string(all_stcts[i].num),
				out, _tnum);
		 
		}
	}
	out_with_tnum("}",
		out, _tnum); 
	  
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		out_with_tnum("struct "+style_stct_name_ext1(all_stcts[i].name),
			out, _tnum);
		out_with_tnum("{",
			out, _tnum);
		

		auto items = all_stcts[i].items; 
		//������
		string tg = "";
		out_with_tnum(tg +"H3D_CLIENT::IUIWnd*" + DEFINE_SPACE + "wnd_item;", out, _tnum + 1);
		for (size_t i = 0; i < items.size(); i++)
		{
			out_with_tnum(items[i].type + DEFINE_SPACE + items[i].name + ";",
				out, _tnum+1); 
		}
		out_with_tnum("",
			out, _tnum + 1); 
		out_with_tnum(style_stct_name_ext1(all_stcts[i].name) +"()",
			out, _tnum + 1);
		out_with_tnum("{",
			out, _tnum + 1);
		out_with_tnum("wnd_item = NULL;",
			out, _tnum + 2);   
		for (size_t i = 0; i < items.size(); i++)
		{
			out_with_tnum(items[i].name + " = NULL;",
				out, _tnum + 2); 
		}
		out_with_tnum("};",
			out, _tnum + 1);
		out_with_tnum("};",
			out, _tnum);  
		out_with_tnum(string("int")+ DEFINE_SPACE+MEMBER_PREFIX
			+ style_stct_name_ext2(all_stcts[i].name)+"_index;",
			out, _tnum);
		out_with_tnum("private:",
			out, 0);
		out_with_tnum(conbine_define(style_stct_name_ext1(all_stcts[i].name), MEMBER_PREFIX + style_stct_name_ext2(all_stcts[i].name))
			+ ARRAY_POSTFIX_SHORT 
			+ "[" 
			+ "MAX_" + formal_allUp(style_stct_name_ext2(all_stcts[i].name)) + "_NUM" 
			+ "];",
			out, _tnum); 
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
		out << "\tfor (int i = 0; i < MAX_" << formal_allUp(def.name) << "_CONTROL_NUM; i++)" << endl;
		out << "\t{" << endl;

		out << "\t\tInitControl(this, " << all_stcts[i].name << "_control" << "_arr[i]" << "." << "wnd_item" << ", " << def.context_id <<", _tstring(L\"item\") + ItoStr(i)); " << endl;
		for (size_t j = 0; j < def.items.size(); j++)
		{
			stct_item_def item_def = def.items[j];
			out <<"\t\tInitControl(this, "<< all_stcts[i].name << "_control" << "_arr[i]"<<"." << item_def.name<<", "<< all_stcts[i].name << "_control" << "_arr[i]"<<".wnd_item, L\""<< item_def.name<<"\");"<<endl;

		}

		out << "\t}" << endl;
	}
}
 