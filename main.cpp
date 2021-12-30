#include "Xeneth-XVI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <malloc.h>
#include <string>
#include <iostream>
#include"xviHeader.h"
#include <filesystem>
using namespace std;

void showMenu()
{
	cout << "-------------------" << endl;
	cout << "    1.连续文件解读   " << endl;
	cout << "    2.单个文件解读   " << endl;
	cout << "    3.文件夹内容读取  " << endl;
	cout << "    4.帮        助   " << endl;
	cout << "    0.退        出   " << endl;
	cout << "-------------------" << endl;
}
void helpMenu()
{
	cout << "帮助文档：" << endl;
	system("pause");
}
void Continue()
{
	string prefix;
	int step;
	int start;
	cout << "请输入文件前缀：";
	cin >> prefix;
	cout << "请输入步进量：";
	cin >> step;
	cout << "请输入初始值：";
	cin >> start;
	while (true)
	{
		string filename = prefix + to_string(start) + ".xvi";
		cout << "当前文件名为：" << filename << endl;
		xviHeader H;
		if (H.OpenXvi(filename.c_str()))
		{
			H.ShowInfo();
			H.OutputXvi(filename.substr(0, filename.length() - 4).c_str());
		}
		else
		{
			break;
		}
		start += step;
	}
	system("pause");
}
void Single()
{
	string filename;
	cout << "请输入文件名：";
	cin >> filename;
	filename += ".xvi";
	const char* file = filename.c_str();
	xviHeader H;
	H.OpenXvi(file);
	H.ShowInfo();
	H.OutputXvi(filename.substr(0, filename.length() - 4).c_str());
	system("pause");
}
void Directoy()
{
	cout << "当前程序所在位置：" ;
	cout << _pgmptr << endl;
	string dir = ".";
	cout << "请输入文件夹:";
	cin >> dir;
	SetCurrentDirectoryA(dir.c_str());
	vector<string> filenames;
	filesystem::path str(dir);
	if (!exists(str))
	{
		cout << "文件夹不存在！" << endl;
		system("pause");
		return;
	}
	int n;
	filesystem::directory_iterator list(str);
	for (const auto& file : list)
	{
		string filename = file.path().filename().string();
		if ((n = filename.find(".xvi")) != string::npos)
		{
			filenames.push_back(filename);
		}
	}
	cout << "该文件夹下的xvi文件有：" << endl;
	for (vector<string>::iterator it = filenames.begin(); it != filenames.end(); it++)
	{
		xviHeader H;
		H.OpenXvi((*it).c_str());
		H.ShowInfo();
		H.OutputXvi((*it).substr(0, (*it).length() - 4).c_str());
	}

	system("pause");
}
int main()
{
	int choice;
	while (true)
	{
		system("cls");
		showMenu();
		cout << "请输入选择：";
		cin >> choice;
		switch (choice) 
		{
		case 1:
			Continue();
			break;
		case 2:
		{
			Single();
			break;
		}
		case 3:
		{
			Directoy();
			break;
		}
		case 4:
			helpMenu();
			break;
		case 0:
			return 1;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}

