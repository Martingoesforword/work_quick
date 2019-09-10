// parsing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//   
#include "tool_xml_get.h"
#include "tool_headfile.h"
#include "tool_stct_analysis.h"

int main()
{
	//加载某个窗口到结构体中
	string windowname = "wnd_helpTip";
	//getline(cin, windowname);
	stct_window window;
	IterateXmlNode(windowname,"./layout.xml", window);
	 
	//获取头文件输出指针对象
	ofstream outfile;
	outfile.open("C:\\sjh\\gg.h");
	//将头文件输出
	analysis_stct_window_indep(window);
	output_headfile(outfile, windowname);
	//获取源文件输出指针对象

	//将源文件输出

	return 0;
}
