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
	for(size_t i =0; i < tennisCourts.size();i++)
	{
		maxusers+=tennisCourts[i].getMaxUsers();
	}
	return maxusers;
}

void Company::createCourt()
{
	// Creates a new Court and saves it
	Court newcourt(year);
	tennisCourts.push_back(newcourt);

}

vector<Court> Company::getCourts()
{
	return tennisCourts;
}

set<User, Comp> Company::getUsers()
{
	return users;
}

vector<Teacher> Company::getTeachers()
{
	return teachers;
}

void Company::deleteUser(string name)
{
	set<User, Comp>::iterator it = users.begin();

	while (it != users.end())
	{
		if(it->getName() == name) {
            User a = *it;
		    a.deleteUser();
			users.erase(it);
		}
		else it++;
	}

	throw NoUserRegistered(name);
}

User Company::getUser(string userName) {

	set<User, Comp>::iterator it = users.begin();

	while (it != users.end())
	{
		if(it->getName() == userName) {
			User a = *it;
			users.erase(it);
			return a;
		}
		else it++;
	}

	throw NoUserRegistered(userName);
}

void Company::reAddUser(User u) //only used in main
{
	users.insert(u);
}

Teacher& Company::getTeacher(std::string teacherName) {
	Teacher t(teacherName,0,"");
	//Finds the teacher
	vector<Teacher>::iterator it = find(teachers.begin(),teachers.end(),t);
	if(it != teachers.end())
		return *it;
	else
		throw NoTeacherRegistered(teacherName);
}

bool Company::makeLesson(int month,int day,double startingHour,string userName)
{
	// Checks if its a possible date
	if(month < date.getMonth() || (month == date.getMonth() && day < date.getDay())) {
		return false;
	}

	try {
		User u;
		u = getUser(userName); // Gets the user
		Teacher& t = getTeacher(u.getTeacher());//Gets the teacher
		for(size_t j =0; j<tennisCourts.size();j++) // Finds the first court where it can reserve the Class
		{
			if(tennisCourts[j].reserveClass(month,day,startingHour,u,t))
			{
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

bool Company::registerUser(string name, int age,bool isGold,string gender, string adress, int nif)
{
	if (age <0) //Checks if it's a possible age
		throw(InvalidAge(age));
	try {
		User u;
		u= getUser(name);
		users.insert(u);//Checks if there's a user already registered
		throw(AlreadyRegisteredUser(name));
	}
	catch(NoUserRegistered &u) {
		size_t i2=0;
		for(size_t i = 1; i < teachers.size();i++)
		{ //Adds a teacher to the student
			if (teachers[i2].getnStudents() >= teachers[i].getnStudents())
				i2 = i;
		}
		teachers[i2].addStudent();
		User newUser(name,age,gender,isGold,teachers[i2].getName(), adress, nif);
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
	try {
		Teacher& t = getTeacher(teacherName); //Checks for a teacher with that name
		throw(AlreadyRegisteredTeacher(teacherName));
	}
	catch(NoTeacherRegistered &t) {
		Teacher newteacher(teacherName,age,gender);
		teachers.push_back(newteacher);
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
	 	Teacher& t = getTeacher(teacherName); //Gets the Teacher
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
	catch(NoTeacherRegistered &t) //Checks if the teacher exists
	{
		cout << t.what() << endl;
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
	for(set<User,Comp>::iterator it = users.begin(); it != users.end(); it++)
	{
		User a;
		a = *it;
		a.storeInfo(outfile, indent);
		indentation(outfile, indent);
		outfile << "," << endl;

	}
	indent--;
	indentation(outfile, indent);
	outfile << "]," << endl;
	indentation(outfile, indent); //Saves the teachers in the company
	outfile << "\"teachers\": [" << endl;
	indent++;
	for(unsigned int i = 0; i < this->teachers.size(); i++)
	{
		this->teachers[i].storeInfo(outfile, indent);
		if(i+1 != this->teachers.size()) {
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
	outfile << "}";
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
				teachers.push_back(t);
				getline(infile,savingString);

			}
		}
        //Gets the card Value
		if (savingString.find("cardValue") != string::npos) {
			savingString = savingString.substr(savingString.find("cardValue") + 11);
			savingString = savingString.substr(0, savingString.find(','));
			this->cardValue = stod(savingString);
		}
        //Gets the year info
		if (savingString.find("year") != string::npos) {
			savingString = savingString.substr(savingString.find("year") + 7);
			savingString = savingString.substr(0, savingString.find_last_of(','));
			this->year = stoi(savingString);
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


		set<User, Comp>::iterator it;
		for(it = users.begin(); it !=users.end(); it++)
		{
			User a = *it;

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
		for(size_t i = 0; i<teachers.size();i++) {
			teachers[i].cleanVectors();
		}
	}
	return *this;
}

void Company::showUsers() { //Shows all users

	set<User, Comp>::iterator it = users.begin();
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

    sort(teachers.begin(),teachers.end(),compareTeacher);
	for(size_t i = 0; i< teachers.size();i++) {
		cout << "Teacher no. " << i+1 << ":" << endl;
		teachers[i].show();
		cout << endl;
	}
}

void Company::showTeacher(std::string teacher) {
	try {
		Teacher t = getTeacher(teacher); //Gets a specific teacher
		t.show();
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
		Teacher t = getTeacher(teacher);
		vector <Lesson*> lessons = t.getLessons();
		for(size_t i =0;i<lessons.size(); i++) {
			cout << "Lesson number " << i+1 << ": " << endl;
			lessons[i]->show();
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


void Company::changeReservation(string name, unsigned int duration, int month, int day, double startingHour)
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
}


void Company::changeName(string name, string newName, int flag)
{
	if (flag == 0)
	{
		//needs new implementation
		getTeacher(name).editName(newName);
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
		getTeacher(name).editAge(newAge);
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
		getTeacher(name).editGender(newgender);
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
    User a = getUser(name);
    a.editNIF(newNIF);
    users.insert(a);
}
void Company::changeAdress(std::string name, std::string newAdress)
{
	User a = getUser(name);
	a.editAdress(newAdress);
	users.insert(a);
}



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
