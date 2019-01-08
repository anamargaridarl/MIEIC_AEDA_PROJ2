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
	tabTeach teachers;
	std::set<User> users; /**< vector with all the Users */
	std::priority_queue<Supporter> techSupport;
	double cardValue;
	Date date; /**< Current date*/

	void updateAvailableDays();

	//get the scheduled reservation of a given user, if possible
	std::vector<Reservation*>::iterator getScheduledReservation( std::vector <Reservation*> &reservs,const int &month, const int &day, const double &startingHour,
																 const unsigned int &duration);
	//get the scheduled lesson of a given teacher, if possible
	std::vector<Lesson*>::iterator getScheduledLesson(std::string teacherName, std::vector<Lesson*> &lessons, const int &month, const int &day, const double &startingHour,
													  const unsigned int &durationn);

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
	bool registerUser(std::string name, int age,bool isGold,std::string gender,std::string adress, int nif, bool active);
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

    void showDate();


    bool removeActiveTeacher(std::string teacher);
    bool rescheduleLessons(std::vector<Reservation *> &reservs, Teacher &subst, std::string username);
    void changeName(std::string name, std::string newName, int flag);
    void changeAge(std::string name, int newAge, int flag);
	void changeGender(std::string name, std::string newgender, int flag);
    void changeisGold(std::string name, bool isGold);
    bool checkNIF(int nif);
    void changeNIF(std::string name, int newNIF);
    void changeAddress(std::string name, std::string newAdress);
	void deleteUser(std::string name);


    void scheduleRepair(int day, int month, unsigned ID);
    void addRepairer(std::string name, std::string gender);
    void removeRepairer(unsigned id);
    void listAllRepairers() const;

    bool modifyReservation(std::string username, int month, int day, double startingHour, unsigned int duration, int newMonth, int newDay, double newStartHour,
						   unsigned int newDuration);

    bool deleteReservation(std::string username, int month, int day, double startingHour, unsigned int duration);
    void listAvailableRepairers(unsigned daysUntilAvailable) const;
    void unscheduleRepair(unsigned id, unsigned day, unsigned month);
    void rescheduleRepair(unsigned id, unsigned day, unsigned month, unsigned newDay, unsigned newMonth);

    void changeRepairerName(unsigned id, std::string newName);
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
