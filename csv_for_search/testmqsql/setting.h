#pragma once
#define PATH_STRINGS_ZH_CN "F:\\workspace\\a\\trunc\\exe\\resources\\strings\\zh_cn"
#define SERVER2
#ifdef SERVER1
#define SERVER_ADDR "172.17.100.114"
#define SERVER_NAME "hardcore"
#define SERVER_PASSWARD "111111"

#endif
#ifdef SERVER2
#define SERVER_ADDR "139.155.25.107"
#define SERVER_NAME "root"
#define SERVER_PASSWARD "mysqlsong8713"
#endif
#define SERVER_DBNAME "csv"
#define SERVER_PROT 3306

#define ITEM_NUM_PER_SEND 1000