#pragma once
#include <string>
#include <vector>
#include "design_stct.h"
using namespace std;

struct stct_list_item_declaration {
	string item_typename_dec;
	string item_name_dec;
};
struct stct_meta_list_declaration
{
	string struct_name_dec;
	vector< stct_list_item_declaration> items_dec;

};

#define STCT_STRING "stct_"
vector<stct_meta_list_declaration> all_stcts;



void format_stct_name(stct_meta_list_declaration& dec12,string name) {
	dec12.struct_name_dec = STCT_STRING;
	dec12.struct_name_dec.append(name);
} 

 
void format_stct(stct_meta_list_declaration& dec12, string name, vector< stct_list_item_declaration>& items_dec) {
	 
	format_stct_name(dec12, name);
	dec12.items_dec = items_dec;
}


int main() {
	stct_meta_list_declaration dec;
	vector< stct_list_item_declaration> items_dec;
	items_dec.push_back({ "attr1_type", "attr1" });
	items_dec.push_back({ "attr2_type", "attr2" });
	items_dec.push_back({ "attr3_type", "attr3" });
	items_dec.push_back({ "attr4_type", "attr4" });
	format_stct(dec, "person_friend", items_dec);


	 
}

