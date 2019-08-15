#pragma once
#include "helper.h"
vector<string> enums_dec_text;

struct stct_enum_item_declaration { 
	string enum_name_dec;
	string enum_value_dec;
};
vector<stct_enum_item_declaration> enums_dec;

void add_enum_dec(string name, string value) {
	enums_dec.push_back({ name , value });
}
void build_dec_text() {
	
	//添加enum定义总体文本
}


int main() {

}