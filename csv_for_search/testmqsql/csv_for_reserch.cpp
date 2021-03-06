 
#include <iostream>  
#include <fstream>    
#include <vector>  
 
#include "winsock2.h"  
#include "windows.h"  
#include "mysql.h"     
#include "setting.h" 
#include <time.h>
#include <corecrt_io.h>
#include <string>
#include "csv_struct.h"
using namespace std;
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
void init_csv_table()
{
	//通过调用mysql_real_connect()连接到服务器  
	cout << "connect succeed!" << endl;
	mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文 
	string sql;
	sql = "CREATE TABLE `csv`.`csv_for_reserch`\
 ( `key_name` VARCHAR(200) NOT NULL ,\
  `value_name` VARCHAR(2000) NOT NULL, \
  `csv_file` VARCHAR(100) NOT NULL)\
  ENGINE = InnoDB;";
	res = mysql_query(&myCont, sql.c_str());//执行查询语句，mysql_query如果查询成功，零；如果出现一个错误，非零。  
	sql = "DELETE FROM `csv`.`csv_for_reserch` WHERE 1";
	mysql_query(&myCont, sql.c_str());
	sql = "CREATE TABLE `csv`.`csv_for_reserch_select_time`( `time` VARCHAR(50) NOT NULL) ENGINE = InnoDB;";
	mysql_query(&myCont, sql.c_str());   
	sql = "CREATE TABLE `csv`.`csv_for_reserch_update_time`( `time` VARCHAR(50) NOT NULL) ENGINE = InnoDB;";
	mysql_query(&myCont, sql.c_str());
	sql = "DELETE FROM `csv`.`csv_for_reserch_update_time` WHERE 1;";
	mysql_query(&myCont, sql.c_str());
	sql = "INSERT INTO csv_for_reserch_update_time(time) VALUES ('"+ get_time_str() +"');";
	mysql_query(&myCont, sql.c_str());
}
void exit_mysql()
{
	mysql_close(&myCont);//关闭MySQL连接  
	mysql_library_end();//关闭MySQL库  

} 
string __formal(string a)
{
	string b = "";
	for (int i = 0; i<a.size();i++)
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
 
string formal(string a)
{
	if (a.find('\\') != string::npos || a.find('\'') != string::npos)
	{
		return __formal(a);
	} 
	
	return a;
}
void deal_send_mysql(vector<csv_kv>& vec,string file_name)
{
	for (int j = 0; j < vec.size(); j+= ITEM_NUM_PER_SEND)
	{
		string sqlll;
		sqlll = "INSERT INTO `csv`.`csv_for_reserch`(key_name,value_name,csv_file) VALUES";
		if (vec.size() == 0) return;
		string key = vec[0].key;
		string value = vec[0].value;
		sqlll += "('" + formal(key) + "','" + formal(value) + "','" + file_name + "')";
		for (int i = j; i < vec.size() && i < j+ ITEM_NUM_PER_SEND; i++)
		{

			key = vec[i].key;
			value = vec[i].value;
			sqlll += ",('" + formal(key) + "','" + formal(value) + "','" + file_name + "')";
		}
		sqlll += ';';
		res = mysql_query(&myCont, sqlll.c_str());//执行查询语句，mysql_query如果查询成功，零；如果出现一个错误，非零。  

		if (res == 1)
		{
			for (int i = 0; i < vec.size(); i++)
			{
				sqlll = "INSERT INTO `csv`.`csv_for_reserch`(key_name,value_name,csv_file) VALUES";
				sqlll += "('" + vec[i].key + "','" + formal(vec[i].value) + "','" + file_name + "');";
				res = mysql_query(&myCont, sqlll.c_str());
				if (res == 1)
				{
				}
			}
		}
	}
	
} 

void IterateCSVNode(string path, string csv_name,int& num)
{
	num++;
	path += string("\\") + csv_name;
	
	vector<csv_kv> kvv;
	parsecsvfile(path, kvv, num); 
	deal_send_mysql(kvv, csv_name);
	
 }
void deal_parse_and_mysql(string path, string file_name,int& num)
{ 
	//对每个文件进行解析
	IterateCSVNode(path, file_name, num);
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
	_findclose(hFile);
	return;
}
int main(int argc, char* argv[])
{ 
	if(!init_mysql()) return 1;
	init_csv_table();
	fileSearchAndDoMysql(PATH_STRINGS_ZH_CN);
	exit_mysql();
	return 0;
}
 