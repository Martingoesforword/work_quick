// parsing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//   
#include "tool_xml_get.h"
#include "tool_headfile.h"
#include "tool_classfile.h"
#include "tool_stct_analysis.h"

int main()
{
	//加载某个窗口到结构体中
	string windowname = "wnd_helpTip";
	//getline(cin, windowname);
	stct_window window;
	IterateXmlNode(windowname,"./layout.xml", window);
	 
	//解析所有结构
	analysis_stct_window_all(window);

	//获取头文件输出指针对象
	ofstream outfile_h;
	string uifilename = formalId(windowname);
	uifilename.at(0) -= 32;
	outfile_h.open("C:/sjh/UI"+ uifilename +".h");

	//将头文件输出 
	output_headfile(outfile_h, windowname);

	//获取源文件输出指针对象
	ofstream outfile_cpp;
	outfile_cpp.open("C:/sjh/UI" + uifilename + ".cpp");

	//将源文件输出
	output_classfile(outfile_cpp, windowname);
	return 0;
}
