 
#include "pch.h" 
#include <iostream>  
#include <fstream>    
#include <vector>  
 
#include "winsock2.h"  
#include "windows.h"  
#include "mysql.h"    
#include "tinyxml.h"
#include "setting.h"
#include <time.h>
#include <corecrt_io.h>using namespace std;
#include <string>
typedef void(*DEAL_FUNC)(string file_path);

MYSQL myCont;//创建MYSQL对象，定义数据库连接句柄  
MYSQL_RES *result;//查询结果集，存放查询结果  
MYSQL_ROW sql_row;//存放一行查询结果的字符串数组  
MYSQL_FIELD *fd; // 包含字段信息的结构 
char column[32][32];
int res;
const char host[] = SERVER_ADDR;
const char user[] = SERVER_NAME;
const char pswd[] = SERVER_PASSWARD;
const char table[] = SERVER_DBNAME;
unsigned int port = SERVER_PROT; 

bool init_mysql()
{ 
	mysql_library_init(0, NULL, NULL);//初始化MySQL库  
	mysql_init(&myCont);//初始化连接处理程序  
	return mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0);
}
string get_time_str()
{
	time_t t = time(0);
	char ch[64];
	strftime(ch, sizeof(ch), "%Y-%m-%d %H:%M", localtime(&t)); //年-月-日 时:分
	return string(ch);
}
void init_layout_table()
{
	//通过调用mysql_real_connect()连接到服务器  
	cout << "connect succeed!" << endl;
	mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文 
	string sql;
#ifdef FIRST_FUN
	sql = "CREATE TABLE `quick_work`.`layout_for_reserch`\
 ( `wnd_name` VARCHAR(200) NOT NULL ,\
  `level` INT(20) NOT NULL ,\
  `layout_file` VARCHAR(200) NOT NULL ,\
  `father1` VARCHAR(200) NOT NULL ,\
  `father2` VARCHAR(200) NOT NULL ,\
  `father3` VARCHAR(200) NOT NULL ,\
  `father4` VARCHAR(200) NOT NULL ,\
  `father5` VARCHAR(200) NOT NULL ,\
  `father6` VARCHAR(200) NOT NULL ,\
  `father7` VARCHAR(200) NOT NULL ,\
  `father8` VARCHAR(200) NOT NULL ,\
  `father9` VARCHAR(200) NOT NULL ,\
  `father10` VARCHAR(200) NOT NULL ,\
  `father11` VARCHAR(200) NOT NULL ,\
  `father12` VARCHAR(200) NOT NULL ) ENGINE = InnoDB;";
	res = mysql_query(&myCont, sql.c_str());//执行查询语句，mysql_query如果查询成功，零；如果出现一个错误，非零。  

#endif // FIRST_FUN

	
	sql = "DELETE FROM `layout_for_reserch` WHERE 1";
	mysql_query(&myCont, sql.c_str());
}
void exit_mysql()
{
	mysql_close(&myCont);//关闭MySQL连接  
	mysql_library_end();//关闭MySQL库  

}
int length = 0;
string sqlll;
bool bsubmit = false;
string __formal(string a)
{
	string b = "";
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != '\'' && a[i] != '\\') b.push_back(a[i]);
		else {
			if (a[i] == '\'')
			{
				b.push_back('\\');
				b.push_back('\'');
			}
		}
	}
	return b;
}
void deal_send_mysql(string wnd_name, string file_name, vector<string> vec)
{
	if (length != 0)
	{
		if (length == 1)
		{ 
			sqlll += ";";
			res = mysql_query(&myCont, sqlll.c_str());//执行查询语句，mysql_query如果查询成功，零；如果出现一个错误，非零。  
			if (res == 1)
			{
				system("pause");
			}
			sqlll = "";
			length = 0;
			bsubmit = true;
		}
		else
		{ 
			sqlll += ",('" + __formal(wnd_name) + "'," + to_string(vec.size() + 1) + ",'" + file_name + "'";
			for (int i = 0; i < 12; i++)
			{
				if (i < vec.size())
				{
					sqlll += ",'" + __formal(vec[i]) + "'";
				}
				else
				{
					sqlll += ",''";
				}
			}
			sqlll += ")";
			length++;
			bsubmit = false;
		}
	}
	else
	{
		//将某个wnd的信息插入数据库+描述字段
		string desc = "默认描述";
		sqlll = "INSERT INTO layout_for_reserch(wnd_name,level,layout_file";
		for (int i = 1; i <= 12; i++)
		{
			sqlll += ",father" + to_string(i);
		}
		sqlll += ")";
		sqlll += "VALUES ('" + wnd_name + "'," + to_string(vec.size() + 1) + ",'" + file_name + "'";
		for (int i = 0; i < 12; i++)
		{
			if (i < vec.size())
			{
				sqlll += ",'" + vec[i] + "'";
			}
			else
			{
				sqlll += ",''";
			}
		}
		sqlll += ")";
		length++;
		bsubmit = false;
	}
	


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
string get_id(TiXmlElement* node)
{
	string id = findSubByTag("ID", node);
	return id;
}
void deal_node(string layout_name, TiXmlElement* node,vector<string> vec,int& num)
{ 
	num++;
	//处理自身
	deal_send_mysql(get_id(node), layout_name, vec);

	//处理子元素
	/*添加目前元素到vector*/
	vec.push_back(get_id(node));
	TiXmlElement* sub_window = node->FirstChildElement(); 
	while (sub_window)
	{
		if (sub_window->Type() == TiXmlNode::TINYXML_ELEMENT)
		{
			if (string(sub_window->Value()) ==  "Control")
			{
				//if (string(((TiXmlElement*)sub_window)->Attribute("Class")) == "Window")
				//{
					deal_node(layout_name, sub_window, vec,num);

				//}
				 
			}
		
		}
		sub_window = (TiXmlElement*)sub_window->NextSiblingElement();
	}
}
void IterateXmlNode(string path, string layout_name,int& num)
{
	path += "\\" + layout_name;
	TiXmlDocument doc(path.c_str());
	doc.LoadFile();
	TiXmlElement* windows = (TiXmlElement*)doc.FirstChildElement();
	if (windows == NULL) return;
	TiXmlElement* firstwindow = (TiXmlElement*)windows->FirstChildElement();
	TiXmlElement* now_window = firstwindow;
	//遍历所有节点

	vector<string> vec;
	while (now_window)
	{
		deal_node(layout_name, now_window, vec, num);
		now_window = (TiXmlElement*)now_window->NextSiblingElement();
	}
	
 }
void deal_parse_and_mysql(string path, string file_name,int& num)
{ 
	//对每个文件进行解析
	IterateXmlNode(path, file_name, num);
}
void fileSearchAndDoMysql(string path)
{
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName;

	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1)
		return;

	do {
		if (fileInfo.attrib == _A_SUBDIR)
			continue;
		int num = 0;
		deal_parse_and_mysql(path, fileInfo.name, num);
		cout << fileInfo.name <<"  "<<num<< endl;

	} while (_findnext(hFile, &fileInfo) == 0);
	if (bsubmit == false)
	{
		sqlll += "; ";
		res = mysql_query(&myCont, sqlll.c_str());//执行查询语句，mysql_query如果查询成功，零；如果出现一个错误，非零。  
	 
		sqlll = "";
		length = 0; 
	}
	_findclose(hFile);
	return;
}
int main(int argc, char* argv[])
{ 
	if(!init_mysql()) return 1;
	init_layout_table();
	fileSearchAndDoMysql(PATH_MUSIC_T);
	exit_mysql();
	return 0;
}
 