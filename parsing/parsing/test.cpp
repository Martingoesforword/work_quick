// parsing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//   
#include "QWU_xml.hpp"
#include "QWU_headfile.hpp"
#include "QWU_classfile.hpp"
#include "QWU_analysis.hpp"

int main()
{    
	  
	//加载某个窗口到结构体中
	string windowname = "wnd_tantan_game_adventure";
	//getline(cin, windowname);
	stct_window window;
	IterateXmlNode(windowname,"F:\\workspace\\a\\trunc\\exe\\NewUIEditor\\resources\\media\\ui\\music_t\\TantanGame.xml", window);
	 
	//解析所有结构
	analysis_main(window);

	//获取头文件输出指针对象
	ofstream outfile_h;
	string uifilename = formal_toHump_deleteFirstOne(windowname); 
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
