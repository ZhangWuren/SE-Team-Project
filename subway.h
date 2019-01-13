#ifndef  STATION_H
#define STATION_H

#include "iostream"
#include "fstream"
#include "string"
#define _TOTAL 331
#define _STATIONS 50
using namespace std;

class Station
{
public:
	Station()
	{

	};
	void setStation(string name, string line, int number) {
		m_name = name;
		m_line = line;
		m_number = number;
	}
	string getName()
	{
		return m_name;
	}
private:
	int m_number;
	string m_name;
	string m_line;
	/*Station *neighbours = new Station[2];
	Station *transneighbours = new Station[4];*/
};

class Map
{
public:
	Map(string filename);
	void print() {
		cout << stanum << endl;
		for (int i = 0; i < stanum; i++)
		{
			cout << stations[i].getName() << endl;
		}
	}
private:
	Station stations[_TOTAL];
	int stanum;
};

class Matrix 
{
public:
	Matrix(Map map)
	{

	}

	int matrix[_TOTAL][_TOTAL];
};

Map::Map(string filename)
{
	fstream fin(filename);
	string readline;
	string transstation[80];
	int transflag = 0;
	int num = 0;
	while (getline(fin, readline))
	{
		if (!readline.empty())
		{
			int indexblank = readline.find(' '); //第一个空格的位置
			int indextrans = readline.find('-'); // - 的位置，表示该站是换乘车站
			if (indextrans == -1) {//没有换乘
				string staname = readline.substr(indexblank + 1);
				string linename = readline.substr(0, indexblank);
				stations[num].setStation(staname, linename, num);
				stanum = num;
				num++;
			}
			else//有换乘
			{
				int flag = 0;
				string staname = readline.substr(indexblank + 1, indextrans - indexblank - 1);
				for (int i = 0; i < transflag; i++)
				{
					if (staname == transstation[i]) {
						flag = 1;
						break;
					}
				}
				if (!flag) {
					transstation[transflag] = staname;
					transflag++;
					string linename = readline.substr(0, indexblank) + "," + readline.substr(indextrans + 1);
					stations[num].setStation(staname, linename, num);
					stanum = num;
					num++;
				}
			}
		}
	}
	stanum++;
}
#endif // ! STATION_H
