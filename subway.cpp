#include "subway.h"
using namespace std;

int main()
{
    string filename = "beijing-subway.txt";
    Map map(filename);
    map.print();
}