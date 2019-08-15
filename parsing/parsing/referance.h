#pragma once

#ifndef LIST_H9D_CONTROL
/*
author : martin
下面表示控件名
结尾必须带空格 作为定义
 
*/
constexpr auto H9D_BTN = "H3D_CLIENT::IUIButton* " ;
constexpr auto H9D_WND = "H3D_CLIENT::IUIWnd* " ;
constexpr auto H9D_ST = "H3D_CLIENT::IUIStaticText* " ;
constexpr auto H9D_SCR = "H3D_CLIENT::I_ScrollBar_Adv* " ;
constexpr auto H9D_IMG = "H3D_CLIENT::IUIImage* " ; 
constexpr auto H9D_CHK = "H3D_CLIENT::IUICheckBox* " ;
constexpr auto H9D_EDBX = "H3D_CLIENT::IUIEditBox* " ;
constexpr auto H9D_EFCT = "H3D_CLIENT::IUIEffectWnd* " ;
constexpr auto H9D_PRCCBR = "H3D_CLIENT::IUIProgressBar* " ;
#endif

#ifndef LIST_H9D_CONTROL_CLASS
constexpr auto H9D_BTN_CLASS = "Button";
constexpr auto H9D_WND_CLASS = "Window";
constexpr auto H9D_ST_CLASS = "StaticText";
constexpr auto H9D_SCR_CLASS = "ScrollControl";
constexpr auto H9D_IMG_CLASS = "Image";
constexpr auto H9D_CHK_CLASS = "CheckBox";
constexpr auto H9D_EDBX_CLASS = "RichEditR";
constexpr auto H9D_EFCT_CLASS = "EffectWnd";
constexpr auto H9D_PRCCBR_CLASS = "H3D_CLIENT::IUIProgressBar* ";
#endif