// parsing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//   
#include "tool_xml_get.h"

int main()
{
	//加载某个窗口到结构体中
	string windowname;
	getline(cin, windowname);
	stct_window window;
	IterateXmlNode(windowname,"./layout.xml", window);

	//将结构体中的数据解析生成详细结构体

	//获取头文件输出指针对象

	//将头文件输出

	//获取源文件输出指针对象

	//将源文件输出

	return 0;
}
