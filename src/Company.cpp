/*
 * Company.cpp
 *
 *  Created on: 30/10/2018
 *      Author: joaomartins
 */

#include "Company.h"

using namespace std;

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

vector<Court> Company::getCourts()
{
	return tennisCourts;
}

vector<User> Company::getUsers()
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

User& Company::getUser(string userName)
{
	User u(userName,0,"",false,"");
	// Finds the User
	vector<User>::iterator it = find(users.begin(),users.end(),u);
	if(it != users.end())
		return *it;
	else
		throw NoUserRegistered(userName);
}


bool Company::makeLesson(int month,int day,double startingHour,string userName,string teacherName)
{
	// Checks if its a possible date
	if(month < date.getMonth() || (month == date.getMonth() && day < date.getDay())) {
		return false;
	}

	try {
		User& u = getUser(userName); // Gets the user
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
				return true;
			}
		}
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
		User& u = getUser(username); // Gets the user
		for(auto i: tennisCourts) //Reserves the first available court
		{
			if(i.reserveFree(month,day,startingHour,duration,u))
				return true;
		}
		return false;
	}
	catch(NoUserRegistered &u) { //Checks if the user is registered
		cout << u.what() << endl;
		return false;
	}
}

bool Company::registerUser(string name, int age,bool isGold,string gender)
{
	if (age <0) //Checks if it's a possible age
		throw(InvalidAge(age));
	try {
		User& u = getUser(name); //Checks if there's a user already registered
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
		User newuser(name,age,gender,isGold,t2.getName());
		users.push_back(newuser);
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
	 	User& u = getUser(userName); //Gets the User
		Teacher temp(teacherName,0,"");
		tabTeach::iterator it = teachers.find(temp);
		if(it == teachers.end())
			throw (NoTeacherRegistered(teacherName));
	 	Report* newr = new Report(userName,teacherName,u.getReservations());
		u.setReport(newr,month);
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
		User& u = getUser(userName); // Gets the user
		// Makes the invoice and saves it
		Invoice* newinvoice = new Invoice(u.getName(),u.getTeacher(),u.getReservations(), u.getisGold());
		u.setInvoice(newinvoice,month);
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
	return true;
}

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
	for(unsigned int i = 0; i < this->users.size(); i++)
	{
		this->users[i].storeInfo(outfile, indent);
		if(i+1 != this->users.size()) {
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
				Court c;
				c.readInfo(infile);
				tennisCourts.push_back(c);
				if (savingString.find(']') != string::npos) {
					break;
				}
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
				users.push_back(u);
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

Company Company::operator++() {
	++this->date; //Increments the date
	if(date.getDay() == 1) { //Checks if the date changes month and year in order to do Invoices and Reports
		for(auto i:users) {
			if(date.getMonth() == 1) {
				i.cleanVectors();
			}
			if(date.getMonth() != 1)
			{
				makeUserReport(date.getMonth()-1,i.getName(),i.getTeacher());
				makeUserInvoice(i.getName(),date.getMonth()-1);
			} else{
				ofstream outfile(to_string((int)this->cardValue - 1) + "-" + to_string(this->date.getYear()-1) + ".json");
			}
			i.cleanReservations();
		}
		for(auto i:teachers) {
			Teacher temp = i;
			temp.cleanVectors();
			teachers.erase(i);
			teachers.insert(temp);
		}
	}
	return *this;
}

bool compareUser (User &u1,User &u2) { //Compares 2 users
    return u1.getName() < u2.getName();
}
void Company::showUsers() { //Shows all users

    sort(users.begin(),users.end(),compareUser);
	for(size_t i = 0; i< users.size();i++) {
		cout << "User no. " << i+1 << ":" << endl;
		users[i].show();
		cout << endl;
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

//remove the teacher from active status and reassign his/her students to another teach and reschedule all possible lessons
bool Company::removeActiveTeacher(std::string teacher) {
	try {
		Teacher temp(teacher,0,"");
		tabTeach::iterator it = teachers.find(temp);
		if(it == teachers.end())
			throw (NoTeacherRegistered(teacher));
		if(!(*it).getStatus())
			throw (InactiveTeacher(teacher));

		temp = *it;
		//get the students that will need to have another teacher assigned
		//vector<User&> students = getTeacherStudents(teacher); // FAILING
		vector<User> students;
		//get the removed teacher's lessons to be rescheduled
		vector<Lesson*> mLessons = temp.getLessons();
		teachers.erase(it);
		//remove the teacher active status
		temp.setStatus(false); // set to inactivity
		temp.cleanVectors(); // clear lessons
		temp.cleanNStudents(); //clear nº students assigned
		teachers.insert(temp); // keep the record
		bool found_active = false;
		for(auto j:teachers) {				//find the first teacher active in the table
			if(j.getStatus()) {
				temp = j;
				found_active = true;
				break;
			}
		}
		if(!found_active)				//if there are none an exception is thrown
			throw (NoActiveTeachersLeft(teacher));
		for(auto i: students)							//reassign another teacher to each student affected
        {												//distribuiting accordingly across the rest of the teachers
			for(auto j: teachers) {
				if (temp.getnStudents() >= j.getnStudents() && j.getStatus())
					temp = j;
			}
			teachers.erase(temp);
			temp.addStudent(); 		// add a student to the substitute teacher
			//rescheduleLessons(mLessons,i,temp); // reschedule the possible lessons
			teachers.insert(temp);
			//i.editTeacher(temp.getName()); //change assignTeacher in User (TO BE UPDATED)
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

/*
std::vector<User&> Company::getTeacherStudents(std::string teacher)  {
    vector<User&> temp;
    for(vector<User>::iterator i = users.begin() ; i != users.end() ; i++) {
        if((*i).getTeacher() == teacher) {
        	temp.push_back(*i);
        }
    }
    return temp;
}
 */
//returns true if at least one lesson is rescheduled
bool Company::rescheduleLessons(std::vector<Lesson *> lessons, User &user, Teacher &subst) {
	vector<Reservation*> reservs = user.getReservations();
	vector<Reservation*> rejects;
	for(auto i: lessons) {
		for (auto j= reservs.begin(); j != reservs.end(); j++) {
			if(i == *j) {
				auto l = find(subst.getLessons().begin(),subst.getLessons().end(),i); //try to find if the teacher already has a class scheduled for the same time
				if(l == subst.getLessons().end()) {
					subst.setLesson(i);   //if not, add to his/her lessons
				}
				else {
					rejects.push_back(*j); //add to the rejected lessons
					reservs.erase(j); //remove from user reservations
					j--;
				}
			}
		}
	}

	user.setReservations(reservs); //set the reservations with the changes made;

	if(!rejects.empty()) {
		cout << "The user: " << user.getName() << "has the following lessons unscheduled:" << endl;
		int n = 1;
		for (auto i: rejects) {
			cout << "Lesson nº " << n << ":\t Day/Month: " << i->getDay() << "/" << i->getMonth() << "\t Time: "
				 << i->getStartingHour() << ":" << i->getStartingHour() + i->getDuration() << endl;
			free(i);
		}
	}

	if(rejects.size() == lessons.size()) {
		return false;
	}
	else {
		return true;
	}
}



//Exception Handling

string NoUserRegistered::what() const
{
	return "The user with name: " + name + ", is not registered in the system. Please register first.";
}

string NoTeacherRegistered::what() const
{
	return "The teacher with name: " + name + ", is not registered in the system. Please register first.";
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
