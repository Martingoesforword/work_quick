// parsing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 
#include <iostream> 
#include "../tinyxml/tinyxml.h" 
using namespace std;
void IterateXmlNode(); 
int main()
{
	IterateXmlNode();
	TiXmlDocument doc;

	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * element = new TiXmlElement("Hello");
	doc.LinkEndChild(element);

	TiXmlText * text = new TiXmlText("World");
	element->LinkEndChild(text);

	doc.SaveFile("C:\\madeByHand.xml"); 
	return 0;
} 
void IterateXmlNode()
{
	TiXmlDocument doc("C:\\madeByHand1.xml");
	if (!doc.LoadFile())
		return;

	TiXmlElement* root =(TiXmlElement*) doc.FirstChildElement();
	if (root == nullptr)
		return; 
	TiXmlElement* messages =(TiXmlElement*) root->FirstChildElement();
	if (messages == nullptr)
		return;

	TiXmlNode* message = nullptr;
	for (message = messages->FirstChild(); message; message = message->NextSibling())
	{
		if (message->Type() == TiXmlNode::TINYXML_ELEMENT)
		{
			cout << message->Value() << ": ";
			TiXmlNode* text = message->FirstChild();
			if (text)
				cout << text->Value() << endl;
		}
	}
	system("pause");
	//TiXmlNode* message = nullptr;
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
} 