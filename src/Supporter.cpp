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
    return (this->repairDates.find(date) == this->repairDates.end());
}

set<Date> &Supporter::getRepairDates() {
    return repairDates;
}

unsigned int Supporter::getDaysUntilAvailable() const {
    return daysUntilAvailable;
}

void Supporter::scheduleRepair(Date date, Date currentDate)
{
    this->repairDates.insert(date);


    if(this->repairDates.size() != 1)
    {
        Date d = *(--(--this->repairDates.end()));
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
