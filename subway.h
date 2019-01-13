#ifndef SUBWAY_H
#define SUBWAY_H
#include "string"
#define TOTAL 400
using namespace std;

class Station //地铁站
{
  public:
    Station(string &staname);
    Station();
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
    Line();

  private:
    Station stations[10];
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
    int m_matrix[TOTAL][TOTAL];
};

#endif