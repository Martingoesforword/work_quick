#pragma once
#include "QWU_include.h"
#include "QWU_function.h"


struct stct_window {
	string id;
	string res_id; 
	vector<stct_window> subs;
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
	string context_id;
	vector<stct_item_def> items;

};


//ȫ�ֱ���
vector<stct_list_def> all_stcts;

//Ϊname���stct_ǰ׺
//struct person---> struct stct_person
void format_stct_name(stct_list_def& dec12, string name);
void add_stct_def(stct_list_def& dec12, string name, vector<stct_item_def>& items);
void print_stct(ofstream& out);
void print_stct_init_def(ofstream& out);

void format_stct_name(stct_list_def& dec12, string name) {
	dec12.name = STCT_PREFIX;
	dec12.name.append(name);
}

void add_stct_def(stct_list_def& dec12, string name, vector<stct_item_def>& items, string context_id) 
{

	format_stct_name(dec12, name);
	dec12.items = items;
	dec12.context_id = context_id;
}
void print_stct(ofstream& out)
{
	/*enum {MaxTipsNum = 3, MaxBoxReward = 5};*/

	out << "\t" << "//�ṹ������ȶ���" << endl;
	out << "\t" << "enum" << endl;
	out << "\t" << "{" << endl;


	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		if (i == 0)
		{
			out << "\t" <<  "\t" << "MAX_" << formal_allUp(all_stcts[i].name) << "_NUM" << " = " << all_stcts[i].num << endl;
		}
		else
		{
			out << "\t"<<  "\t, " << "MAX_" << formal_allUp(all_stcts[i].name) << "_NUM" << " = " << all_stcts[i].num << endl;
		}
	}
	out << "\t" << "}" << endl;
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
		out << "\t" << "struct" << " " << all_stcts[i].name << endl;
		out << "\t" << "{" << endl;

		auto items = all_stcts[i].items;
		out << "\t" << "\tH3D_CLIENT::IUIWnd*   wnd_item;" <<endl;
		for (size_t i = 0; i < items.size(); i++)
		{
			out << "\t" << "\t" << items[i].type << "   " << items[i].name << ";" << endl;
		}
		out << "\t" << "\t" << "\n" << endl;
		out << "\t" << "\t" << all_stcts[i].name << "()" << endl;
		out << "\t" << "\t" << "{" << endl;
		out << "\t" << "\t\twnd_item = NULL" << endl;
		for (size_t i = 0; i < items.size(); i++)
		{
			out << "\t" << "\t\t" << items[i].name << " = NULL;" << endl;
		}
		out << "\t" << "\t" << "}" << endl;
		out << "\t" << "}" << endl;

		/*
	����
	private:
		std::vector<AmusementBoxRewrad>			m_box_reward_vec;
	���ݽṹ�嶨�����ɽṹ��vector
	*/
		out << "private:" << endl;
		out << "\t" << all_stcts[i].name << "   "
			<< all_stcts[i].name << "_arr[" << "MAX_" << formal_allUp(all_stcts[i].name) << "_NUM" << "];" << endl;
	} 
}
void add_list_vector(vector< stct_item_def>& items, string name, int num, string context_id)
{
	stct_list_def dec;
	//�����ж�items  
	//��ʽ��vector
	add_stct_def(dec, name, items, context_id);
	dec.num = num;
	all_stcts.push_back(dec);
}

void print_stct_init_def(ofstream& out)
{
	for (size_t i = 0; i < all_stcts.size(); i++)
	{
		stct_list_def def = all_stcts[i];
		out << "\tfor (int i = 0; i < MAX_" << formal_allUp(def.name) << "_NUM; i++)" << endl;
		out << "\t{" << endl;

		out << "\t\tInitControl(this, " << all_stcts[i].name << "_arr[i]" << "." << "wnd_item" << ", " << "m_wnd_content_list_chatmember, L\"item\" + toWchar(i)); " << endl;
		for (size_t j = 0; j < def.items.size(); j++)
		{
			stct_item_def item_def = def.items[j];
			out <<"\t\tInitControl(this, "<< all_stcts[i].name << "_arr[i]"<<"." << item_def.name<<", "<< all_stcts[i].name << "_arr[i]"<<".wnd_item, L\""<< item_def.name<<"\");"<<endl;

		}

		out << "\t}" << endl;
	}
}