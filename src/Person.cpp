/*
 * Person.cpp
 *
 *  Created on: 21/10/2018
 *      Author: anamargaridarl
 */

#include "Person.h"
#include <string>


using namespace std;

void indentp(std::ofstream &outfile, int &indentation)
{
	for(int i = 0; i < indentation; i++)
	{
		outfile << "\t";
	}
}


////////////////////////////////////////////////////////////////////////////
//////////////////Person////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

Person::Person()
{

}

Person::Person(string name,int age,string gender)
{
	this->name=name;
	this->age=age;
	this->gender=gender;
}

string Person::getName() const
{
	return name;
}

int Person::getAge()
{
	return age;
}

string Person::getGender()
{
	return gender;
}

void Person::setName(string name)
{
	this->name=name;
}

void Person::setAge(int age)
{
	this->age=age;
}

void  Person::setGender(string gender)
{
	this->gender=gender;
}


void Person::storeInfo(ofstream &outfile, int &indentation)
{
	indentp(outfile,indentation);
	outfile << "{" << endl;
	indentation++;
	indentp(outfile,indentation); // Saves the name of person
	outfile << "\"name\": " << "\"" << name<<  "\"" << "," <<  endl;
	indentp(outfile,indentation); // Saves their age
	outfile << "\"age\": "<< "\"" << age  << "\"" << "," <<  endl;
	indentp(outfile,indentation); // Saves their gender
	outfile << "\"gender\": "<< "\"" << gender  << "\""  << "," << endl;
}

bool Person::operator == (const Person & p1)
{
	string name = this->getName();
	string p1_name = p1.getName();
	return this->getName() == p1.getName();
}


void Person::loadClass(std::ifstream &inpfile)
{
	string savingString;

	while(getline(inpfile, savingString))
	{
		if(savingString.find("{") !=string::npos)
			continue;
		else
		{
			if(savingString.find("\"name\": ") != string::npos) //Reads their name
			{
				savingString = savingString.substr(savingString.find(":")+3);
				savingString = savingString.substr(0, savingString.find(",")-1);
				this->name =savingString;
			}
			if(savingString.find("\"age\"") != string::npos) //Reads their age
			{
				savingString = savingString.substr(savingString.find(":")+3);
				savingString = savingString.substr(0, savingString.find(",")-1);
				this->age= stoi(savingString);
			}
			if(savingString.find("\"gender\": ") != string::npos) //Reads their gender
			{
				savingString = savingString.substr(savingString.find(":")+3);
				savingString = savingString.substr(0, savingString.find(",")-1);
				 this->gender = savingString;
				 break;
			}
		}
	}

}

void Person::show()
{
	cout << "Name: " << name << endl;
	cout << "Age: " << age << endl;
	cout << "Gender: " << gender << endl;
}

void Person::editName(string name) {

	this->name = name;
}

void Person::editGender(string gender)
{
	this->gender=gender;
}

void Person::editAge(int age)
{
	this->age = age;
}

////////////////////////////////////////////////////////////////////////////
double calculateEndHour(double startinghour, int duration)
{
	return startinghour + 0.5*duration;
}

Person::~Person()
{

}

////////////////////////////////////////////////////////////////////////////
//////////////////Teacher///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
Teacher::Teacher()
{
	nStudents=0;
}

Teacher::Teacher(string name, int age, string gender):Person(name,age,gender)
{
	nStudents = 0;
}

void Teacher::setLesson(Lesson* lesson)
{
	/*
	 * startingHour and endHour are related to reservation to set in vector
	 * resStart and resEnd are related to the reservations in the vector
	 */

	double startingHour, endHour;
	int duration;

	duration = lesson->getDuration();
	startingHour = lesson->getStartingHour();
	// Calculates if it's possible to reserve the Teacher at that time
	endHour = calculateEndHour(startingHour, duration);

	this->lessons.push_back(lesson);
}

vector<Lesson*> Teacher::getLessons()
{
	return lessons;
}

int Teacher::getnStudents()
{
	return nStudents;
}

