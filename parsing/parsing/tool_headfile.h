#pragma once
#include "tool_includeHelper.h"
#include "tool_indepcontrol.h"
#include "tool_stct.h"
#include "tool.h"
/*
author :matin
���ļ��ṩĳЩ�ϼ��ı��ṹ�Ĺ���
���ļ��ṩ����ͷ�ļ��Ĺ���
���ļ��ṩ����ͷ�ļ������
*/  


//_hname ��Ҫ����ΪUIAmusementPark��ȡwnd_amusement_park������㴰�ڵ�wnd֮��Ĳ��֣���ת����ʽ����
//
void output_headfile(ofstream& out,string _hname) {

	/*
	����
	#ifndef UIAmusementHelp_h
	#define UIAmusementHelp_h
	*/
	out << "#ifndef UI"<< formalFirstUpDeleteOne(_hname)<<"_H" << endl;
	out << "#define UI" << formalFirstUpDeleteOne(_hname)<<"_H" << endl;
	/*
	����
	#include "../../../UIBase.h"
	��Ҫ������ش���
	*/
	out << "#include \"UIBase.h\"" << endl;
	out << "#include <vector>" << endl;

	/*
	����
	class CUIAmusementHelp:  public CUIBase
	{ 
	*/
	out << "class " << "CUI" << formalFirstUpDeleteOne(_hname) << ": public CUIBase" << endl;
	out << "{" << endl;

	/*
	����
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
	
	����
		std::vector<AmusementBoxRewrad>			m_box_reward_vec;
	���ݽṹ�嶨�����ɽṹ��vector
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
	����
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
	����
	private:
		void OnBtnClose(H3D_CLIENT::IUIWnd* wnd);
		void OnBtnJumpWeb(H3D_CLIENT::IUIWnd* wnd);
	*/
	out << "private:" << endl;
	printonfunsign(out, "CUI" + formalFirstUpDeleteOne(_hname));


	/*
	����
	}
	#endif
	*/
	out << "};" << endl;
	out << "#endif"<< endl;
}
 
 