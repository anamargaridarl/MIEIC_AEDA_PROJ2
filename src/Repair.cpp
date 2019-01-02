//
// Created by andrefmrocha on 12/29/18.
//

#include "Repair.h"

Repair::Repair(unsigned int supID, const Date &repairDate) : supID(supID), repairDate(repairDate) {}

bool operator<(Repair r1, Repair r2)
{
    return r1.getRepairDate() < r2.getRepairDate();
}

Date Repair::getRepairDate() const {
    return repairDate;
}

void Repair::setSupID(unsigned int supID) {
    Repair::supID = supID;
}

unsigned int Repair::getSupID() const {
    return supID;
}

void Repair::setRepairDate(const Date &repairDate) {
    Repair::repairDate = repairDate;
}

