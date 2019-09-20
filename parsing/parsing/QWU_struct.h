#pragma once
#include "QWU_include.h"
#include "QWU_function.h"


struct stct_window {
	string id;
	string res_id; 
	vector<stct_window> cons;
};

//�ӡ�_def���Ľṹ���ʾ�м��ʵ��Ӧ����α�������������������м��ʵ�������
//����stct_item_def ��ʾitem�ġ����塯�ṹ�壬������item�ṹ��
//����item�����ʾ�˵Ļ���item_def�ṹ������Ӧ����
//1.������������С�class person���еġ�person���ַ�������
//2.����һ����ʵ����䡮person sjh���еġ�sjh���ַ�������
//����������_def�ṹ���еı�ҪԪ����ĳ�����Զ���������ơ�int a;���е�����token[int,a]������[type,name];
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


//ȫ�ֱ���
vector<stct_list_def> all_stcts;

//Ϊname���stct_ǰ׺
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

	out << "//�ṹ������ȶ���" << endl;
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
	����
	private:
		std::vector<AmusementBoxRewrad>			m_box_reward_vec;
	���ݽṹ�嶨�����ɽṹ��vector
	*/
		out << "private:" << endl;
		out << "\t" << all_stcts[i].name << "   "
			<< all_stcts[i].name << "_arr[" << "MAX_" << all_stcts[i].name << "];" << endl;
	} 
}
void add_list_vector(vector< stct_item_def>& items, string name, int num)
{
	stct_list_def dec;
	//�����ж�items  
	//��ʽ��vector
	add_stct_def(dec, name, items);
	dec.num = num;
	all_stcts.push_back(dec);
}
