#ifndef  SUBWAY_H
#define SUBWAY_H

#include "iostream"
#include "fstream"
#include "string"
#include "string.h"
#include "stack"
#define _TOTAL 330
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
	return 0;
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
	for (unsigned i = 0, j = 0; i < (this->m_line.length()); i++)
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
		memset(m_maze, INF, sizeof(m_maze));
	};
	void setMap(string filename);//根据txt设置地图
	void printLine(string line);//输出地铁线路
	void setMartix();//设置邻接矩阵
	void search(string start, string end);//dijkstra算法
	void greedSearch(Station start, Station end);//贪心搜索
	void printPath(int endnumber, string lastline);//输出路径
	Station Map::getStationbynumber(int number);//根据序号获得站点
	Station Map::getStationbyname(string name);//根据名字获得站点
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

void Map::setMap(string filename)
{
	fstream fin(filename);
	string readline;
	string transstation[80];
	int transflag = 0;
	int num = 0;
	m_stanum = 0;
	while (getline(fin, readline))
	{
		if (!readline.empty())
		{
			int indexblank = readline.find(' '); //第一个空格的位置
			int indextrans = readline.find('-'); // - 的位置，表示该站是换乘车站
			if (indextrans == -1) {//没有换乘
				string staname = readline.substr(indexblank + 1);
				string linename = readline.substr(0, indexblank);
				stations[m_stanum].setStation(staname, linename, num);
				m_stanum++;
				num++;
			}
			else//有换乘
			{
				stations[m_stanum].setIstran();
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
					stations[m_stanum].setStation(staname, linename, num);
					m_stanum++;
					num++;
				}
				else
				{//如果是已经记录的换乘车站
					for (int i = 0; i < _TOTALS; i++) {
						if (staname == stations[i].getName()) {
							stations[m_stanum].setStation(staname, linename, stations[i].getNumber());
							break;
						}
					}
					m_stanum++;
				}
			}
		}
	}
}

void Map::search(string start, string end) //dijkstra算法
{
	this->setMartix();
	memset(m_dis, INF, sizeof(m_dis));
	memset(m_vis, false, sizeof(m_vis));
	memset(m_path, -1, sizeof(m_path));

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

	m_dis[startnumber] = 0;
	for (int i = 0; i < _TOTAL; i++)
	{
		//找到和起点距离最短的点
		int minx = INF;
		int minmark;
		for (int j = 0; j < _TOTAL; j++)
		{
			if (m_vis[j] == false && m_dis[j] <= minx)
			{
				minx = m_dis[j];
				minmark = j;
			}
		}
		//并标记
		m_vis[minmark] = true;
		//更新所有和它连接的点的距离
		for (int j = 0; j < _TOTAL; j++)
		{
			if (m_vis[j] == false && m_dis[j] > m_dis[minmark] + m_maze[minmark][j])
			{
				m_dis[j] = m_dis[minmark] + m_maze[minmark][j];
				m_path[j] = minmark;
			}
		}
	}

	this->printPath(endnumber, lastline);
}

