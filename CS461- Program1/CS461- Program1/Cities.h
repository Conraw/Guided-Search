#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <math.h>

using namespace std;

class Cities
{
public:
	string cityName = " ";
	float x_cord = 0.0;
	float y_cord = 0.0;
	vector<string> Adjacencies;

public:
	void setCityName(string name) { cityName = name; }
	void setXCord(float xVal) { x_cord = xVal; }
	void setYCord(float yVal) { y_cord = yVal; }

	string getCityName() { return cityName; }
	double getXCord() { return x_cord; }
	double getYCord() { return y_cord; }

	void addAdjacency(string city) { Adjacencies.push_back(city); }

	bool containsEndTown(vector<Cities> cities, string endTown, int outerIndex)
	{
		for (int i = 0; i < cities.at(outerIndex).Adjacencies.size(); i++)
		{
			if (cities.at(outerIndex).Adjacencies.at(i) == endTown)
				return true;
		}
		return false;
	}

	string findDistance(vector<Cities> connectedCities,  Cities EndCity, string twoCitiesAgo, string previousCity) {
		
		double distance = 0.0, xPart = 0.0, yPart = 0.0;
		double shortestDistance = 999999999999999999.0;
		string closestAdjacentCity = "";

		for (int i = 0; i < connectedCities.size(); i++)
		{
			for (int k = 0; k < Adjacencies.size(); k++)
			{	
				if (connectedCities.at(i).cityName == Adjacencies.at(k))
				{
					if (connectedCities.at(i).Adjacencies.size() == 1 && (!connectedCities.at(i).containsEndTown(connectedCities, EndCity.cityName, i)))
					{

					}
					else
					{
						double xPart = (EndCity.x_cord - connectedCities.at(i).x_cord)*(EndCity.x_cord - connectedCities.at(i).x_cord);
						double yPart = (EndCity.y_cord - connectedCities.at(i).y_cord)*(EndCity.y_cord - connectedCities.at(i).y_cord);
						distance = sqrt(xPart + yPart);
						if (distance < shortestDistance)
						{
							shortestDistance = distance;
							closestAdjacentCity = connectedCities.at(i).cityName;
						}
					}
				}	
			}
		}
		if (closestAdjacentCity == twoCitiesAgo || closestAdjacentCity == previousCity)
		{
			int randomIndex;
			do 
			{
				 randomIndex = rand() % Adjacencies.size();
				 if (Adjacencies.size() == 1)
				 {
					 break;
				 }
			} while ((Adjacencies.at(randomIndex) == twoCitiesAgo || (Adjacencies.at(randomIndex) == previousCity)));
			closestAdjacentCity = Adjacencies.at(randomIndex);
		}
		return closestAdjacentCity;
	}
};