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
	if (this->m_istran == 0 && another.getType() == 0) //�����ǻ��˳�վ
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
		memset(m_maze, INF, sizeof(m_maze));
	};
	void setMap(string filename);//����txt���õ�ͼ
	void printLine(string line);//���������·
	void setMartix();//�����ڽӾ���
	void search(string start, string end);//dijkstra�㷨
	void greedSearch(Station start, Station end);//̰������
	void printPath(int endnumber, string lastline);//���·��
	Station Map::getStationbynumber(int number);//������Ż��վ��
	Station Map::getStationbyname(string name);//�������ֻ��վ��
	string getSameline(Station s1, Station s2);//�������վ����ͬ��·
	void traversal(string start);//ȫ����
	void addpath(int endnumber, string lastline);
	bool isInMap(string name);//�ж�վ���Ƿ�Ϸ�
	void updateMatrix();//����Ȩֵ
	int getRemainStationNumber();
private:
	Station stations[_TOTALS];
	int m_stanum;
	int m_maze[_TOTAL][_TOTAL];
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
			int indexblank = readline.find(' '); //��һ���ո��λ��
			int indextrans = readline.find('-'); // - ��λ�ã���ʾ��վ�ǻ��˳�վ
			if (indextrans == -1) {//û�л���
				string staname = readline.substr(indexblank + 1);
				string linename = readline.substr(0, indexblank);
				stations[m_stanum].setStation(staname, linename, num);
				m_stanum++;
				num++;
			}
			else//�л���
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
				if (!flag) {//�����δ����¼�Ļ��˳�վ
					transstation[transflag] = staname;
					transflag++;
					stations[m_stanum].setStation(staname, linename, num);
					m_stanum++;
					num++;
				}
				else
				{//������Ѿ���¼�Ļ��˳�վ
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

void Map::search(string start, string end) //dijkstra�㷨
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
		//�ҵ�����������̵ĵ�
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
		//�����
		m_vis[minmark] = true;
		//�������к������ӵĵ�ľ���
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

	while (m_path[p] != -1) //��·��ѹ��ջ��
	{
		q.push(p);
		p = m_path[p];
	}
	q.push(p);

	int i = 0;
	while (!q.empty()) //һ�γ�ջ�������·��
	{
		stationpath[i] = q.top();
		i++;
		q.pop();
	}
	cout << m_dis[endnumber] + 1 << endl;
	for (int i = 0; stationpath[i] != INF; i++) //���
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
				cout << " ����" << line2 << "����";
			}
		}
		cout << endl;
	}
}

void Map::setMartix()
{
	memset(m_maze, INF, sizeof(m_maze));

	//2��10Ϊ����
	m_maze[23][38] = 1;
	m_maze[38][23] = 1;
	m_maze[173][207] = 1;
	m_maze[207][173] = 1;

	for (int i = 0; i < _TOTALS; i++)
	{
		if (i != 0 && i != _TOTALS - 1)
		{
			if (stations[i].compareLine(stations[i + 1])) {
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

	for (int i = 0; this->m_tpath[i] != INF; i++)
	{
		cout << this->m_tpath[i] << this->getStationbynumber(this->m_tpath[i]).getName() <<endl;
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

void Map::greedSearch(Station start,Station end)
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
		for (int j = 0; j < _TOTAL; j++)//�ҵ�����������̵ĵ�
		{
			if (m_vis[j] == false && m_dis[j] <= minx)
			{
				minx = m_dis[j];
				minmark = j;
			}
		}
		m_vis[minmark] = true; //�����
		for (int j = 0; j < _TOTAL; j++)//�������к������ӵĵ�ľ���
		{
			if (m_vis[j] == false && m_dis[j] > m_dis[minmark] + m_maze[minmark][j])
			{
				m_dis[j] = m_dis[minmark] + m_maze[minmark][j];
				m_path[j] = minmark;
			}
		}
	}

	this->addpath(endnumber,start.getFirstline());
}

void Map::addpath(int endnumber, string lastline)
{
	stack<int> q;
	int p = endnumber;
	int stationpath[_TOTAL];
	memset(stationpath, INF, sizeof(stationpath));

	while (m_path[p] != -1) //��·��ѹ��ջ��
	{
		q.push(p);
		p = m_path[p];
	}
	q.push(p);

	int i = 0;
	while (!q.empty()) //һ�γ�ջ�������·��
	{
		stationpath[i] = q.top();
		i++;
		q.pop();
	}

	int mark;
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

void Map::updateMatrix()
{

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
#endif