void Map::printPath(int endnumber, string lastline)
{
	stack<int> q;
	int p = endnumber;
	int stationpath[_TOTAL];
	memset(stationpath, INF, sizeof(stationpath));

	while (m_path[p] != -1) //将路径压入栈中
	{
		q.push(p);
		p = m_path[p];
	}
	q.push(p);

	int i = 0;
	while (!q.empty()) //一次出栈获得正序路径
	{
		stationpath[i] = q.top();
		i++;
		q.pop();
	}
	cout << m_dis[endnumber] + 1 << endl;
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
	memset(m_maze, INF, sizeof(m_maze));

	//2、10为环线
	m_maze[23][38] = 1;
	m_maze[38][23] = 1;
	m_maze[173][207] = 1;
	m_maze[207][173] = 1;

	for (int i = 0; i < _TOTALS; i++)
	{
		if (i != 0 && i != _TOTALS - 1)//排除第一个和最后一个
		{
			if (stations[i].compareLine(stations[i + 1])) {//判断是否为同一条线路
				m_maze[stations[i].getNumber()][stations[i + 1].getNumber()] = 1;
			}
			if (stations[i].compareLine(stations[i - 1])) {
				m_maze[stations[i].getNumber()][stations[i - 1].getNumber()] = 1;
			}


		}
		else
		{
			if (i == 0)
			{
				m_maze[stations[i].getNumber()][stations[i + 1].getNumber()] = 1;
			}
			else
			{
				m_maze[stations[i].getNumber()][stations[i - 1].getNumber()] = 1;
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
	return stations[_TOTALS - 1];
}

Station Map::getStationbyname(string name)
{
	for (int i = 0; i < _TOTALS; i++)
	{
		if (name == stations[i].getName())
		{
			return stations[i];
		}
	}
	return stations[_TOTALS - 1];
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
	for (unsigned i = 0, j = 0; i < (sl1.length()); i++)
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
	for (unsigned i = 0, j = 0; i < (sl2.length()); i++)
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
	return "error";
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

void Map::traversal(string start)
{
	this->setMartix();
	Station startsta = this->getStationbyname(start);
	memset(m_tvis, false, sizeof(m_tvis));
	memset(m_tpath, INF, sizeof(m_tpath));
	int visnumber = this->getRemainStationNumber();

	m_tvis[startsta.getNumber()] = true;

	while (visnumber > 0)
	{
		for (int i = 0; i < _TOTAL; i++)
		{
			if (this->m_tvis[i] != true)
			{
				Station endsta = this->getStationbynumber(i);
				this->greedSearch(startsta, endsta);
				startsta = endsta;
				visnumber = this->getRemainStationNumber();
				break;
			}
		}
	}

	this->greedSearch(startsta, this->getStationbyname(start));

	int count = 0;
	for (int i = 0; this->m_tpath[i] != INF; i++)
	{
		count++;
	}

	cout << count << endl;
	cout << start << endl;
	for (int i = 0; this->m_tpath[i] != INF; i++)
	{
		cout << this->getStationbynumber(this->m_tpath[i]).getName() << endl;
	}
}

bool Map::isInMap(string name)
{
	for (int i = 0; i < _TOTALS; i++)
	{
		if (name == stations[i].getName())
		{
			return true;
		}
	}
	return false;
}

void Map::greedSearch(Station start, Station end)
{
	memset(m_dis, INF, sizeof(m_dis));
	memset(m_vis, false, sizeof(m_vis));
	memset(m_path, -1, sizeof(m_path));

	int startnumber = start.getNumber();
	int endnumber = end.getNumber();

	m_dis[startnumber] = 0;
	for (int i = 0; i < _TOTAL; i++)
	{
		int minx = INF;
		int minmark;
		for (int j = 0; j < _TOTAL; j++)//找到和起点距离最短的点
		{
			if (m_vis[j] == false && m_dis[j] <= minx)
			{
				minx = m_dis[j];
				minmark = j;
			}
		}
		m_vis[minmark] = true; //并标记
		for (int j = 0; j < _TOTAL; j++)//更新所有和它连接的点的距离
		{
			if (m_vis[j] == false && m_dis[j] > m_dis[minmark] + m_maze[minmark][j])
			{
				m_dis[j] = m_dis[minmark] + m_maze[minmark][j];
				m_path[j] = minmark;
			}
		}
	}

	this->addpath(endnumber, start.getFirstline());
}

void Map::addpath(int endnumber, string lastline)
{
	stack<int> q;
	int p = endnumber;
	int stationpath[_TOTAL];
	memset(stationpath, INF, sizeof(stationpath));

	while (m_path[p] != -1) //将路径压入栈中
	{
		q.push(p);
		p = m_path[p];
	}
	q.push(p);

	int i = 0;
	while (!q.empty()) //一次出栈获得正序路径
	{
		stationpath[i] = q.top();
		i++;
		q.pop();
	}

	int mark = 0;
	for (int i = 0; i < _TOTALS * 10; i++)
	{
		if (this->m_tpath[i] == INF)
		{
			mark = i;
			break;
		}
	}

	for (int i = mark, j = 1; stationpath[j] != INF; i++, j++)
	{
		m_tpath[i] = stationpath[j];
		this->m_tvis[stationpath[j]] = true;
	}
}

int Map::getRemainStationNumber()
{
	int count = 0;
	for (int i = 0; i < _TOTAL; i++)
	{
		if (this->m_tvis[i] == false)
		{
			count++;
		}
	}
	return count;
}

void Map::setTransMartix()
{
	memset(m_maze, INF, sizeof(m_maze));

	//2、10为环线
	m_maze[23][38] = 1;
	m_maze[38][23] = 1;
	m_maze[173][207] = 1;
	m_maze[207][173] = 1;

	for (int i = 0; i < _TOTALS; i++)
	{
		if (i != 0 && i != _TOTALS - 1)//如果不是第一个和最后一个
		{
			if (stations[i].getType())
			{//如果是换乘车站，则需要考虑换乘的代价
				{//本条线路上权值仍未1
					if (stations[i].compareLine(stations[i + 1])) {
						m_maze[i][i + 1] = 1;
					}
					if (stations[i].compareLine(stations[i - 1])) {
						m_maze[i][i - 1] = 1;
					}
				}
				{//别的线路上可以换乘的站点
					for (int j = 0; j < _TOTALS; j++)
					{
						if (stations[i].getNumber() == stations[j].getNumber() && i != j)
						{//找到除了本身以外的同名站点
							m_maze[i][j] = 0;//同名站点可以直接到达，赋权值为0

											 //和同名站点的相邻站点，即为换乘，赋权值为3
							if (j != 392 && j!=0)
							{//需考虑巴沟站没有j+1站
								if (stations[j].compareLine(stations[j + 1])) {
									m_maze[i][j + 1] = 3;
								}
								if (stations[j].compareLine(stations[j - 1])) {
									m_maze[i][j - 1] = 3;
								}
							}
							else
							{
								if (j != 0) {
									m_maze[i][j - 1] = 3;
								}
							}
						}
					}
				}
			}
			else
			{//如果不是换乘车站，直接将权值赋为1
				if (stations[i].compareLine(stations[i + 1])) {
					m_maze[i][i + 1] = 1;
				}
				if (stations[i].compareLine(stations[i - 1])) {
					m_maze[i][i - 1] = 1;
				}
			}

		}
		else
		{
			if (i == 0)
			{
				m_maze[i][i + 1] = 1;
			}
			else
			{
				m_maze[i][i - 1] = 1;
				m_maze[i][195] = 3;
			}
		}
	}
}

void Map::test(string filename)
{
	this->setMartix();
	memset(this->m_tvis, false, sizeof(m_tvis));
	fstream fin(filename);
	string readline;
	string stas[_TOTALS * 2];
	for (int i = 0; i < _TOTALS * 10; i++)
	{
		stas[i].clear();
	}
	getline(fin, readline);
	int count = stoi(readline);
	int count1 = 0;
	int i = 0;
	while (getline(fin, readline))
	{
		stas[i] = readline;
		i++;
	}
	for (int i = 1; !stas[i].empty(); i++)
	{
		Station s1 = this->getStationbyname(stas[i]);
		Station s2 = this->getStationbyname(stas[i - 1]);
		m_tvis[s1.getNumber()] = true;
		m_tvis[s2.getNumber()] = true;
		if (!this->m_maze[s1.getNumber()][s2.getNumber()])
		{
			cout << "error" << endl;
			return;
		}
	}

	int novissta[_TOTAL];
	memset(novissta, -1, sizeof(novissta));
	for (int i = 0, j = 0; i < _TOTAL; i++)
	{
		if (this->m_tvis[i] == false)
		{
			novissta[j] = i;
			j++;
		}
	}

	if (novissta[0] == -1)
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
		cout << "遗漏的站点有:" << endl;
		for (int i = 0; novissta[i] != -1; i++)
		{
			cout << this->getStationbynumber(novissta[i]).getName() << endl;
		}
	}
}
#endif