// You need to complete this program for your second project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include <vector>
#include <stack>

struct Point
{
	Point(int x, int y): x(x), y(y) {}
	int x; 
	int y; 
};

std::vector<Point> getPoints(std::ifstream&);
int minY(std::vector<Point>&);
bool sortHelper(Point, Point);
void sortPoints(std::vector<Point>&);
void printVector(const std::vector<Point>&);
int grahamHelper(Point, Point, Point);
void grahamScan(); 

int main(int argc, char *argv[])
{
   //Second project starts here
	grahamScan();


   if (argc < 3) 
      std::cout << "wrong format! should be \"a.exe algType dataFile\"";
   else {
      std::string algType = argv[2];
      std::string dataFilename = argv[3];
      std::string outputFile = "";
      //read your data points from dataFile (see class example for the format)
      
      if (algType[0]=='G') {
         //call your Graham Scan algorithm to solve the problem
         outputFile = "hull_G.txt";
		} 
		else if (algType[0]=='J') {
		         //call your Javis March algorithm to solve the problem
		         outputFile = "hull_J.txt";
		}
		else { //default 
		         //call your Quickhull algorithm to solve the problem
		         outputFile = "hull_Q.txt";
		   }
		}
      
      //write your convex hull to the outputFile (see class example for the format)
      //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.
	
	return 0;
}
void grahamScan(){
	std::ifstream infile ("test.txt", std::ifstream::in);
   std::vector<Point> v = getPoints(infile);
   std::stack<Point> s; 
   printVector(v); 
   sortPoints(v); 
   printVector(v);
   s.push(v[0]);
   s.push(v[1]);
   s.push(v[2]);
   for(int i = 3; i < v.size(); ++i)
   {
   	Point top = s.top(); 
   	s.pop();
   	while(grahamHelper(s.top(), top, v[i]) < 0)
   	{
   		top = s.top(); 
   		s.pop();
   	}
   	s.push(top); 
   	s.push(v[i]);

   }

   while(!s.empty()){
   	Point p = s.top(); 
   	s.pop(); 
   	std::cout << "(" << p.x << ", " << p.y << "),"; 
   }
}
int grahamHelper(Point a, Point b, Point c)
{
	return((b.x - a.x)*(c.y - b.y) - (b.y - a.y)*(c.x - b.x));
}
void printVector(const std::vector<Point>& v){
	for(auto i : v)
		std::cout << "(" << i.x << ", " << i.y << ")" << std::endl; 
}
void sortPoints(std::vector<Point>& v){
	iter_swap(v.begin(), v.begin()+ minY(v));
	std::sort(v.begin()+1, v.end(), sortHelper);
}

bool sortHelper(Point i, Point j){
	return(i.y/i.x <= j.y/j.x); 
}

std::vector<Point> getPoints(std::ifstream& infile){
	std::vector<Point> v; 
	int x, y; 
	while(true){
		infile >> x >> y;
		if(infile.eof())
			break;  
		v.push_back(Point(x,y));
	}
	return v; 
}

int minY(std::vector<Point>& v){
	int minx = v[0].x;
 	int miny = v[0].y;
 	int index = 0; 
	for(int i = 0; i < v.size(); ++i)
	{
		if(v[i].y < miny){
			index = i;
			minx = v[i].x;
 			miny = v[i].y;
		}
		else if(miny == v[i].y && v[i].x < minx){
			index = i;
			minx = v[i].x;
 			miny = v[i].y;
 		}
	}
	std::cout << "(min x: " << minx << ", min y: " << miny << ")" << std::endl; 
	return index; 
}















