#pragma once
#include "tool_includeHelper.h" 
using namespace std;
#define STCT_STRING "stct_"
struct item_declaration {
	string item_typename_dec;
	string item_name_dec;
};
struct list_declaration
{
	string struct_name_dec;
	vector<item_declaration> items_dec;

}; 

vector<list_declaration> all_stcts;


void format_stct_name(list_declaration& dec12,string name) {
	dec12.struct_name_dec = STCT_STRING;
	dec12.struct_name_dec.append(name);
} 
void format_stct(list_declaration& dec12, string name, vector<item_declaration>& items_dec) {
	 
	format_stct_name(dec12, name);
	dec12.items_dec = items_dec;
}
void print_stct(ostream& out)
{
	for (vector<list_declaration>::iterator a = all_stcts.begin(); a != all_stcts.end(); a++)
	{
		//输出"struct "+ 结构体名 + "{\n"
		
		//循环输出结构体中的成员类型定义+" "+ 名称 + ";\n"

		//输出"};"
	}

}
void addlist(vector< item_declaration>& items_dec,string name)
{
	list_declaration dec; 
	//格式化vector
	format_stct(dec, name, items_dec);
	all_stcts.push_back(dec); 
}
int main() {
	 
	 
}

