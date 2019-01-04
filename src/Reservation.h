/*
 * Reservation.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_RESERVATION_H_
#define SRC_RESERVATION_H_

#include <fstream>
#include <math.h>
/**
 * The reservation of a court, to be stored on the people that will be on that court
 */

class Reservation {
protected:
	double price;	/**< Price associated of the reservation */
	unsigned int duration; /**< Duration of said reservation */
private:
	int month; /**< Month of said reservation */
	int day; /**< Day of said reservation */
	double startingHour; /**< Starting Hour of said reservation */
public:
	/**
	 * @brief Constructor of Class
	 */
	Reservation(){};


	/**
	 * @brief Constructor of Class
	 * @param month - Month of the reservation
	 * @param day - Day of the reservation
	 * @param startingHour - Starting Hour of the reservation
	 * @param price - Price of the reservation
	 * @param duration - Duration of the reservation
	 */
	Reservation(int month,int day,double startingHour,double price,unsigned int duration);

	/**
	 * @brief Method to obtain the price of the reservation
	 * @return Price of the reservation
	 */

	virtual double getPrice();

	/**
	 * @brief Method to obtain the Starting Hour of the reservation
	 * @return Starting Hour of the reservation
	 */
	double getStartingHour();

	/**
	 * @brief Method to obtain the duration of the reservation
	 * @return Duration of the reservation
	 */
	int getDuration();

	/**
	 * @brief Method to obtain the month of the reservation
	 * @return Month of the reservation
	 */
	int getMonth();

	/**
	 * @brief Method to obtain the day of the reservation
	 * @return Day of the reservation
	 */
	int getDay();

	/**
	 * @brief Implementation of the equal operator
	 * @param r - the other reservation
	 * @return if - the reservation is the same
	 */
	bool operator ==(Reservation &r) const;

	/**
	 * @brief Store in the information of the reservation to a file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	virtual void storeInfo(std::ofstream &outfile, int indent);

	/**
	 * @brief Indenting the file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	void indent(std::ofstream &outfile, int indent);

	/**
	 * @brief Reading the information of a Reservation from a file
	 * @param infile - file to read the information from
	 */
	virtual void readInfo(std::ifstream &infile);


	/**
	 * @brief Showing the information of the Reservation
	 */
	virtual void show();

	/**
	 * @brief get the format of the Hour as wanted
	 * @param hour - the actual time
	 * @return the hour
	 */
	std::string getHourFormat(double hour);
	/**
	 * @brief Comparison between two dates
	 * @param r - the outside date
	 * @return if they're the same
	 */
	bool operator== ( Reservation & r);
};

/**
 * A Reservation with a Teacher
 */

class Lesson : public Reservation {
public:
	/**
	 * @brief Constructor of a lesson
	 */

	Lesson(){};
	Lesson(int m,int d,double strHr,double price,unsigned int dr);

	/**
	 * @brief Constructor of a lesson
	 * @param m - Month of the lesson
	 * @param d - Day of the lesson
	 * @param strHr - Starting Hour of the lesson
	 * @param price - Price of the lesson
	 * @param dr - Duration of the lesson
	 */
	Lesson(int m,int d,int strHr,double price,unsigned int dr);

	/**
	 * @brief Method to obtain the price of the lesson
	 * @return Price of the lesson
	 */

	double getPrice();

	/**
	 * @brief Store in the information of the lesson to a file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	void storeInfo(std::ofstream &outfile,int indent);

	/**
	 *
	 * @brief Reading the information of a lesson from a file
	 * @param infile - file to read the information from
	 */
	void readInfo(std::ifstream &infile);

	/**
	 * @brief Show the information of the Lesson
	 */
	void show();
};

class Free : public Reservation {
public:

	/**
	 * @brief Constructor of Class
	 */
	Free(){};

	/**
	 * Constructor of Class
	 * @param m - month of the reservation
	 * @param d - day of the reservation
	 * @param strHr - starting Hour of the reservation
	 * @param p - price of the reservation
	 * @param dur - duration of the reservation
	 */
	Free(int m,int d,double strHr,double p,unsigned int dur);

	/**
	 * @brief Method to obtain the price of the free
	 * @return Price of the lesson
	 */
	double getPrice();

	/**
	 *
	 * @brief Store in the information of the Free to a file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	void storeInfo(std::ofstream &outfile,int indent);

	/**
	 *
	 * @brief Reading the information of a Free from a file
	 * @param infile - file to read the information from
	 */
	void readInfo(std::ifstream &infile);

	/**
	 * @brief Show the information of the Free
	 */
	void show();
};



#endif /* SRC_RESERVATION_H_ */
