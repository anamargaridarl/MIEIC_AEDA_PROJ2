/*
*  Created on: 30/10/2018
*      Author: joaomartins
*
 * Company.cpp
 */

#include "Company.h"
#include <string>

using namespace std;
static unsigned maxRepairs = 4;

Company::Company(double cardValue, Date d)
{
	this->cardValue = cardValue;
	date=d;
}

int Company::getMaxUser() const
{
	int maxusers=0;
	// The number of max Users is calculated
	for(auto i : tennisCourts)
	{
		maxusers += i.getMaxUsers();
	}
	return maxusers;
}

void Company::createCourt()
{
	// Creates a new Court and saves it
	Court newcourt(date.getYear());
	tennisCourts.push_back(newcourt);

}

void Company::addRepairer(std::string name, std::string gender)
{
	Supporter ts(name, gender);
	this->techSupport.push(ts);
}

vector<Court> Company::getCourts()
{
	return tennisCourts;
}

set<User> Company::getUsers()
{
	return users;
}

vector<Teacher> Company::getTeachers()
{
	vector<Teacher> temp;
	for(auto i : teachers) {
		if(i.getStatus())
			temp.push_back(i);
	}
	return temp;
}

User Company::getUser(string userName) {

	set<User>::iterator it = users.begin();

		while (it != users.end()) {
			if (it->getName() == userName) {
				User a = *it;
				users.erase(it);
				return a;
			} else it++;
		}

		throw NoUserRegistered(userName);



}

vector<Reservation*>::iterator Company::getScheduledReservation(std::string username,vector<Reservation*> reservs, int month, int day, double startingHour,
                                                                unsigned int duration) {
    Reservation res(month,day,startingHour,0,duration);
    for(auto i = reservs.begin(); i != reservs.end(); i++) {
        if(**i == res) {
            return i;
        }
    }
    throw(NoReservation(username));
}

vector<Lesson*>::iterator Company::getScheduledLesson(std::string teacherName, vector<Lesson*> lessons, int month, int day, double startingHour, unsigned int duration) {
    Lesson l(month, day, startingHour, 0, duration, teacherName);
    for(auto i = lessons.begin(); i!= lessons.end(); i++) {
        if(**i == l) {
            return i;
        }
    }
    return lessons.end();
}

bool Company::makeLesson(int month,int day,double startingHour,string userName)
{
	// Checks if its a possible date
	if(month < date.getMonth() || (month == date.getMonth() && day < date.getDay())) {
		return false;
	}

	try {
		User u = getUser(userName); // Gets the user
		string teacherName = u.getTeacher();
		Teacher temp(teacherName,0,"");
		tabTeach::iterator it = teachers.find(temp); //Gets the teacher
		if(it == teachers.end()) {
			throw (NoTeacherRegistered(teacherName));
		}
		temp = *it;
		if(!temp.getStatus()) {
			throw (InactiveTeacher(teacherName));
		}
		for(auto j : tennisCourts) // Finds the first court where it can reserve the Class
		{
			if(j.reserveClass(month,day,startingHour,u,temp)) {
				teachers.erase(it);
				teachers.insert(temp);
        users.insert(u);
				return true;
			}
		}
		users.insert(u);
		return false;
	}
	catch(NoUserRegistered &u) { // If the user doesn't exist
		cout << u.what() << endl;
		return false;
	}
	catch(NoTeacherRegistered &t) // If the teacher doesn't exist
	{
		cout << t.what() << endl;
		return false;
	}
	catch(InactiveTeacher &i) //if the teacher find is inactive
	{
		cout << i.what() << endl;
		return false;
	}
}

bool Company::makeFree(int month,int day,double startingHour, int duration,string username)
{
	// Checks if its a possible date
	if(month < date.getMonth() || (month == date.getMonth() && day < date.getDay())) {
		cout << "Invalid date. " << endl;
	    return false;
	}

	if(duration > 4) {
	    cout << "Duration exceeds allowed period. " << endl;
	    return false;
	}

	try {
		User u;
		u= getUser(username); // Gets the user
		for(size_t j =0; j<tennisCourts.size();j++) //Reserves the first available court
		{
			if(tennisCourts[j].reserveFree(month,day,startingHour,duration,u)) {
				users.insert(u);
				return true;
			}

		}
		return false;
	}
	catch(NoUserRegistered &u) { //Checks if the user is registered
		cout << u.what() << endl;
		return false;
	}
}

bool Company::checkNIF(int nif) {

	set<User>::iterator it = users.begin();

	while (it != users.end()) {
		if (it->getNIF() == nif || to_string(nif).size() != 9) {
			cout << to_string(nif).size() << endl;
			return false;
		}
		else it++;
	}

	if(to_string(nif).size() != 9)
		return false;
	else
		return true;

}

