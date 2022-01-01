#pragma once
#include "Xeneth-XVI.h"
#include<iostream>
#include<string>
#include <Windows.h>
using namespace std;
class xviHeader
{
	XVIHANDLE*	h;
	XviError	e;
	string		filename;
public:
	xviHeader();			//	Ĭ�Ϲ��캯��
	xviHeader(string file); //	�вι���
	~xviHeader();
	bool OpenXvi(const char* file);			//	��xvi�ļ�
	void ShowInfo();						//	��ʾxvi�ļ���Ϣ
	void GetFrame(int i, fstream frame, fstream phase, fstream test);						//	��ȡ֡���ݲ����֡����
	void OutputXvi(const char* file);		//	��ȡXvi�ļ�
	//void progress();		// ��ʾ��������Ϣ
};