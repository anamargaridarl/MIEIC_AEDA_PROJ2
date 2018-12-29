//
// Created by andrefmrocha on 12/29/18.
//

#ifndef AEDA_PROJECT_REPAIR_H
#define AEDA_PROJECT_REPAIR_H

#include "Date.h"

class Repair {
private:
    unsigned supID;
    Date repairDate;
public:
    Repair(){};

    Repair(unsigned int supID, const Date &repairDate);

    Date getRepairDate() const;

    void setRepairDate(const Date &repairDate);

    void setSupID(unsigned int supID);

    friend bool operator<(Repair r1, Repair r2);

    unsigned int getSupID() const;
};


#endif //AEDA_PROJECT_REPAIR_H
