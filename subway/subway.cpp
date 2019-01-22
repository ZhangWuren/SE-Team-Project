#include "station.h"
using namespace std;

int main(int argc,char *argv[])
{
	string filename = "beijing-subway.txt";
	Map map;
	map.setMap(filename);
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
	if (!strcmp(argv[1], "/z"))
	{
		map.test(argv[2]);
	}
	if (!strcmp(argv[1], "/g"))
	{
		//图形界面 待续
	}
	return 0;
}
