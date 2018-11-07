// You need to complete this program for your second project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include <vector>
#include <stack>
#include <set>

struct Point
{
	Point(int x, int y): x(x), y(y) {}
	Point():x(0), y(0){}
	int x; 
	int y; 
};
#define iPair std::pair<int, int>
  
// Stores the result (points of convex hull) 
std::set<iPair> hull; 
std::vector<iPair> getPairs(std::ifstream&);
void printHull(std::vector<iPair>, int, std::string);
void quickHull(std::vector<iPair>, int, iPair, iPair, int);
int lineDist(iPair, iPair, iPair);
int findSide(iPair, iPair, iPair);
std::vector<Point> getPoints(std::ifstream&);
int minY(std::vector<Point>&);
bool sortHelper(Point, Point);
void sortPoints(std::vector<Point>&);
void printVector(const std::vector<Point>&);
int grahamHelper(Point, Point, Point);
int orientation(Point, Point, Point);
void jarvisMarch(std::string, std::string);
Point nextToTop(std::stack<Point> &);
int dist(Point, Point);
int compare(const void *, const void *);
void grahamScan(std::string, std::string);
Point p0;


int main(int argc, char *argv[])
{
   if (argc < 3) {
      std::cout << "wrong format! should be \"a.exe algType dataFile\"";
    }
   else {
      std::string algType = argv[1];
      std::string dataFilename = argv[2];
      std::string outputFile = "";
      //read your data points from dataFile (see class example for the format)
      
      if (algType[0]=='G') {
      //call your Graham Scan algorithm to solve the problem
      	outputFile = "hull_G.txt";
      	grahamScan(dataFilename, outputFile);
         

			} 
			else if (algType[0]=='J') {
		  //call your Javis March algorithm to solve the problem
		  	outputFile = "hull_J.txt";
		  	jarvisMarch(dataFilename, outputFile); 
		        
			}
			else { //default 
		  //call your Quickhull algorithm to solve the problem
		  	outputFile = "hull_Q.txt";
		  	std::ifstream infile ("test.txt", std::ifstream::in);
   			std::vector<iPair> a = getPairs(infile);
    		int n = a.size();
    		printHull(a, n, outputFile); 

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
void jarvisMarch(std::string input, std::string output) 
{ 
    // There must be at least 3 points 
	std::ifstream infile (input, std::ifstream::in);
	std::ofstream outfile (output);
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
    	outfile << "(" << hull[i].x << ", " << hull[i].y << ")\n"; 
} 



//*************************************************************
/*void grahamScan(std::string input, std::string output){
	 std::ifstream infile (input, std::ifstream::in);
	 std::ofstream outfile (output);
   std::vector<Point> v = getPoints(infile);
   std::stack<Point> s;
   printVector(v);
   sortPoints(v); 
   printVector(v);
   s.push(v[0]);
   s.push(v[1]);
   s.push(v[2]);
   for(int i = 2; i < v.size(); ++i)
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
   	outfile << "(" << p.x << ", " << p.y << "),"; 
   }

}*/
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
	std::sort(v.begin(), v.end(), sortHelper);
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
	return index; 
}
int findSide(iPair p1, iPair p2, iPair p) 
{ 
    int val = (p.second - p1.second) * (p2.first - p1.first) - 
              (p2.second - p1.second) * (p.first - p1.first); 
  
    if (val > 0) 
        return 1; 
    if (val < 0) 
        return -1; 
    return 0; 
} 
  
// returns a value proportional to the distance 
// between the point p and the line joining the 
// points p1 and p2 
int lineDist(iPair p1, iPair p2, iPair p) 
{ 
    return abs ((p.second - p1.second) * (p2.first - p1.first) - 
               (p2.second - p1.second) * (p.first - p1.first)); 
} 
  
// End points of line L are p1 and p2.  side can have value 
// 1 or -1 specifying each of the parts made by the line L 
void quickHull(std::vector<iPair> a, int n, iPair p1, iPair p2, int side) 
{ 
    int ind = -1; 
    int max_dist = 0; 
  
    // finding the point with maximum distance 
    // from L and also on the specified side of L. 
    for (int i=0; i<n; i++) 
    { 
        int temp = lineDist(p1, p2, a[i]); 
        if (findSide(p1, p2, a[i]) == side && temp > max_dist) 
        { 
            ind = i; 
            max_dist = temp; 
        } 
    } 
  
    // If no point is found, add the end points 
    // of L to the convex hull. 
    if (ind == -1) 
    { 
        hull.insert(p1); 
        hull.insert(p2); 
        return; 
    } 
  
    // Recur for the two parts divided by a[ind] 
    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2)); 
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1)); 
} 
  
