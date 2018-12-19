/*
 * Invoice.h
 *
 *  Created on: Oct 21, 2018
 *      Author: andrefmrocha
 */

#ifndef SRC_INVOICE_H_
#define SRC_INVOICE_H_
#include <vector>
#include <string>
#include <iostream>
#include "Reservation.h"


/**
 * Invoice of the month for the user
 */
class Invoice {
	std::vector<Reservation *> reservs; /**< reservations on that month */
	double totalPrice; /**< Price to pay for the month */
	std::string name; /**< Name of the user */
	std::string assignedTeacher; /**< Teacher assigned to the User */
	bool isGold; /**< Does the User own a Gold Card? */
public:

    /**
     * @brief Class Constructor
     */
	Invoice(){};

	/**
	 * @brief Class Constructor
	 * @param name - name of User
	 * @param teacherName - name of Teacher
	 * @param reservs - The reservations
	 * @param isGold - if the user has a Gold Card
	 */
	Invoice(std::string name, std::string teacherName, std::vector<Reservation *> reservs, bool isGold);

	/**
	 * @brief Getter of the price of the month
	 * @return the price to pay
	 */
	double getPrice() const;

	/**
	 * @brief Getter of the reservations
	 * @return vector of reservations
	 */
	std::vector<Reservation *> getReservs();

	/**
	 * @brief Writer of the invoice to the screen
	 * @param out - where to write it to
	 * @param inv - The actual invoice
	 * @return the stream itself
	 */
	friend std::ostream& operator<<(std::ostream &out, Invoice inv);

    /**
     *
     * @brief Store in the information of the Court to a file
     * @param outfile - the file to write information
     * @param indent - current indentation
     */
    void storeInfo(std::ofstream &outfile, int indent);

    /**
	 * @brief Indenting the file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
    void indentation(std::ofstream &outfile, int indent);

    /**
     *
     * @brief Reading the information of a Date from a file
     * @param infile - file to read the information from
     */
    void readInfo(std::ifstream &infile);
};


#endif /* SRC_INVOICE_H_ */
