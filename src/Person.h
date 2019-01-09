/*
 * Person.h
 *
 *  Created on: 21/10/2018
 *      Author: anamargaridarl
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include "Report.h"
#include "Reservation.h"
#include "Invoice.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "stdlib.h"

/**
 * The class that stores the information of the people in the company
 */

class Person
{
public:

	/**
	 * @brief Constructor of the class
	 */
	Person();
	/**
	 * @brief Constructor of the class
	 * @param name - name of the person
	 * @param age - age of the person
	 * @param gender - gender of the person
	 */
	Person(std::string name,int age, std::string gender);

	/**
	 * @brief Getter of the name of the person
	 * @return name of the person
	 */
	std::string getName() const;

	/**
	 *
	 * @brief Store in the information of the Person to a file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	virtual void storeInfo(std::ofstream &outfile, int &indentation);

	/**
	 *
	 * @brief Reading the information of a User from a file
	 * @param infile - file to read the information from
	 */
	virtual void loadClass(std::ifstream &inpfile);

	/**
	 * @brief Showing the information of the person on the screen
	 */
	virtual void show() const;

	/**
	 * @brief cleaning all vectors inside the person
	 */
	virtual void cleanVectors(){};

	/**
	 * @brief Comparing two People
	 * @param p1 - the other person
	 * @return
	 */
	bool operator == (const Person &p1);
//	~Person();

	/**
	 * @brief Changing the gender of said person
	 * @param gender - the new Gender
	 */
	void editGender(std::string gender);

	/**
	 * @brief Changing the age of said person
	 * @param age - the new age
	 */
	void editAge(int age);

	/**
	 * @brief Changing the name of said person
	 * @param name - the new name
	 */
	void editName(std::string name);
private:
	std::string name; /**< name of the person */
	int age;	/**< age of the person */
	std::string gender; 	/**< gender of the person */
};
//////////////////////////////////////////////////
//////////////////////////////////////////////////

/**
 * The users of the court
 */
class User :public Person {
public:

	/**
	 * @brief Constructor of the class
	 */
	User();

	/**
	 * @brief Constructor of the class
	 * @param name - name of the person
	 * @param age - age of the person
	 * @param gender - gender of the person
	 * @param isGold - does the person have the Gold Card
	 * @param assignedTeacher - the teacher assigned to the person
	 * @param address - address of the user
	 * @param nif - nif of the user
	 * @param active - if the user is active or not
	 */
	User(std::string name,int age, std::string gender, bool isGold, std::string assignedTeacher, std::string address, int nif, bool active);

	/**
	 * @brief Getting the size of Reservations vector
	 * @return the number of reservations
	 */
	unsigned int getReservationSize() const;

	/**
	 * Does this User have a Gold Card
	 * @return if the user is gold
	 */
	bool getisGold() const;

	/**
	 * @brief Getting the NIF of said user
	 * @return the current NIF
	 */
	int getNIF() const;

	/**
	 * Getter of the Report of a Specific Month
	 * @param month - month wanted
	 * @return the report of said month
	 */
	Report getReport(int month) const;

	/**
	 * Getter of the Invoice of a Specific Month
	 * @param month - month wanted
	 * @return the Invoice of said month
	 */
	Invoice getInvoice(int month) const;

	/**
	 * @brief Getter of all the Reservation
	 * @return vector of Reservations
	 */
	std::vector<Reservation*> getReservations() const;

	/**
	 * @brief Getter of the assigned teacher
	 * @return the name of the teacher
	 */
	std::string getTeacher() const;

	/**
	 * Setter of the Invoice
	 * @param invoice - invoice to save
	 * @param month - the month of the invoice
	 */
	void setInvoice(Invoice* invoice, int month);


	/**
	 * Setter of the report
	 * @param report - report to save
	 * @param month - the month of the report
	 */
	void setReport(Report* report, int month);

	/**
	 * @brief Setter of the reservation
	 * @param reservation - the reservation to save
	 */
	void setReservation(Reservation* reservation);