void Teacher::addStudent()
{
	nStudents++;
}

void Teacher::storeInfo(ofstream &outfile, int &indentation)
{
	Person::storeInfo(outfile,indentation);

	indentp(outfile,indentation); // Stores the number of Students
	outfile << "\"nStudents\": "<< "\"" << nStudents  << "\""  << "," << endl;

	indentp(outfile,indentation);
	outfile<< "\"lessons\": "; // Saves its lessons
	outfile << "["<< endl;
	for(size_t i= 0; i < lessons.size(); i++)
	{
		int in=indentation+1;;
		if(lessons.at(i) != 0)
		{
		indentp(outfile,indentation);
		lessons.at(i)->storeInfo(outfile,in);
		outfile << " , " <<endl;
		}
	}
	indentp(outfile,indentation);
	outfile << "]"<< endl;

	indentation--;
	indentp(outfile,indentation);
	outfile<<"}"<< endl;

}


void Teacher::loadClass(std::ifstream &inpfile)
{
	Person::loadClass(inpfile);

	string savingString;

	getline(inpfile, savingString); // Reads the number of Students
	if (savingString.find("\"nStudents\": ") != string::npos)
	{
		savingString = savingString.substr(savingString.find(":") + 3);
		savingString = savingString.substr(0, savingString.find(",") - 1);
		this->nStudents = stoi(savingString);
	}

	getline(inpfile, savingString); //lessons
		// Gets their lessons
		if(savingString.find("lessons") != string::npos)
		{
		while(getline(inpfile, savingString) && (savingString.find("]") == string::npos) )
		{
			getline(inpfile, savingString);
			Lesson *A = new Lesson();
			//getline(inpfile, savingString);
			A->readInfo(inpfile);
			lessons.push_back(A);
			getline(inpfile, savingString); //}

		}
		}


}

void Teacher::show()
{
	Person::show();
	cout << "Number of students: "<< nStudents << endl;
}

void Teacher::cleanVectors()
{
	lessons.clear();
}

Teacher::~Teacher()
{

}


////////////////////////////////////////////////////////////////////////////
//////////////////User//////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
User::User()
{
	reports.resize(12);
	invoices.resize(12);
}


User::User(string name,int age,string gender, bool isGold, string assignedTeacher, string adress, int nif):Person(name,age,gender)
{
	this->isGold = isGold;
	this->assignedTeacher = assignedTeacher;
	this->adress = adress;
	this->NIF =nif;
	reports.resize(12);
	invoices.resize(12);
}

void User::makeGold()
{
	isGold = true;
}

void User::stopGold()
{
	isGold = false;
}

bool User::getisGold()
{
	return isGold;
}

int User::getNIF()
{
	return NIF;
}
string User::getAdress()
{
	return adress;
}

Report User::getReport(int month)
{
	if(month > 12) // Checks if it's a possible month
		throw(IncorrectMonth());

	if(reports.at(month -1) == 0) // Checks if there's no report available
	{
		throw(ReportNotAvailable(month));
	}
	else
		return *reports.at(month -1);
}

Invoice User::getInvoice(int month)
{
	if(month > 12) // Checks if it's a possible month
			throw(IncorrectMonth());

		if(invoices.at(month -1) == 0) // Checks if there's no invoice available
		{
			throw(InvoiceNotAvailable(month));
		}
		else
			return *invoices.at(month -1);
}

void User::setReport(Report* report, int month)
{
	if(month > 12) // Checks if it's a possible month
			throw(IncorrectMonth());

	if(reports.at(month-1)!=0) //Checks if there's a report already there
	{
		throw(ReportAlreadyExists(month));
	}
	else
	{
		reports.at(month-1)= report;
	}
}

void User::setInvoice(Invoice* invoice, int month)
{
	if(month > 12) // Checks if it's a possible month
				throw(IncorrectMonth());

		if(invoices.at(month-1)!=0) //Checks if there's an invoice already there
		{
			throw(InvoiceAlreadyExists(month));
		}
		else
		{
			invoices.at(month-1)= invoice;
		}
}

