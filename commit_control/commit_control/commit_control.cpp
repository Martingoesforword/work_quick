// commit_control.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "mysql.h" 
using namespace std;
int main()
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
		sql = "select commit_state form work_flag";
		res = mysql_query(&myCont, sql.c_str());


	system("C:\\\"Program Files\"\\TortoiseSVN\\bin\\TortoiseProc.exe /command:commit /path:\"F:\\workspace\\QQX5_Mainland\\trunc\\src\\star\"");



    std::cout << "Hello World!\n"; 
}
 