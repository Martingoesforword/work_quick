#pragma once
#include "QWU_include.h"
#include "QWU_independent.hpp"
#include "QWU_struct.h"
#include "QWU_function.h"
/*
author :matin
���ļ��ṩĳЩ�ϼ��ı��ṹ�Ĺ���
���ļ��ṩ����Դ�ļ��Ĺ���
���ļ��ṩ����Դ�ļ������
*/


//_hname ��Ҫ����ΪUIAmusementPark��ȡwnd_amusement_park������㴰�ڵ�wnd֮��Ĳ��֣���ת����ʽ����
//
void output_classfile(ofstream& out, string _hname);


//ʵ��
void output_classfile(ofstream& out, string _hname) {

	/*
	����
	#include  "UIAmusementParkHelp.h"  
	*/
	out << "#include \"UI" << formal_toHump_deleteFirstOne(_hname) << ".h\"" << endl; 
	 
	 

	/*
	���캯��

	*/
	out << "CUI" << formal_toHump_deleteFirstOne(_hname) << "::CUI" << formal_toHump_deleteFirstOne(_hname) << "()" << endl;
	out << "{" << endl; 

	out << "\t" << _hname <<" = getWindow(L\"music_t\", L\""<< _hname <<"\");" << endl;
	
	//����---init����
	print_initdef(out,  "CUI" + formal_toHump_deleteFirstOne(_hname));

	out << "}" << endl;

	/*
	��̬���
	����
	bool CUIAmusementParkHelp::IsShow()
	{
		return getStateWnd()->IsShow();
	}
	*/
	

	//����
	out << "CUI" << formal_toHump_deleteFirstOne(_hname) << "::~CUI" << formal_toHump_deleteFirstOne(_hname) << "()" << endl;
	out << "{" << endl;
	out << "\t" << "//�������Լ��Ĵ���" << endl;
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
	out << "\t" << "//�������Լ��Ĵ���" << endl; 
	out << "\t" << "Show();" << endl;
	out << "}" << endl;
	
	//onbtn����
	print_onBtnFun_def(out, "CUI" + formal_toHump_deleteFirstOne(_hname));


	//initUI����


	//update����
}

