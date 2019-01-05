/*
 * Company.h
 *
 *  Created on: 30/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_COMPANY_H_
#define SRC_COMPANY_H_

#include <queue>
#include "Calendar.h"
#include "Court.h"
#include "Date.h"
#include <unordered_set>
#include "picosha2.h"
#include <set>
#include "Supporter.h"

struct teacherHash
{
	size_t operator() (const Teacher & t1) const
	{
		size_t result =0;
		std::string hash = picosha2::hash256_hex_string(t1.getName());
		for(auto i: hash)
			result += i*10;
		return result;
	}

	bool operator() (const Teacher & t1, const Teacher & t2) const
	{
		return t1.getName() == t2.getName();
	}
};



/**
 * The company itself, operation all of the rest
 */

typedef std::unordered_set<Teacher,teacherHash,teacherHash> tabTeach;


class Company
{
private:
	std::vector<Court> tennisCourts; /**< vector with all the Courts */
	tabTeach teachers; /**< Hashtable with all the teachers*/
	std::set<User> users; /**< BST with all the Users */
	std::priority_queue<Supporter> techSupport; /**< Heap with all the Repairer*/
	double cardValue;
	Date date; /**< Current date*/

	void updateAvailableDays();
public:
	/**
	 *
	 * @brief Class Constructor
	 */
    Company() {};

    /**
     * @brief Class constructor
     * @param d - current date
     */
	Company(double cardValue, Date d);

	/**
	 * @brief getter of Maximum of users in all courts
	 * @return maximum of users in all courts
	 */
	int getMaxUser()const;

	/**
	 * @brief Creating a new Court
	 */
	void createCourt();
	//tested

	/**
	 * @brief Getter of the current Courts.
	 * @return vector of Courts
	 */
	std::vector<Court> getCourts();
	//tested

	/**
	 * @brief Getter of the current Users.
	 * @return vector of Users
	 */
	std::set <User> getUsers();
	//tested

	/**
	 * @brief Getter of the current Teachers.
	 * @return vector of Teachers
	 */
	std::vector<Teacher> getTeachers(); //returns the teachers working for the company, currently

	/**
	 * @brief Getter of a specific User
	 * @param userName - name of the User
	 * @return a reference to the user
	 */

	void reAddUser(User u);
	User getUser(std::string userName);

	Teacher getTeacher(std::string teacherName);



	/**
	 * Reserving the Court, User and Teacher for a new Lesson.
	 * @param month - the month of the lesson
	 * @param day - the day of the lesson
	 * @param startingHour - the starting Hour for it
	 * @param userName - the name of the User
	 * @param teacherName - the name of the Teacher
	 * @return if it was successful created
	 */
	bool makeLesson(int month,int day,double startingHour,std::string userName);
	//tested

	/**
	 * @brief Reserving the Court, User and Teacher for a new Reservation.
	 * @param month - the month of the lesson
	 * @param day - the day of the lesson
	 * @param startingHour - the starting Hour for it
	 * @param duration - the duration it
	 * @param username - the name of the User
	 * @return if it was successful created
	 */
	bool makeFree(int month,int day, double startingHour,int duration, std::string username);
	//tested

	/**
	 * @brief Register a new User to the system.
	 * @param name - the name of the user
	 * @param age - the age of the user
	 * @param isGold - if he wants to have the Gold card or not
	 * @param gender - the gender of the User
	 * @return if the user was succesfully created
	 */
	bool registerUser(std::string name, int age,bool isGold,std::string gender,std::string adress, int nif);
	//tested

	/**
	 * @brief - Register a new Teacher to the system.
	 * @param teacherName - the name of the Teacher
	 * @param age - the age of the Teacher
	 * @param gender - the gender of the Teacher
	 * @return if the Teacher was succesfully created
	 */
	bool registerTeacher(std::string teacherName,int age,std::string gender);

	/**
	 * @brief Make a Report for a specific user.
	 * @param month - month it relates to
	 * @param userName - the name of the user
	 * @param teacherName - the name of the teacher
	 * @return if if was made sucessfuly
	 */
	bool makeUserReport(int month,std::string userName,std::string teacherName);




	/**
	 * @brief Make an Invoice for a specific user.
	 * @param userName -  month it relates to
	 * @param month - the name of the user
	 * @return if if was made sucessfuly
	 */


	bool makeUserInvoice(std::string userName, int month);

	/**
	 * @brief Method to show a specific Report.
	 * @param name - name of the User
	 * @param month - month they want
	 * @return if it was properly shown
	 */
	//needs reports to be properly saved to be tested
	bool showReport(std::string name, int month);

	/**
	 * @brief Method to show a specific Invoice.
	 * @param name - name of the User
	 * @param month - month they want
	 * @return if it was properly shown
	 */
	//needs invoices to be prpperly saved to be tested
	bool showInvoice(std::string name,int month);
	//to implement

	/**
	 * @brief Store in the information of the Company to a file.
	 * @param outfile - the file to write information
	 * @param identation - current indentation
	 */
	void storeInfo(std::ofstream &outfile,int identation);

