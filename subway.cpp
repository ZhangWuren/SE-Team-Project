#include "station.h"
using namespace std;

int main()
{
    string filename = "beijing-subway.txt";
	Map map;
	map.setMap(filename);
	map.search("苹果园", "古城");
}