bool Company::registerUser(string name, int age,bool isGold,string gender, string adress, int nif)
{
	if (age <0) //Checks if it's a possible age
		throw(InvalidAge(age));
	if(!checkNIF(nif))
		throw(InvalidNIF(nif));
	try {

		User u;
		u= getUser(name);
		users.insert(u);//Checks if there's a user already registered
		throw(AlreadyRegisteredUser(name));
	}
	catch(NoUserRegistered &u) {
		Teacher t2("",0,"");
		for(auto i: teachers)
		{ //Adds a teacher to the student
			if (t2.getnStudents() >= i.getnStudents() && i.getStatus())
				t2 = i;
		}
		teachers.erase(t2);
		t2.addStudent();
		teachers.insert(t2);
		User newUser(name,age,gender,isGold,t2.getName(), adress, nif);
		users.insert(newUser);
		return true;
	}
	catch(AlreadyRegisteredUser &u) {
		cout << u.what() << endl;
		return false;
	}
}


bool Company::registerTeacher(string teacherName, int age,string gender)
{
	if (age <0) //Checks if it's a possible age
		throw(InvalidAge(age));
	Teacher temp(teacherName,age,gender);
	try {
		tabTeach::iterator it = teachers.find(temp); //try to find if the wanted teacher is already registered
		if(it == teachers.end()) {  //if not, proceeds to check for other available teacher to substitute
            bool subst = false;
		    for(auto i: teachers) {
                if(i.getName() != "" && !i.getStatus())    //search the teachers table to find a available one
                {
                    temp = i;
                    subst = true;
                    break;
                }
            }
		    if(!subst)                                     //if there is none, create a teacher with the wanted parameter
		        throw (NoTeacherRegistered(teacherName));
        }
		if(it->getStatus())                                //if the teacher is found and already in service, an exception is thrown
			throw(AlreadyRegisteredTeacher(teacherName));
		else{                                           //if the teacher is found and is inactive
			temp = *it;
		}
        teachers.erase(temp);                           //alter the information and set the teacher back to activity
        temp.setStatus(true);
        teachers.insert(temp);
        return true;
    }
	catch(NoTeacherRegistered &t) {
		teachers.insert(temp);
		return true;
	}
	catch(AlreadyRegisteredTeacher &u) {
		cout << u.what() << endl;
		return false;
	}
}

bool Company::makeUserReport(int month,string userName,string teacherName)
{
	try
	{
	 	User u = getUser(userName); //Gets the User
		Teacher temp(teacherName,0,"");
		tabTeach::iterator it = teachers.find(temp);
		if(it == teachers.end())
			throw (NoTeacherRegistered(teacherName));
	 	Report* newr = new Report(userName,teacherName,u.getReservations());
		u.setReport(newr,month);
		users.insert(u);
	}
	catch(NoUserRegistered &u) //Checks if the user doesn't exist
	{
		cout << u.what() << endl;
		return false;
	}
	catch(NoTeacherRegistered &t) //Checks if the teacher doesn't exist
	{
		cout << t.what() << endl;
		return false;
	}
	catch(IncorrectMonth &e) //Checks if the month exists
	{
		cout << e.what() << endl;
		return false;
	}
	catch (ReportAlreadyExists &r) //Checks if there's already report for that day
	{
		cout << r.what() << endl;
		return false;
	}
	return true;
}

bool Company::makeUserInvoice(string userName,int month)
{
	try
	{
		User u = getUser(userName); // Gets the user
		// Makes the invoice and saves it
		Invoice* newinvoice = new Invoice(u.getName(),u.getTeacher(),u.getReservations(), u.getisGold());
		u.setInvoice(newinvoice,month);
		users.insert(u);
	}
	catch(NoUserRegistered &u) //Checks if the user exists
	{
		cout << u.what() << endl;
		return false;
	}
	catch(IncorrectMonth &e) //Checks if the month doesn't exist
	{
		cout << e.what() << endl;
		return false;
	}
	catch (InvoiceAlreadyExists &i) //Checks if the invoice exists
	{
		cout << i.what() << endl;
		return false;
	}
	return true;
}

void Company::scheduleRepair(int day, int month, unsigned ID)
{
	if(this->tennisCourts.size() > ID)
		throw NoCourtID(ID);
	Date d(day, month, this->date.getYear());
	vector<Supporter> aux;
	while(!this->techSupport.empty())
	{
		Supporter sup = this->techSupport.top();
		this->techSupport.pop();
		if(sup.checkAvailability(d) && sup.numRepairs() < maxRepairs)
		{
			sup.scheduleRepair(d, this->date, ID);
			this->techSupport.push(sup);
			for(auto &i: aux)
			{
				this->techSupport.push(i);
			}
			return;
		} else
		{
			aux.push_back(sup);
		}
	}
	for(const auto &i: aux)
	{
		this->techSupport.push(i);
	}
	throw NoSupporterAvailable(day, month);

}


