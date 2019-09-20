#pragma once
#include "QWU_include.h"
#include "QWU_independent.hpp"
#include "QWU_struct.h"
#include "QWU_function.h"
/*
author :matin
���ļ��ṩĳЩ�ϼ��ı��ṹ�Ĺ���
���ļ��ṩ����ͷ�ļ��Ĺ���
���ļ��ṩ����ͷ�ļ������
*/  


//_hname ��Ҫ����ΪUIAmusementPark��ȡwnd_amusement_park������㴰�ڵ�wnd֮��Ĳ��֣���ת����ʽ����
//
void output_headfile(ofstream& out, string _hname);
void output_idndef_code_BEGIN(ofstream& out, string _hname);
void output_idndef_code_END(ofstream& out, string _hname);
void output_haedimport_code(ofstream& out, string _hname);
void output_class_def_code_BEGIN(ofstream& out, string _hname);
void output_class_def_code_END(ofstream& out, string _hname);
void output_fun_declare_code_RUBBISH(ofstream& out, string _hname);
void output_mem_def_code_RUBBISH(ofstream& out, string _hname);
 

//ʵ��
void output_idndef_code_BEGIN(ofstream& out, string _hname)
{
	/*
	����
	#ifndef UIAmusementHelp_h
	#define UIAmusementHelp_h
	*/
	out << "#ifndef UI" << formal_toHump_deleteFirstOne(_hname) << "_H" << endl;
	out << "#define UI" << formal_toHump_deleteFirstOne(_hname) << "_H" << endl;
}
void output_idndef_code_END(ofstream& out, string _hname)
{
	out << "#endif" << endl;
} 
void output_haedimport_code(ofstream& out, string _hname)
{ 
	/*
	����
	#include "../../../UIBase.h"
	��Ҫ������ش���
	*/
	out << "#include \"UIBase.h\"" << endl;
	out << "#include <vector>" << endl;
}
void output_class_def_code_BEGIN(ofstream& out, string _hname)
{
	/*
	����
	class CUIAmusementHelp:  public CUIBase
	{
	*/
	out << "class " << "CUI" << formal_toHump_deleteFirstOne(_hname) << ": public CUIBase" << endl;
	out << "{" << endl;
}
void output_class_def_code_END(ofstream& out, string _hname)
{
	out << "};" << endl;
}
void output_fun_declare_code_RUBBISH(ofstream& out, string _hname)
{
	out << "public:" << endl;
	out << "\t" << "CUI" << formal_toHump_deleteFirstOne(_hname) << "();" << endl;
	out << "\t" << "~CUI" << formal_toHump_deleteFirstOne(_hname) << "();" << endl;
	out << "\t" << "void ShowWnd();" << endl;
	out << "protected:" << endl;
	out << "\t" << "virtual void OnShow();" << endl;
	out << "\t" << "virtual void OnHide();" << endl;
	out << "private:" << endl;
	out << "\t" << "void Init();" << endl;
	out << "\t" << "bool IsShow();" << endl;
}
void output_mem_def_code_RUBBISH(ofstream& out, string _hname)
{ 
	out << "private:" << endl;
	out << "\t" << "H3D_CLIENT::IUIWnd*   " << _hname << ";" << endl;
}


void output_headfile(ofstream& out,string _hname) {

	
	output_idndef_code_BEGIN(out, _hname);
	output_haedimport_code(out, _hname);
	output_class_def_code_BEGIN(out, _hname);
	
	//�ṹ�弰���ֵö��
	print_stct(out);

	output_fun_declare_code_RUBBISH(out, _hname); 
	output_mem_def_code_RUBBISH(out, _hname);
	out << "private:" << endl;
	print_memberdef(out);
  
	 
	out << "private:" << endl;
	print_onBtnFun_declare(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	 
	output_idndef_code_END(out, _hname);
}
 
 