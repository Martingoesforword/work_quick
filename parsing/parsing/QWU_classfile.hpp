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
void output_checkdata_func_code(ofstream& out, string _hname);
void output_init_func_code(ofstream& out, string _hname);
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
	OUTPUT(0,) << "#include \"UI" << formal_toHump_deleteFirstOne(_hname) << ".h\"" << endl;
	H3D_NOTICE____H3D_NOTICE
	OUTPUT(0,) << "#include \"ui\\hall\\UIHall.h\"" << endl;
	 
}
void output_construction_func_code(ofstream& out, string _hname)
{

	OUTPUT(0,) << "CUI" << formal_toHump_deleteFirstOne(_hname) << "::CUI" << formal_toHump_deleteFirstOne(_hname) << "()" << endl;
	OUTPUT(0,) << ":CUIBase(L\""+ _hname +"\")\n";
	OUTPUT(0, SS);
	OUTPUT(1,) << "//这里为不可重入的Init函数，进行初始化所有数据（UI和Data数据），在对象构建的时候执行一遍";
	OUTPUT(1,) << "Init();"<<endl;
	OUTPUT(0, 1);
	OUTPUT(0, EE);
}
void output_deconstruction_func_code(ofstream& out, string _hname)
{
	//析构
	OUTPUT(0,) << "CUI" << formal_toHump_deleteFirstOne(_hname) << "::~CUI" << formal_toHump_deleteFirstOne(_hname) << "()" << endl;
	OUTPUT(0, SS);
	OUTPUT(1,) << "//输入你自己的代码" << endl;
	OUTPUT(0, EE);
}
void output_checkdata_func_code(ofstream& out, string _hname)
{
	//IsShow
	OUTPUT(0,) << "bool CUI" << formal_toHump_deleteFirstOne(_hname) << "::CheckData()" << endl;
	OUTPUT(0, SS);
	OUTPUT(1,) << "//这个函数是假函数，只是用来标识重入数据（调用函数次数；生成对象次数等数据）需要进行检查方可使用，需要在重入函数中进行调用起到提醒作用" << endl;
	OUTPUT(0, EE);
}
void output_isshow_func_code(ofstream& out, string _hname)
{
	//IsShow
	OUTPUT(0,) << "bool CUI" << formal_toHump_deleteFirstOne(_hname) << "::IsShow()" << endl;
	OUTPUT(0, SS);
	OUTPUT(1,) << "return m_stateWnd->IsShow();" << endl;
	OUTPUT(0, EE);
}
void output_init_func_code(ofstream& out, string _hname)
{
	//Init
	OUTPUT(0,) << "bool CUI" << formal_toHump_deleteFirstOne(_hname) << "::Init()" << endl;
	OUTPUT(0, SS);
	OUTPUT(1,) << "//初始化UI代码段(本质为UI属性的相关数据)，分为UI绑定（UI资源绑定，UI操作函数绑定）和UI属性初始化（例如是否为显示状态）" << endl;
	print_initdef(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	
	print_stct_init_def(out);

	OUTPUT(0, 1);
	OUTPUT(1,) << "//初始化UI中=======UI属性初始化" << endl;
	OUTPUT(0, 1);

	OUTPUT(1,) << "//初始化Data代码段(本质为其他数据，下标等数据)" << endl;
	{
		H3D_NOTICE____H3D_NOTICE
		OUTPUT(1,) << "此处实现生成控件显示show属性等属性的初始化" << endl;
		//print_init_control_property(out);
	}
	

	OUTPUT(0, EE);
}
void output_onshow_func_code(ofstream& out, string _hname)
{
	//OnShow
	OUTPUT(0,) << "void CUI" << formal_toHump_deleteFirstOne(_hname) << "::OnShow()" << endl;
	OUTPUT(0, SS);
	OUTPUT(1,) << "GetWndManager()->ShowModalWnd(L\"" << _hname << "\",L\"music_t\", NULL);" << endl;
	OUTPUT(0, EE);
}
void output_onhide_func_code(ofstream& out, string _hname)
{
	//OnHide
	OUTPUT(0,) << "void CUI" << formal_toHump_deleteFirstOne(_hname) << "::OnHide()" << endl;
	OUTPUT(0, SS);
	OUTPUT(1,) << "GetWndManager()->HideModalWnd(false," << _hname << ");" << endl;
	OUTPUT(0, EE);
}
void output_showwnd_func_code(ofstream& out, string _hname)
{
	//ShowWnd
	OUTPUT(0,) << "void CUI" << formal_toHump_deleteFirstOne(_hname) << "::ShowWnd()" << endl;
	OUTPUT(0, SS);
	OUTPUT(1,) << "//输入你自己的代码" << endl;
	OUTPUT(1,) << "Show();" << endl;
	OUTPUT(0, EE);
}

void output_classfile(ofstream& out, string _hname) {

	output_classimport_code(out, _hname);
	output_construction_func_code(out, _hname);
	output_deconstruction_func_code(out, _hname);
	output_init_func_code(out, _hname);
	output_isshow_func_code(out, _hname);
	output_checkdata_func_code(out, _hname);
	output_onshow_func_code(out, _hname);
	output_onhide_func_code(out, _hname);
	output_showwnd_func_code(out, _hname);
	 
	//onbtn函数
	print_onBtnFun_def(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	print_onToolTips_def(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	print_onScroll_def_with_refresh(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	//init函数


	//update函数
}

