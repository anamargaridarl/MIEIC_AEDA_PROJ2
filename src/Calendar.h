/*
 * Year.h
 *
 *  Created on: Oct 20, 2018
 *      Author: andrefmrocha
 */

#ifndef SRC_YEAR_H_
#define SRC_YEAR_H_
#include <utility>
#include<vector>
#include<iostream>
#include <algorithm>

/**
 * Each day of reservations
 */

class Day{
public:

	/**
	 * @brief Class Constructor
	 */
    Day(){};

    /**
     * @brief Class Constructor
     * @param workHours - when does the court work
     */
	Day(std::pair<int, int> workHours);

	/**
	 * @brief Check if there's reservation at a given time
	 * @param startingHours - starting hours of the reservation
	 * @param duration - duration of the reservation
	 * @return if it free
	 */
	bool checkSchedule(double startingHours, int duration) const;

	/**
	 * @brief Set a reservation
	 * @param startingHours - starting hours of the reservation
	 * @param duration - duration of the reservation
	 */
	void setSchedule(double startingHours, int duration);

	/**
	 * @brief Set the schedule
	 * @param schedule - vector of the schedule
	 */
	void setSchedule(std::vector<bool> schedule);

	/**
	 * @brief Set the Starting Hour
	 * @param sH - starting Hour
	 */
	void setSH(int sH);

	/**
	 * @brief Getter of the schedule
	 * @return vector of the schedule
	 */
	std::vector<bool> getSchedule();

	/**
	 * @brief Getter of the Starting Hour
	 * @return vector of the Starting Hour
	 */
	int getSH() const;
private:
	int startingHour; /**< Starting hour of the day */
	std::vector<bool> schedule; /**< Schedule for the day */
};


/**
 * The whole month of reservations
 */
class Month {
public:
	/**
	 * @brief Class Constructor
	 */
    Month(){};

    /**
     * @brief Class constructor
     * @param month - the current month
     * @param days - number of days
     */
	Month(int month, int days);

	/**
	 * Getter of the day
	 * @param day - the day wanted
	 * @return the day
	 */
	Day& getDay(int day);

	/**
	 * Getter of the month
	 * @return the month
	 */
	int getMonth();

	/**
	 * @brief Getter of the Number of days
	 * @return number of days
	 */
	int getNoDays();

	/**
	 * @brief Setter of the days
	 * @param days - vector of days
	 */
	void setDays(std::vector<Day> days);

	/**
	 * @brief Setter of the month
	 * @param month - the month
	 */
	void setMonth(int month);
private:
	int month; /**< Current month */
	std::vector<Day> days; /**< Vector of each day */
};

/**
 * The year with all of its months
 */

class Year {
public:
	/**
	 * @brief Class Constructor
	 */
    Year(){};

    /**
     * @brief Class Constructor
     * @param year - current year
     */
	Year(int year);

	/**
	 * @brief Getter of the month
	 * @param month - the month wanted
	 * @return the month
	 */
	Month& getMonth(int month);

	/**
	 * @brief Setter of the months
	 * @param months - vector of months
	 */
	void setMonths(std::vector<Month> months);
private:
	std::vector<Month> months; /**< vector of all months **/
};

#endif /* SRC_YEAR_H_ */





