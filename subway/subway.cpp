#include "station.h"
using namespace std;

int main()
{
    string filename = "beijing-subway.txt";
	Map map;
	map.setMap(filename);
	map.search("良乡大学城北", "魏公村");// /b功能
	map.printLine("房山");// /c功能
}