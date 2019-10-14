#pragma once
#include "QWU_include.h"
#include "QWU_independent.hpp"
#include "QWU_struct.hpp"
#include "QWU_function.h"
/*
author :matin
此文件提供某些较简单文本结构的构建
此文件提供总体头文件的构建
此文件提供总体头文件的输出
*/  


//_hname 需要类似为UIAmusementPark（取wnd_amusement_park这个顶层窗口的wnd之后的部分，并转化格式）、
//
void output_headfile(ofstream& out, string _hname);
void output_idndef_code_BEGIN(ofstream& out, string _hname);
void output_idndef_code_END(ofstream& out, string _hname);
void output_haedimport_code(ofstream& out, string _hname);
void output_class_def_code_BEGIN(ofstream& out, string _hname);
void output_class_def_code_END(ofstream& out, string _hname);
void output_func_declare_code_RUBBISH(ofstream& out, string _hname);
void output_mem_def_code(ofstream& out, string _hname);
 

//实现
void output_idndef_code_BEGIN(ofstream& out, string _hname)
{
	/*
	类似
	#ifndef UIAmusementHelp_h
	#define UIAmusementHelp_h
	*/
	OUTPUT(0,) << "#ifndef UI" << formal_toHump_deleteFirstOne(_hname) << "_H" << endl;
	OUTPUT(0,) << "#define UI" << formal_toHump_deleteFirstOne(_hname) << "_H" << endl;
}
void output_idndef_code_END(ofstream& out, string _hname)
{
	
	OUTPUT(0,) << "#endif" << endl;
} 
void output_haedimport_code(ofstream& out, string _hname)
{ 
	/*
	类似
	#include "../../../UIBase.h"
	需要后面相关处理
	*/
	H3D_NOTICE____H3D_NOTICE
	OUTPUT(0,) << "#include \"UIBase.h\"" << endl;
}
void output_class_def_code_BEGIN(ofstream& out, string _hname)
{
	/*
	类似
	class CUIAmusementHelp:  public CUIBase
	{
	*/
	OUTPUT(0,) << "class " << "CUI" << formal_toHump_deleteFirstOne(_hname) << ": public CUIBase" << endl;
	OUTPUT(0, SS);
}
void output_class_def_code_END(ofstream& out, string _hname)
{
	OUTPUT(0, EEWS);
}
void output_func_declare_code_RUBBISH(ofstream& out, string _hname)
{
	OUTPUT(0,) << "public:" << endl;
	OUTPUT(1,) << "CUI" << formal_toHump_deleteFirstOne(_hname) << "();" << endl;
	OUTPUT(1,) << "~CUI" << formal_toHump_deleteFirstOne(_hname) << "();" << endl;
	OUTPUT(1,) << "void ShowWnd();" << endl;
	OUTPUT(0,) << "protected:" << endl;
	OUTPUT(1,) << "//OnShow函数是复杂切状态函数（本质是组合型UI更新函数），需要在其中调用CheckData函数检查所有数据的合法性，根据数据合法性表选择性地此函数中初始化" << endl;
	OUTPUT(1,) << "virtual void OnShow();" << endl; 
	OUTPUT(1,) << "//OnHide函数是切状态函数（本质是组合型UI更新函数），需要在其中调用CheckData函数检查所有数据的合法性，根据数据合法性表选择性地此函数中初始化" << endl;
	OUTPUT(1,) << "virtual void OnHide();" << endl;
	OUTPUT(0,) << "private:" << endl;
	OUTPUT(1,) << "//此处的函数表示数据和UI初始化的函数，类似Init函数在对象周期中只会使用一次" << endl;
	OUTPUT(1,) << "void Init();" << endl;
	OUTPUT(1,) << "void CheckData();" << endl;
	OUTPUT(1,) << "//refreshInterface函数是总的UI更新函数，所有对UI的修改都要从这个函数进入；" << endl;
	OUTPUT(1,) << "void refreshInterface();" << endl;
	OUTPUT(1,) << "//UpdateData函数是总的更新数据函数（虚假的，用来作为写代码提示函数），由于其多样性，需要有很多，但命名规则为updateDataXXXXX，XXXXX是有树形结构的" << endl;
	OUTPUT(1,) << "void UpdateData();" << endl;
	OUTPUT(1,) << "bool IsShow();" << endl;
}
void output_mem_def_code(ofstream& out, string _hname)
{ 
	OUTPUT(0,) << "private:" << endl;
	print_memberdef(out);
}


void output_headfile(ofstream& out,string _hname) {

	
	output_idndef_code_BEGIN(out, _hname);
	output_haedimport_code(out, _hname);


	output_class_def_code_BEGIN(out, _hname);
	
	
	print_stct_data(out);
	//结构体及最大值枚举
	print_stct(out, 1);
	
	output_func_declare_code_RUBBISH(out, _hname); 
	output_mem_def_code(out, _hname);  
  
	 
	OUTPUT(0,) << "private:" << endl;
	print_onBtnFun_declare(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	print_onToolTips_declare(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	print_onScroll_declare(out, "CUI" + formal_toHump_deleteFirstOne(_hname));

	OUTPUT(0,) << "private:" << endl;
	print_refreshFun_declare(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	output_class_def_code_END(out, _hname);
	output_idndef_code_END(out, _hname);
}
 
 