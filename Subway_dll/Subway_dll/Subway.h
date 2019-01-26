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
	void setMap(string filename);//����txt���õ�ͼ
	void printLine(string line);//���������·
	void setMartix();//�����ڽӾ���
	void search(string start, string end);//dijkstra�㷨
	void greedSearch(Station start, Station end);//̰������
	void printPath(int endnumber, string lastline);//���·��
	Station getStationbynumber(int number);//������Ż��վ��
	Station getStationbyname(string name);//�������ֻ��վ��
	string getSameline(Station s1, Station s2);//�������վ����ͬ��·
	void traversal(string start);//ȫ����
	void addpath(int endnumber, string lastline);//����ȫ����·��
	bool isInMap(string name);//�ж�վ���Ƿ�Ϸ�
	int getRemainStationNumber();//���ȫ����ʱδ�����ĳ�վ
	void setTransMartix();//���ǻ��˴����ǵ�Ȩֵ����
	void test(string filename);// /z���ܣ�����
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
