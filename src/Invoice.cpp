/*
 * Invoice.cpp
 *
 *  Created on: Oct 21, 2018
 *      Author: andrefmrocha
 */

#include "Invoice.h"

using namespace std;
static double goldCard = 10;

Invoice::Invoice(string name, string teacher, vector<Reservation *> reservs, bool isGold)
{
	this->name = name;
	this->assignedTeacher = teacher;
	this->reservs  = reservs;
	this->totalPrice = 0;
	this->isGold = isGold;
	for(auto i : reservs) // Calculates the price of the total of reservations
	{
		this->totalPrice+= i->getPrice();
	}
	if(isGold) // Adds the price of the Gold Card if necessary
		this->totalPrice+=goldCard;
}


double Invoice::getPrice() const
{
	return this->totalPrice;
}

vector<Reservation*> Invoice::getReservs()
{
	return reservs;
}
ostream & operator<<(ostream &out, Invoice inv)
{
	if(inv.getReservs().empty()) { // Checks if there were any Reservations
		out << "There were no reservations made by the user for this month." << endl;
		//Check if user is gold  and put monthly fee
	} else{ // Shows all reservations
		out << "Discrimination of every use of the court by the user:" << endl;
		for(unsigned int i = 0; i < inv.getReservs().size(); i++)
		{
			out << i +1 << " - " << inv.getReservs()[i]->getDay() << "/" << inv.getReservs()[i]->getMonth() << " : " << inv.getReservs()[i]->getPrice() << endl;
		}
	}
	out << "Final price:" << inv.getPrice(); // And their final price
	return out;
}

void Invoice::indentation(std::ofstream &outfile, int indent)
{
	for(int i = 0; i < indent; i++)
	{
		outfile << "\t";
	}
}


void Invoice::storeInfo(std::ofstream &outfile, int indent)
{
	indentation(outfile, indent);
	outfile << "{" << endl;
	indent++;
    indentation(outfile, indent); // Saves if it is a Gold Member
    outfile << "\"isGold\": " << this->isGold << "," << endl;
    indentation(outfile, indent); // Saves the reservations
	outfile << "\"reservs\": [" << endl;
	indent++;
	for(unsigned int i = 0; i < this->reservs.size(); i++)
	{
		this->reservs[i]->storeInfo(outfile, indent);
		if(i+1 != this->reservs.size())
			outfile << "," << endl;
		else
		{
			outfile << endl;
		}
	}
	indent--;
	indentation(outfile, indent);
	outfile << "]," << endl;
	indentation(outfile, indent); // Saves the totalPrice
	outfile << "\"totalPrice\": " << this->totalPrice <<  "," << endl;
	indentation(outfile, indent); // Saves the name of the User
	outfile << "\"name\": " << "\"" << this->name << "\"" << "," << endl;
	indentation(outfile, indent); // Saves the teacher of the User
	outfile << "\"assignedTeacher\": " << "\"" << this->assignedTeacher << "\""<< endl;
	indent--;
	indentation(outfile, indent);
	outfile << "}";
}


void Invoice::readInfo(std::ifstream &infile)
{
	string savingString;
	while (getline(infile, savingString))
	{
	    if(savingString.find("isGold") != string::npos) // Reads if it's Gold
        {
	        savingString = savingString.substr(savingString.find("isGold") + 9,1);
	        this->isGold = (savingString != "0");
        }
		if(savingString.find("reservs") != string::npos) // Reads the reservations
		{
			while (getline(infile, savingString))
			{
				if(savingString.find("free") != string::npos) // Checks if it's a free
				{
					Reservation * free = new Free();
					free->readInfo(infile);
					reservs.push_back(free);
				}

				if(savingString.find("lesson") != string::npos) // Checks if it's a lesson
				{
					Reservation * free = new Lesson();
					free->readInfo(infile);
					reservs.push_back(free);
				}

				if(savingString.find(']') != string::npos)
				{
					break;
				}
			}
		}

		if(savingString.find("totalPrice") != string::npos) // Reads the total Price
		{
			savingString = savingString.substr(savingString.find("totalPrice") + 12);
			savingString = savingString.substr(0, savingString.find(','));
			this->totalPrice = stod(savingString);
		}

		if(savingString.find("name") != string::npos) // Reads the name of the user
		{
			savingString = savingString.substr(savingString.find("name") + 7);
			savingString = savingString.substr(1, savingString.find_last_of('\"') - 1);
			this->name = savingString;
		}

		if(savingString.find("assignedTeacher") != string::npos) // Reads the name of the teacher assigned
		{
			savingString = savingString.substr(savingString.find("assignedTeacher") + 18);
			savingString = savingString.substr(1, savingString.find_last_of('\"') - 1);
			this->assignedTeacher = savingString;
			break;
		}
	}
}