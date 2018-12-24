//
// Created by andrefmrocha on 12/24/18.
//

#include "Supporter.h"
using namespace std;

Supporter::Supporter(const std::string &name, const std::string &gender) : name(name), gender(gender) {}

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

bool Supporter::operator<(Supporter sp)
{
    return this->getDaysUntilAvailable() > sp.getDaysUntilAvailable();
}

bool Supporter::checkAvailability(Date date)
{
    return (this->repairDates.find(date) != this->repairDates.end());
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
    this->daysUntilAvailable = (unsigned)(currentDate - date);
}

unsigned Supporter::numRepairs() const
{
    return this->repairDates.size();
}