	/**
	 * @brief To indent the file
	 * @param outfile - where to write
	 * @param indentation - current indentation
	 */
	void indentation(std::ofstream &outfile,int indentation);

	/**
	 * @brief Reads the company information of a file
	 * @param infile
	 */
	void readInfo(std::ifstream &infile);

	/**
	 * @brief The operator to go through a day and all its necessary situations
	 * @return the company itself
	 */
	Company operator++();

	/**
	 * @brief shows all Users
	 */
	void showUsers();


	/**
	 * @brief shows all Teachers
	 */
	void showTeachers();

	/**
	 * @brief shows all Courts
	 */
	void showCourts();

	/**
	 * @brief show a specific User
	 * @param name - name of the User
	 */
    void showUser(std::string name);

	/**
	 * @brief show a specific User
	 * @param name - name of the User
	 */
    void showTeacher(std::string teacher);

    /**
     * @brief Show the Reservations of a specific user
     * @param name - Name of the User
     */
    void showUserReservations (std::string name);

    /**
     * @brief Shows the lessons of the Teacher
     * @param teacher - name of the Teacher
     */
    void showTeacherLessons (std::string teacher);

    /**
     * @brief Showing the Current date
     */
    void showDate();


    /**
     * @brief Changing the status of teacher
     * @param teacher - the name of said teacher
     * @param newstat - the status wanted to maintain
     * @return if the teacher was found and changed
     */
    bool changeTeacherStatus(std::string teacher,bool newstat);

    /**
     * @brief Removal of an active Teacher
     * @param teacher - the name of said teacher
     * @return if it was successfull
     */
    bool removeActiveTeacher(std::string teacher);


    /**
     * @brief Rescheduling the Lessons of a given teacher
     * @param lessons - the lessons to be changed
     * @param reservs - the reservations to be changed in the user
     * @param subst - the teacher itself
     * @param username - the user
     * @return if it was successful
     */
     bool rescheduleLessons(std::vector<Reservation *> &reservs, Teacher &subst, std::string username);

    /**
     * @brief Changing the name of a person
     * @param name - the current name
     * @param newName - the new Name
     * @param flag if it is a teacher or a student
     */

  
    void changeName(std::string name, std::string newName, int flag);

    /**
     * @brief Changing the age of a person
     * @param name - the current name
     * @param newAge - the new age
     * @param flag - if it is a teacher or a student
     */
    void changeAge(std::string name, int newAge, int flag);
    /**
     * @brief Changing the Gender of a person
     * @param name - the current name
     * @param newgender - the new Gender
     * @param flag - if it is a teacher or a student
     */
	void changeGender(std::string name, std::string newgender, int flag);

	/**
	 * @brief Changing if a person is Gold or not
	 * @param name - the current name
	 * @param isGold - the new Gold status
	 */
    void changeisGold(std::string name, bool isGold);

    /**
     * @brief Checking if the given value is a proper NIF
     * @param nif - the actual NIF
     * @return - if it is a NIF or not
     */
    bool checkNIF(int nif);

    /**
     * @brief Changing the NIF of a user
     * @param name - the current name
     * @param newNIF - the newNIF
     */
    void changeNIF(std::string name, int newNIF);

    /**
     * @brief Changing the Address of a user
     * @param name - the current name
     * @param newAddress - the new Address
     */
    void changeAddress(std::string name, std::string newAddress);




	
	void changeReservation(std::string name, unsigned int duration, int month, int day, double startingHour);
  /**
	 * @brief Deleting a User
	 * @param name - the name of the User
	 */
	void deleteUser(std::string name);


	/**
	 * @brief Scheduling a repair for a given Court
	 * @param day - the day of the repair
	 * @param month - the month of the repair
	 * @param ID - the ID of the court
	 */
    void scheduleRepair(int day, int month, unsigned ID);

    /**
     * @brief Add a new Repairer to the company
     * @param name - the name of said Repairer
     * @param gender - the gender of said Repairer
     */
    void addRepairer(std::string name, std::string gender);

    /**
     * @brief Removal of a Repairer from the company
     * @param id - The Repairer ID
     */
    void removeRepairer(unsigned id);

    /**
     * @brief Listing all Repairers
     */
    void listAllRepairers() const;


    //get the scheduled reservation of a given user, if possible
    /**
     * @brief Get a scheduled Reservation of a given user
     * @param userName - the name of the User
     * @param reservs - the reservations of a given user
     * @param month - the month of the reservation
     * @param day - the day of the reservation
     * @param startingHour - the starting hour of the reservation
     * @param duration - the duration of the reservation
     * @return - an iterator pointing to the reservation
     */
    //get the scheduled lesson of a given teacher, if possible
	std::vector<Lesson*>::iterator getScheduledLesson(std::string teacherName, std::vector<Lesson*> lessons, int month,int day,double startingHour, unsigned int duration);

