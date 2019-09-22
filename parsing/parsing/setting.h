#pragma once

/*
	setting:
*/
//结构体命名前缀
#define STCT_PREFIX "stct_"

//需要注意的代码处
#define H9D_NOTICE____H9D_NOTICE print_notice notice(out);



/*
	future:
*/
//备注
/*
RUBBISH函数为垃圾函数代码，需要替换，修改和优化

*/

//任务
/*
1.需要将private等放入函数中（或者根据逻辑进行选择）-----ok
2.添加列表init函数for循环-----ok
3.去除mem命名后面冗余的首界面名字-----ok
4.m_前缀-----ok
5.按类型输出，使之整齐划一
6.支持内部独立窗口识别
7.支持控件基本函数生成
8.增加识别信息模块
9.增加UI协同的内容，例如str命名，string文件生成，描述文件的生成等
	1.增加一个输出文件模块，可单独配置
10.滚动框没有实现完全
*/