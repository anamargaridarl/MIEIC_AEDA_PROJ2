/*
 * Report.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_REPORT_H_
#define SRC_REPORT_H_

#include <iostream>
#include <string>
#include <vector>
#include "Reservation.h"
/**
 * Report of how the user did during this last month
 */
//#include <math.h>

class Report{
private:
	std::vector<Reservation*> reservations; /**< Reservations of this month */
	std::string name;	/**< Name of the user */
	std::string teacherName;	/**< Name of the teacher */
	int grade;	/**< Grade of the user this month */
public:

	/**
	 * @brief Class Constructor
	 */
    Report() {};


	/**
     * @brief Class Constructor
     * @param userName - name of the user
     * @param teacherName - name of the teacher
     * @param reservs - the reservations
     */
	Report(std::string userName, std::string teacherName,const std::vector<Reservation*> &reservs);

	/**
	 * @brief Writer of the information of the Report
	 * @param os - the stream
	 * @param r - the report itself
	 * @return the stream
	 */
	friend std::ostream & operator <<(std::ostream & os,Report r);

	/**
	 * @brief Getter of the name of the User
	 * @return the name of the User
	 */
	std::string getName();

	/**
	 * @brief Getter of the name of the teacher
	 * @return the name of the teacher
	 */
	std::string getTeacherName();

	/**
	 * @brief getter of the Grade
	 * @return the grade itself
	 */
	int getGrade();

	/**
	 * @brief Getter of the name of the Lessons
	 * @return the vector of reservations
	 */
	std::vector<Reservation*> getLessons();

	/**
	 * @brief Indenting the file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	void indentation(std::ofstream &outfile, int indent);

	/**
	 * @brief Store in the information of the report to a file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	void readInfo(std::ifstream &infile);

	/**
	 * @brief Reading the information of a Report from a file
	 * @param infile - file to read the information from
	 */
	void storeInfo(std::ofstream &outfile, int indent);

	/**
	 * @brief get the format of the Hour as wanted
	 * @param hour - the actual time
	 * @return the hour
	 */
	std::string getHourFormat(double hour);
};

#endif /* SRC_REPORT_H_ */