void Company::updateAvailableDays()
{
	vector<Supporter> aux;
	while(!this->techSupport.empty())
	{
		Supporter sup = this->techSupport.top();
		--sup;
		aux.push_back(sup);
		this->techSupport.pop();
	}
	for(const auto &i: aux)
	{
		this->techSupport.push(i);
	}
}

Company Company::operator++() {
	++this->date; //Increments the date
	if(date.getDay() == 1) { //Checks if the date changes month and year in order to do Invoices and Reports
		set<User>::iterator it;
		for(it = users.begin(); it !=users.end(); it++)
		{
			User a = *it;
			users.erase(it);
			if(date.getMonth() == 1) {
				a.cleanVectors();
			}
			if(date.getMonth() != 1)
			{
				makeUserReport(date.getMonth()-1,a.getName(),a.getTeacher());
				makeUserInvoice(a.getName(),date.getMonth()-1);
			} else{
				ofstream outfile(to_string((int)this->cardValue - 1) + "-" + to_string(this->date.getYear()-1) + ".json");
			}

			a.cleanReservations();
			users.insert(a);
		}
		for(auto i:teachers) {
			Teacher temp = i;
			temp.cleanVectors();
			teachers.erase(i);
			teachers.insert(temp);
		}
	}
	this->updateAvailableDays();
	return *this;
}

//----------------------------------------------------------------------------------------------------------------

/*void Company::changeReservation(string name, unsigned int duration, int month, int day, double startingHour)
{
	//need testing after function changeReservation

	Reservation a(month,day,startingHour,0,duration);
	User b = getUser(name);

	vector<Reservation *> res= b.getReservations();
	vector<Reservation *>::iterator it;
	it = find(res.begin(), res.end(), &a);

	if(it != res.end())
	{
		//it->changereservation
		users.insert(b);
	} else
		throw(NoReservation(name));
}*/


void Company::changeName(string name, string newName, int flag)
{
	if (flag == 0)
	{
		//needs new implementation
//		getTeacher(name).editName(newName);
	}
	else
	{
		User a = getUser(name);
		a.editName(newName);
		users.insert(a);
	}

}

void Company::changeAge(string name, int newAge, int flag)
{
	if (flag == 0)
	{
		//needs new implementation
//		getTeacher(name).editAge(newAge);
	}
	else
	{
		User a = getUser(name);
		a.editAge(newAge);
		users.insert(a);
	}

}

void Company::changeGender(string name, string newgender, int flag)
{
	if (flag == 0)
	{
		//needs new implementation
//		getTeacher(name).editGender(newgender);
	}
	else
	{
		User a = getUser(name);
		a.editGender(newgender);
		users.insert(a);
	}
}

void Company::changeisGold(string name, bool isGold)
{
	User a = getUser(name);
	a.editIsGold(isGold);
	users.insert(a);
}

//need to implement in main
void Company::changeNIF(std::string name, int newNIF)
{
	if(!checkNIF(newNIF))
		throw(InvalidNIF(newNIF));

	User a = getUser(name);
	a.editNIF(newNIF);
	users.insert(a);
}
void Company::changeAddress(std::string name, std::string newAdress)
{
	User a = getUser(name);
	a.editAdress(newAdress);
	users.insert(a);
}


bool Company::changeTeacherStatus(std::string teacher, bool newstat) {
	try {
		Teacher temp(teacher,0,"");
		tabTeach::iterator it = teachers.find(temp);
		if(it == teachers.end())
			throw (NoTeacherRegistered(teacher));
		temp = *it;
		teachers.erase(it);
		temp.setStatus(newstat);
		teachers.insert(temp);
		return true;
	}
	catch(NoTeacherRegistered &t) {
		cout << t.what() << endl;
		return false;
	}
}

