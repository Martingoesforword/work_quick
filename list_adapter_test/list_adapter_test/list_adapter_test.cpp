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

class sjh_view: public view_base 
{
	
public:
	sjh_view(IUIWnd*   m_wnd_item,
		IUICheckBox*   m_checkBox_choise,
		IUIImage*   m_img_sex,
		IUIStaticText*   m_st_appellation,
		IUIStaticText*   m_st_name) :m_wnd_item(m_wnd_item),
	 m_checkBox_choise(m_checkBox_choise),
	 m_img_sex(m_img_sex),
	  m_st_appellation(m_st_appellation),
	 m_st_name(m_st_name)
	{

	}
	IUIWnd*   m_wnd_item;
	IUICheckBox*   m_checkBox_choise;
	IUIImage*   m_img_sex;
	IUIStaticText*   m_st_appellation;
	IUIStaticText*   m_st_name;
};	

void updata_func_a_b(sjh_data a, sjh_view b)
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
	
	IUIWnd*   m_wnd_item1 = nullptr;
	IUICheckBox*   m_checkBox_choise1 = nullptr;
	IUIImage*   m_img_sex1 = nullptr;
	IUIStaticText*   m_st_appellation1 = nullptr;
	IUIStaticText*   m_st_name1 = nullptr;

	IUIWnd*   m_wnd_item2 = nullptr;
	IUICheckBox*   m_checkBox_choise2 = nullptr;
	IUIImage*   m_img_sex2 = nullptr;
	IUIStaticText*   m_st_appellation2 = nullptr;
	IUIStaticText*   m_st_name2 = nullptr;


	//模拟滚动控件
	I_ScrollBar_Adv* scr = nullptr;
	//数据
	sjh_data from_data[] = { {1,"Yeel",true,true,"儿子"},{2,"Yeel1",true,true,"儿子"},{3,"Yeel2",true,true,"儿子"}, };
	//模拟显示
	sjh_view view_item1(m_wnd_item1, m_checkBox_choise1, m_img_sex1, m_st_appellation1, m_st_name1);
	sjh_view view_item2(m_wnd_item2, m_checkBox_choise2, m_img_sex2, m_st_appellation2, m_st_name2);
	vector<sjh_view> to_view = { view_item1,view_item2 };
	//模拟更新函数 
	ListUpdate<sjh_data, sjh_view> li(2,scr, from_data, to_view,updata_func_a_b);


}
 