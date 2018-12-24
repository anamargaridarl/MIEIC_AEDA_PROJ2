//
// Created by andrefmrocha on 12/24/18.
//

#ifndef AEDA_PROJECT_SUPPORTERS_H
#define AEDA_PROJECT_SUPPORTERS_H

#include <string>
#include <set>
#include "Date.h"

class Supporter {
private:
    std::string name;
    std::string gender;
    std::set<Date> repairDates;
    unsigned daysUntilAvailable;

public:

    Supporter(const std::string &name, const std::string &gender);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getGender() const;

    void setGender(const std::string &gender);

    unsigned int getDaysUntilAvailable() const;

    std::set<Date> &getRepairDates() ;

    bool checkAvailability(Date date);

    void scheduleRepair(Date date, Date currentDate);

    bool operator<(Supporter sp);

};


#endif //AEDA_PROJECT_SUPPORTERS_H
