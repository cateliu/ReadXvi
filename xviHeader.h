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
	xviHeader();			//	默认构造函数
	xviHeader(string file); //	有参构造
	~xviHeader();
	bool OpenXvi(const char* file);			//	打开xvi文件
	void ShowInfo();						//	显示xvi文件信息
	void GetFrame(int i, fstream frame, fstream phase, fstream test);						//	获取帧数据并输出帧数据
	void OutputXvi(const char* file);		//	读取Xvi文件
	//void progress();		// 显示进度条信息
};