	/**
	 *
	 * @brief Store in the information of the User to a file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	void storeInfo(std::ofstream &outfile, int &indentation);

	/**
	 *
	 * @brief Reading the information of a User from a file
	 * @param infile - file to read the information from
	 */
	void loadClass(std::ifstream &inpfile);

	/**
	 * @brief Showing the information of the user on the screen
	 */
	void show();


	/**
	 * @brief cleaning all vectors inside the User
	 */
	void cleanVectors();

	/**
	 * @brief cleaning the Reservations
	 */
	void cleanReservations(int month);
	/**
	 * @param Setter of the reservationf of the user
	 * @param reservs - the reservation themselves
	 */
	void setReservations(std::vector<Reservation*> reservs);
	//~User();
	/**
	 * @brief Editing if a User is Gold
	 * @param isGold - new Gold Status
	 */
	void editIsGold(bool isGold);

	/**
	 * @brief Changing the Address of a user
	 * @param adress - the new Address
	 */
  	void editAdress(std::string address);

  	/**
  	 * @brief Changing the NIF of a user
  	 * @param NIF - the new NIF
  	 */
 	void editNIF(int NIF);

 	/**
 	 * @brief Deleting a User info
 	 */
	void deleteUser();


	/**
	 * @brief Editing the name of a Teacher assigned
	 * @param newTeacher - the new name of the teacher assigned
	 */
	void editTeacher(std::string newTeacher);

	/**
	 * @brief CHanging the reservations of a user
	 * @param r
	 */
	void editReservations(std:: vector<Reservation*>r);

	/**
	 * @brief Comparing two users, a comparison done firstly by number of reservations
	 * and then by size
	 * @param r1 the first user
	 * @param r2 the second user
	 * @return if the first is smaller than the second
	 */
  	friend bool operator<(User r1, User r2);

  	/**
  	 * @brief Getter if he a user is active or not
  	 * @return if he is active
  	 */
    bool isActive() const;

    /**
     * @param Setter for the active data member of the User
     * @param active - the new state of activity
     */
    void changeActive(bool active);



private:
	bool isGold; /**< does the user have a Gold Card? */
	int NIF; /**< The NIF of a user*/
	std::string address; /**< The address of said user*/
	bool active;
	std::string assignedTeacher; /**< name of the assigned teacher*/
	std::vector<Report*> reports; /**< vector of the reports */
	std::vector<Reservation*> reservations; /**< vector of the reservations */
	std::vector<Invoice*> invoices; /**< vector of the invoices */
};

//////////////////////////////////////////////////
//////////////////////////////////////////////////

/**
 * The Teachers that give classes
 */
class Teacher: public Person {
public:

	/**
	 * @brief Constructor of the Class
	 */
	Teacher();

	/**
	 *
	 * @brief Constructor of the Class
	 * @param name - name of teacher
	 * @param age - age of the teacher
	 * @param gender - gender of the teacher
	 */
	Teacher(std::string name, int age, std::string gender);

	/**
	 * @brief Setter of a lesson
	 * @param lesson - lesson to save
	 */
	void setLesson(Lesson* lesson);

	/**
	 * @brief Getter of the lessons
	 * @return vector of lessons
	 */
	std::vector<Lesson*> getLessons() const;

	/**
	 *
	 * @brief Store in the information of the User to a file
	 * @param outfile - the file to write information
	 * @param indent - current indentation
	 */
	void storeInfo(std::ofstream &outfile, int &indentation);

	/**
	 * @brief Adding Students to the teacher
	 */
	void addStudent();

	/**
	 * @brief Getter of the number of students
	 * @return numeber of students
	 */
	int getnStudents() const ;

	//getter of the teacher working status
	bool getStatus() const;

	/**
	 *
	 * @brief Reading the information of a User from a file
	 * @param infile - file to read the information from
	 */
	void loadClass(std::ifstream &inpfile);

	/**
	 * @brief Showing the information of the user on the screen
	 */
	void show() const;

	/**
	 * @brief Cleaning all the vectors of the Teacher
	 */
	void cleanVectors();


	/**
	 * @brief Sets the new status of the teacher
	 * @param newstat - the new status
	 */
	void setStatus(bool newstat);

