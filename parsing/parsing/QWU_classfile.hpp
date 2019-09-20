#pragma once
#include "QWU_include.h"
#include "QWU_independent.hpp"
#include "QWU_struct.h"
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


//实现
void output_classfile(ofstream& out, string _hname) {

	/*
	类似
	#include  "UIAmusementParkHelp.h"  
	*/
	out << "#include \"UI" << formal_toHump_deleteFirstOne(_hname) << ".h\"" << endl; 
	 
	 

	/*
	构造函数

	*/
	out << "CUI" << formal_toHump_deleteFirstOne(_hname) << "::CUI" << formal_toHump_deleteFirstOne(_hname) << "()" << endl;
	out << "{" << endl; 

	out << "\t" << _hname <<" = getWindow(L\"music_t\", L\""<< _hname <<"\");" << endl;
	
	//构造---init函数
	print_initdef(out,  "CUI" + formal_toHump_deleteFirstOne(_hname));

	out << "}" << endl;

	/*
	静态语句
	类似
	bool CUIAmusementParkHelp::IsShow()
	{
		return getStateWnd()->IsShow();
	}
	*/
	

	//析构
	out << "CUI" << formal_toHump_deleteFirstOne(_hname) << "::~CUI" << formal_toHump_deleteFirstOne(_hname) << "()" << endl;
	out << "{" << endl;
	out << "\t" << "//输入你自己的代码" << endl;
	out << "}" << endl;

	//IsShow
	out << "bool CUI" << formal_toHump_deleteFirstOne(_hname) << "::IsShow()" << endl;
	out << "{" << endl;
	out << "\t" << "return getStateWnd()->IsShow();" << endl;
	out << "}" << endl;

	//OnShow
	out << "void CUI" << formal_toHump_deleteFirstOne(_hname) << "::OnShow()" << endl;
	out << "{" << endl;
	out << "\t" << "GetWndManager()->ShowModalWnd(L\""<< _hname <<"\",L\"music_t\", NULL);" << endl;
	out << "}" << endl;

	//OnHide
	out << "void CUI" << formal_toHump_deleteFirstOne(_hname) << "::OnHide()" << endl;
	out << "{" << endl;
	out << "\t" << "GetWndManager()->HideModalWnd(false," << _hname << ");" << endl;
	out << "}" << endl;

	//ShowWnd
	out << "void CUI" << formal_toHump_deleteFirstOne(_hname) << "::ShowWnd()" << endl;
	out << "{" << endl; 
	out << "\t" << "//输入你自己的代码" << endl; 
	out << "\t" << "Show();" << endl;
	out << "}" << endl;
	
	//onbtn函数
	print_onBtnFun_def(out, "CUI" + formal_toHump_deleteFirstOne(_hname));


	//initUI函数


	//update函数
}

