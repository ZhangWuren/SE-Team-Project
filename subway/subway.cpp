#include "station.h"
using namespace std;

int main(int argc,char *argv[])
{
	string filename = "beijing-subway.txt";
	Map map;
	map.setMap(filename);
	//map.search("良乡大学城北", "魏公村");// /b功能 最短路
	//map.search("知春路", "苹果园");
	//map.search("知春路", "魏公村");
	//map.printLine("房山");// /c功能
	//map.traversal("知春路");// /a功能，全遍历
	//cout << argv[1] << endl;
	if (!strcmp(argv[1], "/b"))
	{
		map.search(argv[2], argv[3]);
	}
	if (!strcmp(argv[1], "/c"))
	{
		map.printLine(argv[2]);
	}
	if (!strcmp(argv[1], "/a"))
	{
		map.traversal(argv[2]);
	}
	
}
