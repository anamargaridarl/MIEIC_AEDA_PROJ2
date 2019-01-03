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

string isNumber(string flagNumbers) {

    bool isNumber = false;

    while (!isNumber) {
        for (string::const_iterator k = flagNumbers.begin(); k != flagNumbers.end(); ++k)
            isNumber = isdigit(*k);

        if(!isNumber) {
            cout << "Unavailable option. Try again" << endl;
            cin >> flagNumbers;
        }
    }

    return flagNumbers;
}

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

    string flag;
    cin >> flag;

    while (flag != "1" && flag != "2" && flag != "3") {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error...Try again: " << endl;
        cin >> flag;
    }

    return stoi(flag);

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
    cout << "4.Add Court                              " << endl;// Adds a new Court
    cout << "5.Repair                                 " << endl;
    cout << "6.Show Person                            " << endl; // Shows a person or all people of a class
    cout << "7.Show Courts                            " << endl; // Shows courts information
    cout << "8.Increment day                          " << endl; // Increments the day
    cout << "9.Exit                                   " << endl; // Exit
    cout << "-----------------------------------------" << endl;

    string flag;
    cin >> flag;

    while (flag != "1" && flag != "2" && flag != "3" && flag != "4" && flag != "5" && flag != "6" && flag != "7" && flag != "8" && flag != "9") {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << " Error...Try again: " << endl;
        cin >> flag;
    }

    return stoi(flag);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DevelopCompany(Company &C, unsigned int cardValue) {

    string name, gender, assignedT, address;
    int age;
    bool isGold;
    int m, d, strH;
    float duration;
    string adress;
    int nif;
    int n;

    /*Used to handle options in menu*/
    int flagMenu = 0;
    int flagAux;
    int flagAux2;
    string flagCase;
    string flagOptions;
    string flagNumbers;


    while (true) {

        flagMenu = Menu(cardValue, C);

        switch (flagMenu) {
            case 1: //Add Person
            {
                /////////////////////////////////////////////////////////////


            	cout << "----------------------------------------------"<< endl;
                cout << "1.Add User" << endl;
                cout << "2.Add Teacher" << endl;
                cout << "3.Go back" << endl;
            	cout << "----------------------------------------------"<< endl;

                cin >> flagCase;

                while (flagCase != "1" && flagCase != "2" && flagCase != "3") {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagCase;
                }

                flagAux = stoi(flagCase);
                /////////////////////////////////////////////////////////////
                if (flagAux == 1) // If there's no Teachers, there can't be Users
                {
                	 if (C.getTeachers().empty()) {
                 cout << " Can't added Users. Company needs teachers first."      << endl;
                 break;
                	 }
                }

                if (flagAux != 3) //Add User or Teacher
                {
                    cin.ignore();
                    cout << "Name: " << endl;
                    getline(cin, name);
                    cout << "Age: " << endl;
                    cin >> flagNumbers;

                    age = stoi( isNumber(flagNumbers));

                    cout << "Gender" << endl;
                    cin >> gender;

                    if (flagAux == 1) //Add User
                    {
                        cout << "Gold Card?" << endl;
                        cout << "Option: 1.yes 0.no " << endl;
                        cin >> isGold;
                        cin.ignore();
                        cout << "Address:" << endl;
                        getline(cin, adress);
                        cout << "NIF:" << endl;
                        cin >>flagNumbers;

                        nif = stoi( isNumber(flagNumbers));


                        //Finally register the User
                        try
                        {
                            if(!C.registerUser(name, age, isGold, gender,adress,nif))
                                cout << " Error adding User. Try again" << endl;
                        }
                        catch(InvalidNIF &u)
                        {
                            cout << u.what() << endl;
                            cout << " Error adding User. Try again" << endl;
                        }
                        catch(InvalidAge &u)
                        {
                            cout << u.what() << endl;
                            cout << " Error adding User. Try again" << endl;

                        }



                    } else if (flagAux == 2) //Add Teacher
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
                cout << "----------------------------------------------"<< endl;
                cout << "1.Add Free class" << endl;
                cout << "2.Add Lesson" << endl;
                cout << "3.Go back" << endl;
            	cout << "----------------------------------------------"<< endl;

                cin >> flagCase;

                while (flagCase != "1" && flagCase != "2" && flagCase != "3") {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << " Error...Try again: " << endl;
                    cin >> flagCase;
                }
                ///////////////////////////////////////////////////////////////
                flagAux = stoi(flagCase);

                if (flagAux != 3) //Add Lesson or Free Class
                {

                    cout << "Month: " << endl; //Gets the information for the reservations
                    cin >> flagNumbers;
                    m = stoi(isNumber(flagNumbers));

                    cout << "Day: " << endl;
                    cin >> flagNumbers;
                    d = stoi(isNumber(flagNumbers));

                    cout << "Starting Hour: " << endl;
                    cin >> flagNumbers;
                    strH = stoi(isNumber(flagNumbers));

                    cin.ignore();
                    cout << "Name of User: " << endl;
                    getline(cin,name);

                    if(C.getCourts().empty())
                    {
                    	cout << "Try again... No courts added to the company" << endl;
                    	break;
                    }

                    if (flagAux == 1) //Add Free Class
                    {
                    	cout << "How many players? "<< endl;
                    	cin >> flagNumbers;
                    	n = stoi(isNumber(flagNumbers));

                    	if(n > 4)
                    	{
                    		cout << "The court can't support that many people" << endl;
                    		break;
                    	}
                        cout << "Duration" << endl;
                        cout << "(write the number of periods of half an hour)" << endl;
                        cout << "1h --> 2; 2h30 --> 5" << endl;
                        cin >> flagNumbers;
                        duration = stoi(isNumber(flagNumbers));
                        //Tries to make the reservation
                        if (!C.makeFree(m, d, strH, duration, name))
                            cout << " Error adding Free class. Try again" << endl;

                    } else if (flagAux == 2) //Add Lesson
                    {
                        try {
                            // Tries to make the reservation
                            if (!C.makeLesson(m, d, strH, name))
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

                cout << "----------------------------------------------" << endl;
                cout << "1.Person: Edit Basic Information" << endl;
                cout << "2.Person: Delete    " << endl;
                cout << "3.Reservation: Edit Information" << endl;
                cout << "4.Reservation: Delete" << endl;
                cout << "5.Go back" << endl;
                cout << "----------------------------------------------" << endl;

                cin >> flagCase;

                while (flagCase != "1" && flagCase != "2" && flagCase != "3") {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << " Error...Try again: " << endl;
                    cin >> flagCase;
                }

                flagAux= stoi(flagCase);

                ///----------------------------------------------------------------
                if (flagAux == 1) { //edit person basic information

                    cout << "1.User" << endl;
                    cout << "2.Teacher" << endl;
                    cout << "3.Back" << endl;

                    cin >> flagCase;

                    while (flagCase != "1" && flagCase != "2" && flagCase != "3") {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << " Error...Try again: " << endl;
                        cin >> flagCase;
                    }

                    string newGN;

                    flagAux= stoi(flagCase);
                    ///----------------------------------------------------------------
                    ///------------------------------------------------------------
                    if (flagAux == 1) { //edit user
                        cout << "1.Edit Name" << endl;
                        cout << "2.Age " << endl;
                        cout << "3.Gender " << endl;
                        cout << "4.GoldCard " << endl;
                        cout << "5.Address " << endl;
                        cout << "6.NIF " << endl;

                        cin >> flagOptions;

                        while (flagOptions != "0" && flagOptions != "1" && flagOptions != "2" && flagOptions != "3" && flagOptions != "4" && flagOptions != "5" &&
                                flagOptions != "6") {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << " Error...Try again: " << endl;
                            cin >> flagOptions;
                        }

                        flagAux2 = stoi(flagOptions);

                        cin.ignore();
                        cout << "Name:" << endl;
                        getline(cin, name);

                        switch (flagAux2) {
                            case 1: {
                                //cin.ignore();
                                cout << "New Name" << endl;
                                getline(cin, newGN);
                                try{
                                    C.changeName(name, newGN, 1);
                                }
                                catch(NoUserRegistered &u)
                                {
                                    cout << u.what() << endl;
                                }
                                break;
                            }
                            case 2: {
                                cout << "New Age" << endl;
                                cin >> flagNumbers;
                                age = stoi(isNumber(flagNumbers));
                                try{
                                    C.changeAge(name, age, 1);
                                }
                                catch(NoUserRegistered &u)
                                {
                                    cout << u.what() << endl;
                                }
                                break;
                            }
                            case 3: {
                                cout << "New Gender" << endl;
                                cin >> newGN;
                                try{
                                    C.changeGender(name, newGN, 1);
                                }
                                catch(NoUserRegistered &u)
                                {
                                    cout << u.what() << endl;
                                }
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
                                try {
                                    C.changeAddress(name, address);
                                }
                                catch(NoUserRegistered &u)
                                {
                                    cout << u.what() << endl;
                                }
                                break;
                            }
                            case 6: {
                                cout << "Change NIF" << endl;
                                cin >> flagNumbers;
                                nif = stoi(isNumber(flagNumbers));
                                try {
                                    C.changeNIF(name, nif);
                                }
                                catch(NoUserRegistered &u)
                                {
                                    cout << u.what() << endl;
                                }
                                catch(InvalidNIF &u)
                                {
                                    cout << u.what() << endl;
                                }
                                break;
                            }


                        }

                    ///------------------------------------------------------------
                    } else if(flagAux == 2){ //edit teacher
                        cout << "1.Edit Name" << endl;
                        cout << "2.Age " << endl;
                        cout << "3.Gender " << endl;
                        //need to had more categories after merge

                        cin >> flagOptions;

                        while (flagOptions != "0" && flagOptions!= "1" && flagOptions != "2" && flagOptions != "3") {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << " Error...Try again: " << endl;
                            cin >> flagOptions;
                        }

                        flagAux2 = stoi(flagOptions);

                        cin.ignore();
                        cout << "Name:" << endl;
                        getline(cin, name);


                        switch (flagAux2) {
                            case 1: {
                                cout << "New Name" << endl;
                                getline(cin, newGN);
                                C.changeName(name, newGN, 0);
                                break;
                            }
                            case 2: {
                                cout << "New Age" << endl;
                                cin >> flagNumbers;
                                age = stoi(isNumber(flagNumbers));
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
                } else if (flagAux == 2) { //delete person

                    int flagP;

                    cout << "1.User" << endl;
                    cout << "2.Teacher" << endl;
                    cout << "3.Back" << endl;

                    cin >> flagOptions;

                    while (flagOptions != "1" && flagOptions != "2" && flagOptions != "3") {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << " Error...Try again: " << endl;
                        cin >> flagOptions;
                    }


                    flagAux2 =stoi(flagOptions);
                    cout << "Name: " << endl;
                    cin >> name;


                    if (flagAux2 == 1) {
                        C.deleteUser(name);
                    } else if(flagAux2 == 2) {
                        C.removeActiveTeacher(name);
                    }
                    else
                    {
                        break;
                    }

                ///------------------------------------------------------------
                } else if (flagAux == 3) { //edit reservation
                    cout << "to complete" << endl;
                ///------------------------------------------------------------
                } else if (flagAux == 4) { //delete reservation
                    cout << "to complete" << endl;
                ///------------------------------------------------------------
                } else if (flagAux == 5) { //go back
                    break;
                }
                ///------------------------------------------------------------
            }
            case 4: //Adds the Courts
            {
            	C.createCourt();
            	break;
            }
            case 5: //Repair
            {
                cout << "----------------------------------------------"<< endl;
                cout << "1.Add Repairer                                " << endl;
                cout << "2.Schedule Repair" << endl;
                cout << "3.Show Repairers" << endl;
                cout << "4.Go back" << endl;
                cout << "----------------------------------------------"<< endl;

                cin >> flagCase;

                while (flagCase != "1" && flagCase != "2" && flagCase != "3" && flagCase != "4") {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagCase;
                }
                ///////////////////////////////////////////////////////////////

                flagAux = stoi(flagCase);
                
                break;
            }
            case 6: //Shows the person
            {
                ///////////////////////////////////////////////////////////////

            	cout << "----------------------------------------------"<< endl;
                //Chooses what information he wants
                cout << "1.Show all Teachers and Users" << endl;
                cout << "2.Show User (information/report/invoice/schedule)" << endl;
                cout << "3.Show Teacher (information/schedule)" << endl;
                cout << "4.Go back" << endl;
            	cout << "----------------------------------------------"<< endl;

                cin >> flagCase;

                while (flagCase != "1" && flagCase != "2" && flagCase != "3" && flagCase != "4") {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagCase;
                }
                ///////////////////////////////////////////////////////////////

                flagAux = stoi(flagCase);

                switch (flagAux) {
                    case 1://all teachers and Users
                    {
                        C.showTeachers();
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

                    	cin >> flagOptions;

                    	 while (flagOptions != "1" && flagOptions != "2" && flagOptions != "3" && flagOptions != "4") {
                    		 cin.clear();
                    		 cin.ignore(1000, '\n');
                    		 cout << "Error...Try again: " << endl;
                    		 cin >> flagOptions;
                    	 }

                    	 flagAux2 =stoi(flagOptions);
                        cin.ignore();
                        cout << "Name of User: " << endl;
                        getline(cin, name);


                        if(flagAux2 == 1)
                        	C.showUser(name);

                        if (flagAux2 == 2)
                        {
                        	 cout << "Month: " << endl;
                        	 cin>>flagNumbers;
                            m = stoi(isNumber(flagNumbers));

                        	C.showReport(name,m);
                        }
                        else if(flagAux2 == 3)
                        {
                        	cout << "Month: " << endl;
                        	cin >> flagNumbers;
                            m = stoi(isNumber(flagNumbers));
                        	C.showInvoice(name, m);
                        }
                        else if(flagAux2 == 4)
                        {
                        	C.showUserReservations(name);
                        }

                        break;
                    }
                    case 3: //show teacher
                    {

                    	cout << "1.Show Information" << endl;
                    	cout << "2.Show Schedule" << endl;

                    	cin >> flagOptions;

                    	while (flagOptions != "1" && flagOptions != "2") {
                    		cin.clear();
                    		cin.ignore(1000, '\n');
                    		cout << "Error...Try again: " << endl;
                    		cin >> flagOptions;
                    	}

                    	flagAux2 = stoi(flagOptions);
                    	cin.ignore();
                    	cout << "Name of User: " << endl;
                    	getline(cin, name);

                    	if(flagAux2 ==1)
                    	{
                        C.showTeacher(name);
                    	}
                    	else if(flagAux2 == 2)
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
            case 7: //show courts
            {
            	C.showCourts();
            	break;
            }
            case 8: {
                ++C;
                break;
            }
            case 9: { // Does the user want to save the information?
                cout << "Save and exit? " << endl;
                cout << "1.Yes 0.No" << endl;
                cin >> flagCase;

                while (flagCase != "1" && flagCase != "0") {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagOptions;
                }

                flagAux = stoi(flagCase);

                if(C.getCourts().size() == 0)
                {
                	cout << "Company cant be saved without courts assigned to it"<< endl;
                }
                else if (flagAux == 1) {
                	ofstream outfile;
                	outfile.open((to_string(cardValue) + ".json").c_str());
                    C.storeInfo(outfile, 0);
                    return 0;
                }
                else if (flagAux == 0)
                	return 0;

                break;

            }
        }

    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    unsigned int year, day, month;
    string aux;
    int cv;
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
            cin >> aux;
            day = stoi(isNumber(aux));
            cin >> aux;
            month = stoi(isNumber(aux));
            cin >> aux;
            year = stoi(isNumber(aux));

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

            cout << "Card Value of the company? " << endl;
            cin >> aux;
            cv = stoi(isNumber(aux));

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



