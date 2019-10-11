#pragma once
#include "QWU_include.h"
#ifndef LIST_H3D_CONTROL_OUT
#define LIST_H3D_CONTROL_OUT
/*
author : martin
下面表示控件名
结尾必须带空格 作为定义
 
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
string H3D_BTN_CODE = "m_btn_";
string H3D_WND_CODE = "m_wnd_";
string H3D_ST_CODE = "m_st_";
string H3D_SCR_CODE = "m_scr_";
string H3D_IMG_CODE = "m_img_";
string H3D_CHK_CODE = "m_chk_";
string H3D_EDBX_CODE = "m_rt_";
string H3D_EFCT_CODE = "m_ew_";
string H3D_PRCCBR_CODE = "m_pb_";
#endif

//回调函数flag
//例如btn_close_clk_tp表示需要有onclick回调函数, 但是这个参数flag只出现在绑定函数中，不出现在类成员变量命名中，需要实现去除相关flag的函数，但是需要保留其id，以便绑定的时候使用
#ifndef LIST_H3D_EXT_DESCRIPTION
#define LIST_H3D_EXT_DESCRIPTION
string H3D_HAS_ONCLICK = "_clk"; 
string H3D_HAS_ONTOOOLTIPS = "_tp";  
string H3D_HAS_ONMOVE = "_mv"; 
string H3D_HAS_ONSCROLLCHANGE = "_src"; 
#endif 

#define OUTWITH_0000000000000_Tab out
#define OUTWITH_1111111111_Tab out << "\t"
#define OUTWITH_2222222_Tab out << "\t\t" 
#define OUTWITH_3333_Tab out << "\t\t\t" 
#define OUTWITH_4Tab out << "\t\t\t\t" 
#define OUTWITH_1NewLINE out  << endl;
#define OUTWITH_2NewLINE out << "\n" << endl;
#define OUTWITH_3NewLINE out << "\n\n" << endl;