#pragma once
#include "QWU_include.h"
#ifndef LIST_H3D_CONTROL_OUT
#define LIST_H3D_CONTROL_OUT
/*
author : martin
�����ʾ�ؼ���
��β������ո� ��Ϊ����
 
*/ 
string H3D_BTN = "H3D_CLIENT::IUIButton*" ;
string H3D_WND = "H3D_CLIENT::IUIWnd*" ;
string H3D_ST = "H3D_CLIENT::IUIStaticText*" ;
string H3D_SCR = "H3D_CLIENT::I_ScrollBar_Adv*" ;
string H3D_IMG = "H3D_CLIENT::IUIImage*" ; 
string H3D_CHK = "H3D_CLIENT::IUICheckBox*" ;
string H3D_EDBX = "H3D_CLIENT::IUIEditBox*" ;
string H3D_EFCT = "H3D_CLIENT::IUIEffectWnd*" ;
string H3D_PRCCBR = "H3D_CLIENT::IUIProgressBar*" ;
#endif

#ifndef LIST_H3D_CONTROL_CLASS
#define LIST_H3D_CONTROL_CLASS
string H3D_BTN_CLASS = "Button";
string H3D_WND_CLASS = "Window"; 
string H3D_ST_CLASS = "StaticText";
string H3D_SCR_CLASS = "ScrollControl";
string H3D_IMG_CLASS = "Image";
string H3D_CHK_CLASS = "CheckBox";
string H3D_EDBX_CLASS = "RichEditR";
string H3D_EFCT_CLASS = "EffectWnd";
string H3D_PRCCBR_CLASS = "ProgressBar";
#endif

#ifndef LIST_H3D_CONTROL_PREFIX
#define LIST_H3D_CONTROL_PREFIX
string H3D_BTN_PREFIX = "btn";
string H3D_WND_PREFIX = "wnd";
string H3D_ST_PREFIX = "st";
string H3D_SCR_PREFIX = "scrollBar";
string H3D_IMG_PREFIX = "img";
string H3D_CHK_PREFIX = "checkBox";
string H3D_EDBX_PREFIX = "rt";
string H3D_EFCT_PREFIX = "ew";
string H3D_PRCCBR_PREFIX = "pb";
#endif

#ifndef LIST_H3D_CONTROL_PROGRAMMER
#define LIST_H3D_CONTROL_PROGRAMMER
string H3D_BTN_CODE = "btn_";
string H3D_WND_CODE = "wnd_";
string H3D_ST_CODE = "st_";
string H3D_SCR_CODE = "scr_";
string H3D_IMG_CODE = "img_";
string H3D_CHK_CODE = "chk_";
string H3D_EDBX_CODE = "rt_";
string H3D_EFCT_CODE = "ew_";
string H3D_PRCCBR_CODE = "pb_";
#endif

//�ص�����flag
//����btn_close_clk_tp��ʾ��Ҫ��onclick�ص�����, �����������flagֻ�����ڰ󶨺����У������������Ա���������У���Ҫʵ��ȥ�����flag�ĺ�����������Ҫ������id���Ա�󶨵�ʱ��ʹ��
#ifndef LIST_H3D_EXT_DESCRIPTION
#define LIST_H3D_EXT_DESCRIPTION
string H3D_HAS_ONCLICK = "_clk"; 
string H3D_HAS_ONTOOOLTIPS = "_tp";  
string H3D_HAS_ONMOVE = "_mv"; 
string H3D_HAS_ONSCROLLCHANGE = "_src"; 
#endif 

#define POINT_CALL "->"


//����n����ʾtab�ĸ��� 
//����m����ʾѡ�����������ͣ����ֱ�ʾ���и�����SS��EE��ʾǰ�������,EEWS��ʾ��semicolon(;)�ĺ�����
#define OUTPUT(n,m) OUTWITH_##n##n##_##m##_HAHA

#define OUTWITH_00__HAHA out
#define OUTWITH_11__HAHA out << "\t"
#define OUTWITH_22__HAHA out << "\t\t" 
#define OUTWITH_33__HAHA out << "\t\t\t" 
#define OUTWITH_44__HAHA out << "\t\t\t\t" 
#define OUTWITH_55__HAHA out << "\t\t\t\t\t" 

#define OUTWITH_00_SS_HAHA out << "{"<<endl 
#define OUTWITH_11_SS_HAHA out << "\t{"<<endl 
#define OUTWITH_22_SS_HAHA out << "\t\t{"<<endl 
#define OUTWITH_33_SS_HAHA out << "\t\t\t{"<<endl 
#define OUTWITH_44_SS_HAHA out << "\t\t\t\t{"<<endl  
#define OUTWITH_55_SS_HAHA out << "\t\t\t\t\t{"<<endl 

#define OUTWITH_00_EEWS_HAHA out << "};"<<endl  
#define OUTWITH_55_EEWS_HAHA out << "\t\t\t\t\t};"<<endl  
#define OUTWITH_44_EEWS_HAHA out << "\t\t\t\t};"<<endl 
#define OUTWITH_33_EEWS_HAHA out << "\t\t\t};"<<endl 
#define OUTWITH_22_EEWS_HAHA out << "\t\t};"<<endl 
#define OUTWITH_11_EEWS_HAHA out << "\t};"<<endl 


#define OUTWITH_00_EE_HAHA out << "}"<<endl  
#define OUTWITH_11_EE_HAHA out << "\t}"<<endl  
#define OUTWITH_22_EE_HAHA out << "\t\t};"<<endl  
#define OUTWITH_33_EE_HAHA out << "\t\t\t};"<<endl  
#define OUTWITH_44_EE_HAHA out << "\t\t\t\t};"<<endl  
#define OUTWITH_55_EE_HAHA out << "\t\t\t\t\t};"<<endl 

#define OUTWITH_00_0_HAHA
#define OUTWITH_00_1_HAHA out << endl;
#define OUTWITH_00_2_HAHA out << "\n" << endl;
#define OUTWITH_00_3_HAHA out << "\n\n" << endl;
#define OUTWITH_00_4_HAHA out << "\n\n\n" << endl;
#define OUTWITH_00_5_HAHA out << "\n\n\n\n" << endl;