 
#include "winsock2.h"   
#include "windows.h"  
#include <iostream>
#include <string> 
#include "tinyxml.h"
#include <corecrt_io.h>
#include "setting.h" 
#include "mysql.h"

using namespace std;
typedef void(*DEAL_FUNC)(string file_path);

void deal_parse_and_mysql(string file_path, DEAL_FUNC func)
{
	const char host[] = SERVER_ADDR;    
	const char user[] = SERVER_NAME;    
	const char pswd[] = SERVER_PASSWARD;
	const char table[] = SERVER_DBNAME; 
	unsigned int port = SERVER_PROT;    
	MYSQL myCont;//创建MYSQL对象，定义数据库连接句柄  
	//MYSQL_RES *result;//查询结果集，存放查询结果  
	//MYSQL_ROW sql_row;//存放一行查询结果的字符串数组  
	//MYSQL_FIELD *fd; // 包含字段信息的结构
	//char column[32][32];
	int res;
	mysql_library_init(0, NULL, NULL);//初始化MySQL库  
	mysql_init(&myCont);//初始化连接处理程序  
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		//通过调用mysql_real_connect()连接到服务器  
		cout << "connect succeed!" << endl;
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文 
		string sql;
		sql = "CREATE TABLE `quick_work`.`layout_for_reserch`\
 ( `wnd_name` VARCHAR(50) NOT NULL ,\
  `level` INT(20) NOT NULL ,\
  `father1` VARCHAR(50) NOT NULL ,\
  `father2` VARCHAR(50) NOT NULL ,\
  `father3` VARCHAR(50) NOT NULL ,\
  `father4` VARCHAR(50) NOT NULL ,\
  `father5` VARCHAR(50) NOT NULL ,\
  `father6` VARCHAR(50) NOT NULL ,\
  `father7` VARCHAR(50) NOT NULL ,\
  `father8` VARCHAR(50) NOT NULL ,\
  `father9` VARCHAR(50) NOT NULL ,\
  `father10` VARCHAR(50) NOT NULL ,\
  `father11` VARCHAR(50) NOT NULL ,\
  `father12` VARCHAR(50) NOT NULL ) ENGINE = InnoDB;";
		res = mysql_query(&myCont, sql.c_str());//执行查询语句，mysql_query如果查询成功，零；如果出现一个错误，非零。  

		sql = "INSERT INTO layout_for_reserch(wnd_name,level)\
 VALUES ('" + string("fdfd") + "'," + "1" + "); ";
		res = mysql_query(&myCont, sql.c_str());//执行查询语句，mysql_query如果查询成功，零；如果出现一个错误，非零。  
		 
	}
				
}
void fileSearchAndDoMysql(string path, DEAL_FUNC func)
{
	long hFile = 0; 
	struct _finddata_t fileInfo;
	string pathName;
 
	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1)
		return;

	do {
		if (fileInfo.attrib == _A_SUBDIR)
			continue;
		//cout << path + "\\" + fileInfo.name << endl;
		func(path + "\\" + fileInfo.name);
	 
		
	} while (_findnext(hFile, &fileInfo) == 0); 
	_findclose(hFile);
	return;
}
int main()
{
	
	fileSearchAndDoMysql(PATH_MUSIC_T,(DEAL_FUNC)deal_parse_and_mysql);
	//TiXmlDocument doc();
	//TiXmlElement* windows = (TiXmlElement*)doc.FirstChildElement(); 

	//TiXmlElement* firstwindow = (TiXmlElement*)windows->FirstChildElement(); 


 
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
	system("pause");
	return 0;
}
 