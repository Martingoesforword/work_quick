#pragma once
#include "tool_includeHelper.h"
#include "tool_indepcontrol.h"
#include "tool_stct.h"
/*
author :matin
此文件提供某些较简单文本结构的构建
此文件提供总体头文件的构建
此文件提供总体头文件的输出
*/  

//将类似wnd_amusement_park转化为UIAmusementPark
//要求：结尾不可为_
string formalIfdef(string hname)
{
	string one = hname.substr(hname.find_first_of("_"), hname.size());
	string two = "UI";
	for (int i = 0; i < one.size(); i++)
	{ 
		if (one[i] != '_')
		{
			two.push_back(one[i]);
		}
		else
		{
			i+=1;
			two.push_back(one[i]-32);
			i += 1;
		}
	}
}

//_hname 需要类似为UIAmusementPark（取wnd_amusement_park这个顶层窗口的wnd之后的部分，并转化格式）、
//
void output_headfile(ostream out,string _hname) {

	/*
	类似
	#ifndef UIAmusementHelp_h
	#define UIAmusementHelp_h
	*/
	out << "#ifndef "<< formalIfdef(_hname) << endl;

	/*
	类似
	#include "../../../UIBase.h"
	需要后面相关处理
	*/
	out << "#include \"UIBase.h\"" << endl;

	/*
	类似
	class CUIAmusementHelp:  public CUIBase
	{ 
	*/
	out << "class " << "C" << formalIfdef(_hname) << ": public CUIBase" << endl;
	out << "{" << endl;

	/*
	类似
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
	tool_enum {MaxTipsNum = 3, MaxBoxReward = 5};
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
	out << "\t" << "C" << formalIfdef(_hname) <<"();"<< endl;
	out << "\t" << "~C" << formalIfdef(_hname) << "();" << endl;
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
	printdefown(out);
 

	/*
	类似
		std::vector<AmusementBoxRewrad>			m_box_reward_vec;
	根据结构体定义生成结构体vector
	*/
	printdefown(out);



	/*
	类似
	private:
		void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
		void OnBtnJumpWeb(H3D_CLIENT::IUIWnd* wnd);
	*/
	out << "private:" << endl;
	


	/*
	类似
	}
	#endif
	*/
	out << "};" << endl;
	out << "#endif"<< endl;
}
 
 