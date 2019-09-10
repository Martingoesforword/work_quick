#pragma once
#include "tool_includeHelper.h" 
using namespace std;
#define STCT_STRING "stct_"
struct stct_item {
	
	string type;
	string name;
};
struct stct_list
{
	int num;
	string name;
	vector<stct_item> items;

}; 

vector<stct_list> all_stcts;


void format_stct_name(stct_list& dec12,string name) {
	dec12.name = STCT_STRING;
	dec12.name.append(name);
} 
void format_stct(stct_list& dec12, string name, vector<stct_item>& items) {
	 
	format_stct_name(dec12, name);
	dec12.items = items;
}
void print_stct(ostream& out)
{
	/*enum {MaxTipsNum = 3, MaxBoxReward = 5};*/
	out << "enum" << endl;
	out << "{" << endl;

	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		if (i == 0)
		{
			out << "\t" << "MAX_" << all_stcts[i].name << " = " << all_stcts[i].num << endl;
		}
		else
		{
			out << "\t, " << "MAX_" << all_stcts[i].name << " = " << all_stcts[i].num << endl;
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

		}; 
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
		out << "};" << endl;  

			/*
		类似
			std::vector<AmusementBoxRewrad>			m_box_reward_vec;
		根据结构体定义生成结构体vector
		*/	
		out << "std::vector<" << all_stcts[i].name << ">" << "   "
			<< all_stcts[i].name << "_vec;" << endl;
	}
	 
	

}
void addlist(vector< stct_item>& items, string name, int num)
{
	stct_list dec; 
	//类型判断items  
	//格式化vector
	format_stct(dec, name, items);
	dec.num = num;
	all_stcts.push_back(dec); 
}
int main() {
	 
	 
}

