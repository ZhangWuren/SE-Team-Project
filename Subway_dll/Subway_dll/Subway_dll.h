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
	
	static _declspec(dllexport) void setMap(string filename);//根据txt设置地图
	static _declspec(dllexport) 	void printLine(string line);//输出地铁线路
	static _declspec(dllexport) 	void setMartix();//设置邻接矩阵
	static _declspec(dllexport) void search(string start, string end);//dijkstra算法
	static _declspec(dllexport) void greedSearch(Station start, Station end);//贪心搜索
	static _declspec(dllexport) void printPath(int endnumber, string lastline);//输出路径
	static _declspec(dllexport) Station getStationbynumber(int number);//根据序号获得站点
	static _declspec(dllexport) Station getStationbyname(string name);//根据名字获得站点
	static _declspec(dllexport) string getSameline(Station s1, Station s2);//获得两个站的相同线路
	static _declspec(dllexport) void traversal(string start);//全遍历
	static _declspec(dllexport) 	void addpath(int endnumber, string lastline);//增加全遍历路径
	static _declspec(dllexport) bool isInMap(string name);//判断站点是否合法
	static _declspec(dllexport) int getRemainStationNumber();//获得全遍历时未遍历的车站
	static _declspec(dllexport) void setTransMartix();//考虑换乘代价是的权值矩阵
	static _declspec(dllexport) 	void test(string filename);// /z功能，测试
};