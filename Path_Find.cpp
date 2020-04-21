#include "Path_Find.h"
#include <cstdlib>
#include <queue>
#include <stack>
#include <vector>
#include <time.h>
#include <windows.h>
//Map
Map::Map(): Wide(10), Height(10){
	map = new int*[Height];
	for(int i = 0; i < Height; i++){
		map[i] = new int[Wide];
		for(int j = 0; j < Wide; j++)
			map[i][j] = NULL;
	}
}

Map::Map(int h, int w): Wide(w), Height(h){
	map = new int*[Height];
	for(int i = 0; i < Height; i++){
		map[i] = new int[Wide];
		for(int j = 0; j < Wide; j++)
			map[i][j] = NULL;
	}
}

Map::Map(const Map&src){
	Height = src.getHeight();
	Wide = src.getWide();
	map = new int*[Height];
	for(int i = 0; i < Height; i++){
		map[i] = new int[Wide];
		for(int j = 0; j < Wide; j++)
			map[i][j] = src.getPos(i, j);
	}

}

Map::~Map(){
	if(map != NULL){
		for(int i = 0; i < Height; i++)
			if(map[i] != NULL){
				delete[] map[i];
				map[i] = NULL;
			}
		delete[] map;
		map = NULL;
	}
}

//Set & Get
void Map::Set(int h, int w){
	Height = h;
	Wide = w;

	map = new int*[Height];
	for(int i = 0; i < Height; i++){
		map[i] = new int[Wide];
		for(int j = 0; j < Wide; j++)
			map[i][j] = NULL;
	}
}

void Map::setMap(int**m){
	map = m;
}

void Map::setPos(int k, int i, int j){
	map[i][j] = k;
}

void Map::setRandomMap(){
	srand(unsigned int(clock()));
	for(int i = 0; i < Height; i++)
		for(int j = 0; j < Wide; j++){
			if(rand() % 3 == 0 && !(i == Height - 1 && j == Wide - 1) && !(i == 0 && j == 0))
				map[i][j] = 2;
		}
}

int Map::getPos(int i, int j) const{
	return map[i][j];
}

int Map::getWide() const{
	return Wide;
}

int Map::getHeight() const{
	return Height;
}

int** Map::getMap() const{
	return map;
}

//Check
bool Map::IsX(int i) const{
	return (i >= 0 && i < Height);
}

bool Map::IsY(int j) const{
	return (j >= 0 && j < Wide);
}

//Print
void Map::Print(ostream& out) const{
	for(int i = 0; i < Height; i++){
		for(int j = 0; j < Wide; j++){
			if(map[i][j] == 9)
				out << " *";
			else if(map[i][j] == 1)
				out << " -";
			else if(map[i][j] == 2)
				out << " X";
			else
				out << " .";
		}
		out << endl;
	}
}



//Path Find
//Check
bool Path_Find::IsX(int i) const{
	return (i >= 0 && i < map.getHeight());
}

bool Path_Find::IsY(int j) const{
	return (j >= 0 && j < map.getWide());
}

bool Path_Find::IsGoal(int t) const{
	return t == Goal;
}

void Path_Find::XYConvert(int k, int& x, int& y) const{
	x = k / map.getWide();
	y = k % map.getWide();
}

int Path_Find::ConvertXY(int x, int y) const{
	return x * map.getWide() + y;
}

//Set & Get
void Path_Find::setGoal(int i, int j){
	Goal = i * map.getWide() + j;
}

void Path_Find::setStart(int i, int j){
	Start = i * map.getWide() + j;
}

void Path_Find::setMap(Map src){
	map.Set(src.getHeight(), src.getWide());
	int**m = new int*[map.getHeight()];
	for(int i = 0; i < map.getHeight(); i++){
		m[i] = new int[map.getWide()];
		for(int j = 0; j < map.getWide(); j++)
			m[i][j] = src.getPos(i, j);
	}
	map.setMap(m);
}

void Path_Find::setRandomMap(){
	map.setRandomMap();
}

int Path_Find::getMapWide() const{
	return map.getWide();
}

int Path_Find::getMapHeight() const{
	return map.getHeight();
}

Map Path_Find::getMap() const{
	return map;
}

int Path_Find::getStart() const{
	return Start;
}

int Path_Find::getGoal() const{
	return Goal;
}

//Print
void Path_Find::PrintMap(ostream& out) const{
	map.Print(out);
}

//Main Operations

//Breadth First Search
bool Path_Find::Search_BFS(){
	queue<int> Q;
	Q.push(Start);

	while(!Q.empty()){
		int t = Q.front();
		Q.pop();
		int xt, yt;
		XYConvert(t, xt, yt);
		map.setPos(9, xt, yt);

		if(IsGoal(t)){
			return true;
		}

		for(int i = xt - 1; i <= xt + 1; i++)
			for(int j = yt - 1; j <= yt + 1; j++)
				if(IsX(i) && IsY(j) && map.getPos(i, j) != 1 && map.getPos(i, j) != 2 && map.getPos(i, j) != 9){
					map.setPos(1, i, j);
					int t1 = ConvertXY(i, j);
					Q.push(t1);
				}
	}
	
	return false;
}

//Seach A Star Distance
float Path_Find::Heuristic_Distance(int x1, int y1) const{
	int x2, y2;
	XYConvert(Goal, x2, y2);
	return sqrt( float( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) ) );
}

