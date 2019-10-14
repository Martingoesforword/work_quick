#pragma once
#include "QWU_include.h"
#include "QWU_independent.hpp"
#include "QWU_struct.hpp"
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
void output_classimport_code(ofstream& out, string _hname);
void output_construction_func_code(ofstream& out, string _hname);
void output_deconstruction_func_code(ofstream& out, string _hname);
void output_isshow_func_code(ofstream& out, string _hname);
void output_checkdata_func_code(ofstream& out, string _hname);
void output_init_func_code(ofstream& out, string _hname);
void output_onshow_func_code(ofstream& out, string _hname);
void output_onhide_func_code(ofstream& out, string _hname);
void output_showwnd_func_code(ofstream& out, string _hname);


//ʵ��
void output_classimport_code(ofstream& out, string _hname)
{
	/*
	����
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
	OUTPUT(1,) << "//����Ϊ���������Init���������г�ʼ���������ݣ�UI��Data���ݣ����ڶ��󹹽���ʱ��ִ��һ��";
	OUTPUT(1,) << "Init();"<<endl;
	OUTPUT(0, 1);
	OUTPUT(0, EE);
}
void output_deconstruction_func_code(ofstream& out, string _hname)
{
	//����
	OUTPUT(0,) << "CUI" << formal_toHump_deleteFirstOne(_hname) << "::~CUI" << formal_toHump_deleteFirstOne(_hname) << "()" << endl;
	OUTPUT(0, SS);
	OUTPUT(1,) << "//�������Լ��Ĵ���" << endl;
	OUTPUT(0, EE);
}
void output_checkdata_func_code(ofstream& out, string _hname)
{
	//IsShow
	OUTPUT(0,) << "bool CUI" << formal_toHump_deleteFirstOne(_hname) << "::CheckData()" << endl;
	OUTPUT(0, SS);
	OUTPUT(1,) << "//��������Ǽٺ�����ֻ��������ʶ�������ݣ����ú������������ɶ�����������ݣ���Ҫ���м�鷽��ʹ�ã���Ҫ�����뺯���н��е�������������" << endl;
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
	OUTPUT(1,) << "//��ʼ��UI�����(����ΪUI���Ե��������)����ΪUI�󶨣�UI��Դ�󶨣�UI���������󶨣���UI���Գ�ʼ���������Ƿ�Ϊ��ʾ״̬��" << endl;
	print_initdef(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	
	print_stct_init_def(out);

	OUTPUT(0, 1);
	OUTPUT(1,) << "//��ʼ��UI��=======UI���Գ�ʼ��" << endl;
	OUTPUT(0, 1);

	OUTPUT(1,) << "//��ʼ��Data�����(����Ϊ�������ݣ��±������)" << endl;
	{
		H3D_NOTICE____H3D_NOTICE
		OUTPUT(1,) << "�˴�ʵ�����ɿؼ���ʾshow���Ե����Եĳ�ʼ��" << endl;
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
	OUTPUT(1,) << "//�������Լ��Ĵ���" << endl;
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
	 
	//onbtn����
	print_onBtnFun_def(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	print_onToolTips_def(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	print_onScroll_def_with_refresh(out, "CUI" + formal_toHump_deleteFirstOne(_hname));
	//init����


	//update����
}

