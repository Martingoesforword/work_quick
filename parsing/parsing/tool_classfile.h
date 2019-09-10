#pragma once
#include "tool_includeHelper.h"
#include "tool_indepcontrol.h"
#include "tool_stct.h"
#include "tool.h"
/*
author :matin
���ļ��ṩĳЩ�ϼ��ı��ṹ�Ĺ���
���ļ��ṩ����Դ�ļ��Ĺ���
���ļ��ṩ����Դ�ļ������
*/


//_hname ��Ҫ����ΪUIAmusementPark��ȡwnd_amusement_park������㴰�ڵ�wnd֮��Ĳ��֣���ת����ʽ����
//
void output_classfile(ofstream& out, string _hname) {

	/*
	����
	#include  "UIAmusementParkHelp.h"  
	*/
	out << "#include \"UI" << formalIfdef(_hname) << ".h\"" << endl; 
	 

	/*
	���캯��

	*/
	out << "void CUI" << formalIfdef(_hname) << "::CUI" << formalIfdef(_hname) << "()" << endl;
	out << "{" << endl; 

	out << "\t" << _hname <<" = getWindow(L\"music_t\", L\""<< _hname <<"\");" << endl;
	
	//����---init����
	printinitown(out,  "CUI" + formalIfdef(_hname));

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
	out << "void CUI" << formalIfdef(_hname) << "::~CUI" << formalIfdef(_hname) << "()" << endl;
	out << "{" << endl;
	out << "\t" << "//�������Լ��Ĵ���" << endl;
	out << "}" << endl;

	//IsShow
	out << "bool CUI" << formalIfdef(_hname) << "::IsShow()" << endl;
	out << "{" << endl;
	out << "\t" << "return getStateWnd()->IsShow();" << endl;
	out << "}" << endl;

	//OnShow
	out << "void CUI" << formalIfdef(_hname) << "::OnShow()" << endl;
	out << "{" << endl;
	out << "\t" << "GetWndManager()->ShowModalWnd(L\""<< _hname <<"\",L\"music_t\", NULL);" << endl;
	out << "}" << endl;

	//OnHide
	out << "void CUI" << formalIfdef(_hname) << "::OnHide()" << endl;
	out << "{" << endl;
	out << "\t" << "GetWndManager()->HideModalWnd(false," << _hname << ");" << endl;
	out << "}" << endl;

	//ShowWnd
	out << "void CUI" << formalIfdef(_hname) << "::ShowWnd()" << endl;
	out << "{" << endl; 
	out << "\t" << "//�������Լ��Ĵ���" << endl; 
	out << "\t" << "Show();" << endl;
	out << "}" << endl;
	
	//onbtn����
	printonfundef(out, "CUI" + formalIfdef(_hname));


	//initUI����


	//update����
}

