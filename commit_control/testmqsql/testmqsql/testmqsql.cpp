 
#include "pch.h" 
#include <iostream>  
#include <fstream>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <vector>  
 
#include "winsock2.h"  
#include "windows.h"  
#include "mysql.h"   
#include "flag_string.h"
using namespace std;
 
 

int main(int argc, char* argv[])
{
	string path = "D:\\src\\No.1-task-用户机型画像分析\\资源\\1\\beifen\\";
	const char host[] = "localhost";    //MySQL服务器IP地址；若是本地可填写“localhost”或127.0.0.1  
	const char user[] = "root";         //MySQL的用户名  
	const char pswd[] = "root";         //密码  
	const char table[] = "quick_work";        //数据库名称  
	unsigned int port = 3306;           //MySQL服务端口号，默认是3306          
	MYSQL myCont;//创建MYSQL对象，定义数据库连接句柄  
	MYSQL_RES *result;//查询结果集，存放查询结果  
	MYSQL_ROW sql_row;//存放一行查询结果的字符串数组  
	MYSQL_FIELD *fd; // 包含字段信息的结构 
	int res;
	mysql_library_init(0, NULL, NULL);//初始化MySQL库  
	mysql_init(&myCont);//初始化连接处理程序  
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		//通过调用mysql_real_connect()连接到服务器  
		cout << "connect succeed!" << endl;
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文 
		string sql;
		sql = "select * from work_flag; ";
		res = mysql_query(&myCont, sql.c_str());
		result = mysql_store_result(&myCont);
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);// result 查询的结果集
		string flag;
		if(NULL != row)
		{
			flag = row[0];
		}
		mysql_free_result(result); 
		

		//可在这里进行修改，添加自己的标志符
		if (flag == MERGE_SVN_STATE)
		{
			MessageBoxA(NULL,"目前不可提交代码，请注意","错误",0);
		}
		else if(flag != MERGE_SVN_STATE)
		{
			system("C:\\\"Program Files\"\\TortoiseSVN\\bin\\TortoiseProc.exe /command:commit /path:\"F:\\workspace\\QQX5_Mainland\\trunc\\src\\star\"");
		}
		
	} 
	return 0;
}
 