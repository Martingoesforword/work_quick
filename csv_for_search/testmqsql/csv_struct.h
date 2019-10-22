#pragma once
#include <string> 
#include <iostream>
#include <fstream> //定义读写已命名文件的类型
#include <vector>
#include <sstream> //多定义的类型则用于读写存储在内存中的string对象

using namespace std;
struct csv_kv
{
	string key;
	string value; 
	csv_kv(string key1,
	string value1)
	{
		key = key1;
		value = value1;
	}
};

void parsecsvfile(string file_name, vector<csv_kv>& vec,int & num)
{
	ifstream inFile(file_name, ios::in); 
	string lineStr; 
	while (getline(inFile, lineStr))  
	{ 
		num++;
		string now_str = lineStr;
		int point = lineStr.find_first_of(',');
		if (point == string::npos) {
			continue;
		} 
		string key_str = lineStr.substr(0, point);
		 
		if (now_str.empty() || (now_str.size() > 0 && now_str[point +1] == '"' && now_str[now_str.size() - 1] != '"'&& now_str[now_str.size() - 2] != '"'))
		{
			
			do
			{
				getline(inFile, now_str);
				lineStr += "\n" + now_str;  
			} while (now_str.size() && (now_str.size()>1&& now_str[now_str.size() - 1] != '"' && now_str.size() > 2 && now_str[now_str.size() - 2] != '"' &&now_str.size() > 3 && now_str[now_str.size() - 3] != '"' &&now_str.size() > 4 && now_str[now_str.size() - 4] != '"' &&now_str.size() > 5 && now_str[now_str.size() - 5] != '"'&&now_str.size() > 6 && now_str[now_str.size() - 6] != '"'&&now_str.size() > 7 && now_str[now_str.size() - 7] != '"'));
		} 
		if (lineStr.size() <= lineStr.size() - point - 1) continue;
		string value_str = lineStr.substr(point +1, lineStr.size()- point -1);
		if (key_str.empty() || value_str.empty())
		{
			continue;
		}
		csv_kv kv(key_str, value_str);

		vec.push_back(kv);
		 
	}

}