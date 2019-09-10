#pragma once
#include "tool_includeHelper.h" 
#include "tool_staticText.h"
#include "tool.h"
 

struct stct_indepinfo
{ 
	string type;	 
	string name;
	string idname;
	string parentname; 
	bool Isonclick;
	string onclickname;
};

vector< stct_indepinfo> indeps; 

//parentconbinenameΪ���� ��wnd_amusement_park_list�� ,��ʾwindow���ṹ
void add(string conclassname, string id,string parentconbinename,bool isonclick = false)
{
	if (!conclassname.compare(H9D_BTN_CLASS))
	{
		stct_indepinfo indep;
		indep.type = H9D_BTN;
		indep.idname = id;
		indep.name = "btn_" + formalId(parentconbinename) + "_" + formalId(id);
		indep.parentname = parentconbinename;
		if (isonclick)
		{
			indep.Isonclick = true;
			indep.onclickname = "on_btn_" + formalId(parentconbinename) + "_" + formalId(id);
		}
		indeps.push_back(indep);
	}
	else if(!conclassname.compare(H9D_IMG_CLASS))
	{
		stct_indepinfo indep;
		indep.type = H9D_IMG;
		indep.idname = id;
		indep.name = "img_" + formalId(parentconbinename) + "_" + formalId(id);
		indep.parentname = parentconbinename; 
		indep.Isonclick = false;
		indeps.push_back(indep);
	}
	else if (!conclassname.compare(H9D_ST_CLASS))
	{
		stct_indepinfo indep;
		indep.type = H9D_ST;
		indep.idname = id;
		indep.name = "st_" + formalId(parentconbinename) + "_" + formalId(id);
		indep.parentname = parentconbinename;
		indep.Isonclick = false;
		indeps.push_back(indep);
	}
	else if (!conclassname.compare(H9D_WND_CLASS))
	{
		stct_indepinfo indep;
		indep.type = H9D_WND;
		indep.idname = id;
		indep.name = "wnd_" + formalId(parentconbinename) + "_" + formalId(id);
		indep.parentname = parentconbinename;
		indep.Isonclick = false;  
		indeps.push_back(indep);
	}
	else if (!conclassname.compare(H9D_SCR_CLASS))
	{
		stct_indepinfo indep;
		indep.type = H9D_SCR;
		indep.idname = id;
		indep.name = "scr_" + formalId(parentconbinename) + "_" + formalId(id);
		indep.parentname = parentconbinename;
		indep.Isonclick = false;
		indeps.push_back(indep);
	}
}

void printdefown(ofstream& out)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//ʵ�ֽ����ж������ 
		out << "\t" << indeps[i].type << "   " << indeps[i].name << ";" << endl;
	}
}
void printinitown(ofstream& out,string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//ʵ�ֽ����г�ʼ�����
		//����InitControl(this, m_richedit_content, m_wnd, L"rt_tips");
		//InitControl(this, m_btn_close, m_wnd, L"btn_close", SetPressFunc(&CUIAmusementParkHelp::OnBtnClose));
		if (!indeps[i].Isonclick)
		{
			out << "\t" << "InitControl(this"
				<< ", " << indeps[i].name
				<< ", " << indeps[i].parentname
				<< ", " << "L\"" << indeps[i].idname << "\");"
				<< endl;
		}
		else
		{
			out << "\t" << "InitControl(this"
				<< ", " << indeps[i].name
				<< ", " << indeps[i].parentname
				<< ", " << "L\"" << indeps[i].idname << "\""
				<<", "<<"SetPressFunc(&"<<globleclassname<<"::"<<indeps[i].onclickname<<"));"
				<< endl;
		}
	
		
	}
}
void printonfunown(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//ʵ�ֽ�����onbtn�����������::����Ҫ�ӽ�β�ķֺţ��������ڶ��岿��
		//����void CUIAmusementParkHelp::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
		if (indeps[i].Isonclick)
		{
			out << "\t" << "void " << globleclassname << "::" << indeps[i].onclickname
				<< "(H3D_CLIENT::IUIWnd* wnd);" << endl;
		}
	}
}
void printonfundef(ofstream& out, string globleclassname)
{
	for (size_t i = 0; i < indeps.size(); i++)
	{
		//ʵ�ֽ�����onbtn�����������::����Ҫ�ӽ�β�ķֺţ��������ڶ��岿��
		//����void CUIAmusementParkHelp::OnBtnClose(H3D_CLIENT::IUIWnd* wnd)
		if (indeps[i].Isonclick)
		{
			out << "void " << globleclassname << "::" << indeps[i].onclickname
				<< "(H3D_CLIENT::IUIWnd* wnd)" << endl;
			out << "{" << endl;
			out << "\t" <<"//����д����Ĵ���"<< endl;
			out << "}" << endl;
		}
	}
}
