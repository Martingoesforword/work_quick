// parsing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//   
#include "tool_xml_get.h"

int main()
{
	string windowname;
	getline(cin, windowname);
	stct_window window;
	IterateXmlNode(windowname,"./layout.xml", window);
	return 0;
}
