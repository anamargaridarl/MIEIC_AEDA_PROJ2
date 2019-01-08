/*
 * Reservation.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation(int month,int day,double startingHour,double price,unsigned int duration) : price(price)
{
	this->month = month;
	this->day = day;
	this->startingHour = startingHour;
	this->duration = duration;
}

double Reservation::getPrice()
{
	return price;
}

double Reservation::getStartingHour()
{
	return startingHour;
}

int Reservation::getDuration()
{
	return duration;
}

int Reservation::getMonth()
{
	return month;
}

int Reservation::getDay()
{
	return day;
}
bool Reservation::operator ==(Reservation &r) const
	{
		return (this->day == r.getDay() && this->month == r.getMonth() && this->startingHour == r.getStartingHour());
	}

Lesson::Lesson(int m,int d,double strHr,double p,unsigned int dr,string teacherName) : Reservation(m,d,strHr,p,dr)
{
	this->teacherName = teacherName;
}

double Lesson::getPrice()
{
	return price;
}


Free::Free(int m,int d,double strHr,double p,unsigned int dur) : Reservation(m,d,strHr,p,dur)
{

}

double Free::getPrice()
{
	return price;
}


void Reservation::indent(std::ofstream &outfile, int indent)
{
	for(int i = 0; i < indent; i++)
	{
		outfile << "\t";
	}
}

void Reservation::storeInfo(std::ofstream &outfile, int indent)
{
	Reservation::indent(outfile, indent); // Saves the price
	outfile << "\"price\": " << this->price << "," << endl;
	Reservation::indent(outfile, indent); // Saves the duration
	outfile << "\"duration\": " << this->duration<< "," << endl;
	Reservation::indent(outfile, indent); // Saves the month
	outfile << "\"month\": " << this->month << "," << endl;
	Reservation::indent(outfile, indent); // Saves the day
	outfile << "\"day\": " << this->day << "," << endl;
	Reservation::indent(outfile, indent); // Saves the Starting Hour
	outfile << "\"startingHour\": " << this->startingHour << endl;
	indent--;
	Reservation::indent(outfile, indent);
	outfile << "}";
}


void Reservation::readInfo(std::ifstream &infile)
{
	string savingString;
	bool flag = false;
	while (getline(infile, savingString))
	{ 	// Reads the price
		if(savingString.find("price") != string::npos)
		{
			savingString = savingString.substr(savingString.find("price") + 8);
			this->price = stod(savingString.substr(0, savingString.find(',')));
		}
		// Reads the duration
		if(savingString.find("duration") != string::npos)
		{
			this->duration = (unsigned  int) stoul(savingString.substr(savingString.find("duration") + 11, 1));
		}

		// Reads the month
		if(savingString.find("month") != string::npos)
		{
			savingString = savingString.substr(savingString.find("month") + 8);
			savingString = savingString.substr(0, savingString.find(','));
			this->month = stoi(savingString);
		}

		// Reads the day
		if(savingString.find("day") != string::npos)
		{
			savingString = savingString.substr(savingString.find("day") + 6, 2);
			savingString = savingString.substr(0, savingString.find(','));
			this->day = stoi(savingString);
		}

		// Reads the Starting Hour
		if(savingString.find("startingHour") != string::npos)
		{
			flag = true;
			savingString = savingString.substr(savingString.find("startingHour") + 15);
			savingString = savingString.substr(0, savingString.find(','));
			this->startingHour = stod(savingString);
		}

		if(flag)
		{
			break;
		}
	}
}

string Reservation::getHourFormat(double hour) {

	string hr = to_string((int)floor(hour));
	hr += ":";
	if((hour - floor(hour)) == 0)
		hr += "00";
	else
		hr+= "30";

	return hr;
}

void Reservation::show() {
	cout << "Month: " << to_string(getMonth()) << endl;
	cout << "Day: " << to_string(getDay()) << endl;
	double final;
	cout << "Period of class: " << getHourFormat(getStartingHour()) << " - " << getHourFormat(getStartingHour()+((double)(getDuration())*0.5))<< endl;
	cout << "Price: " << to_string(getPrice()) << endl;
}

bool Reservation::operator== (Reservation & r)
{
	return (duration == r.getDuration() && month == r.getMonth() && day == r.getDay()
			&& startingHour == r.getStartingHour());
}

std::string Reservation::getTeacher() const {
	return "";
}

void Reservation::setMonth(int month) {
	this->month = month;
}

void Reservation::setDay(int day) {
	this->day = day;
}

void Reservation::setStartHour(double startH) {
this->startingHour = startH;
}

void Reservation::setDuration(unsigned int dur) {
	this->duration = dur;
}

void Reservation::setPrice(double price) {
	this->price = price;
}

void Reservation::setTeacher(std::string teacher) {

}

void Free::readInfo(std::ifstream &infile)
{
	Reservation::readInfo(infile);
}

void Lesson::readInfo(std::ifstream &infile)
{
    string savingString;
    while(getline(infile, savingString))
    {
        if(savingString.find("teacherName") != string::npos)
        {
            savingString = savingString.substr(savingString.find(" ") + 2);
            savingString = savingString.substr(0, savingString.size() - 2);
            this->teacherName = savingString;
            break;
        }
    }
	Reservation::readInfo(infile);
}

void Free::storeInfo(std::ofstream &outfile, int indent)
{
    Reservation::indent(outfile, indent);
    outfile << "{" << endl;
    indent++;
    Reservation::indent(outfile, indent); // Stores if it's a free before saving the information
    outfile << "\"type\": " << "\"free\", " << endl;
    Reservation::storeInfo(outfile, indent);
}

void Free::show() {
	cout << "Free mode: " << endl;
	Reservation::show();
}

std::string Free::getTeacher() const {
	return "";
}

void Lesson::storeInfo(std::ofstream &outfile, int indent)
{
    Reservation::indent(outfile, indent);
    outfile << "{" << endl;
    indent++;
    Reservation::indent(outfile, indent); // Stores if it's a lesson before saving the information
    outfile << "\"type\": " << "\"lesson\", " << endl;
    Reservation::indent(outfile, indent);
    outfile << "\"teacherName\": \"" << this->teacherName << "\", " << endl;
    Reservation::storeInfo(outfile, indent);
}

void Lesson::show() {
	cout << "Lesson : " << endl;
	Reservation::show();
	cout << "Teacher: " << teacherName << endl;
}

std::string Lesson::getTeacher() const {
	return teacherName;
}

void Lesson::setTeacher(std::string teacher) {
this->teacherName = teacher;
}