	/**
	 * @brief Clears the Number of students the teacher has
	 */
	void cleanNStudents();

	/**
	 * @brief Remove a single student from the Teacher's counter of students
	 */
	void removeStudent();

	/**
	 * @brief Setter of the lessons of the Teacher
	 * @param les
	 */
	void setLessons(std::vector<Lesson*> les);
	void cleanReservation(int month);


private:
	std::vector<Lesson*> lessons; /**< vector of the lessons */
	int nStudents;	/**< number of students */
	bool active; /**< true if is a current employee of the company */
};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * When a Report already exists on that month
 */
class ReportAlreadyExists
{
private:
	int month;
public:
	ReportAlreadyExists(int month){ this->month =month;}
	int getMonth(){return month;}
	std::string what() const;
};


/*
 * When an Invoice already exists on that month
 */
class InvoiceAlreadyExists
{
private:
	int month;
public:
	InvoiceAlreadyExists(int month){ this->month =month;}
	int getMonth(){return month;}
	std::string what() const;
};

/*
 * When a Report does not exist for that month
 */

class ReportNotAvailable
{
public:
	ReportNotAvailable(int month){ this->month =month;}
	int month;
	int getMonth(){return month;}
	std::string what() const;
};

/*
 * When an Invoice does not exist for that month
 */

class InvoiceNotAvailable
{
public:
	InvoiceNotAvailable(int month){ this->month =month;}
	int month;
	int getMonth(){return month;}
	std::string what() const;
};


/**
 * When the month does not exist
 */
class IncorrectMonth
{
public:
	IncorrectMonth(){};
	std::string what() const;
};

/**
 * When there is already a reservation at that time
 */
class AlreadyReservedHours
{
public:
	AlreadyReservedHours(){};
	virtual std::string what() const{}

};


/////
class InsideRes: public AlreadyReservedHours
{
private:
	double resStart,endHour;
public:
	InsideRes(double resStart, double endHour){
		this->resStart = resStart;
		this->endHour=endHour;
	}
	std::string what() const;
};

class EndHourInsideRes : public AlreadyReservedHours
{
private:
	double resStart,resEnd;
public:
	EndHourInsideRes(double resStart, double resEnd){
		this->resStart = resStart;
		this->resEnd=resEnd;
	}
	std::string what() const;
};

class StartHourInsideRes : public AlreadyReservedHours
{
private:
	double StartingHour, endHour;
public:
	StartHourInsideRes(double StartingHour, double endHour){
		this->StartingHour = StartingHour;
		this->endHour=endHour;
	}
	std::string what() const;
};

double calculateEndHour(double startinghour, int duration);


/**
 * @brief Function to find out if a certain person is available at this time
 * @tparam t - type of reservation
 * @param res - the reservation of the person
 * @param startingHour - the hour the new reservation starts
 * @param endHour - the hour the new reservation ends
 * @param day - the day of the reservation
 * @param month - the month of the reservation
 * @return 0 if all went as expected
 */
template< class t>
int CheckAvailable(std::vector<t *> res,double startingHour, double endHour,int day, int month)
{
	for(size_t i =0; i < res.size(); i++)
	{
		if(res.at(i)->getDay() == day && res.at(i)->getMonth() == month)
		{
			//res- values from reservation already made
		double resStart = res.at(i)->getStartingHour();
		double resEnd = calculateEndHour(resStart,res.at(i)->getDuration());

		if(startingHour >= resStart && endHour <= resEnd)
			// tempo da reserva esta em espaço ocupado
			throw(InsideRes(resStart,endHour));
		else if(startingHour <= resStart && endHour >= resStart)
			//tempo da reserva entra em espaço ocupado
			throw(EndHourInsideRes(resStart,resEnd));
		else if(startingHour >= resStart && endHour >= resEnd && startingHour <= resEnd)
			//tempo da reserva esta a meio
			throw(StartHourInsideRes(startingHour, endHour));
		}
	}
	return 0;
}


#endif /* SRC_PERSON_H_ */
