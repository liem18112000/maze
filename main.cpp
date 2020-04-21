#include <iostream>
using namespace std;

#include <time.h>

#include "Path_Find.h"

int main(){

	Path_Find PF1;

	Map map;

	map.Set(10, 10);

	PF1.setMap(map);

	PF1.setRandomMap();

	PF1.setStart(0, 0);

	PF1.setGoal(PF1.getMapHeight() - 1, PF1.getMapWide() - 1);

	int step1, open1;

	time_t begin1 ,end1;

	cout << "Map : \n";

	PF1.PrintMap(cout);

	begin1 = clock();

	PF1.Search_A_Star_Distance(step1, open1);

	end1 = clock();

	cout << "Step : " << step1 << endl;

	cout << "Open path : " << open1 << endl;

	cout << "Time Exe : " << float(end1 - begin1) / 1000 << endl;

	system("pause");
	return 0;
}