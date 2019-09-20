#pragma once
#include "QWU_include.h"
#include "tinyxml.h" 
#include "QWU_struct.hpp" 
//解析一个xml的某个节点
void IterateXmlNode(string windowname, string path, stct_window& res_window);

//去除NULL判断函数
void CheckNULL(void* ptr);
void CheckNULL(int is);

//根据标签名在xml树结构中查找节点并返回节点文本（只能查找基本的子叶节点）
string findSubByTag(string tag, TiXmlElement* xml);

//将必要的窗口数据生成窗口树结构
void deal_window(stct_window *res, TiXmlElement* xml, bool isWindow);

//查找ID为id的xml指针
TiXmlElement* findXmlById(string id, TiXmlElement* xml);


//实现
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
	//获得顶层窗口属性
	string id = findSubByTag("ID", xml);
	string res_id = findSubByTag("ResourceID", xml);
	res->id = id;
	res->res_id = res_id;

	if (!isWindow) return;
	//获得控件属性
	TiXmlNode* node = nullptr;
	for (node = xml->FirstChild(); node; node = node->NextSibling())
	{
		if (node->Type() == TiXmlNode::TINYXML_ELEMENT && !strcmp(node->Value(), "Control"))
		{
			//循环找寻子节点为Control的节点，并进行处理
			string conclassname = ((TiXmlElement*)node)->Attribute("Class");
			if (conclassname.compare("Window"))
			{
				//不是window控件
				TiXmlElement* control = (TiXmlElement*)node;
				stct_window control_res;
				deal_window(&control_res, control, false);
				res->subs.push_back(control_res);
			}
			else if (!conclassname.compare("Window"))
			{
				//是window控件
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

	
	//处理第一个window，建立window结构体 
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