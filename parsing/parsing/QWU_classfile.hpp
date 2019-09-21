#pragma once
#include "QWU_include.h"
#include "QWU_independent.hpp"
#include "QWU_struct.hpp"
#include "QWU_function.h"
/*
author :matin
此文件提供某些较简单文本结构的构建
此文件提供总体源文件的构建
此文件提供总体源文件的输出
*/


//_hname 需要类似为UIAmusementPark（取wnd_amusement_park这个顶层窗口的wnd之后的部分，并转化格式）、
//
void output_classfile(ofstream& out, string _hname); 
void output_classimport_code(ofstream& out, string _hname);
void output_construction_func_code(ofstream& out, string _hname);
void output_deconstruction_func_code(ofstream& out, string _hname);
void output_isshow_func_code(ofstream& out, string _hname);
void output_onshow_func_code(ofstream& out, string _hname);
void output_onhide_func_code(ofstream& out, string _hname);
void output_showwnd_func_code(ofstream& out, string _hname);


//实现
void output_classimport_code(ofstream& out, string _hname)
{
	/*
	类似
	#include  "UIAmusementParkHelp.h"
	*/
	out << "#include \"UI" << formal_toHump_deleteFirstOne(_hname) << ".h\"" << endl;

}
void output_construction_func_code(ofstream& out, string _hname)
{

	out << "CUI" << formal_toHump_deleteFirstOne(_hname) << "::CUI" << formal_toHump_deleteFirstOne(_hname) << "()" << endl;
	
	out << "{" << endl;
	out << "\t" << "m_wnd" << " = getWindow(L\"music_t\", L\"" << _hname << "\");" << endl;

	//init函数
	print_initdef(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	out << endl;
	print_stct_init_def(out);
	out << endl;
	out << "}" << endl;
}
void output_deconstruction_func_code(ofstream& out, string _hname)
{
	//析构
	out << "CUI" << formal_toHump_deleteFirstOne(_hname) << "::~CUI" << formal_toHump_deleteFirstOne(_hname) << "()" << endl;
	out << "{" << endl;
	out << "\t" << "//输入你自己的代码" << endl;
	out << "}" << endl;
}
void output_isshow_func_code(ofstream& out, string _hname)
{
	//IsShow
	out << "bool CUI" << formal_toHump_deleteFirstOne(_hname) << "::IsShow()" << endl;
	out << "{" << endl;
	out << "\t" << "return getStateWnd()->IsShow();" << endl;
	out << "}" << endl;
}
void output_onshow_func_code(ofstream& out, string _hname)
{
	//OnShow
	out << "void CUI" << formal_toHump_deleteFirstOne(_hname) << "::OnShow()" << endl;
	out << "{" << endl;
	out << "\t" << "GetWndManager()->ShowModalWnd(L\"" << _hname << "\",L\"music_t\", NULL);" << endl;
	out << "}" << endl;
}
void output_onhide_func_code(ofstream& out, string _hname)
{
	//OnHide
	out << "void CUI" << formal_toHump_deleteFirstOne(_hname) << "::OnHide()" << endl;
	out << "{" << endl;
	out << "\t" << "GetWndManager()->HideModalWnd(false," << _hname << ");" << endl;
	out << "}" << endl;
}
void output_showwnd_func_code(ofstream& out, string _hname)
{
	//ShowWnd
	out << "void CUI" << formal_toHump_deleteFirstOne(_hname) << "::ShowWnd()" << endl;
	out << "{" << endl;
	out << "\t" << "//输入你自己的代码" << endl;
	out << "\t" << "Show();" << endl;
	out << "}" << endl;
}

void output_classfile(ofstream& out, string _hname) {

	output_classimport_code(out, _hname);
	output_construction_func_code(out, _hname);
	output_deconstruction_func_code(out, _hname);
	output_isshow_func_code(out, _hname);
	output_onshow_func_code(out, _hname);
	output_onhide_func_code(out, _hname);
	output_showwnd_func_code(out, _hname);
	 
	//onbtn函数
	print_onBtnFun_def(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	print_onToolTips_def(out, "CUI" + formal_toHump_deleteFirstOne(_hname));

	//init函数


	//update函数
}

