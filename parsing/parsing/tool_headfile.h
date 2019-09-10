#pragma once
#include "tool_includeHelper.h"
#include "tool_indepcontrol.h"
#include "tool_stct.h"
#include "tool.h"
/*
author :matin
此文件提供某些较简单文本结构的构建
此文件提供总体头文件的构建
此文件提供总体头文件的输出
*/  


//_hname 需要类似为UIAmusementPark（取wnd_amusement_park这个顶层窗口的wnd之后的部分，并转化格式）、
//
void output_headfile(ofstream& out,string _hname) {

	/*
	类似
	#ifndef UIAmusementHelp_h
	#define UIAmusementHelp_h
	*/
	out << "#ifndef UI"<< formalFirstUpDeleteOne(_hname)<<"_H" << endl;
	out << "#define UI" << formalFirstUpDeleteOne(_hname)<<"_H" << endl;
	/*
	类似
	#include "../../../UIBase.h"
	需要后面相关处理
	*/
	out << "#include \"UIBase.h\"" << endl;
	out << "#include <vector>" << endl;

	/*
	类似
	class CUIAmusementHelp:  public CUIBase
	{ 
	*/
	out << "class " << "CUI" << formalFirstUpDeleteOne(_hname) << ": public CUIBase" << endl;
	out << "{" << endl;

	/*
	类似
	enum {MaxTipsNum = 3, MaxBoxReward = 5};
	struct AmusementBoxRewrad
	{
		H3D_CLIENT::IUIWnd*			wnd_boxReward;
		H3D_CLIENT::IUIButton*		btn_Reward; 
		H3D_CLIENT::IUIStaticText*	st_RewardNum;
		H3D_CLIENT::IUIEffectWnd*	effect_Reward;

		AmusementBoxRewrad()
		{
			wnd_boxReward = NULL;
			btn_Reward = NULL;
			st_RewardNum = NULL;
			effect_Reward = NULL;
		}

	};
	
	类似
		std::vector<AmusementBoxRewrad>			m_box_reward_vec;
	根据结构体定义生成结构体vector
	*/ 
	print_stct(out); 

	/*
	类似
	public:
		CUIAmusementHelp();
		~CUIAmusementHelp();
		void ShowWnd();
	protected:
		virtual void OnShow();
		virtual void OnHide(); 
	private:
		void Init();
		bool IsShow();
	*/
	out << "public:" << endl;
	out << "\t" << "CUI" << formalFirstUpDeleteOne(_hname) <<"();"<< endl;
	out << "\t" << "~CUI" << formalFirstUpDeleteOne(_hname) << "();" << endl;
	out << "\t" << "void ShowWnd();" << endl;
	out << "protected:" << endl;
	out << "\t" << "virtual void OnShow();" << endl;
	out << "\t" << "virtual void OnHide();" << endl;
	out << "private:" << endl;
	out << "\t" << "void Init();" << endl;
	out << "\t" << "bool IsShow();" << endl;

	/*
	类似
	private:
		H3D_CLIENT::IUIWnd*			m_wnd_helpTip;
		H3D_CLIENT::IUIButton*		m_btn_close;  
		H3D_CLIENT::IUIImage*		m_img_background;
		H3D_CLIENT::IUIStaticText*	m_st_title;
		H3D_CLIENT::IUIStaticText*	m_st_helpContent;
		
	*/
	out << "private:" << endl;  
	out << "\t" <<"H3D_CLIENT::IUIWnd*   "<<_hname<<";" << endl;
	printmemberdef(out);
 




	/*
	类似
	private:
		void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
		void OnBtnJumpWeb(H3D_CLIENT::IUIWnd* wnd);
	*/
	out << "private:" << endl;
	printonfunsign(out, "CUI" + formalFirstUpDeleteOne(_hname));


	/*
	类似
	}
	#endif
	*/
	out << "};" << endl;
	out << "#endif"<< endl;
}
 
 