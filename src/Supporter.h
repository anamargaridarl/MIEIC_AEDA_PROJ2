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
    unsigned ID;
    static unsigned currentID;

public:

    Supporter(const std::string &name, const std::string &gender);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getGender() const;

    void setGender(const std::string &gender);

    unsigned int getDaysUntilAvailable() const;

    unsigned numRepairs()const;

    std::set<Date> &getRepairDates() ;

    bool checkAvailability(Date date);

    void scheduleRepair(Date date, Date currentDate);

    friend bool operator<(const Supporter sp1, const Supporter sp2);

    unsigned int getID() const;
};


#endif //AEDA_PROJECT_SUPPORTERS_H
