#pragma once
#include "helper.h" 
#include "enum.h"

struct stct_indepinfo
{
	string type;
	string name;
	string parentname; 
	bool Isonclick;
	string onclickname;
};

vector< stct_indepinfo> indeps;
  

//实现
//将类似btn_close转化为close
string formalId(string id)
{
	string ret = id.substr(id.find_first_of("_")+1, id.size());
	return ret;
}
//parentconbinename为类似 （wnd_amusement_park_list） ,表示window树结构
void add(string conclassname, string id,string parentconbinename,bool isonclick = false)
{
	if (conclassname.compare(H9D_BTN_CLASS))
	{
		stct_indepinfo indep;
		indep.type = H9D_BTN;
		indep.name = "btn_" + formalId(parentconbinename) + "_" + formalId(id);
		indep.parentname = parentconbinename;
		if (isonclick)
		{
			indep.Isonclick = true;
			indep.onclickname = "on_btn_" + formalId(parentconbinename) + "_" + formalId(id);
		}
		indeps.push_back(indep);
	}
	else if(conclassname.compare(H9D_IMG_CLASS))
	{
		stct_indepinfo indep;
		indep.type = H9D_IMG;
		indep.name = "img_" + formalId(parentconbinename) + "_" + formalId(id);
		indep.parentname = parentconbinename; 
		indep.Isonclick = false;
		indeps.push_back(indep);
	}
	else if (conclassname.compare(H9D_ST_CLASS))
	{
		stct_indepinfo indep;
		indep.type = H9D_ST;
		indep.name = "st_" + formalId(parentconbinename) + "_" + formalId(id);
		indep.parentname = parentconbinename;
		indep.Isonclick = false;
		indeps.push_back(indep);
	}
	else if (conclassname.compare(H9D_WND_CLASS))
	{
		stct_indepinfo indep;
		indep.type = H9D_WND;
		indep.name = "wnd_" + formalId(parentconbinename) + "_" + formalId(id);
		indep.parentname = parentconbinename;
		indep.Isonclick = false;
		indeps.push_back(indep);
	}
}

void printdefown(ostream& out)
{
	for ( vector< stct_indepinfo>::iterator i = indeps.begin(); i != indeps.end(); i++)
	{
		//实现将所有定义输出 
	}
}
void printinitown(ostream& out)
{
	for (vector< stct_indepinfo>::iterator i = indeps.begin(); i != indeps.end(); i++)
	{
		//实现将所有初始化输出
 
	}
}
void printonfunown(ostream& out)
{
	for (vector< stct_indepinfo>::iterator i = indeps.begin(); i != indeps.end(); i++)
	{
		//实现将所有onbtn函数声明输出::不需要加结尾的分号，可重用于定义部分
 
	}
}
 