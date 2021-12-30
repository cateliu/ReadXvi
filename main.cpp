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
	cout << "    1.�����ļ����   " << endl;
	cout << "    2.�����ļ����   " << endl;
	cout << "    3.�ļ������ݶ�ȡ  " << endl;
	cout << "    4.��        ��   " << endl;
	cout << "    0.��        ��   " << endl;
	cout << "-------------------" << endl;
}
void helpMenu()
{
	cout << "�����ĵ���" << endl;
	system("pause");
}
void Continue()
{
	string prefix;
	int step;
	int start;
	cout << "�������ļ�ǰ׺��";
	cin >> prefix;
	cout << "�����벽������";
	cin >> step;
	cout << "�������ʼֵ��";
	cin >> start;
	while (true)
	{
		string filename = prefix + to_string(start) + ".xvi";
		cout << "��ǰ�ļ���Ϊ��" << filename << endl;
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
	cout << "�������ļ�����";
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
	cout << "��ǰ��������λ�ã�" ;
	cout << _pgmptr << endl;
	string dir = ".";
	cout << "�������ļ���:";
	cin >> dir;
	SetCurrentDirectoryA(dir.c_str());
	vector<string> filenames;
	filesystem::path str(dir);
	if (!exists(str))
	{
		cout << "�ļ��в����ڣ�" << endl;
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
	cout << "���ļ����µ�xvi�ļ��У�" << endl;
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
		cout << "������ѡ��";
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

