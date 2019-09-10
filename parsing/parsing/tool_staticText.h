#pragma once
#include "tool_includeHelper.h"
#ifndef LIST_H9D_CONTROL_OUT
#define LIST_H9D_CONTROL_OUT
/*
author : martin
下面表示控件名
结尾必须带空格 作为定义
 
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