void Path_Find::Search_A_Star_Distance(int &step, int &open){
	pair<float, int> temp;
	int x, y;
	XYConvert(Start, x, y);
	temp.first = Heuristic_Distance(x, y);
	temp.second = Start;
	priority_queue< pair<float, int>, vector<pair<float, int> >, greater<pair<float, int> > > PQ;
	PQ.push(temp);
	step = 0;
	open = 0;

	while(!PQ.empty()){
		pair<float, int> t;
		t = PQ.top();
		int xt, yt;
		XYConvert(t.second, xt, yt);
		map.setPos(9, xt, yt);
		PQ.pop();
		step++;

		system("cls");
		PrintMap(cout);
		Sleep(500);

		if(IsGoal(t.second)){
			cout << "Find Path Successfully!" << endl;
			return ;
		}

		for(int i = xt - 1; i <= xt + 1; i++)
			for(int j = yt - 1; j <= yt + 1; j++)
				if(IsX(i) && IsY(j) && map.getPos(i, j) != 1 && map.getPos(i, j) != 2 && map.getPos(i, j) != 9){
					map.setPos(1, i, j);
					pair<float, int> t1;
					t1.second = ConvertXY(i, j);
					t1.first = Heuristic_Distance(i, j) + Heuristic_Distance(xt, yt, i, j);
					PQ.push(t1);
					open++;
				}
	}

	cout << "Find Path Fail!" << endl;
	return ;
}

//IDA Star Distance
bool Path_Find::Recursion(int &step, int&open, int k){
	pair<float, int> temp;
	int x, y;
	XYConvert(Start, x, y);
	float Dist = float(k) + Heuristic_Distance(x, y);
	temp.first = -Dist;
	temp.second = Start;
	priority_queue< pair<float, int>, vector<pair<float, int> >, greater<pair<float, int> > > PQ;
	PQ.push(temp);
	step = 0;
	open = 0;

	while(!PQ.empty()){
		pair<float, int> t;
		t = PQ.top();
		int xt, yt;
		XYConvert(t.second, xt, yt);
		map.setPos(9, xt, yt);
		PQ.pop();
		step++;

		/*system("cls");
		Sleep(250);
		PrintMap(cout);*/

		if(IsGoal(t.second)){
			cout << "Find Path Successfully!" << endl;
			return true;
		}

		if(t.first >= 0){
			return false;
		}

		for(int i = xt - 1; i <= xt + 1; i++)
			for(int j = yt - 1; j <= yt + 1; j++)
				if(IsX(i) && IsY(j) && map.getPos(i, j) != 1 && map.getPos(i, j) != 2 && map.getPos(i, j) != 9){
					map.setPos(1, i, j);
					pair<float, int> t1;
					t1.second = ConvertXY(i, j);
					t1.first = Heuristic_Distance(i, j) - Dist;
					PQ.push(t1);
					open++;
				}
	}

	return false;
}

void Path_Find::IDA_Star_Distance(int &step, int &open){
	int n = (map.getHeight() > map.getWide()) ? map.getHeight() : map.getWide();
	step = 0;
	open = 0;
	Map temp = this->map;
	for(int i = 0 ; i < n; i++){
		if(Recursion(step, open, i))
			return ;
		else
			this->map = temp;
	}

	cout << "Find Path Fail!" << endl;
	return ;
}

//Improve A Star Distance
float Path_Find::Heuristic_Distance(int x1, int y1, int x2, int y2) const{
	return sqrt( float( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) ) );
}

void Path_Find::Improve_A_Star_Distance(int &step, int &open){
	pair<float, int> temp, temp1;
	int x, y, x1, y1;
	XYConvert(Start, x, y);
	XYConvert(Goal, x1, y1);

	temp.first = Heuristic_Distance(x, y);
	temp.second = Start;

	temp1.first = Heuristic_Distance(x1, y1);
	temp1.second = Goal;

	priority_queue< pair<float, int>, vector<pair<float, int> >, greater<pair<float, int> > > PQ;
	PQ.push(temp);

	priority_queue< pair<float, int>, vector<pair<float, int> >, greater<pair<float, int> > > PQ1;
	PQ1.push(temp1);

	step = 0;
	open = 0;

	while(!PQ.empty() && !PQ1.empty()){
		pair<float, int> t, t1;
		t = PQ.top();
		t1 = PQ1.top();

		int xt, yt, xt1, yt1;
		XYConvert(t.second, xt, yt);
		XYConvert(t1.second, xt1, yt1);

		map.setPos(9, xt, yt);
		map.setPos(9, xt1, yt1);

		PQ.pop();
		PQ1.pop();
		step += 2;

		system("cls");
		PrintMap(cout);
		Sleep(500);

		float h_dist = Heuristic_Distance(xt1, yt1, xt, yt);

		if(h_dist == sqrt(float(2)) || h_dist == 1){
			cout << "Find Path Successfully!" << endl;
			return ;
		}

		setGoal(xt1, yt1);

		for(int i = xt - 1; i <= xt + 1; i++)
			for(int j = yt - 1; j <= yt + 1; j++)
				if(IsX(i) && IsY(j) && map.getPos(i, j) != 1 && map.getPos(i, j) != 2 && map.getPos(i, j) != 9){
					map.setPos(1, i, j);
					pair<float, int> t;
					t.second = ConvertXY(i, j);
					t.first = Heuristic_Distance(i, j);
					PQ.push(t);
					open++;
				}

		for(int i = xt1 - 1; i <= xt1 + 1; i++)
			for(int j = yt1 - 1; j <= yt1 + 1; j++)
				if(IsX(i) && IsY(j) && map.getPos(i, j) != 1 && map.getPos(i, j) != 2 && map.getPos(i, j) != 9){
					map.setPos(1, i, j);
					pair<float, int> t1;
					t1.second = ConvertXY(i, j);
					t1.first = Heuristic_Distance(i, j, xt, yt);
					PQ1.push(t1);
					open++;
				}
	}

	cout << "Find Path Fail!" << endl;
	return ;
}
