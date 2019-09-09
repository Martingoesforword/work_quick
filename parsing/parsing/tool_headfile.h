#pragma once
#include "tool_includeHelper.h"
#include "tool_indepcontrol.h"
#include "tool_stct.h"
/*
author :matin
���ļ��ṩĳЩ�ϼ��ı��ṹ�Ĺ���
���ļ��ṩ����ͷ�ļ��Ĺ���
���ļ��ṩ����ͷ�ļ������
*/  

//������wnd_amusement_parkת��ΪUIAmusementPark
//Ҫ�󣺽�β����Ϊ_
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

//_hname ��Ҫ����ΪUIAmusementPark��ȡwnd_amusement_park������㴰�ڵ�wnd֮��Ĳ��֣���ת����ʽ����
//
void output_headfile(ostream out,string _hname) {

	/*
	����
	#ifndef UIAmusementHelp_h
	#define UIAmusementHelp_h
	*/
	out << "#ifndef "<< formalIfdef(_hname) << endl;

	/*
	����
	#include "../../../UIBase.h"
	��Ҫ������ش���
	*/
	out << "#include \"UIBase.h\"" << endl;

	/*
	����
	class CUIAmusementHelp:  public CUIBase
	{ 
	*/
	out << "class " << "C" << formalIfdef(_hname) << ": public CUIBase" << endl;
	out << "{" << endl;

	/*
	����
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
	����
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
	����
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
	����
		std::vector<AmusementBoxRewrad>			m_box_reward_vec;
	���ݽṹ�嶨�����ɽṹ��vector
	*/
	printdefown(out);



	/*
	����
	private:
		void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
		void OnBtnJumpWeb(H3D_CLIENT::IUIWnd* wnd);
	*/
	out << "private:" << endl;
	


	/*
	����
	}
	#endif
	*/
	out << "};" << endl;
	out << "#endif"<< endl;
}
 
 