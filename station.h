#ifndef  STATION_H
#define STATION_H

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

int Station::compareLine(Station another)
{
	if (this->m_istran == 0 && another.getType() == 0) //都不是换乘车站
	{
		if (this->m_line == another.getLine())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if (this->m_istran == 1 && another.getType() == 0)
	{
		string line = this->getFirstline();
		/*while (*line != "-1") {
			if (*line == another.getLine()) {
				return 1;
			}
			else
			{
				line++;
			}
		}
		return 0;*/
		if (line == another.getLine())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if (this->m_istran == 0 && another.getType() == 1)
	{
		string line = another.getFirstline();
		/*while (*line != "-1") {
			if (*line == this->getLine())
			{
				return 1;
			}
			else
			{
				line++;
			}
		}
		return 0;*/
		if (this->getLine() == line)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if (this->m_istran == 1 && another.getType() == 1)
	{
		string line1 = this->getFirstline();
		string line2 = another.getFirstline();
		/*while (*line1 != "-1")
		{
			while (*line2 != "-1")
			{
				if (*line1 == *line2) {
					return 1;
				}
				else
				{
					line2++;
				}
			}
			line2 = another.getLines();
			line1++;
		}
		return 0;*/
		if (line1 == line2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

string Station::getFirstline()
{
	int index[2] = { -1,-1 };
	static string line[4];
	for (int i = 0; i < 4; i++)
	{
		line[i].clear();
		line[i].append("-1");
	}
	for (int i = 0, j = 0; i < this->m_line.length(); i++)
	{
		if (this->m_line[i] == ',')
		{
			index[j] = i;
			j++;
		}
	}
	line[0] = this->m_line.substr(0, index[0]);
	if (index[1] == -1) {
		line[1] = this->m_line.substr(index[0] + 1);
	}
	else
	{
		line[1] = this->m_line.substr(index[0] + 1, index[1] - index[0] - 1);
		line[2] = this->m_line.substr(index[1] + 1);
	}
	return line[0];
}

class Map
{
public:
	Map()
	{
		memset(maze, INF, sizeof(maze));
	};
	void setMap(string filename);//根据txt设置地图
	void printLine(string line);
	void setMartix();//设置邻接矩阵
	void search(string start, string end);//dijkstra算法
	void printPath(int endnumber, string lastline);//输出路径
	Station Map::getStationbynumber(int number);
	string getSameline(Station s1, Station s2);
private:
	Station stations[_TOTALS];
	int stanum;
	int maze[_TOTAL][_TOTAL];
	bool vis[_TOTAL];
	int dis[_TOTAL];
	int path[_TOTAL];
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

void Map::search(string start, string end) //dijkstra算法
{
	this->setMartix();
	memset(dis, INF, sizeof(dis));
	memset(vis, false, sizeof(vis));
	memset(path, -1, sizeof(path));

	int startnumber;
	int endnumber;
	string lastline;
	for (int i = 0; i < _TOTALS; i++)
	{
		if (start == stations[i].getName())
		{
			startnumber = stations[i].getNumber();
			lastline = stations[i].getFirstline();
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
			{
				dis[j] = dis[minmark] + maze[minmark][j];
				path[j] = minmark;
			}
		}
	}

	this->printPath(endnumber, lastline);
	/*stack<int> q;
	int p = endnumber;
	while (path[p] != -1)
	{
		q.push(p);
		p = path[p];
	}
	q.push(p);
	cout << "换乘站" << ":" << dis[endnumber] + 1;
	while (!q.empty())
	{
		cout << endl;
		string sta;
		for (int i = 0; i < _TOTALS; i++)
		{
			if (stations[i].getNumber() == q.top())
			{
				sta = stations[i].getName();
				if (stations[i].getLines() != lastline)
				{
					cout << sta;
					lastline = stations[i].getLines();
				}
				else
				{
					cout << sta;
				}
				break;
			}
		}
		q.pop();
	}
	cout << endl;*/
}

void Map::printPath(int endnumber, string lastline)
{
	stack<int> q;
	int p = endnumber;
	int stationpath[_TOTAL];
	memset(stationpath, INF, sizeof(stationpath));

	while (path[p] != -1) //将路径压入栈中
	{
		q.push(p);
		p = path[p];
	}
	q.push(p);

	int i = 0;
	while (!q.empty()) //一次出栈获得正序路径
	{
		stationpath[i] = q.top();
		i++;
		q.pop();
	}
	cout << dis[endnumber] + 1 << endl;
	for (int i = 0; stationpath[i] != INF; i++) //输出
	{
		Station sta = this->getStationbynumber(stationpath[i]);
		cout << sta.getName();
		if (sta.getType() && stationpath[i + 1] != INF && i != 0)
		{
			Station laststa = this->getStationbynumber(stationpath[i - 1]);
			Station nextsta = this->getStationbynumber(stationpath[i + 1]);
			string line1 = this->getSameline(laststa, sta);
			string line2 = this->getSameline(sta, nextsta);
			if (line1 != line2)
			{
				cout << " 换乘" << line2 << "号线";
			}
		}
		cout << endl;
	}
}

void Map::setMartix()
{
	memset(maze, INF, sizeof(maze));

	//2、10为环线
	maze[23][38] = 1;
	maze[38][23] = 1;
	maze[173][207] = 1;
	maze[207][173] = 1;

	for (int i = 0; i < _TOTALS; i++)
	{
		if (i != 0 && i != _TOTALS - 1)
		{
			if (stations[i].compareLine(stations[i + 1])) {
				maze[stations[i].getNumber()][stations[i + 1].getNumber()] = 1;
			}
			if (stations[i].compareLine(stations[i - 1])) {
				maze[stations[i].getNumber()][stations[i - 1].getNumber()] = 1;
			}


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

Station Map::getStationbynumber(int number)
{
	for (int i = 0; i < _TOTALS; i++)
	{
		if (stations[i].getNumber() == number)
		{
			return stations[i];
		}
	}
}

string Map::getSameline(Station s1, Station s2)
{
	string sl1 = s1.getLine();
	string sl2 = s2.getLine();
	int index[2] = { -1,-1 };
	string line1[4];
	string line2[4];
	for (int i = 0; i < 4; i++)
	{
		line1[i].clear();
		line1[i].append("-1");
	}
	for (int i = 0, j = 0; i < sl1.length(); i++)
	{
		if (sl1[i] == ',')
		{
			index[j] = i;
			j++;
		}
	}
	line1[0] = sl1.substr(0, index[0]);
	if (index[1] == -1) {
		line1[1] = sl1.substr(index[0] + 1);
	}
	else
	{
		line1[1] = sl1.substr(index[0] + 1, index[1] - index[0] - 1);
		line1[2] = sl1.substr(index[1] + 1);
	}

	index[0] = -1; index[1] = -1;
	for (int i = 0; i < 4; i++)
	{
		line2[i].clear();
		line2[i].append("-1");
	}
	for (int i = 0, j = 0; i < sl2.length(); i++)
	{
		if (sl2[i] == ',')
		{
			index[j] = i;
			j++;
		}
	}
	line2[0] = sl2.substr(0, index[0]);
	if (index[1] == -1) {
		line2[1] = sl2.substr(index[0] + 1);
	}
	else
	{
		line2[1] = sl2.substr(index[0] + 1, index[1] - index[0] - 1);
		line2[2] = sl2.substr(index[1] + 1);
	}

	for (int i = 0; line1[i] != "-1"; i++)
	{
		for (int j = 0; line2[j] != "-1"; j++)
		{
			if (line1[i] == line2[j]) {
				return line1[i];
			}
		}
	}
}

void Map::printLine(string line)
{
	for (int i = 0; i < _TOTALS; i++)
	{
		if (this->stations[i].getFirstline() == line)
		{
			cout << this->stations[i].getName() << endl;
		}
	}
}
#endif
