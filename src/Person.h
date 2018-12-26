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
	 * @brief Getter of the age of the person
	 * @return age of the person
	 */
	int getAge();

	/**
	 * @brief Getter of the gender of the person
	 * @return gender of the person
	 */
	std::string getGender();

	/**
	 * @brief Setter of the name of the person
	 * @param name - name of the person
	 */
	void setName(std::string name);

	/**
	 * @brief Setter of the age of the person
	 * @param age - age of the person
	 */
	void setAge(int age);

	/**
	 * @brief Setter of the gender of the person
	 * @param gender - gender of the person
	 */
	void setGender(std::string gender);

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
	virtual void show();

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
	~Person();
	void editGender(std::string gender);
	void editAge(int age);
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
	 */
	User(std::string name,int age, std::string gender, bool isGold, std::string assignedTeacher, std::string adress, int nif);

	/**
	 * @brief Make a person have a Gold Card
	 */
	void makeGold();

	/**
	 * @brief Stop a person from having a Gold Card
	 *
	 */
	void stopGold();

	/**
	 * Does this User have a Gold Card
	 * @return if the user is gold
	 */

	int getNIF();
	std::string getAdress();
	unsigned int getReservationSize() const;
	bool getisGold();

	/**
	 * Getter of the Report of a Specific Month
	 * @param month - month wanted
	 * @return the report of said month
	 */
	Report getReport(int month);

	/**
	 * Getter of the Invoice of a Specific Month
	 * @param month - month wanted
	 * @return the Invoice of said month
	 */
	Invoice getInvoice(int month);

	/**
	 * @brief Getter of all the invoices
	 * @return vector of Invoices
	 */
	std::vector<Invoice*> getInvoices();

	/**
	 * @brief Getter of all the Reservation
	 * @return vector of Reservations
	 */
	std::vector<Reservation*> getReservations();

	/**
	 * @brief Getter of the assigned teacher
	 * @return the name of the teacher
	 */
	std::string getTeacher();

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
	void cleanReservations();
	~User();
	void editIsGold(bool isGold);
    void editAdress(std::string adress);
    void editNIF(int NIF);

private:
	bool isGold; /**< does the user have a Gold Card? */
	int NIF;
	std::string adress;
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
	std::vector<Lesson*> getLessons();

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
	int getnStudents();

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
	 * @brief Cleaning all the vectors of the Teacher
	 */
	void cleanVectors();
	~Teacher();
private:
	std::vector<Lesson*> lessons; /**< vector of the lessons */
	int nStudents;	/**< number of students */
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
