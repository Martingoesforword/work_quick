#pragma once
#include "QWU_include.h"
#include "tinyxml.h" 
#include "QWU_struct.hpp" 
//����һ��xml��ĳ���ڵ�
void IterateXmlNode(string windowname, string path, stct_window& res_window);

//ȥ��NULL�жϺ���
void CheckNULL(void* ptr);
void CheckNULL(int is);

//���ݱ�ǩ����xml���ṹ�в��ҽڵ㲢���ؽڵ��ı���ֻ�ܲ��һ�������Ҷ�ڵ㣩
string findSubByTag(string tag, TiXmlElement* xml);

//����Ҫ�Ĵ����������ɴ������ṹ
void deal_window(stct_window *res, TiXmlElement* xml, bool isWindow);

//����IDΪid��xmlָ��
TiXmlElement* findXmlById(string id, TiXmlElement* xml);


//ʵ��
void CheckNULL(void* ptr)
{
	if (!ptr) { exit(1); }
}
void CheckNULL(int is)
{
	if (!is) { exit(1); }
}
string findSubByTag(string tag, TiXmlElement* xml)
{
	TiXmlNode* node = nullptr;
	for (node = xml->FirstChild(); node; node = node->NextSibling())
	{
		if (node->Type() == TiXmlNode::TINYXML_ELEMENT && !strcmp(node->Value(), tag.c_str()))
		{

			return node->FirstChild() ? node->FirstChild()->Value() : "";
		}
	}
	return "";
}
void deal_window(stct_window *res, TiXmlElement* xml, bool isWindow)
{
	//��ö��㴰������
	string id = findSubByTag("ID", xml);
	string res_id = findSubByTag("ResourceID", xml);
	res->id = id;
	res->res_id = res_id;

	if (!isWindow) return;
	//��ÿؼ�����
	TiXmlNode* node = nullptr;
	for (node = xml->FirstChild(); node; node = node->NextSibling())
	{
		if (node->Type() == TiXmlNode::TINYXML_ELEMENT && !strcmp(node->Value(), "Control"))
		{
			//ѭ����Ѱ�ӽڵ�ΪControl�Ľڵ㣬�����д���
			string conclassname = ((TiXmlElement*)node)->Attribute("Class");
			if (conclassname.compare("Window"))
			{
				//����window�ؼ�
				TiXmlElement* control = (TiXmlElement*)node;
				stct_window control_res;
				deal_window(&control_res, control, false);
				res->subs.push_back(control_res);
			}
			else if (!conclassname.compare("Window"))
			{
				//��window�ؼ�
				TiXmlElement* control = (TiXmlElement*)node;
				stct_window control_res;
				deal_window(&control_res, control, true);
				res->subs.push_back(control_res);
			}
		}

	}
}
void IterateXmlNode(string windowname,string path, stct_window& res_window )
{
	TiXmlDocument doc(path.c_str());
	CheckNULL(doc.LoadFile());
	TiXmlElement* windows = (TiXmlElement*)doc.FirstChildElement();
	CheckNULL(windows);

	TiXmlElement* firstwindow = (TiXmlElement*)windows->FirstChildElement();
	CheckNULL(firstwindow);

	
	//�����һ��window������window�ṹ�� 
	deal_window(&res_window, (TiXmlElement*)firstwindow, true);
	 
	//TiXmlNode* message = nullptr;
	/*
	while (message = messages->IterateChildren(message))
	{
		if (message->Type() == TiXmlNode::TINYXML_ELEMENT)
		{
			cout << message->Value() << ": ";
			TiXmlNode* text = message->FirstChild();
			if (text)
				cout << text->Value() << endl;
		}
	}
	*/
}
TiXmlElement* findXmlById(string id, TiXmlElement* xml)
{
	TiXmlNode* node = nullptr;
	for (node = xml->FirstChild(); node; node = node->NextSibling())
	{
		 
		if (node->Type() == TiXmlNode::TINYXML_ELEMENT 
			&& findSubByTag("ID", (TiXmlElement*)node) == id)
		{
			return  (TiXmlElement*)node;
		}
	}

}