#pragma once
#include "QWU_include.h"
#ifndef LIST_H9D_CONTROL_OUT
#define LIST_H9D_CONTROL_OUT
/*
author : martin
�����ʾ�ؼ���
��β������ո� ��Ϊ����
 
*/
string H9D_BTN = "H3D_CLIENT::IUIButton*" ;
string H9D_WND = "H3D_CLIENT::IUIWnd*" ;
string H9D_ST = "H3D_CLIENT::IUIStaticText*" ;
string H9D_SCR = "H3D_CLIENT::I_ScrollBar_Adv*" ;
string H9D_IMG = "H3D_CLIENT::IUIImage*" ; 
string H9D_CHK = "H3D_CLIENT::IUICheckBox*" ;
string H9D_EDBX = "H3D_CLIENT::IUIEditBox*" ;
string H9D_EFCT = "H3D_CLIENT::IUIEffectWnd*" ;
string H9D_PRCCBR = "H3D_CLIENT::IUIProgressBar*" ;
#endif

#ifndef LIST_H9D_CONTROL_CLASS
#define LIST_H9D_CONTROL_CLASS
string H9D_BTN_CLASS = "Button";
string H9D_WND_CLASS = "Window"; 
string H9D_ST_CLASS = "StaticText";
string H9D_SCR_CLASS = "ScrollControl";
string H9D_IMG_CLASS = "Image";
string H9D_CHK_CLASS = "CheckBox";
string H9D_EDBX_CLASS = "RichEditR";
string H9D_EFCT_CLASS = "EffectWnd";
string H9D_PRCCBR_CLASS = "ProgressBar";
#endif

#ifndef LIST_H9D_CONTROL_PREFIX
#define LIST_H9D_CONTROL_PREFIX
string H9D_BTN_PREFIX = "btn";
string H9D_WND_PREFIX = "wnd";
string H9D_ST_PREFIX = "st";
string H9D_SCR_PREFIX = "scrollBar";
string H9D_IMG_PREFIX = "img";
string H9D_CHK_PREFIX = "chk";
string H9D_EDBX_PREFIX = "rt";
string H9D_EFCT_PREFIX = "ew";
string H9D_PRCCBR_PREFIX = "pb";
#endif

#ifndef LIST_H9D_CONTROL_PROGRAMMER
#define LIST_H9D_CONTROL_PROGRAMMER
string H9D_BTN_CODE = "m_btn_";
string H9D_WND_CODE = "m_wnd_";
string H9D_ST_CODE = "m_st_";
string H9D_SCR_CODE = "m_scr_";
string H9D_IMG_CODE = "m_img_";
string H9D_CHK_CODE = "m_chk_";
string H9D_EDBX_CODE = "m_rt_";
string H9D_EFCT_CODE = "m_ew_";
string H9D_PRCCBR_CODE = "m_pb_";
#endif

//�ص�����flag
//����btn_close_clk_tp��ʾ��Ҫ��onclick�ص�����, �����������flagֻ�����ڰ󶨺����У������������Ա���������У���Ҫʵ��ȥ�����flag�ĺ�����������Ҫ������id���Ա�󶨵�ʱ��ʹ��
#ifndef LIST_H9D_EXT_DESCRIPTION
#define LIST_H9D_EXT_DESCRIPTION
string H9D_HAS_ONCLICK = "_clk"; 
string H9D_HAS_ONTOOOLTIPS = "_tp";  
string H9D_HAS_ONMOVE = "_mv"; 
string H9D_HAS_ONSCROLLCHANGE = "_src"; 
#endif