bool Company::modifyReservation(std::string username, int month, int day, double startingHour, unsigned int duration, int newMonth, int newDay, double newStartHour,
                                unsigned int newDuration) {
    User u;
    Teacher temp;
    Reservation* res = NULL;
    try {
        u = getUser(username); //try and get the user
        vector<Reservation*> reservs = u.getReservations(); // retrieve the reservations
        vector<Reservation*>::iterator itRes = getScheduledReservation(username, reservs, month, day, startingHour, duration); // get the position on the vector
        res = *itRes;

        if(getScheduledReservation(username,reservs,newMonth,newDay,newStartHour,newDuration) != reservs.end()) {
            throw ReservationAlreadyExists(username);
        }

        if(!res->getTeacher().empty()) { // if the reservation is a lesson
            temp = getTeacher(u.getName());
            vector<Lesson*> lessons = temp.getLessons(); // retrieve the teachers lessons
            vector<Lesson*>::iterator itLesson = getScheduledLesson(temp.getName(),temp.getLessons(),month,day,startingHour,duration);


            if(getScheduledLesson(temp.getName(),lessons,newMonth,newDay,newStartHour,newDuration) != lessons.end()) { // check if the teacher already has a lesson scheduled for the new date
                throw TeacherUnavailable(temp.getName());
            }

            //check court availability and change lesson
            bool flag = true;
            for(auto i: this->tennisCourts)
            {
                if(i.isOccupied(month, day, startingHour, duration))
                {
                    i.modifyReservation(month, day, startingHour, duration, newMonth, newDay, newStartHour, newDuration);
                    flag = false;
                    break;
                }
            }
            if(flag)
                throw NoCourtfound(month, day, startingHour);
            //change lesson in lessons and reservs
            (*itLesson)->setMonth(newMonth);
            (*itLesson)->setDay(newDay);
            (*itLesson)->setStartHour(newStartHour);
            (*itLesson)->setDuration(newDuration);
            (*itRes)->setMonth(newMonth);
            (*itRes)->setDay(newDay);
            (*itRes)->setStartHour(newStartHour);
            (*itRes)->setDuration(newDuration);

            teachers.insert(temp); // confirm procedure
            u.setReservations(reservs);
            temp.setLessons(lessons);

            users.insert(u); //confirm procedure
            return true;
        }
        else { // if its a free reservation

            //check court availability and change free

            bool flag = true;
            for(auto i: this->tennisCourts)
            {
                if(i.isOccupied(month, day, startingHour, duration))
                {
                    i.modifyReservation(month, day, startingHour, duration, newMonth, newDay, newStartHour, newDuration);
                    flag = false;
                    break;
                }
            }
            if(flag)
                throw NoCourtfound(month, day, startingHour);
            //change free in reservs
            (*itRes)->setMonth(newMonth);
            (*itRes)->setDay(newDay);
            (*itRes)->setStartHour(newStartHour);
            (*itRes)->setDuration(newDuration);

            u.setReservations(reservs);
            users.insert(u);
            return true;
        }
    }
    catch (NoUserRegistered &u) {
        cout << u.what() << endl;
        return false;
    }
    catch (TeacherUnavailable &t) {
        users.insert(u);
        cout << t.what() << endl;
        return false;
    }
    catch(ReservationAlreadyExists & r) {
        users.insert(u);
        teachers.insert(temp);
        cout << r.what() << endl;
        return false;
    }
    catch (NoCourtfound &c){
        users.insert(u);
        if(!res->getTeacher().empty())
            teachers.insert(temp);
        cout << c.what() << endl;
    }
    catch (CourtReserved & c){
        users.insert(u);
        if(!res->getTeacher().empty())
            teachers.insert(temp);
        cout << c.what() << endl;
    }
}


//returns true if at least one lesson is rescheduled
bool Company::rescheduleLessons(std::vector<Reservation *> &reservs, Teacher &subst, string username) {

    vector<Reservation *> rejects;
    vector<Lesson *> lsns = subst.getLessons();
    for (auto j = reservs.begin(); j != reservs.end(); j++) {
        bool found = false;
        for (auto i : lsns) {
            if (**j == *i) {
                rejects.push_back(*j); //add to the rejected lessons
                reservs.erase(j); //remove from user reservations
                j--;
                found = true;
                break;
            }
        }
        if (!found) {
            lsns.push_back(dynamic_cast<Lesson *>(*j));
        }
    }

    subst.setLessons(lsns);

    if (!rejects.empty()) {
        cout << "The user: " << username << "has the following lessons unscheduled:" << endl;
        int n = 1;
        for (auto i: rejects) {
            cout << "Lesson nº " << n << ":\t Day/Month: " << i->getDay() << "/" << i->getMonth() << "\t Time: "
                 << i->getStartingHour() << ":" << i->getStartingHour() + i->getDuration() << endl;
            free(i);
        }
    }

    return !(rejects.size() == lsns.size());
}


void Company::rescheduleRepair(unsigned id, unsigned day, unsigned month, unsigned newDay, unsigned newMonth)
{
    Company::unscheduleRepair(id, day, month);
    Company::scheduleRepair(newDay, newMonth, id);
}



 //----------------------------------------------------------------------------------------------------------------

