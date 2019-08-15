#pragma once
#include "helper.h"

/*
author :martin
提供头文件中类定义文本的构建
*/
vector<string> class_text;
void build_class_text() {

}

/*
author :martin
提供头文件中类成员定义文本的构建
暂时提供成员变量定义文本的构建
*包括控件结构体数组的定义[需要关注数组长度也就是enum中定义的常量与长度的关系]*
*/
vector<string> class_member_text;

void build_class_member_text() {

}

struct stct_class_member_declaration {
	string member_type;
	string member_name;
};
