#pragma once
#include "QWU_include.h"
#include "QWU_independent.hpp"
#include "QWU_struct.hpp"
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
void output_func_declare_code_RUBBISH(ofstream& out, string _hname);
void output_mem_def_code(ofstream& out, string _hname);
 

//ʵ��
void output_idndef_code_BEGIN(ofstream& out, string _hname)
{
	/*
	����
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
	����
	#include "../../../UIBase.h"
	��Ҫ������ش���
	*/
	H3D_NOTICE____H3D_NOTICE
	OUTPUT(0,) << "#include \"UIBase.h\"" << endl;
}
void output_class_def_code_BEGIN(ofstream& out, string _hname)
{
	/*
	����
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
	OUTPUT(1,) << "//OnShow�����Ǹ�����״̬�����������������UI���º���������Ҫ�����е���CheckData��������������ݵĺϷ��ԣ��������ݺϷ��Ա�ѡ���Եش˺����г�ʼ��" << endl;
	OUTPUT(1,) << "virtual void OnShow();" << endl; 
	OUTPUT(1,) << "//OnHide��������״̬�����������������UI���º���������Ҫ�����е���CheckData��������������ݵĺϷ��ԣ��������ݺϷ��Ա�ѡ���Եش˺����г�ʼ��" << endl;
	OUTPUT(1,) << "virtual void OnHide();" << endl;
	OUTPUT(0,) << "private:" << endl;
	OUTPUT(1,) << "//�˴��ĺ�����ʾ���ݺ�UI��ʼ���ĺ���������Init�����ڶ���������ֻ��ʹ��һ��" << endl;
	OUTPUT(1,) << "void Init();" << endl;
	OUTPUT(1,) << "void CheckData();" << endl;
	OUTPUT(1,) << "//refreshInterface�������ܵ�UI���º��������ж�UI���޸Ķ�Ҫ������������룻" << endl;
	OUTPUT(1,) << "void refreshInterface();" << endl;
	OUTPUT(1,) << "//UpdateData�������ܵĸ������ݺ�������ٵģ�������Ϊд������ʾ������������������ԣ���Ҫ�кܶ࣬����������ΪupdateDataXXXXX��XXXXX�������νṹ��" << endl;
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
	//�ṹ�弰���ֵö��
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
 
 