//
// Created by andrefmrocha on 12/24/18.
//

#include "Supporter.h"
using namespace std;

#include <iostream>
unsigned Supporter::currentID = 0;

Supporter::Supporter(const std::string &name, const std::string &gender) : name(name), gender(gender)
{
    this->ID = ++currentID;
    this->daysUntilAvailable = 0;
    this->repairDates.clear();
}

const std::string &Supporter::getName() const {
    return name;
}

void Supporter::setName(const std::string &name) {
    Supporter::name = name;
}

const std::string &Supporter::getGender() const {
    return gender;
}

void Supporter::setGender(const std::string &gender) {
    Supporter::gender = gender;
}

bool operator<(const Supporter sp1, const Supporter sp2)
{
    return sp1.getDaysUntilAvailable() > sp2.getDaysUntilAvailable();
}


bool Supporter::checkAvailability(Date date)
{
    Repair rp(this->ID, date);
    return (this->repairDates.find(rp) == this->repairDates.end());
}

set<Repair> &Supporter::getRepairDates() {
    return repairDates;
}

unsigned int Supporter::getDaysUntilAvailable() const {
    return daysUntilAvailable;
}

void Supporter::scheduleRepair(Date date, Date currentDate, unsigned courtID)
{
    Repair rp(courtID, date);
    this->repairDates.insert(rp);


    if(this->repairDates.size() != 1)
    {
        Date d = (--(--this->repairDates.end()))->getRepairDate();
        if((date - currentDate) > 1 &&  (date - d) == 1)
            this->daysUntilAvailable++;
    } else{
        if((date - currentDate) > 1)
            return;
        else
            this->daysUntilAvailable++;
    }
}

unsigned Supporter::numRepairs() const
{
    return this->repairDates.size();
}

unsigned int Supporter::getID() const {
    return ID;
}


ostream &operator<<(std::ostream &out, const Supporter & sp)
{
    out << "Name: " << sp.name << endl << "ID: " << sp.ID << endl << "Gender: " << sp.getGender() << endl
        << "Days Until Next Available: " << sp.daysUntilAvailable << endl;
    return out;
}

void Supporter::indent(std::ofstream &outfile, int indentation)
{
    for(int i = 0; i < indentation; i++)
    {
        outfile << "\t";
    }
}

void Supporter::storeInfo(std::ofstream &outfile, int indentation)
{
    indent(outfile, indentation);
    outfile << "{" << endl;
    indentation++;
    indent(outfile, indentation);
    outfile << "\"Name\": \"" << this->name << "\"," << endl;
    indent(outfile, indentation);
    outfile << "\"ID\": " << this->ID << "," << endl;
    indent(outfile, indentation);
    outfile << "\"Gender\": \"" << this->gender << "\","<< endl;
    indent(outfile, indentation);
    outfile << "\"DaysUntilAvailable\": " << this->daysUntilAvailable <<  "," << endl;
    indent(outfile, indentation);
    outfile << "\"RepairDates\": " << endl;
    indent(outfile, indentation);
    outfile << "[" << endl;
    indentation++;
    auto it = this->repairDates.begin();
    for(it; it != this->repairDates.end(); it++)
    {
        indent(outfile, indentation);
        outfile << "{" << endl;
        indentation++;
        indent(outfile, indentation);
        outfile << "\"ID:\": "<<it->getSupID() << ","<< endl;
        indent(outfile, indentation);
        outfile << "\"repairDate\":" << endl;
        it->getRepairDate().storeInfo(outfile, indentation);
        indentation--;
        outfile << endl;
        indent(outfile, indentation);
        outfile<< "}";
        if((++it) == this->repairDates.end())
            break;
        outfile << "," << endl;
        it--;
    }
    outfile << endl;
    indentation--;
    indentation--;
    indent(outfile, indentation);
    outfile << "]" << endl;
    outfile << "}" << endl;
}

void Supporter::readInfo(std::ifstream &infile)
{
    string savingString;
    while (getline(infile, savingString))
    {
        if(savingString.find("Name") != string::npos)
        {
            savingString = savingString.substr(savingString.find(" "));
            savingString = savingString.substr(2, savingString.size() - 4);
            this->name = savingString;
        }
        else if(savingString.find("ID") != string::npos)
        {
            savingString = savingString.substr(savingString.find(" ") + 1);
            savingString = savingString.substr(0, savingString.size()-1);
            this->ID = (unsigned)stoul(savingString);
            if(this->ID > this->currentID)
                this->currentID = this->ID + 1;
        }
        else if(savingString.find("Gender") != string::npos)
        {
            savingString = savingString.substr(savingString.find(" ") + 2);
            savingString = savingString.substr(0, savingString.size() - 2);
            this->gender = savingString;
        }
        else if(savingString.find("DaysUntilAvailable") != string::npos)
        {
            savingString = savingString.substr(savingString.find(" ") + 1);
            savingString = savingString.substr(0, savingString.size() - 1);
            this->daysUntilAvailable = (unsigned) stoul(savingString);
        }
        else if(savingString.find("RepairDates") != string::npos)
        {
            while (getline(infile, savingString))
            {
                Repair rp;
                Date d;
                if(savingString.find("ID") != string::npos)
                {
                    savingString = savingString.substr(savingString.find(" ") + 1);
                    savingString = savingString.substr(0, savingString.size() - 1);
                    rp.setSupID((unsigned) stoul(savingString));
                }
                else if(savingString.find("repairDate") != string::npos)
                {
                    d.readInfo(infile);
                    rp.setRepairDate(d);
                    this->repairDates.insert(rp);
                    getline(infile, savingString);
                }
                if(savingString.find("]") != string::npos) {
                    break;
                }
            }
        }
    }
}

Supporter Supporter::operator--()
{
    if(this->daysUntilAvailable != 0)
    {
        this->daysUntilAvailable--;
    }
    return *this;
}