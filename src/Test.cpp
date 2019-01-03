/*#include "Calendar.h"
#include "Company.h"
using namespace std;


int main() {

	Date d(1,1,2018);
	Company c1(1,d);

	//Adding teacher
	cout << "Test 1" << endl;
	c1.registerTeacher("Alberto",10,"Pato");

		cout << "1.a: " << endl;
		c1.showTeacher("Alberto");

		cout << "1.b: " << endl;
		c1.showTeachers();

	//Adding teacher
	cout << endl << "Test 2: " << endl;
	c1.registerTeacher("Pedro",13,"Banal");

		cout << "2.a: " << endl;
		c1.showTeacher("Pedro");

		cout << "2.b: " << endl;
		c1.showTeachers();

	//Adding users and check for assigned teachers
	cout << "Test 3" << endl;
	c1.registerUser("Manel",30,true,"Frango");
	c1.registerUser("Nando",23,false,"Calhau");
	c1.showUsers();

	//Parse info to json
	cout << " Test 4: " << endl;
	ofstream outfile;
	outfile.open((to_string(1) + ".json").c_str());
	c1.createCourt();
	c1.storeInfo(outfile,0);
	cout << "Test finished" << endl;


	//FAILING
	 //Reading info from json
	cout << "Test 5: " << endl;
	ifstream infile;
	infile.open((to_string(1) + ".json").c_str());
	c1.readInfo(infile);
	cout << "Show info" << endl;
	c1.showCourts();
	c1.showUsers();
	c1.showTeachers();
	c1.showDate();


	//Try to register a teacher with a invalid name
	cout << "Test 6: " << endl;
	c1.registerTeacher("Pedro",12,"galo");


	//Reserve lessons
	cout << "Test 7: " << endl;
	if(c1.makeLesson(12,23,10,"Manel","Alberto")) {
		cout << "Lesson 1 scheduled" << endl;
	}
	if(c1.makeLesson(12,2,10,"Manel","Alberto")) {
		cout << "Lesson 2 scheduled" << endl;
	}
	if(c1.makeLesson(12,3,8,"Nando","Pedro")) {
		cout << "Lesson 3 scheduled" << endl;
	}
	cout << "7.a. " << endl;
	cout << "N reservs: " << c1.getUser("Manel").getReservations().size() << endl;
	c1.makeUserReport(12,"Manel","Alberto");
	c1.showReport("Manel",12);
	cout << "7.b. " << endl;
	cout << "N reservs: " << c1.getUser("Nando").getReservations().size() << endl;
	c1.makeUserReport(12,"Nando","Pedro");
	c1.showReport("Nando",12);
	cout << "7.c. " << endl;
	c1.makeUserInvoice("Manel",12);
	c1.showInvoice("Manel",12);
	cout <<"7.d." << endl;
	ofstream osd;
	osd.open("1.json");
	c1.storeInfo(osd,0);
	ifstream infile;
	infile.open("1.json");
	c1.readInfo(infile);
	c1.showUsers();
	c1.showTeachers();
	c1.showUserReservations("Manel");
	cout << "Tests finished" << endl;

	//FAILING

	cout << endl << "Test 8: " << endl;
	c1.removeActiveTeacher("Alberto");
	c1.showTeachers();
	//c1.showUsers();

	return 0;
}
*/