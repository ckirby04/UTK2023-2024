/* Program Name: Boiling Water Lab
 * Student Name: Clark Kirby
 * Program Description: Calculates the boiling point of water at various locations 
 * based on altitude.	*/

#include <cmath> 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

double elevationToBoilingPoint(const double elevation) {

	double pressure = 29.921 * pow(1 - 0.0000068753 * elevation, 5.2559);
    double boilingPoint = 49.161 * log(pressure) + 44.932;

    return boilingPoint;
}

int main(int argc, char **argv) {
	
	if (!(argc == 2)){ // if the program isnt run with one one extra argument, the file, then quit 
		cerr << "usage: ./boiling filename" << endl;
		return 1;
	}
	
	ifstream fin;	// just a reminder for me to always close this.
	fin.open(argv[1]);
	if(!(fin.is_open())){	 // if file fails to open
		cerr << "File failed to open." << endl;
		return 1;
	}
	

	vector <string> cities;	// vector of city names
	vector <int> elevations;	// no vector for state, we dont use that garbage
	string city;
	string state; // garbage
	string elevation;
	string line;	

	getline(fin, line);	// excuse the first "title" line

	while( getline(fin, line) ){ // keeps reading lines until no more lines in file

		istringstream stream(line);	// intake the line into the stream
		
		getline(stream, city, ',');
		getline(stream, state, ',');
		getline(stream, elevation, ',');

		cities.push_back(city); // add the city name to the vector
		elevations.push_back(stoi(elevation));
	}	
	fin.close(); // always close
	

	cout << "Boiling Point at Altitude Calculator" << endl; 


	for( int i = 0; i < cities.size(); i++ ){	// print the list of city names added to the vector
		cout << i + 1 << ". " << cities[i] << endl;
	}

	
	cout << "Enter city number: ";
	int num;
	cin >> num;
	num -= 1; // convert from base 1 to base 0 indexing for the vector

	string finalCity = cities[num]; // final city selected, for printing 
	double finalElevation = elevationToBoilingPoint(elevations[num]); // calls boilingpoint function 


	cout << "The boiling point at " << finalCity << " is " << finalElevation << " degrees Fahrenheit." << endl;
	
    return 0;
}
