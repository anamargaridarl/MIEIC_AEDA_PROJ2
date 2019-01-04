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
    /**
     * @brief Default constructor for repairs
     */
    Repair(){};

    /**
     * @brief Constructor for a new Repair
     * @param supID - the ID of the support
     * @param repairDate - the date of the repair
     */
    Repair(unsigned int supID, const Date &repairDate);

    /**
     * @brief Getter of the repair Date
     * @return the date itself
     */
    Date getRepairDate() const;

    /**
     * @brief Setter of the Repair Date
     * @param repairDate
     */
    void setRepairDate(const Date &repairDate);

    /**
     * @brief Setter of the Supporter ID
     * @param supID
     */
    void setSupID(unsigned int supID);

    /**
     * @brief Comparison of two repairs, they are compared by their dates
     * @param r1 - the first repair
     * @param r2 - the second repair
     * @return if the first repair is first of the second
     */
    friend bool operator<(Repair r1, Repair r2);

    /**
     * @brief Getter for the support ID associated with the Repair
     * @return the ID of the Supporter
     */
    unsigned int getSupID() const;
};


#endif //AEDA_PROJECT_REPAIR_H
