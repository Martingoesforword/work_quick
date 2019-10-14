// list_adapter_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "adapter.h"
#include "ui.h"
#include <vector>
class sjh_data
{
public:
	int64 m_pstid;
	string m_name;
	bool m_is_male;
	bool m_is_selected;
	string m_appellation;
};
class view_base
{
public:
	IUIWnd*   m_wnd_item;
};
class sjh_view/*: public view_base*/
{
public: 
	IUIWnd*   m_wnd_item;
	IUICheckBox*   m_checkBox_choise;
	IUIImage*   m_img_sex;
	IUIStaticText*   m_st_appellation;
	IUIStaticText*   m_st_name;
};	

void updata_func_a_b(sjh_data a, sjh_view b,int index)
{
	//设置名称
	string name = a.m_name;
	b.m_st_name->SetText(name);

	//设置性别（有其他性别）
	const string res_str_img_male = "uir_yunduanxb_xblan";
	const string res_str_img_female = "uir_yunduanxb_xbfen";
	if (a.m_is_male)
	{
		b.m_img_sex->SetResourceID(res_str_img_male);
	}
	else
	{
		b.m_img_sex->SetResourceID(res_str_img_female);
	}

	//设置家族关系
	string appellation = a.m_appellation;
	b.m_st_appellation->SetText(appellation);

	//设置选中状态
	bool is_selected = a.m_is_selected;
	b.m_checkBox_choise->Check(is_selected);

	//列表m_s_friend_control_arr内部wnd_item刷新
	b.m_wnd_item->ShowWindow(true); 

}
int main()
{
	IUIWnd*   m_wnd_item1;
	IUICheckBox*   m_checkBox_choise1;
	IUIImage*   m_img_sex1;
	IUIStaticText*   m_st_appellation1;
	IUIStaticText*   m_st_name1;

	IUIWnd*   m_wnd_item2;
	IUICheckBox*   m_checkBox_choise2;
	IUIImage*   m_img_sex2;
	IUIStaticText*   m_st_appellation2;
	IUIStaticText*   m_st_name2;


	//模拟滚动控件
	I_ScrollBar_Adv* scr;
	//数据
	vector<sjh_data> from_data = { {1,"Yeel",true,true,"儿子"},{2,"Yeel1",true,true,"儿子"},{3,"Yeel2",true,true,"儿子"}, };
	//模拟显示
	vector<sjh_view> to_view = { {m_wnd_item1,m_checkBox_choise1,m_img_sex1,m_st_appellation1,m_st_name1 },{m_wnd_item2,m_checkBox_choise2,m_img_sex2,m_st_appellation2,m_st_name2 } };
	//模拟更新函数 
	ListUpdate<sjh_data, sjh_view> li(scr, from_data, to_view,updata_func_a_b);


}
 