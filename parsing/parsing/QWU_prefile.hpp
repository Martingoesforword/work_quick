#pragma once
#include "QWU_include.h"
#include "QWU_independent.hpp"
#include "QWU_struct.hpp"
#include "QWU_function.h"
/*
author :matin
此文件提供所有配置文件的输出
1.字符串csv
2.布局文件对应关系----需要后期再布局编辑器中提供支持（增加字段，或者使用无效字段，或者使用caption：str_xxxxx;含义，然后进行解析，但需要在程序中全部初始化caption）
3.小细节注意点：例如滚动条注意点；文字csv注意点等；代码效率注意点；代码规范注意点；
4.mmp位置注意----后期可以进行独立更新，每日更新并推送
5.常用路径注意：资源路径；配置路径；布局路径；特效路径；需分设计路径；track执行案路径
6.项目路径：dump路径---后期可以直接打开最新dump文件；
7.生成bug自反馈文档初始状态
8.
*/


//_hname 需要类似为UIAmusementPark（取wnd_amusement_park这个顶层窗口的wnd之后的部分，并转化格式）、
//
void output_prefile(ofstream& out, string _hname1, string _hname2, string _hname3); 


//实现
 
void output_prefile_1(ofstream& out, string _hname) {



}
void output_prefile_2(ofstream& out, string _hname) {



}
void output_prefile_3(ofstream& out, string _hname) {



}
void output_prefile(ofstream& out, string _hname1, string _hname2, string _hname3) {
	_hname1 = "./协作/readme.txt";
	_hname1 = "./自检/readme.txt";
	_hname1 = "./说明/readme.txt";
	
	
	output_prefile_1(out, _hname1);
	output_prefile_2(out, _hname2);
	output_prefile_3(out, _hname3);
	 
}

