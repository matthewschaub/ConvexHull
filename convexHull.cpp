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
int orientation(Point, Point, Point);
void jarvisMarch();  

int main(int argc, char *argv[])
{
   //Second project starts here
	//grahamScan();
	jarvisMarch(); 



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
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

 
// Prints convex hull of a set of n points.
void jarvisMarch() 
{ 
    // There must be at least 3 points 
	std::ifstream infile ("test.txt", std::ifstream::in);
   std::vector<Point> v = getPoints(infile);
   int n = v.size(); 
   if (n < 3) return; 
   // Initialize Result 
   std::vector<Point> hull; 
  	// Find the leftmost point 
   int l = minY(v);
  
    // Start from leftmost point, keep moving counterclockwise 
    // until reach the start point again.  This loop runs O(h) 
    // times where h is number of points in result or output. 
    int p = l, q; 
    do
    { 
        // Add current point to result 
        hull.push_back(v[p]); 
  
        // Search for a point 'q' such that orientation(p, x, 
        // q) is counterclockwise for all points 'x'. The idea 
        // is to keep track of last visited most counterclock- 
        // wise point in q. If any point 'i' is more counterclock- 
        // wise than q, then update q. 
        q = (p+1)%n; 
        for (int i = 0; i < n; i++) 
        { 
           // If i is more counterclockwise than current q, then 
           // update q 
           if (orientation(v[p], v[i], v[q]) == 2) 
               q = i; 
        } 
  
        // Now q is the most counterclockwise with respect to p 
        // Set p as q for next iteration, so that q is added to 
        // result 'hull' 
        p = q; 
  
    } while (p != l);  // While we don't come to first point 
  
    // Print Result 
    for (int i = 0; i < hull.size(); i++) 
    	std::cout << "(" << hull[i].x << ", " << hull[i].y << ")\n"; 
} 



//*************************************************************
void grahamScan(){
	std::ifstream infile ("test.txt", std::ifstream::in);
   std::vector<Point> v = getPoints(infile);
   std::stack<Point> s; 
   sortPoints(v); 
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















