/*
 * Date.h
 *
 *  Created on: Oct 29, 2018
 *      Author: andrefmrocha
 */

#ifndef SRC_DATE_H_
#define SRC_DATE_H_


#include <cmath>
#include <fstream>
/**
 * Class to save the current date of the company system
 */
class Date {
	unsigned int day; /**< current day */
	unsigned int month; /**< current month */
	unsigned int year; /**< current year */
public:

	/**
	 * @brief Class Constructor
	 */
	Date();

	/**
	 * @brief Class Constructor
	 * @param day - current day
	 * @param month - current month
	 * @param year - current year
	 */
	Date(unsigned int day, unsigned int month, unsigned int year);

	/**
	 * @brief incrementation of the date
	 * @return the date itself
	 */
	Date operator++();

	/**
	 *
	 * @brief Store in the information of the Date to a file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	void storeInfo(std::ofstream &outfile, int indentation);

	/**
	 * @brief Indenting the file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	void indent(std::ofstream&outfile, int identation);

	/**
	 *
	 * @brief Reading the information of a Date from a file
	 * @param infile - file to read the information from
	 */
	void readInfo(std::ifstream &infile);

	/**
	 * @brief Getter for the day
	 * @return the actual day
	 */
	unsigned int getDay();

	/**
	 * @brief Getter for the month
	 * @return the actual month
	 */
	unsigned int getMonth();

	/**
	 * @brief Getter for the year
	 * @return the actual year
	 */
	unsigned int getYear();

	bool operator==(Date d);

    int operator-(Date d);

    bool operator<(Date d);
};


/**
 * When a date is invalid
 */
class BadDate
{
public:
	std::string what();
};

#endif /* SRC_DATE_H_ */