bool Company::showReport(string name, int month)
{
	User u;
	try {
		u = getUser(name); //Gets the user
	}
	catch(NoUserRegistered &e) { //Checks if the user doesn't exist
		cout << e.what() << endl;
		return false;
	}

	try
	{
		cout << u.getReport(month) << endl; //Gets the report based on the month
	}
	catch (IncorrectMonth &e) //Checks if the month is possible
	{
		cout << e.what() << endl;
		return false;
	}
	catch (ReportNotAvailable &e) //Checks if the report is available
	{
		cout << e.what() << endl;
		return false;
	}
	users.insert(u);
	return true;
}

bool Company::showInvoice(string name,int month)
{
	User u;
	try {
		u = getUser(name); //Gets the user
	}
	catch(NoUserRegistered &e) { //Checks if the user exists
		cout << e.what() << endl;
		return false;
	}
	try
	{
		cout << u.getInvoice(month) << endl; //Gets the invoice
	}
	catch (IncorrectMonth &e) //Checks if the month exists
	{
		cout << e.what() << endl;
		return false;
	}
	catch (InvoiceNotAvailable &e) //Checks if the invoice is available
	{
		cout << e.what() << endl;
		return false;
	}
	users.insert(u);
	return true;
}

void Company::showUsers() { //Shows all users

	set<User>::iterator it = users.begin();
	for (size_t i = 0; i < users.size(); i++) {
		User a = *it;
		cout << "User no. " << i + 1 << ":" << endl;
		a.show();
		cout << endl;
		it++;
	}
}

bool compareTeacher (Teacher &t1,Teacher &t2) { //Compares 2 teachers
    return t1.getName() < t2.getName();
}
void Company::showTeachers() { //Shows all teachers

	vector<Teacher> listing;
	for(auto i: teachers) {
		listing.push_back(i);
	}
	sort(listing.begin(),listing.end(),compareTeacher);
	int n=0;
	for(auto i: listing) {
		n++;
		cout << "Teacher no. " << n << ":" << endl;
		i.show();
		cout << endl;
	}
}

void Company::showTeacher(std::string teacher) {
	try {
		Teacher temp(teacher,0,"");
		tabTeach::iterator t = teachers.find(temp); //Gets a specific teacher
		if(t == teachers.end())
			throw(NoTeacherRegistered(teacher));
		(*t).show();
		cout << endl;
	}
	catch (NoTeacherRegistered &e) //Checks if the teacher exists
	{
		cout << e.what() << endl;
	}
}

void Company::showUser(std::string name) {
	try {
		User u = getUser(name); //Gets a specific user
		u.show();
		cout << endl;
		users.insert(u);
	}
	catch (NoUserRegistered &e) //Checks if the user exists
	{
		cout << e.what() << endl;
	}
}

void Company::showCourts() {
	int n=0; //Checks for all available courts at a given day
	for(size_t i=0; i<tennisCourts.size();i++) {
		try{
			tennisCourts[i].occupied(date.getMonth(),date.getDay(),8,12);
			n++;
		}
		catch(CourtReserved &c)
		{}
	}
	cout << "There are still " << n << " totally empty courts for today." << endl;
	cout << "There is a maximum of " << tennisCourts[0].getMaxUsers() << " per court." << endl;
	cout << endl;
}

void Company::showUserReservations(std::string name) {
	try {
		User u = getUser(name);
		users.insert(u);
		vector <Reservation*> reservations = u.getReservations();
		for(size_t i =0;i<reservations.size(); i++) {
			cout << "Reservation number " << i+1 << ": " << endl;
			reservations[i]->show();
			cout << endl;
		}
	}
	catch (NoUserRegistered &e)
	{
		cout << e.what() << endl;
	}
}

void Company::showTeacherLessons(std::string teacher) {
	try {
		Teacher temp(teacher,0,"");
		tabTeach::iterator t = teachers.find(temp);
		if(t == teachers.end())
			throw(NoTeacherRegistered(teacher));
		vector <Lesson*> lessons = (*t).getLessons();
		int n =0;
		for(auto i: lessons) {
			n++;
			cout << "Lesson number " << n << ": " << endl;
			i->show();
			cout << endl;
		}
	}
	catch (NoTeacherRegistered &e)
	{
		cout << e.what() << endl;
	}
}

void Company::showDate()
{
	cout << date.getDay() << "-" << date.getMonth() << "-"<< date.getYear() << endl << endl;
}

void Company::listAllRepairers() const
{
	if(this->techSupport.empty())
		cout << "The company does not possess any Repairers" << endl;
	else
	{
		priority_queue<Supporter> copy = this->techSupport;
		while(!copy.empty())
		{
			cout << copy.top();
			copy.pop();
		}
	}
}

//------------------------------------------------------------------------------------------------------------------


void Company::indentation(std::ofstream &outfile, int indentation)
{
	for(int i = 0; i < indentation; i++)
	{
		outfile << "\t";
	}
}

