#pragma once
#include "QWU_include.h"
#include "QWU_independent.hpp"
#include "QWU_struct.hpp"
#include "QWU_function.h"
/*
author :matin
���ļ��ṩ���������ļ������
1.�ַ���csv
2.�����ļ���Ӧ��ϵ----��Ҫ�����ٲ��ֱ༭�����ṩ֧�֣������ֶΣ�����ʹ����Ч�ֶΣ�����ʹ��caption��str_xxxxx;���壬Ȼ����н���������Ҫ�ڳ�����ȫ����ʼ��caption��
3.Сϸ��ע��㣺���������ע��㣻����csvע���ȣ�����Ч��ע��㣻����淶ע��㣻
4.mmpλ��ע��----���ڿ��Խ��ж������£�ÿ�ո��²�����
5.����·��ע�⣺��Դ·��������·��������·������Ч·����������·����trackִ�а�·��
6.��Ŀ·����dump·��---���ڿ���ֱ�Ӵ�����dump�ļ���
7.����bug�Է����ĵ���ʼ״̬
8.
*/


//_hname ��Ҫ����ΪUIAmusementPark��ȡwnd_amusement_park������㴰�ڵ�wnd֮��Ĳ��֣���ת����ʽ����
//
void output_prefile(ofstream& out, string _hname1, string _hname2, string _hname3); 


//ʵ��
 
void output_prefile_1(ofstream& out, string _hname) {



}
void output_prefile_2(ofstream& out, string _hname) {



}
void output_prefile_3(ofstream& out, string _hname) {



}
void output_prefile(ofstream& out, string _hname1, string _hname2, string _hname3) {
	_hname1 = "./Э��/readme.txt";
	_hname1 = "./�Լ�/readme.txt";
	_hname1 = "./˵��/readme.txt";
	
	
	output_prefile_1(out, _hname1);
	output_prefile_2(out, _hname2);
	output_prefile_3(out, _hname3);
	 
}

