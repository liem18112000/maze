#pragma once
#include <iostream>
using namespace std;

#include <cmath>

class Map{
private:
	int **map;
	int Wide;
	int Height;

public:
	Map();
	Map(int, int);
	Map(const Map&);
	~Map();

	//Set & Get
	void Set(int, int);
	void setMap(int**);
	void setPos(int, int, int);
	void setRandomMap();
	int getPos(int, int) const;
	int getWide() const;
	int getHeight() const;
	int** getMap() const;

	//Check
	bool IsX(int) const;
	bool IsY(int) const;

	//Print
	void Print(ostream&) const;
};



class Path_Find
{
private:
	Map map;
	int Start;
	int Goal;

	void XYConvert(int, int&, int&) const;
	int ConvertXY(int, int) const;

public:
	//Check
	bool IsX(int) const;
	bool IsY(int) const;
	bool IsGoal(int) const;

	//Set & Get
	void setGoal(int, int);
	void setStart(int, int);
	void setMap(Map);
	void setRandomMap();
	int getMapWide() const;
	int getMapHeight() const;
	Map getMap() const;
	int getStart() const;
	int getGoal() const;

	//Print
	void PrintMap(ostream&) const;

//Main Operations
	//Breadth First Search
	bool Search_BFS();

	//Seach A Star Distance
	float Heuristic_Distance(int , int) const;
	void Search_A_Star_Distance(int &, int &);

	//IDA Star Distance
	bool Recursion(int &, int&, int);
	void IDA_Star_Distance(int &, int &);

	//Improve A Star Distance
	float Heuristic_Distance(int , int, int, int) const;
	void Improve_A_Star_Distance(int &, int &);

};