void User::setReservation(Reservation* reservation)
{
	/*
	 * startingHour and endHour are related to reservation to set in vector
	 * resStart and resEnd are related to the reservations in the vector
	 */

	double startingHour, endHour;
	int duration;

	duration = reservation->getDuration();
	startingHour = reservation->getStartingHour();

	endHour = calculateEndHour(startingHour, duration); //Calculates the final Hour
	// Checks if the user is available at that time
	if(CheckAvailable(reservations,startingHour,endHour, reservation->getDay(), reservation->getMonth())==0)
		reservations.push_back(reservation);
}

vector<Reservation*> User::getReservations()
{
	return reservations;
}
unsigned int User::getReservationSize() const
{
    return reservations.size();
}

string User::getTeacher()
{
	return this->assignedTeacher;
}

vector<Invoice*> User::getInvoices()
{
	return invoices;
}

void User::storeInfo(ofstream &outfile, int &indentation)
{
	Person::storeInfo(outfile, indentation);

	indentp(outfile,indentation); // Saves if the User is gold
	outfile << "\"isGold\": "<< "\""<< isGold << "\""<< "," << endl;
	indentp(outfile,indentation); // Saves the assigned Teacher
	outfile << "\"assigned Teacher\": "<< "\""<< assignedTeacher <<"\"" << "," <<  endl;
	indentp(outfile,indentation);
	outfile << "\"NIF\": "<< "\""<< NIF <<"\"" << "," <<  endl;
	indentp(outfile,indentation);
	outfile << "\"adress\": "<< "\""<< adress <<"\"" << "," <<  endl;


	outfile<< "\"reports\": "; // Saves all the reports
	outfile << "["<< endl;
	int in=indentation+1;
	for(size_t i =0; i < reports.size(); i++)
	{
		if(reports.at(i) != 0)
		{
		indentp(outfile,in);
		reports.at(i)->storeInfo(outfile,in);
		outfile << " , " <<endl;
		}
	}
	indentp(outfile,indentation);
	outfile << "]"<<","<<endl;

	indentp(outfile,indentation);
	outfile<< "\"reservations\": "; // Saves the reservations
	outfile << "["<< endl;
	for(size_t i =0; i < reservations.size(); i++)
	{
		if(reservations.at(i) != 0)
		{
		indentp(outfile,in);
		reservations.at(i)->storeInfo(outfile,in);
		outfile << " , " <<endl;
		}
	}
	indentp(outfile,indentation);
	outfile << "]"<< ","<<endl;

	indentp(outfile,indentation);
	outfile<< "\"invoices\": "; // Saves the invoices
	outfile << "["<< endl;
	for(size_t i =0; i < invoices.size(); i++)
	{
		if(invoices.at(i) != 0)
		{
		indentp(outfile,in);
		invoices.at(i)->storeInfo(outfile,in);
		outfile << " , " <<endl;
		}
	}

	indentp(outfile,indentation);
	outfile << "]"<< endl;

	indentation--;
	indentp(outfile,indentation);
	outfile<<"}"<< endl;

}



