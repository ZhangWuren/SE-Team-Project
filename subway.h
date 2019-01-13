#ifndef SUBWAY_H
#define SUBWAY_H
#include "string"
#define _TOTAL 393
#define _MAXS 100
using namespace std;

class Station //地铁站
{
public:
  Station(string &staname){

  };
  Station(){

  };
  string getName();
  void setLaststa(Station laststa);
  void setNextsta(Station nextsta);

private:
  string m_staname;
  Station laststa();
  Station nextsta();
  int m_transLine[3];
};

class Line //地铁线
{
public:
  Line(){};
  void setLine(string stations[_MAXS]);

private:
  Station stations[_MAXS];
  int m_order;
  string m_name;
  bool m_ifcircle;
};

class Map //线路图
{
public:
  Map(string filename);

  void outputLine(int &num);
  void search(string &start, string &end);

private:
  Line lines[23];
};

class Matrix //邻接矩阵
{
public:
  Matrix(Map map, Station strat);

private:
  int m_matrix[_TOTAL][_TOTAL];
};

Map::Map(string filename)
{
  fstream fin(filename);
  string readline[_MAXS];
  int staorder = 0;
  int lineorder = 0;
  string linetype;
  string templinetype;
  while (getline(fin, readline[staorder]))
  {
    if (readline[staorder].empty()) //下一条线
    {
      int index = readline[staorder - 1].find(' ');
      string sub = readline[staorder - 1].substr(0, index);
      cout << sub << ' ' << staorder << endl;
      staorder = 0;

      this->lines[linetype].setLine(*readline);
    }
    else
    {
      staorder++;
    }
  }
  int index = readline[staorder - 1].find(' ');
  string sub = readline[staorder - 1].substr(0, index);
  cout << sub << ' ' << staorder << endl;
};
#endif