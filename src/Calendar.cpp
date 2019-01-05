/*
 * Year.cpp
 *
 *  Created on: Oct 20, 2018
 *      Author: andrefmrocha
 */

#include "Calendar.h"
#include <cmath>
using namespace std;

Year::Year(int year)
{
	// It is first determined if it is a leap year
	bool isLeapYear = false;
	if((year % 4 == 0 && year % 100 !=0) || year % 400 == 0)
		isLeapYear = true;

	for (int i = 1; i < 13; i++)
	{
		//Checks if it's February
		if(i == 2)
		{
			if(isLeapYear)
				this->months.push_back(Month(i, 29));
			else
				this->months.push_back(Month(i, 28));
		}
		else
		{
			//Determines the number of days in a normal month
			int daysInMonth = 30 + (i + (int)floor((double)i/8))%2;
			this->months.push_back(Month(i, daysInMonth));
		}
	}
}

void Year::setMonths(std::vector<Month> months)
{
    this->months = months;
}


Month& Year::getMonth(int month)
{
	return this->months[month - 1];
}

Month::Month(int month, int days)
{
	this->month = month;
	// Pushes all the Days into the month
	for(int i = 0;  i < days; i++)
	{
		this->days.push_back(Day(pair<int, int> (8, 20)));
	}
}

Day& Month::getDay(int day)
{
	Day day1 = this->days[day - 1];
	return this->days[day - 1];
}


void Month::setDays(std::vector<Day> days)
{
    this->days = days;
}

void Month::setMonth(int month)
{
	this->month = month;
}

Day::Day(pair<int, int> workingHours)
{
	// Prepares the hours the vector of booleans to be pushes
	int hours = workingHours.second - workingHours.first;
	hours*=2;
	//Pushes all the booleans into the vector
	for(int i = 0;  i < hours; i++)
	{
		this->schedule.push_back(false);
	}
	this->startingHour = workingHours.first;
}

bool Day::checkSchedule(double startingHours, int duration) const
{
	// Checks if the court is open
	if(startingHours < this->startingHour)
	{
		return false;
	}
	startingHours -= this->startingHour;
	// Since the duration of each is half an hour, it is necessary to calculate the starting Hour
	startingHours *= 2;
	for(int i = startingHours; i < (startingHours+duration); i++)
	{
		if(this->schedule[i] == true) // If any of the times is occupied, it returns false
		{
			return false;
		}
	}
	return true;
}

void Day::setSchedule(double startingHours, int duration)
{
	startingHours -= this->startingHour;
	startingHours*=2;
	// The vector is filled with true values
	for(int i = startingHours; i < (startingHours+duration); i++)
	{
		this->schedule[i] = true;
	}
}

void Day::unsetSchedule(double startingHours, int duration)
{
	startingHours -= this->startingHour;
	startingHours*=2;
	// The vector is filled with true values
	for(int i = startingHours; i < (startingHours+duration); i++)
	{
		this->schedule[i] = false;
	}
}

void Day::setSchedule(std::vector<bool> schedule)
{
    this->schedule = schedule;
}

int Month::getMonth()
{
	return month;
}

std::vector<bool> Day::getSchedule()
{
	return this->schedule;
}

int Month::getNoDays()
{
	return this->days.size();
}

int Day::getSH() const
{
	return this->startingHour;
}

void Day::setSH(int sH)
{
	this->startingHour = sH;
}
