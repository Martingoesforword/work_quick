#pragma once

/*
	setting:
*/
//类成员前缀
#define MEMBER_PREFIX "m_"
//数组后缀
#define ARRAY_POSTFIX_SHORT "_arr" 
#define ARRAY_POSTFIX "_array" 
//结构体命名前缀
#define STCT_PREFIX "struct_"
#define STCT_PREFIX_SHORT "S"
//需要注意的代码处
#define H3D_NOTICE____H3D_NOTICE print_notice notice(out);

//定义空格数
#define DEFINE_SPACE "   "


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
10.滚动框没有实现完全：刷新函数；对回调函数wnd的理解；
11.滚动框命名错误，需要修正
12.参照生成的第一次工作代码：UIReturningPrivateChat.h.cpp进行优化
13.在不同操作回调汇总自动生成需要对数据进行检查的注释
14.类型优化：生成的函数尽量为const
*/


/*
大型结构化任务
1.一期：总结并准备策划，美术，测试后期需要的文档类型集合
2.二期：先实现程序产出的文件生成
3.三期：实现所有的文件生成
4.四期：实现UI协作的工具集
*/