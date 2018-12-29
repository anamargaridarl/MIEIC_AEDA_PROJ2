/*
 * Main.cpp
 *
 *  Created on: 31/10/2018
 *      Author: anamargaridarl
 */

#include "Person.h"
#include "Court.h"
#include "Calendar.h"
#include "Date.h"
#include "Invoice.h"
#include "Report.h"
#include "Reservation.h"
#include "Company.h"

#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The first load of the Company
int MainIntro() {
    cout << "-------------Tenis Company-----------------" << endl;
    cout << "                                         " << endl;
    cout << "Choose option:                           " << endl;
    cout << "                                         " << endl;
    cout << "1.New Company                           " << endl; // Creating a new one
    cout << "2.Load Company                            " << endl; // Or loading another from a file
    cout << "3.Exit                                   " << endl;
    cout << "--------------------------------------------" << endl;

    int flag;
    cin >> flag;

    while (flag != 1 && flag != 2 && flag != 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error...Try again: " << endl;
        cin >> flag;
    }

    return flag;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Constant Menu shown after each operation
int Menu(const int cardValue,Company &C) {
    cout << "-------------Company " << cardValue << "-----------------------" << endl;
    cout << "           "; C.showDate();
    cout << "Choose option:                           " << endl;
    cout << "                                         " << endl;
    cout << "1.Add Person                             " << endl; // Adds a new Person
    cout << "2.Add Reservation                        " << endl; // Adds a new Reservation
    cout << "3.Change Information                     " << endl;
    cout << "4.Add Court                              " << endl; // Adds a new Court
    cout << "5.Show Person                            " << endl; // Shows a person or all people of a class
    cout << "6.Show Courts                            " << endl; // Shows courts information
    cout << "7.Increment day                          " << endl; // Increments the day
    cout << "8.Exit                                   " << endl; // Exit
    cout << "-----------------------------------------" << endl;

    int flag;
    cin >> flag;

    while (flag != 1 && flag != 2 && flag != 3 && flag != 4 && flag != 5 && flag != 6 && flag != 7 && flag != 8) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << " Error...Try again: " << endl;
        cin >> flag;
    }

    return flag;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DevelopCompany(Company &C, unsigned int cardValue) {

    string name, gender, assignedT, address;
    int age;
    bool isGold;
    int m, d, strH;
    float duration;
    int save;
    string adress;
    int nif;

    int flagMenu = 0;

    while (true) {


        flagMenu = Menu(cardValue, C);

        switch (flagMenu) {
            case 1: //Add Person
            {
                /////////////////////////////////////////////////////////////
                int flagP;

            	cout << "----------------------------------------------"<< endl;
                cout << "1.Add User" << endl;
                cout << "2.Add Teacher" << endl;
                cout << "3.Go back" << endl;
            	cout << "----------------------------------------------"<< endl;

                cin >> flagP;

                while (flagP != 1 && flagP != 2 && flagP != 3) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagP;
                }
                /////////////////////////////////////////////////////////////
                if (flagP == 1) // If there's no Teachers, there can't be Users
                {
                	 if (C.getTeachers().empty()) {
                 cout << " Can't added Users. Company needs teachers first."      << endl;
                 break;
                	 }
                }

                if (flagP != 3) //Add User or Teacher
                {
                    cin.ignore();
                    cout << "Name: " << endl;
                    getline(cin, name);
                    cout << "Age: " << endl;
                    cin >> age;
                    cout << "Gender" << endl;
                    cin >> gender;

                    if (flagP == 1) //Add User
                    {
                        cout << "Gold Card?" << endl;
                        cout << "Option: 1.yes 0.no " << endl;
                        cin >> isGold;
                        cin.ignore();
                        cout << "Adress:" << endl;
                        getline(cin, adress);
                        cout << "NIF:" << endl;
                        cin >>nif;


                        //Finally register the User
                        if (!(C.registerUser(name, age, isGold, gender,adress,nif)))
                            cout << " Error adding User. Try again" << endl;



                    } else if (flagP == 2) //Add Teacher
                    { // Or the Teacher
                        if (!(C.registerTeacher(name, age, gender)))
                            cout << " Error adding User. Try again" << endl;
                    }
                }
                break;
            }
            case 2: //add reservation
            {
                ///////////////////////////////////////////////////////////////
                int flagR;

            	cout << "----------------------------------------------"<< endl;
                cout << "1.Add Free class" << endl;
                cout << "2.Add Lesson" << endl;
                cout << "3.Go back" << endl;
            	cout << "----------------------------------------------"<< endl;

                cin >> flagR;

                while (flagR != 1 && flagR != 2 && flagR != 3) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << " Error...Try again: " << endl;
                    cin >> flagR;
                }
                ///////////////////////////////////////////////////////////////

                if (flagR != 3) //Add Lesson or Free Class
                {

                    cout << "Month: " << endl; //Gets the information for the reservations
                    cin >> m;
                    cout << "Day: " << endl;
                    cin >> d;
                    cout << "Starting Hour: " << endl;
                    cin >> strH;
                    cin.ignore();
                    cout << "Name of User: " << endl;
                    getline(cin,name);

                    if(C.getCourts().empty())
                    {
                    	cout << "Try again... No courts added to the company" << endl;
                    	break;
                    }

                    if (flagR == 1) //Add Free Class
                    {
                    	int n;
                    	cout << "How many players? "<< endl;
                    	cin >> n;
                    	if(n > 4)
                    	{
                    		cout << "The court can't support that many people" << endl;
                    		break;
                    	}
                        cout << "Duration" << endl;
                        cout << "(write the number of periods of half an hour)" << endl;
                        cout << "1h --> 2; 2h30 --> 5" << endl;
                        cin >> duration;
                        //Tries to make the reservation
                        if (!C.makeFree(m, d, strH, duration, name))
                            cout << " Error adding Free class. Try again" << endl;

                    } else if (flagR == 2) //Add Lesson
                    {
                        try {
                            User user = C.getUser(name);
                            // Tries to make the reservation
                            if (!C.makeLesson(m, d, strH, name, user.getTeacher()))
                                cout << " Error adding Lesson. Try again" << endl;
                        }
                        catch(NoUserRegistered &u) { // If the user doesn't exist
                            cout << u.what() << endl;
                        }
                    }
                }

                break;
            }
            case 3: { //edit information
                int flagR;

                cout << "----------------------------------------------" << endl;
                cout << "1.Person: Edit Basic Information" << endl;
                cout << "2.Person: Delete    " << endl;
                cout << "3.Reservation: Edit Information" << endl;
                cout << "4.Reservation: Delete" << endl;
                cout << "5.Go back" << endl;
                cout << "----------------------------------------------" << endl;

                cin >> flagR;

                while (flagR != 1 && flagR != 2 && flagR != 3) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << " Error...Try again: " << endl;
                    cin >> flagR;
                }
                ///----------------------------------------------------------------
                if (flagR == 1) { //edit person basic information

                    int flagP;

                    cout << "1.User" << endl;
                    cout << "2.Teacher" << endl;
                    cout << "3.Back" << endl;

                    cin >> flagP;

                    while (flagP != 1 && flagP != 2 && flagP != 3) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << " Error...Try again: " << endl;
                        cin >> flagP;
                    }

                    int flagM;
                    string newGN;

                ///----------------------------------------------------------------
                    ///------------------------------------------------------------
                    if (flagP == 1) { //edit user
                        cout << "1.Edit Name" << endl;
                        cout << "2.Age " << endl;
                        cout << "3.Gender " << endl;
                        cout << "4.GoldCard " << endl;
                        cout << "5.Address " << endl;
                        cout << "6.NIF " << endl;

                        cin >> flagM;

                        while (flagM != 0 && flagM != 1 && flagM != 2 && flagM != 3 && flagM != 4 && flagM != 5 &&
                               flagM != 6) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << " Error...Try again: " << endl;
                            cin >> flagM;
                        }

                        cin.ignore();
                        cout << "Name:" << endl;
                        getline(cin, name);

                        switch (flagM) {
                            case 1: {
                                //cin.ignore();
                                cout << "New Name" << endl;
                                getline(cin, newGN);
                                C.changeName(name, newGN, 1);
                                break;
                            }
                            case 2: {
                                cout << "New Age" << endl;
                                cin >> age;
                                C.changeAge(name, age, 1);
                                break;
                            }
                            case 3: {
                                cout << "New Gender" << endl;
                                cin >> newGN;
                                C.changeGender(name, newGN, 1);
                                break;
                            }
                            case 4: {
                                cout << "Change Gold Status: (1-add card, 0-remove gold card)" << endl;
                                cin >> isGold;
                                C.changeisGold(name, isGold);
                                break;
                            }
                            case 5: {
                                cin.ignore();
                                cout << "Change address" << endl;
                                getline(cin, address);
                                C.changeAdress(name,address);
                                break;
                            }
                            case 6: {
                                cout << "Change NIF" << endl;
                                cin >> nif;
                                C.changeNIF(name,nif);
                                break;
                            }


                        }

                    ///------------------------------------------------------------
                    } else if(flagP == 2){ //edit teacher
                        cout << "1.Edit Name" << endl;
                        cout << "2.Age " << endl;
                        cout << "3.Gender " << endl;
                        //need to had more categories after merge

                        cin >> flagM;

                        while (flagM != 0 && flagM != 1 && flagM != 2 && flagM != 3) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << " Error...Try again: " << endl;
                            cin >> flagM;
                        }

                        cin.ignore();
                        cout << "Name:" << endl;
                        getline(cin, name);


                        switch (flagM) {
                            case 1: {
                                cout << "New Name" << endl;
                                getline(cin, newGN);
                                C.changeName(name, newGN, 0);
                                break;
                            }
                            case 2: {
                                cout << "New Age" << endl;
                                cin >> age;
                                C.changeAge(name, age, 0);
                                break;
                            }
                            case 3: {
                                cout << "New Gender" << endl;
                                cin >> newGN;
                                C.changeGender(name, newGN, 0);
                                break;
                            }
                        }
                    }else
                        {
                        break;
                    }

                ///------------------------------------------------------------
                } else if (flagR == 2) { //delete person

                    int flagP;

                    cout << "1.User" << endl;
                    cout << "2.Teacher" << endl;
                    cout << "3.Back" << endl;

                    cin >> flagP;

                    while (flagP != 1 && flagR != 2 && flagR != 3) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << " Error...Try again: " << endl;
                        cin >> flagP;
                    }

                    cout << "Name: " << endl;
                    cin >> name;

                    if (flagP == 1) {
                        C.deleteUser(name);
                    } else if(flagP == 2) {
                        //delete teacher
                    }
                    else
                    {
                        break;
                    }

                ///------------------------------------------------------------
                } else if (flagR == 3) { //edit reservation
                    cout << "to complete" << endl;
                ///------------------------------------------------------------
                } else if (flagR == 4) { //delete reservation
                    cout << "to complete" << endl;
                ///------------------------------------------------------------
                } else if (flagR == 5) { //go back
                    break;
                }
                ///------------------------------------------------------------
            }
            case 4: //Adds the Courts
            {
            	C.createCourt();
            	break;
            }
            case 5: //Shows the person
            {
                ///////////////////////////////////////////////////////////////
                int flagR;

            	cout << "----------------------------------------------"<< endl;
                //Chooses what information he wants
                cout << "1.Show all Teachers and Users" << endl;
                cout << "2.Show User (information/report/invoice/schedule)" << endl;
                cout << "3.Show Teacher (information/schedule)" << endl;
                cout << "4.Go back" << endl;
            	cout << "----------------------------------------------"<< endl;

                cin >> flagR;

                while (flagR != 1 && flagR != 2 && flagR != 3 && flagR != 4) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagR;
                }
                ///////////////////////////////////////////////////////////////

                switch (flagR) {
                    case 1://all teachers and Users
                    {
                        C.showTeachers();
                        cout << "pele"<< endl;
                        C.showUsers();
                        break;
                    }
                    case 2: //show user
                    {
                    	int flagR;

                    	cout << "----------------------------------------------"<< endl;
                    	cout << "1.Show Information" << endl;
                    	cout << endl;
                    	cout << "----------------------------------------------"<< endl;
                    	cout << "Consult invoice or report of specific month" << endl;
                     	cout << "----------------------------------------------"<< endl;
                    	cout << "2.Show Report" << endl;
                        cout << "3.Show Invoice" << endl;
                        cout << "----------------------------------------------"<< endl;
                        cout << endl;
                    	cout << "4.Show Schedule" << endl;
                    	cout << "----------------------------------------------"<< endl;

                    	cin >> flagR;

                    	 while (flagR != 1 && flagR != 2 && flagR != 3 && flagR != 4) {
                    		 cin.clear();
                    		 cin.ignore(1000, '\n');
                    		 cout << "Error...Try again: " << endl;
                    		 cin >> flagR;
                    	 }
                        cin.ignore();
                        cout << "Name of User: " << endl;
                        getline(cin, name);


                        if(flagR == 1)
                        	C.showUser(name);

                        if (flagR == 2)
                        {
                        	 cout << "Month: " << endl;
                        	 cin>>m;
                        	C.showReport(name,m);
                        }
                        else if(flagR == 3)
                        {
                        	cout << "Month: " << endl;
                        	cin >> m;
                        	C.showInvoice(name, m);
                        }
                        else if(flagR == 4)
                        {
                        	C.showUserReservations(name);
                        }

                        break;
                    }
                    case 3: //show teacher
                    {
                    	int flagR;

                    	cout << "1.Show Information" << endl;
                    	cout << "2.Show Schedule" << endl;

                    	cin >> flagR;

                    	while (flagR != 1 && flagR != 2) {
                    		cin.clear();
                    		cin.ignore(1000, '\n');
                    		cout << "Error...Try again: " << endl;
                    		cin >> flagR;
                    	}
                    	cin.ignore();
                    	cout << "Name of User: " << endl;
                    	getline(cin, name);

                    	if(flagR ==1)
                    	{
                        C.showTeacher(name);
                    	}
                    	else if(flagR == 2)
                    	{
                    		C.showTeacherLessons(name);
                    	}

                        break;
                    }
                    case 4: //go back
                    {
                        break;
                    }
                }

                break;
            }
            case 6: //show courts
            {
            	C.showCourts();
            	break;
            }
            case 7: {
                ++C;
                break;
            }
            case 8: { // Does the user want to save the information?
                cout << "Save and exit? " << endl;
                cout << "1.Yes 0.No" << endl;
                cin >> save;

                if(C.getCourts().size() == 0)
                {
                	cout << "Company cant be saved without courts assigned to it"<< endl;
                }
                else if (save == 1) {
                	ofstream outfile;
                	outfile.open((to_string(cardValue) + ".json").c_str());
                    C.storeInfo(outfile, 0);
                    return 0;
                }
                else if (save == 0)
                	return 0;

                break;

            }
        }

    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    unsigned int year, day, month;
    ////////////////////////////////////

    int flag = MainIntro();

    switch (flag) {
        case 1: //new Company
        {
        	bool flag = true;
        	Date D;

        	int cardValue = 1;
        	ifstream infile;
        	infile.open((to_string(cardValue) + ".json").c_str());
        	while(infile.is_open()) // Checks which name can be used for the Json file
        	{
        		cardValue++;
        		infile.close();
        		infile.open((to_string(cardValue) + ".json").c_str());

        	}

        	while(flag)
        	{ // Asks for the current date
            cout << "Please enter date (day month year): " << endl;
            cin >> day;
            cin >> month;
            cin >> year;

            try {
                Date F(day, month, year);
                D = F; // Checks if it is a possible date

            } catch (BadDate &e) {
                cout << e.what() << endl;
                continue;
            }
             flag = false;

          	}

            Company C(cardValue, D);

            DevelopCompany(C, cardValue);

            break;

        }
        case 2: //load company
        {

            int cv;
            cout << "Card Value of the company? " << endl;
            cin >> cv;

            Company C;

            ifstream infile;
            infile.open((to_string(cv) + ".json").c_str());

            while (!infile.is_open()) {
                cerr << "There is no company with Card Value n: " << cv << "! Please try again." << endl;
                cin.clear();
                cin.ignore(1000, '/n');
                cout << "Card Value of the company?" << endl;
                cin >> cv;
                infile.open((to_string(cv) + ".json").c_str());
            }

            C.readInfo(infile);

            DevelopCompany(C, cv);

            break;
        }
        case 3: //exit
        {
            return 0;
        }
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