void Company::storeInfo(std::ofstream &outfile, int indent) {
	indentation(outfile, indent);
	outfile << "{" << endl;
	indent++;
	indentation(outfile, indent); //Stores the tennis courts
	outfile << "\"tennisCourts\": [" << endl;
	indent++;
	for(unsigned int i = 0; i < this->tennisCourts.size(); i++)
	{
		this->tennisCourts[i].storeInfo(outfile, indent);
		if(i+1 != this->tennisCourts.size())
			outfile << "," << endl;
		else
		{
			outfile << endl;
		}
	}
	indent--;
	indentation(outfile, indent);
	outfile << "]," << endl;
	indentation(outfile, indent); //Saves the users in the company
	outfile << "\"users\": [" << endl;
	indent++;
	for(set<User>::iterator it = users.begin(); it != users.end(); )
	{
		User a;
		a = *it;
		a.storeInfo(outfile, indent);
		indentation(outfile, indent);
        it++;
        if( it != this->users.end()) {
            indentation(outfile, indent);
            outfile << "," << endl;
        }

	}
	indent--;
	indentation(outfile, indent);
	outfile << "]," << endl;
	indentation(outfile, indent); //Saves the teachers in the company
	outfile << "\"teachers\": [" << endl;
	indent++;
	for(tabTeach::iterator i = teachers.begin(); i != this->teachers.end();)
	{
		Teacher temp = *i;
		temp.storeInfo(outfile, indent);
		i++;
		if(i != this->teachers.end()) {
			indentation(outfile, indent);
			outfile << "," << endl;
		}
		else
		{
			//outfile << endl;
		}
	}
	indent--;
	indentation(outfile, indent);
	outfile << "]," << endl;

	indentation(outfile, indent); //Saves the repairer in the company
	outfile << "\"repairers\": [" << endl;
	indent++;
	priority_queue<Supporter> temp = techSupport;
	while(!techSupport.empty())
	{
		Supporter s = techSupport.top();
		s.storeInfo(outfile, indent);
		techSupport.pop();

		if(!techSupport.empty()) {
			indentation(outfile, indent);
			outfile << "," << endl;
		}
	}
	indent--;
	indentation(outfile, indent);
	outfile << "]," << endl;

	indentation(outfile, indent); //Saves value of the card
	outfile << "\"cardValue\": " << this->cardValue <<  "," << endl;

	indentation(outfile, indent); //Saves the date information
	outfile << "\"Date\": " << endl;
	indent++;
	date.storeInfo(outfile,indent);
	outfile << endl;
	indent--;
	indentation(outfile, indent);
	outfile << "}" << endl;


}

void Company::readInfo(std::ifstream &infile) {
	string savingString;

	while (getline(infile, savingString)) { //Gets all the tennis courts

		if (savingString.find("tennisCourts") != string::npos) {
			while (getline(infile, savingString)) {
			if (savingString.find(']') != string::npos) {
					break;
				}

				Court c;
				c.readInfo(infile);
				tennisCourts.push_back(c);
			}
		}

		//Gets all the users info
		if (savingString.find("users") != string::npos) {
			while (getline(infile, savingString)) {
				if (savingString.find(']') != string::npos) {
					break;
				}
				User u;
				u.loadClass(infile);
				users.insert(u);
			}
		}

		//Gets all the teachers info
		if (savingString.find("teachers") != string::npos) {
			while (getline(infile, savingString)) {
				if (savingString.find(']') != string::npos) {
					break;
				}
				Teacher t;
				t.loadClass(infile);
				teachers.insert(t);
				getline(infile,savingString);

			}
		}

		//Gets all the repairers info
		if (savingString.find("repairers") != string::npos) {
			while (getline(infile, savingString)) {
				if (savingString.find(']') != string::npos) {
					break;
				}
				Supporter t;
				t.readInfo(infile);
				techSupport.push(t);
				getline(infile,savingString);

			}
		}


		//Gets the card Value
		if (savingString.find("cardValue") != string::npos) {
			savingString = savingString.substr(savingString.find("cardValue") + 11);
			savingString = savingString.substr(0, savingString.find(','));
			this->cardValue = stod(savingString);
		}

		//Gets the Date info
		if (savingString.find("Date") != string::npos) {
			Date d;
			d.readInfo(infile);
			this->date = d;
		}

	}
}


//------------------------------------------------------------------------------------------------------------------

