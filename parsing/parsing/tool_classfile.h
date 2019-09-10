#pragma once
#include "tool_includeHelper.h"
#include "tool_indepcontrol.h"
#include "tool_stct.h"
#include "tool.h"
/*
author :matin
此文件提供某些较简单文本结构的构建
此文件提供总体源文件的构建
此文件提供总体源文件的输出
*/


//_hname 需要类似为UIAmusementPark（取wnd_amusement_park这个顶层窗口的wnd之后的部分，并转化格式）、
//
void output_classfile(ofstream& out, string _hname) {

	/*
	类似
	#include  "UIAmusementParkHelp.h"  
	*/
	out << "#include \"UI" << formalFirstUpDeleteOne(_hname) << ".h\"" << endl; 
	 

	/*
	构造函数

	*/
	out << "CUI" << formalFirstUpDeleteOne(_hname) << "::CUI" << formalFirstUpDeleteOne(_hname) << "()" << endl;
	out << "{" << endl; 

	out << "\t" << _hname <<" = getWindow(L\"music_t\", L\""<< _hname <<"\");" << endl;
	
	//构造---init函数
	printinitdef(out,  "CUI" + formalFirstUpDeleteOne(_hname));

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
	out << "CUI" << formalFirstUpDeleteOne(_hname) << "::~CUI" << formalFirstUpDeleteOne(_hname) << "()" << endl;
	out << "{" << endl;
	out << "\t" << "//输入你自己的代码" << endl;
	out << "}" << endl;

	//IsShow
	out << "bool CUI" << formalFirstUpDeleteOne(_hname) << "::IsShow()" << endl;
	out << "{" << endl;
	out << "\t" << "return getStateWnd()->IsShow();" << endl;
	out << "}" << endl;

	//OnShow
	out << "void CUI" << formalFirstUpDeleteOne(_hname) << "::OnShow()" << endl;
	out << "{" << endl;
	out << "\t" << "GetWndManager()->ShowModalWnd(L\""<< _hname <<"\",L\"music_t\", NULL);" << endl;
	out << "}" << endl;

	//OnHide
	out << "void CUI" << formalFirstUpDeleteOne(_hname) << "::OnHide()" << endl;
	out << "{" << endl;
	out << "\t" << "GetWndManager()->HideModalWnd(false," << _hname << ");" << endl;
	out << "}" << endl;

	//ShowWnd
	out << "void CUI" << formalFirstUpDeleteOne(_hname) << "::ShowWnd()" << endl;
	out << "{" << endl; 
	out << "\t" << "//输入你自己的代码" << endl; 
	out << "\t" << "Show();" << endl;
	out << "}" << endl;
	
	//onbtn函数
	printonfundef(out, "CUI" + formalFirstUpDeleteOne(_hname));


	//initUI函数


	//update函数
}

