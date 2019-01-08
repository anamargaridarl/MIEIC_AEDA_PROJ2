//
// Created by andrefmrocha on 12/24/18.
//

#ifndef AEDA_PROJECT_SUPPORTERS_H
#define AEDA_PROJECT_SUPPORTERS_H

#include <string>
#include <set>
#include <iostream>
#include "Repair.h"

class Supporter {
private:
    std::string name;/**< The name of the Supporter */
    std::string gender;/**< The gender of the Supporter */
    std::set<Repair> repairDates;/**< The dates of already done and coming repairs*/
    unsigned daysUntilAvailable;/**< The number of days until the Supporter is once again available*/
    unsigned ID; /**< The ID of the Supporter */
    static unsigned currentID; /**< The ID of the next added Supporter */

public:

    /**
     * @brief Default constructor of the Supporter
     */
    Supporter(){};

    /**
     * @brief Constructor of the Supporter
     * @param name - the name of the Supporter
     * @param gender - the gender of the Supporter
     */
    Supporter(const std::string &name, const std::string &gender);

    /**
     * @brief Getter for the name of the Supporter
     * @return the name of the Supporter
     */
    const std::string &getName() const;

    /**
     * @brief Setter for the name of the Supporter
     * @param name - the new Name of the Supporter
     */
    void setName(const std::string &name);

    /**
     * @brief Getter for the Gender of the Supporter
     * @return the actual gender
     */
    const std::string &getGender() const;

    /**
     * @brief Setter for the gender of the Supporter
     * @param gender
     */
    void setGender(const std::string &gender);

    /**
     * @brief Getter for the Number of Days Available
     * @return the number of days until available
     */
    unsigned int getDaysUntilAvailable() const;

    /**
     * @brief The number of Repairs done and/or scheduled
     * @return the actual number of repairs
     */
    unsigned numRepairs()const;

    /**
     * @brief Getter of the repair Dates
     * @return
     */
    std::set<Repair> &getRepairDates() ;

    /**
     * @brief Check if the Supporter is available at a given date
     * @param date - the date of the repair
     * @return - if he is available
     */
    bool checkAvailability(Date date);

    /**
     * @brief Schedule a new Repair for the Supporter
     * @param date - the date of the Repair
     * @param currentDate - the current Date, for the calculation of the days until available
     * @param courtID - the ID of the Court assigned
     */
    void scheduleRepair(Date date, Date currentDate, unsigned courtID);

    /**
     * @brief The comparation between two supporters for ordering a heap by the number
     * of days until the supporter is available
     * @param sp1 - the first supporter
     * @param sp2 - the second supporter
     * @return which supporter is available first
     */
    friend bool operator<(const Supporter sp1, const Supporter sp2);

    /**
     * @brief Getter for the ID of the Supporter
     * @return the actual ID
     */
    unsigned int getID() const;

    /**
     * @brief The writing to a stream of information about a given supporter
     * @param out - the stream itself
     * @param sp - the supporter
     * @return the stream itself
     */
    friend std::ostream &operator<<(std::ostream& out, const Supporter & sp);

    /**
     * @brief The storer of the information of a given Supporter
     * @param outfile  - the file stream
     * @param indentation - the current indentation
     */
    void storeInfo(std::ofstream &outfile, int indentation);

    /**
     * @brief Indentation of the file stream
     * @param outfile - the file stream
     * @param indentation - the current indentantion
     */
    void indent(std::ofstream &outfile, int indentation);

    /**
     * @brief The parser of the information of a Supporter
     * @param infile - the file stream
     */
    void readInfo(std::ifstream &infile);

    /**
     * @brief The operation of reducing the number of days available
     * @return - the supporter himself
     */
    Supporter operator--();

};


#endif //AEDA_PROJECT_SUPPORTERS_H
