#pragma once
#include "QWU_include.h"
#include "QWU_function.h"


struct stct_window {
	string id;
	string res_id; 
	vector<stct_window> cons;
};

//加‘_def’的结构体表示中间的实体应该如何被定义出来，而并非是中间的实体的内容
//例如stct_item_def 表示item的‘定义’结构体，并不是item结构体
//比如item如果表示人的话，item_def结构体内容应该是
//1.定义人类语句中‘class person’中的‘person’字符串本身
//2.定义一个人实例语句‘person sjh’中的‘sjh’字符串本身
//综上所述，_def结构体中的必要元素是某种语言定义语句类似‘int a;’中的所有token[int,a]的类型[type,name];
struct stct_item_def {

	string type;
	string name;
};
struct stct_list_def
{
	int num;
	string name;
	vector<stct_item_def> items;

};


//全局变量
vector<stct_list_def> all_stcts;

//为name添加stct_前缀
//struct person---> struct stct_person
void format_stct_name(stct_list_def& dec12, string name) {
	dec12.name = STCT_PREFIX;
	dec12.name.append(name);
}

void add_stct_def(stct_list_def& dec12, string name, vector<stct_item_def>& items) {

	format_stct_name(dec12, name);
	dec12.items = items;
}
void print_stct(ofstream& out)
{
	/*enum {MaxTipsNum = 3, MaxBoxReward = 5};*/

	out << "//结构体最大宽度定义" << endl;
	out << "enum" << endl;
	out << "{" << endl;


	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		if (i == 0)
		{
			out << "\t" << "MAX_" << formal_allUp(all_stcts[i].name) << "_NUM" << " = " << all_stcts[i].num << endl;
		}
		else
		{
			out << "\t, " << "MAX_" << formal_allUp(all_stcts[i].name) << "_NUM" << " = " << all_stcts[i].num << endl;
		}
	}
	out << "}" << endl;
	/*
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

		}
		*/
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		out << "struct" << " " << all_stcts[i].name << endl;
		out << "{" << endl;

		auto items = all_stcts[i].items;
		for (size_t i = 0; i < items.size(); i++)
		{
			out << "\t" << items[i].type << "   " << items[i].name << ";" << endl;
		}
		out << "\t" << "\n" << endl;
		out << "\t" << all_stcts[i].name << "()" << endl;
		out << "\t" << "{" << endl;
		for (size_t i = 0; i < items.size(); i++)
		{
			out << "\t\t" << items[i].name << "= NULL;" << endl;
		}
		out << "\t" << "}" << endl;
		out << "}" << endl;

		/*
	类似
	private:
		std::vector<AmusementBoxRewrad>			m_box_reward_vec;
	根据结构体定义生成结构体vector
	*/
		out << "private:" << endl;
		out << "\t" << all_stcts[i].name << "   "
			<< all_stcts[i].name << "_arr[" << "MAX_" << all_stcts[i].name << "];" << endl;
	} 
}
void add_list_vector(vector< stct_item_def>& items, string name, int num)
{
	stct_list_def dec;
	//类型判断items  
	//格式化vector
	add_stct_def(dec, name, items);
	dec.num = num;
	all_stcts.push_back(dec);
}