void printHull(std::vector<iPair> a, int n, std::string output) 
{ 
    std::ofstream outfile (output);
    // a[i].second -> y-coordinate of the ith point 
    if (n < 3) 
    { 
        std::cout << "Convex hull not possible\n"; 
        return; 
    } 
  
    // Finding the point with minimum and 
    // maximum x-coordinate 
    int min_x = 0, max_x = 0; 
    for (int i=1; i<n; i++) 
    { 
        if (a[i].first < a[min_x].first) 
            min_x = i; 
        if (a[i].first > a[max_x].first) 
            max_x = i; 
    } 
  
    // Recursively find convex hull points on 
    // one side of line joining a[min_x] and 
    // a[max_x] 
    quickHull(a, n, a[min_x], a[max_x], 1); 
  
    // Recursively find convex hull points on 
    // other side of line joining a[min_x] and 
    // a[max_x] 
    quickHull(a, n, a[min_x], a[max_x], -1); 
  
    std::cout << "The points in Convex Hull are:\n"; 
    while (!hull.empty()) 
    { 
        outfile << "(" <<( *hull.begin()).first << ", " << (*hull.begin()).second << ") "; 
        hull.erase(hull.begin()); 
    }
    std::cout << std::endl; 
} 
std::vector<iPair> getPairs(std::ifstream& infile){
	std::vector<iPair> v; 
	int x, y; 
	while(true){
		infile >> x >> y;
		if(infile.eof())
			break;  
		v.push_back(iPair(x,y));
	}
	return v; 
}
Point nextToTop(std::stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}
 
// A utility function to return square of distance between p1 and p2
int dist(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
 
// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *) vp1;
    Point *p2 = (Point *) vp2;
 
    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (dist(p0, *p2) >= dist(p0, *p1)) ? -1 : 1;
 
    return (o == 2) ? -1 : 1;
}
 
// Prints convex hull of a set of n points.
void grahamScan(std::string input, std::string output)
{
    std::ifstream infile (input, std::ifstream::in);
	 	std::ofstream outfile (output);
	 	std::vector<Point> v = getPoints(infile);
	 	int n = v.size(); 

    int ymin = minY(v); 
    iter_swap(v.begin(), v.begin()+ minY(v));
 
    // Sort n-1 points with respect to the first point.  A point p1 comes
    // before p2 in sorted ouput if p2 has larger polar angle (in
    // counterclockwise direction) than p1
    p0 = v[0];
    qsort(&v[1], n - 1, sizeof(Point), compare);
 
    // Create an empty stack and push first three points to it.
    std::stack<Point> S;
    S.push(v[0]);
    S.push(v[1]);
    S.push(v[2]);
 
    // Process remaining n-3 points
    for (int i = 3; i < n; i++)
    {
        // Keep removing top while the angle formed by points next-to-top,
        // top, and points[i] makes a non-left turn
        while (orientation(nextToTop(S), S.top(), v[i]) != 2)
            S.pop();
        S.push(v[i]);
    }
 
    // Now stack has the output points, print contents of stack
    while (!S.empty())
    {
        Point p = S.top();
        outfile << "(" << p.x << ", " << p.y << ")" << std::endl;
        S.pop();
    }
}