void Company::removeRepairer(unsigned id)
{
	vector<Supporter> aux;
	while(!this->techSupport.empty())
	{
		Supporter sup = this->techSupport.top();
		this->techSupport.pop();
		if(sup.getID() == id)
		{
			for(auto &i: aux)
			{
				this->techSupport.push(i);
			}
			for(auto i: sup.getRepairDates())
			{
				try
				{
					this->scheduleRepair(i.getRepairDate().getDay(), i.getRepairDate().getMonth(), i.getSupID());
				}
				catch(NoSupporterAvailable &e)
				{
					cout << e.what();
				}

			}
			return;
		} else
		{
			aux.push_back(sup);
		}
	}

	for(const auto &i: aux)
	{
		this->techSupport.push(i);
	}
	throw NoSupporterID(id);
}


//remove the teacher from active status and reassign his/her students to another teach and reschedule all possible lessons
bool Company::removeActiveTeacher(std::string teacher) {
	try {
		Teacher rem_teacher(teacher,0,"");
		tabTeach::iterator it = teachers.find(rem_teacher);
		if(it == teachers.end())
			throw (NoTeacherRegistered(teacher));
		if(!(*it).getStatus())
			throw (InactiveTeacher(teacher));

		rem_teacher = *it;
		//get the removed teacher's lessons to be rescheduled
		vector<Lesson*> mLessons = rem_teacher.getLessons();
		teachers.erase(it);
		//remove the teacher active status
		rem_teacher.setStatus(false); // set to inactivity
		rem_teacher.cleanVectors(); // clear lessons
		rem_teacher.cleanNStudents(); //clear nº students assigned
		teachers.insert(rem_teacher); // keep the record

		Teacher new_teacher(teacher,0,"");
		bool found_active = false;

		for(auto j:teachers) {				//find the first teacher active in the table
			if(j.getStatus()) {
				new_teacher = j;
				found_active = true;
				break;
			}
		}
		if(!found_active)				//if there are none an exception is thrown
			throw (NoActiveTeachersLeft(teacher));

		for(auto i: users)							//reassign another teacher to each student affected
		{												//distribuiting accordingly across the rest of the teachers

			if(i.getTeacher() == rem_teacher.getName()) {
				for (auto j: teachers) {
					if (new_teacher.getnStudents() >= j.getnStudents() && j.getStatus())
						new_teacher = j;
				}
				teachers.erase(new_teacher);
				new_teacher.addStudent();// add a student to the substitute teacher
				std::vector<Reservation *> reservs = i.getReservations();
				rescheduleLessons(reservs, new_teacher,i.getName()); // reschedule the possible lessons
				teachers.insert(new_teacher);

				User u = i;
				users.erase(i);
				u.editTeacher(new_teacher.getName());//ana side
				u.editReservations(reservs); //ana side
				users.insert(u);
			}
		}
		return true;
	}
    catch(NoTeacherRegistered &t) {
        cout << t.what() << endl;
        return false;
    }
    catch(InactiveTeacher &i) {
        cout << i.what() << endl;
        return false;
    }
}



void Company::deleteUser(string name)
{
	User u = this->getUser(name);
	u.deleteUser();
}


void Company::listAvailableRepairers(unsigned daysUntilAvailable) const
{
	priority_queue<Supporter> copy = this->techSupport;
	while (!copy.empty())
	{
		if(copy.top().getDaysUntilAvailable() < daysUntilAvailable)
			cout << copy.top();
		copy.pop();
	}
}


void Company::unscheduleRepair(unsigned id, unsigned day, unsigned month)
{
	vector<Supporter> aux;
	Repair rp(0, Date(day, month, this->date.getYear()));
	while(!this->techSupport.empty())
	{
		Supporter sup = this->techSupport.top();
		this->techSupport.pop();
		auto it = sup.getRepairDates().find(rp);
		if(it != sup.getRepairDates().end())
		{
			if(it->getSupID() == id)
			{
				sup.getRepairDates().erase(it);
				for(const auto &i: aux)
				{
					this->techSupport.push(i);
					return;
				}
			}
		}
		aux.push_back(sup);
	}
	for(const auto &i: aux)
	{
		this->techSupport.push(i);
		return;
	}
	throw NoRepair(day, month, id);
}