	/**
    * @brief Get a scheduled Reservation of a given teacher
    * @param userName - the name of the Teacher
    * @param reservs - the reservations of a given Teacher
    * @param month - the month of the lesson
    * @param day - the day of the lesson
    * @param startingHour - the starting hour of the lesson
    * @param duration - the duration of the lesson
    * @return - an iterator pointing to the lesson
    */
	std::vector<Reservation*>::iterator getScheduledReservation(std::string userName, std::vector <Reservation*> reservs, int month,int day, double startingHour, unsigned int duration);

	/**
	 * @brief modifying the time of a given Reservation
	 * @param username - the name of the user
	 * @param month - the month of the reservation
	 * @param day - the day of the reservation
	 * @param startingHour - the starting hour of the reservation
	 * @param duration - the duration of the reservation
	 * @param newMonth - the new month of the reservation
	 * @param newDay - the new day of the reservation
	 * @param newStartHour - the new starting hour of the reservation
	 * @param newDuration - the new duration of the reservation
	 * @return - if it was successful
	 */
    bool modifyReservation(std::string username, int month, int day, double startingHour, unsigned int duration, int newMonth, int newDay, double newStartHour,
						   unsigned int newDuration);

	/**
	 * @brief deleting the time of a given Reservation
	 * @param username - the name of the user
	 * @param month - the month of the reservation
	 * @param day - the day of the reservation
	 * @param startingHour - the starting hour of the reservation
	 * @param duration - the duration of the reservation
	 * @return - if it was successful
	 */
    bool deleteReservation(std::string username, int month, int day, double startingHour, unsigned int duration);
  	/**
     * @brief Listing all Repairers available to in the next days
     * @param daysUntilAvailable - the maximum number of days for the repairer to be available
     */
    void listAvailableRepairers(unsigned daysUntilAvailable) const;

    /**
     * @brief Unscheduling a given Repair to a specific Court
     * @param id - the ID of the Court
     * @param day - the day of the Repair
     * @param month - the month of the Repair
     */
    void unscheduleRepair(unsigned id, unsigned day, unsigned month);

	/**
	 * @brief Rescheduling a given Repair to a specific Court
	 * @param id - the ID of the Court
	 * @param day - the day of the Repair
	 * @param month - the month of the Repair
	 * @param newDay - the new Day of the Repair
	 * @param newMonth - the new Month of the Mont
	 */
    void rescheduleRepair(unsigned id, unsigned day, unsigned month, unsigned newDay, unsigned newMonth);
};




/**
 * When a user does not exist
 */

class NoReservation
{
private:
	std::string name;
public:
	NoReservation(std::string name) { this->name=name;}
	std::string what()const;
};


class NoUserRegistered
{
private:
	std::string name;
public:
	NoUserRegistered(std::string name) { this->name=name;}
	std::string what()const;
};

class NoSupporterAvailable
{
	unsigned day;
	unsigned month;
public:
	NoSupporterAvailable(unsigned day, unsigned month):day(day), month(month) {}
	std::string what()const;
};


/**
 * When a Teacher does not exist
 */
class NoTeacherRegistered
{
private:
	std::string name;
public:
	NoTeacherRegistered(std::string name) {this->name = name;}
	std::string what()const;
};


/**
 * When the age is not valid
 */
class InvalidAge
{
private:
	int age;
public:
	InvalidAge(int age) { this->age=age;}
	std::string what()const;
};


/**
 * When that name is already in the system
 */

class AlreadyRegisteredUser
{
private:
	std::string name;
public:
	AlreadyRegisteredUser(std::string name) { this->name=name;}
	std::string what()const;
};

/**
 * When that name is already in the system
 */
class AlreadyRegisteredTeacher
{
private:
	std::string name;
public:
	AlreadyRegisteredTeacher(std::string name) { this->name=name;}
	std::string what()const;
};

class InvalidDate
{
	int month;
	int day;
public:
	InvalidDate(int day, int month) { this->day = day, this->month = month;}
	std::string what() const;
};


class InactiveTeacher
{
private:
    std::string name;
public:
    InactiveTeacher(std::string name) {this->name = name;}
    std::string what() const;
};

class NoActiveTeachersLeft {
private:
	std::string name;
public:
	NoActiveTeachersLeft(std::string name) { this->name = name; }
	std::string what()const;
};

class InvalidNIF
{
private:
	int nif;
public:
	InvalidNIF(int nif) { this->nif=nif;}
	std::string what()const;
};


class NoSupporterID
{
private:
    unsigned ID;
public:
    NoSupporterID(unsigned ID):ID(ID){};
    std::string what() const;
};

class NoCourtID {
private:
	unsigned ID;
public:
	NoCourtID(unsigned ID) : ID(ID) {};

	std::string what() const;

};

class ReservationAlreadyExists
{
private:
	std::string name;
public:
	ReservationAlreadyExists(std::string name) {this->name = name;}
	std::string what() const;
};

class TeacherUnavailable
{
private:
	std::string name;
public:
  TeacherUnavailable(std::string name) {this->name = name;}
  std::string what() const;
};

class NoRepair{
private:
	unsigned day;
	unsigned month;
	unsigned id;
public:
	NoRepair(unsigned day, unsigned month, unsigned id): day(day), month(month), id(id){};
	std::string what() const;
};


#endif /* SRC_COMPANY_H_ */
