// You need to complete this program for your second project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>


int main(int argc, char *argv[])
{
   //Second project starts here
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
      
      //write your convex hull to the outputFile (see class example for the format)
      //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.
	
	return 0;
}

int minY (ifstream& infile){

}