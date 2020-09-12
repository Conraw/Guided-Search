//461 Program 1 Connor Schafer

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "Cities.h"

	using namespace std;

int main()
{
	ifstream file1in("coordinates.txt");
	ifstream file2in("Adjacencies.txt");
	//checking to see if files open properly
	if (!file1in)
	{
		cerr << "Error opening Coordinates file!";
		system("pause");
		return 1;
	}
	if (!file2in)
	{
		cerr << "Error opening Adjacencies file!";
		system("pause");
		return 1;
	}

	string city, line;
	double xcord, ycord;
	vector<Cities> cityVector;

	file1in >> city;
	while (file1in >> xcord >> ycord)
	{ 
		Cities currentCity;
		//setting the variables in the class
		currentCity.setCityName(city);
		currentCity.setXCord(xcord);
		currentCity.setYCord(ycord);
		cityVector.push_back(currentCity);
		file1in >> city;
	}

	while (getline(file2in, line))
	{
	
	    //Base function ripped from "https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/" 
		//function to iterate through the getline in file 2 open
		//breaks up each line into words
		//adds the words after the first to the adjacency vector
		int counter = 0;
		string word = "";
		string cityName;
		for (auto x : line)
		{
			if (x == ' ' && counter == 0)
			{
				cityName = word;
				word = "";
				counter++;
			}
			else if (x == ' ' && counter > 0)
			{
				for (int i = 0; i < cityVector.size(); i++)
				{
					if (cityName == cityVector.at(i).cityName)				
						cityVector.at(i).addAdjacency(word);				
				}
				word = "";
			}
			else		
				word = word + x;		
		}	
	}
	//Very Code Heavy Way of seeing if start and end town exist.
	string townStart;
	string townEnd;
	bool exists = false;
	cout << "What is your starting town(spelled correctly) : ";
	cin >> townStart;

	int startTownNumber;
	for (startTownNumber = 0; startTownNumber < cityVector.size(); startTownNumber++)
	{
		string currentTown = cityVector.at(startTownNumber).cityName;
		if (currentTown == townStart)
		{
			exists = true;
			break;
		}
	}
	if (exists)
	{
		cout << "Valid Start Town" << endl;
	}
	else
	{
		cout << "Start Town Doesn't Exist" << endl;
		//closing files and ending
		file1in.close();
		file2in.close();
		cout << endl;
		system("pause");
		return 0;
	}
	exists = false;

	cout << "What is your ending town(spelled correctly) : ";
	cin >> townEnd;
	int endTownNumber = 0;
	Cities EndCity;
	for (int i = 0; i < cityVector.size(); i++)
	{
		string currentTown = cityVector.at(i).cityName;
		EndCity = cityVector.at(i);
		if (currentTown == townEnd)
		{
			endTownNumber = i;
			exists = true;
			break;
		}
	}
	if (exists)
	{
		cout << "Valid Ending Town" << endl;
	}
	else
	{
		cout << "Ending Town Doesn't Exist" << endl;
		//closing files and ending
		file1in.close();
		file2in.close();
		cout << endl;
		system("pause");
		return 0;
	}

	if (cityVector.at(startTownNumber).containsEndTown(cityVector, townEnd,startTownNumber))
	{
		cout << endl << endl << "Start and End City are connected";
		file1in.close();
		file2in.close();
		cout << endl;
		system("pause");
		return 0;
	}

	string currentCity = townStart;
	cout << endl << endl << endl << "Starting at " << currentCity << endl;
	string previousCity = "";
	string twoCitiesAgo = "";
	while (currentCity != townEnd)
	{
		int cityNumber = 0;
		
		for (int i = 0; i < cityVector.size(); i++)
		{
			if (currentCity == cityVector.at(i).getCityName())
			{
				cityNumber = i;
				break;
			}
		}
		Cities CurrentCityCLASS = cityVector.at(cityNumber);

		if (cityVector.at(cityNumber).containsEndTown(cityVector, townEnd, cityNumber))
		{
			cout  << currentCity <<  "  is connected to the end town of " <<  townEnd << endl;
			break;
		} 
		else
		{	
			twoCitiesAgo = previousCity;
			previousCity = currentCity;
			currentCity = CurrentCityCLASS.findDistance(cityVector, EndCity, twoCitiesAgo, previousCity);
		}

		cout << "Next City is " << currentCity << endl;

	}

	//closing files and ending
	file1in.close();
	file2in.close();
	cout << endl;
	system("pause");
	return 0;
}