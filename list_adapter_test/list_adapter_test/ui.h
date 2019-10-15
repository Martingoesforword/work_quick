#pragma once 
#include <string>
using namespace std;
class IUIWnd 
{
public:
	void ShowWindow(bool show) {}
};
class IUICheckBox : public IUIWnd
{
private:
	bool ischeck;
public:
	void Check(bool check) { ischeck = check; }
};
class IUIImage : public IUIWnd
{
private:
	string id;
public:
	void SetResourceID(string id1) { id = id1; }
};
class IUIStaticText : public IUIWnd
{
private:
	string caption;
public:
	void SetText(string caption1) { caption = caption1; }
}; 
class I_ScrollBar_Adv : public IUIWnd
{ 
}; 