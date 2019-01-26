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

class Station
{
public:
	Station()
	{
		m_istran = 0;
	};
	void setStation(string name, string line, int number) {
		m_name = name;
		m_line = line;
		m_number = number;
	}
	void setIstran() {
		m_istran = 1;
	}
	string getName()
	{
		return m_name;
	}
	int getNumber()
	{
		return m_number;
	}
	int getType()
	{
		return m_istran;
	}
	string getLine()
	{
		return m_line;
	}
	int compareLine(Station another);
	string getFirstline();
private:
	int m_number;
	int m_istran;
	string m_name;
	string m_line;
};

class Map
{
public:
	Map()
	{
		memset(m_maze, INF, sizeof(m_maze));
	};
	void setMap(string filename);//根据txt设置地图
	void printLine(string line);//输出地铁线路
	void setMartix();//设置邻接矩阵
	void search(string start, string end);//dijkstra算法
	void greedSearch(Station start, Station end);//贪心搜索
	void printPath(int endnumber, string lastline);//输出路径
	Station getStationbynumber(int number);//根据序号获得站点
	Station getStationbyname(string name);//根据名字获得站点
	string getSameline(Station s1, Station s2);//获得两个站的相同线路
	void traversal(string start);//全遍历
	void addpath(int endnumber, string lastline);//增加全遍历路径
	bool isInMap(string name);//判断站点是否合法
	int getRemainStationNumber();//获得全遍历时未遍历的车站
	void setTransMartix();//考虑换乘代价是的权值矩阵
	void test(string filename);// /z功能，测试
private:
	Station stations[_TOTALS];
	int m_stanum;
	int m_maze[_TOTALS][_TOTALS];
	bool m_vis[_TOTAL];
	int m_dis[_TOTAL];
	int m_path[_TOTAL];
	bool m_tvis[_TOTAL];
	int m_tpath[_TOTAL * 100];
};
