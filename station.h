#ifndef  STATION_H
#define STATION_H

#include "iostream"
#include "fstream"
#include "string"
#include "string.h"
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
		memset(maze, INF, sizeof(maze));
	};
	void setMap(string filename);
	void print() {
		cout << stanum << endl;
		for (int i = 0; i < stanum; i++)
		{
			cout << stations[i].getName() << endl;
		}
	}
	void setMartix();//设置邻接矩阵
	void search(string start, string end);

private:
	Station stations[_TOTALS];
	int stanum;
	int maze[_TOTAL][_TOTAL];
};

void Map::setMap(string filename)
{
	fstream fin(filename);
	string readline;
	string transstation[80];
	int transflag = 0;
	int num = 0;
	stanum = 0;
	while (getline(fin, readline))
	{
		if (!readline.empty())
		{
			int indexblank = readline.find(' '); //第一个空格的位置
			int indextrans = readline.find('-'); // - 的位置，表示该站是换乘车站
			if (indextrans == -1) {//没有换乘
				string staname = readline.substr(indexblank + 1);
				string linename = readline.substr(0, indexblank);
				stations[stanum].setStation(staname, linename, num);
				stanum++;
				num++;
			}
			else//有换乘
			{
				stations[stanum].setIstran();
				int flag = 0;
				string staname = readline.substr(indexblank + 1, indextrans - indexblank - 1);
				string linename = readline.substr(0, indexblank) + "," + readline.substr(indextrans + 1);
				for (int i = 0; i < transflag; i++)
				{
					if (staname == transstation[i]) {
						flag = 1;
						break;
					}
				}
				if (!flag) {//如果是未曾记录的换乘车站
					transstation[transflag] = staname;
					transflag++;
					stations[stanum].setStation(staname, linename, num);
					stanum++;
					num++;
				}
				else
				{//如果是已经记录的换乘车站
					for (int i = 0; i < _TOTALS; i++) {
						if (staname == stations[i].getName()) {
							stations[stanum].setStation(staname, linename, stations[i].getNumber());
							break;
						}
					}
					stanum++;
				}
			}
		}
	}
}

void Map::search(string start, string end)
{
	bool vis[_TOTAL];
	int dis[_TOTAL];
	this->setMartix();
	memset(dis, INF, sizeof(dis));
	memset(vis, false, sizeof(vis));

	int startnumber;
	int endnumber;
	for (int i = 0; i < _TOTALS; i++)
	{
		if (start == stations[i].getName())
		{
			startnumber = stations[i].getNumber();
			break;
		}
	}
	for (int i = 0; i < _TOTALS; i++)
	{
		if (end == stations[i].getName())
		{
			endnumber = stations[i].getNumber();
			break;
		}
	}

	dis[startnumber] = 0;
	for (int i = 0; i < _TOTAL; i++)
	{
		//找到和起点距离最短的点
		int minx = INF;
		int minmark;
		for (int j = 0; j < _TOTAL; j++)
		{
			if (vis[j] == false && dis[j] <= minx)
			{
				minx = dis[j];
				minmark = j;
			}
		}
		//并标记
		vis[minmark] = true;
		//更新所有和它连接的点的距离
		for (int j = 0; j < _TOTAL; j++)
		{
			if (vis[j] == false && dis[j] > dis[minmark] + maze[minmark][j])
				dis[j] = dis[minmark] + maze[minmark][j];
		}
	}

	cout << dis[endnumber] << endl;
}

void Map::setMartix()
{
	memset(maze, INF, sizeof(maze));
	for (int i = 0; i < _TOTALS; i++)
	{
		if (i != 0 && i != _TOTALS - 1)
		{
			maze[stations[i].getNumber()][stations[i + 1].getNumber()] = 1;
			maze[stations[i].getNumber()][stations[i - 1].getNumber()] = 1;
		}
		else
		{
			if (i == 0)
			{
				maze[stations[i].getNumber()][stations[i + 1].getNumber()] = 1;
			}
			else
			{
				maze[stations[i].getNumber()][stations[i - 1].getNumber()] = 1;
			}
		}
	}
}
#endif // ! STATION_H
