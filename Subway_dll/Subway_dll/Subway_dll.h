#pragma once

#include "iostream"
#include "fstream"
#include "string"
#include "string.h"
#include "stack"
#define _TOTAL 331
#define _TOTALS 393
#define _STATIONS 50
#define INF 0x7f7f7f7f
using namespace std;

class Station {
public:
	static _declspec(dllexport) int compareLine(Station another);
	static _declspec(dllexport) string getFirstline();
};

class Map
{
public:
	
	static _declspec(dllexport) void setMap(string filename);//����txt���õ�ͼ
	static _declspec(dllexport) 	void printLine(string line);//���������·
	static _declspec(dllexport) 	void setMartix();//�����ڽӾ���
	static _declspec(dllexport) void search(string start, string end);//dijkstra�㷨
	static _declspec(dllexport) void greedSearch(Station start, Station end);//̰������
	static _declspec(dllexport) void printPath(int endnumber, string lastline);//���·��
	static _declspec(dllexport) Station getStationbynumber(int number);//������Ż��վ��
	static _declspec(dllexport) Station getStationbyname(string name);//�������ֻ��վ��
	static _declspec(dllexport) string getSameline(Station s1, Station s2);//�������վ����ͬ��·
	static _declspec(dllexport) void traversal(string start);//ȫ����
	static _declspec(dllexport) 	void addpath(int endnumber, string lastline);//����ȫ����·��
	static _declspec(dllexport) bool isInMap(string name);//�ж�վ���Ƿ�Ϸ�
	static _declspec(dllexport) int getRemainStationNumber();//���ȫ����ʱδ�����ĳ�վ
	static _declspec(dllexport) void setTransMartix();//���ǻ��˴����ǵ�Ȩֵ����
	static _declspec(dllexport) 	void test(string filename);// /z���ܣ�����
};