bool Company::deleteReservation(std::string username, int month, int day, double startingHour, unsigned int duration) {

	User u;
	Teacher temp;
	Reservation* res = NULL;
	try {
		u = getUser(username); //try and get the user
		vector<Reservation*> reservs = u.getReservations(); // retrieve the reservations
		vector<Reservation*>::iterator itRes = getScheduledReservation(username, reservs, month, day, startingHour, duration); // get the position on the vector
		res = *itRes;

		if(!res->getTeacher().empty()) { // if the reservation is a lesson
			temp = getTeacher(u.getName());
			vector<Lesson*> lessons = temp.getLessons(); // retrieve the teachers lessons
			vector<Lesson*>::iterator itLesson = getScheduledLesson(temp.getName(),temp.getLessons(),month,day,startingHour,duration);

            bool flag = true;
            for(auto i: this->tennisCourts)
            {
                if(i.isOccupied(month, day, startingHour, duration))
                {
                    i.unsetReservation(month, day, startingHour, duration);
                    flag = false;
                    break;
                }
            }
            if(flag)
                throw NoCourtfound(month, day, startingHour);
			lessons.erase(itLesson);				//remove from users' reservation and teachers' lessons
            reservs.erase(itRes);

            //remove in court

            u.setReservations(reservs);
            temp.setLessons(lessons);

            teachers.insert(temp); // confirm procedure

            users.insert(u); //confirm procedure
			return true;
		}
		else { // if its a free reservation
            bool flag = true;
            for(auto i: this->tennisCourts)
            {
                if(i.isOccupied(month, day, startingHour, duration))
                {
                    i.unsetReservation(month, day, startingHour, duration);
                    flag = false;
                    break;
                }
            }
            if(flag)
                throw NoCourtfound(month, day, startingHour);
            reservs.erase(itRes);

			//remove in court

			u.setReservations(reservs);
			users.insert(u);
			return true;
		}
	}
	catch (NoUserRegistered &u) {
		cout << u.what() << endl;
		return false;
	}
    catch (NoCourtfound &c){
        users.insert(u);
        if(!res->getTeacher().empty())
            teachers.insert(temp);
        cout << c.what() << endl;
    }
}
//------------------------------------------------------------------------------------------------------------

/*
//returns true if at least one lesson is rescheduled
bool Company::rescheduleLessons(std::vector<Reservation *> &reservs, Teacher &subst, string username) {
	vector<Reservation*> rejects;
	for (auto j= reservs.begin(); j != reservs.end(); j++) {
		vector<Lesson*> lsns = subst.getLessons();
		bool found = false;
		for(auto i : lsns) {
			if (**j == *i) {
				rejects.push_back(*j); //add to the rejected lessons
				reservs.erase(j); //remove from user reservations
				j--;
				found = true;
				break;
			}
		}
		if(!found) {
			lsns.push_back(dynamic_cast<Lesson *>(*j));
		}
	}
	subst.setLessons(lsns);
	if(!rejects.empty()) {
		cout << "The user: " << username << "has the following lessons unscheduled:" << endl;
		int n = 1;
		for (auto i: rejects) {
			cout << "Lesson nº " << n << ":\t Day/Month: " << i->getDay() << "/" << i->getMonth() << "\t Time: "
				 << i->getStartingHour() << ":" << i->getStartingHour() + i->getDuration() << endl;
			free(i);
		}
	}
	return !(rejects.size() == lessons.size());
}
*/



//---------------------------------------------------------------------------------------------------------

//Exception Handling

string NoReservation::what() const
{
	return "No Reservation available under user: " + name + "under those conditions";
}

string NoUserRegistered::what() const
{
	return "The user with name: " + name + ", is not registered in the system. Please register first.";
}

string NoTeacherRegistered::what() const
{
	return "The teacher with name: " + name + ", is not registered in the system. Please register first.";
}

std::string NoSupporterAvailable::what() const
{
	return "There are no supporters available at " + to_string(this->day) + " of " + to_string(this->month) + " \n";
}

string InvalidAge::what() const
{
	return "This age is invalid: " + to_string(this->age);
}

string AlreadyRegisteredUser::what() const
{
	return "There is already a registered user with the name: " + this->name;
}

string AlreadyRegisteredTeacher::what() const
{
	return "There is already a registered teacher with the name: " + this->name;
}

std::string InvalidDate::what() const {
	return "The date given is invalid. Day " + to_string(day) + " of month " + to_string(month) + " has passed.";
}


std::string InactiveTeacher::what() const {
	return "The teacher with name: " + name + ", is not currently working for the company.";
}

std::string NoActiveTeachersLeft::what() const {
	return "The teacher with name: " + name + ", is the last teacher available. Cannot be removed.";
}

std::string InvalidNIF::what() const {
	return "Invalid NIF: " + to_string(nif);
}
  
std::string NoSupporterID::what() const
{
	return "The supporter with the ID " + to_string(this->ID) + " is not registered in this company\n";
}

std::string NoCourtID::what() const
{
	return "The Court with the ID " + to_string(this->ID) + " is not registered in this company\n";
}

std::string ReservationAlreadyExists::what() const {
	return "There is already a reservation made at that time for the user: " + this->name;
}


std::string TeacherUnavailable::what() const {
	return "The teacher: " + this->name + " is not available at that time." ;
}
std::string NoRepair::what() const
{
	return "No Repair scheduled to the date of " + to_string(this->month) + " on the " + to_string(this->day) + " for the" +
	+ " Court Number " + to_string(this->id);
}