void User::loadClass(std::ifstream &inpfile) {
	Person::loadClass(inpfile);
	bool flag = true;
	string savingString;

	while (getline(inpfile, savingString) && flag) { //Reads if the User is gold
		if (savingString.find("\"isGold\": ") != string::npos) {
			savingString = savingString.substr(savingString.find(":") + 3);
			savingString = savingString.substr(0, savingString.find(",") - 1);

			int i = stoi(savingString);
			if (i == 1)
				this->isGold = true;
			else
				this->isGold = false;
		}
		//Saves the assigned Teacher
		if (savingString.find("\"assigned Teacher\": ") != string::npos) {
			savingString = savingString.substr(savingString.find(":") + 3);
			savingString = savingString.substr(0, savingString.find(",") - 1);
			this->assignedTeacher = savingString;
		}

		if (savingString.find("\"adress\": ") != string::npos) {
			savingString = savingString.substr(savingString.find(":") + 3);
			savingString = savingString.substr(0, savingString.find(",") - 1);
			this->adress = savingString;
		}

        if (savingString.find("\"NIF\": ") != string::npos) {
            savingString = savingString.substr(savingString.find(":") + 3);
            savingString = savingString.substr(0, savingString.find(",") - 1);
            this->NIF = stoi(savingString);
        }


        //Saves the reports
		if (savingString.find("\"reports\": ") != string::npos) {
			while (getline(inpfile, savingString) && (savingString.find("]") == string::npos)) {
				Report *I = new Report();
				I->readInfo(inpfile);
				reports.push_back(I);
				getline(inpfile, savingString);
			}

		}
		//Saves the reservations
		if (savingString.find("\"reservations\": ") != string::npos) {

			while (getline(inpfile, savingString) && (savingString.find("]") == string::npos)) {
				getline(inpfile, savingString);// type
				if (savingString.find("\"free\"") != string::npos) {
					Free *F = new Free();
					F->readInfo(inpfile);
					reservations.push_back(F);
					getline(inpfile, savingString);
				} else if (savingString.find("\"lesson\"") != string::npos) {
					Lesson *L = new Lesson();
					L->readInfo(inpfile);
					reservations.push_back(L);
					getline(inpfile, savingString); //}
				}
			}
		}

		//Saves all the invoices
		if (savingString.find("\"invoices\": ") != string::npos) {
			while (getline(inpfile, savingString) && (savingString.find("]") == string::npos)) {
				Invoice *I = new Invoice();
				I->readInfo(inpfile);
				invoices.push_back(I);
				getline(inpfile, savingString);
			}
			flag = false;
		}
	}
}



void User::show()
{
	string a;

	Person::show();
	if(isGold)
	{
		a = "yes";
	}
	else
		a = "no";

	cout << "isGold: " << a<< endl;
	cout <<"Assigned Teacher: "<< assignedTeacher << endl;
	cout << "Adress: "<< adress << endl;
    cout <<"NIF: " << NIF << endl;

}

void User::cleanVectors()
{
	reports.clear();
	reports.resize(12);
	invoices.clear();
	invoices.resize(12);
}

void User::cleanReservations()
{
	reservations.clear();
}

void User::editIsGold(bool isGold)
{
	this->isGold = isGold;
}

void User::editAdress(string adress)
{
	this->adress = adress;
}

void User::editNIF(int NIF)
{
	this->NIF = NIF;
}

void User::editAssignedTeacher(string newTeacher)
{
	this->assignedTeacher = newTeacher;
	//need to make modification in teacher as well
}


void User::deleteUser()
{
    for(size_t i = 0; i< reports.size(); i++)
    {
        delete reports.at(i);
    }

    for(size_t i = 0; i< invoices.size(); i++)
    {
        delete invoices.at(i);
    }
	for(size_t i = 0; i< reservations.size(); i++)
	{
		delete reservations.at(i);
	}

}


/////////////////////////////////////////////////////////////////////////////////////////
//Handling exceptions
string ReportAlreadyExists::what() const
{
	return "The Report of month " + to_string(month) + " is already associated with the user";
}

string InvoiceAlreadyExists::what() const
{
	return "The Invoice of month " + to_string(month) + " is already associated with the user";
}


string ReportNotAvailable::what() const
{
	return "There is no report available of month " + to_string(month)  + " associated with the user";
}

string InvoiceNotAvailable::what() const
{
	return "There is no invoice available of month " + to_string(month)  + " associated with the user";
}
string IncorrectMonth::what() const
{
	return "Incorrect month ";
}

string InsideRes::what() const
{
	return "Schedule unavailable. A reservation is already made between " + to_string(resStart) + " and " + to_string(endHour);
}

string EndHourInsideRes::what() const
{
	return "Schedule unavailable. A reservation is already made  between " + to_string(resStart) + " and " + to_string(resEnd);
}

string StartHourInsideRes::what() const
{
	return "Schedule unavailable. A reservation is already made  between " + to_string(StartingHour) + " and " + to_string(endHour);
}

