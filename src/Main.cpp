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

string name, gender, assignedT, address, newname;
bool isGold;
int age, m, d, strH;
float duration, newduration;
int nif,n,id;
int newm, newd, newstrH;


/*Used to handle options in menu*/
int flagMenu = 0;
int flagAux;
int flagAux2;
string flagCase;
string flagOptions;
string flagNumbers;

string spaceAtEnd(string name)
{
   string copy = name;
   int pos;

   if(copy.find(' ') != string::npos)
   {
       pos = copy.find(' ');
       if(pos == copy.size() - 1 ) {
           copy  = copy.substr(0, copy.size() - 1);
           return copy;
       }
       else return copy;
   }
   else
       return copy;
}

string isNumber(string flagNumbers) {

    bool isNumber = false;

    while (!isNumber) {
        for (string::const_iterator k = flagNumbers.begin(); k != flagNumbers.end(); ++k)
            isNumber = isdigit(*k);

        if (!isNumber) {
            cout << "Unavailable option. Try again" << endl;
            cin >> flagNumbers;
        }
    }

    return flagNumbers;
}

bool editPerson(Company &C)
{
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

    flagAux = stoi(flagCase);

    ///------------------------------------------------------------
    if (flagAux == 1) { //edit user
        cout << "1.Edit Name" << endl;
        cout << "2.Age " << endl;
        cout << "3.Gender " << endl;
        cout << "4.GoldCard " << endl;
        cout << "5.Address " << endl;
        cout << "6.NIF " << endl;

        cin >> flagOptions;

        while (flagOptions != "0" && flagOptions != "1" && flagOptions != "2" && flagOptions != "3" &&
               flagOptions != "4" && flagOptions != "5" &&
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
                try {
                    C.changeName(spaceAtEnd(name), newGN, 1);
                }
                catch (NoUserRegistered &u) {
                    cout << u.what() << endl;
                }
                catch (NoTeacherRegistered &t) {
                	cout << t.what() << endl;
                }
                break;
            }
            case 2: {
                cout << "New Age" << endl;
                cin >> flagNumbers;
                age = stoi(isNumber(flagNumbers));
                try {
                    C.changeAge(name, age, 1);
                }
                catch (NoUserRegistered &u) {
                    cout << u.what() << endl;
                }
				catch (NoTeacherRegistered &t) {
					cout << t.what() << endl;
				}
                break;
            }
            case 3: {
                cout << "New Gender" << endl;
                cin >> newGN;
                try {
                    C.changeGender(name, newGN, 1);
                }
                catch (NoUserRegistered &u) {
                    cout << u.what() << endl;
                }
				catch (NoTeacherRegistered &t) {
					cout << t.what() << endl;
				}
                break;
            }
            case 4: {
                cout << "Change Gold Status: (1-add card, 0-remove gold card)" << endl;
                cin >> isGold;
                C.changeisGold(spaceAtEnd(name), isGold);
                break;
            }
            case 5: {
                cin.ignore();
                cout << "Change address" << endl;
                getline(cin, address);
                try {
                    C.changeAddress(spaceAtEnd(name), spaceAtEnd(address));
                }
                catch (NoUserRegistered &u) {
                    cout << u.what() << endl;
                }
                break;
            }
            case 6: {
                cout << "Change NIF" << endl;
                cin >> flagNumbers;
                nif = stoi(isNumber(flagNumbers));
                try {
                    C.changeNIF(spaceAtEnd(name), nif);
                }
                catch (NoUserRegistered &u) {
                    cout << u.what() << endl;
                }
                catch (InvalidNIF &u) {
                    cout << u.what() << endl;
                }
                break;
            }


        }

        ///------------------------------------------------------------
    } else if (flagAux == 2) { //edit teacher
        cout << "1.Edit Name" << endl;
        cout << "2.Age " << endl;
        cout << "3.Gender " << endl;
        //need to had more categories after merge

        cin >> flagOptions;

        while (flagOptions != "0" && flagOptions != "1" && flagOptions != "2" && flagOptions != "3") {
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
                C.changeName(spaceAtEnd(name), spaceAtEnd(newGN), 0);
                break;
            }
            case 2: {
                cout << "New Age" << endl;
                cin >> flagNumbers;
                age = stoi(isNumber(flagNumbers));
                C.changeAge(spaceAtEnd(name), age, 0);
                break;
            }
            case 3: {
                cout << "New Gender" << endl;
                cin >> newGN;
                C.changeGender(spaceAtEnd(name), spaceAtEnd(newGN), 0);
                break;
            }
        }
    } else {
        return true;
    }

    return false;
}


bool showPerson(Company &C)
{
    cout << "----------------------------------------------" << endl;
    cout << "1.Show all Teachers and Users" << endl;
    cout << "2.Show User (information/report/invoice/schedule)" << endl;
    cout << "3.Show Teacher (information/schedule)" << endl;
    cout << "4.Go back" << endl;
    cout << "----------------------------------------------" << endl;

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
            cout << "----------------------------------------------" << endl;
            cout << "1.Show Information" << endl;
            cout << endl;
            cout << "----------------------------------------------" << endl;
            cout << "Consult invoice or report of specific month" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "2.Show Report" << endl;
            cout << "3.Show Invoice" << endl;
            cout << "----------------------------------------------" << endl;
            cout << endl;
            cout << "4.Show Schedule" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "5.Go back" << endl;
            cout << "----------------------------------------------" << endl;

            cin >> flagOptions;

            while (flagOptions != "1" && flagOptions != "2" && flagOptions != "3" &&
                   flagOptions != "4"  &&
                   flagOptions != "5") {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Error...Try again: " << endl;
                cin >> flagOptions;
            }

            flagAux2 = stoi(flagOptions);
            cin.ignore();

            if(flagAux2 == 5)
                break;

            cout << "Name of User: " << endl;
            getline(cin, name);

            if (flagAux2 == 1)
                C.showUser(spaceAtEnd(name));

            if (flagAux2 == 2) {
                cout << "Month: " << endl;
                cin >> flagNumbers;
                m = stoi(isNumber(flagNumbers));

                C.showReport(name, m);
            } else if (flagAux2 == 3) {
                cout << "Month: " << endl;
                cin >> flagNumbers;
                m = stoi(isNumber(flagNumbers));
                C.showInvoice(spaceAtEnd(name), m);
            } else if (flagAux2 == 4) {
                C.showUserReservations(spaceAtEnd(name));
            }
            break;
        }
        case 3: //show teacher
        {

            cout << "1.Show Information" << endl;
            cout << "2.Show Schedule" << endl;
            cout << "3.Go back" << endl;

            cin >> flagOptions;

            while (flagOptions != "1" && flagOptions != "2" && flagOptions != "3") {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Error...Try again: " << endl;
                cin >> flagOptions;
            }


            flagAux2 = stoi(flagOptions);

            if (flagAux2 == 3)
                break;

            cin.ignore();
            cout << "Name of User: " << endl;
            getline(cin, name);

            if (flagAux2 == 1) {
                C.showTeacher(spaceAtEnd(name));
            } else if (flagAux2 == 2) {
                C.showTeacherLessons(spaceAtEnd(name));
            }

            break;
        }
        case 4: //go back
        {
            return true;
        }

    }

    return false;

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
int Menu(const int cardValue, Company &C) {
    cout << "-------------Company " << cardValue << "-----------------------" << endl;
    cout << "           ";
    C.showDate();
    cout << "Choose option:                           " << endl;
    cout << "                                         " << endl;
    cout << "1.Person                                 " << endl;
    cout << "2.Reservation                            " << endl;
    cout << "3.Court                                  " << endl;
    cout << "4.Repair                                 " << endl;
    cout << "5.Increment day                          " << endl;
    cout << "6.Exit                                   " << endl;
    cout << "-----------------------------------------" << endl;

    string flag;
    cin >> flag;

    while (flag != "1" && flag != "2" && flag != "3" && flag != "4" && flag != "5" && flag != "6") {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << " Error...Try again: " << endl;
        cin >> flag;
    }

    return stoi(flag);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DevelopCompany(Company &C, unsigned int cardValue) {

    while (true) {

        flagMenu = Menu(cardValue, C);

        switch (flagMenu) {
            case 1: //Add Person
            {
                /////////////////////////////////////////////////////////////


                cout << "----------------------------------------------" << endl;
                cout << "1.Add User" << endl;
                cout << "2.Add Teacher" << endl;
                cout << "3.Edit Infomation" << endl;
                cout << "4.Show Infomation" << endl;
                cout << "5.Remove Person" << endl;
                cout << "6.Go back" << endl;
                cout << "----------------------------------------------" << endl;

                cin >> flagCase;

                while (flagCase != "1" && flagCase != "2" && flagCase != "3" && flagCase != "4" && flagCase != "5" &&
                       flagCase != "6") {
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
                        cout << " Can't added Users. Company needs teachers first." << endl;
                        break;
                    }
                }

                //---------------------------------------------------------------------------------
                if (flagAux == 1 || flagAux == 2) //Add User or Teacher
                {
                    cin.ignore();
                    cout << "Name: " << endl;
                    getline(cin, name);
                    cout << "Age: " << endl;
                    cin >> flagNumbers;

                    age = stoi(isNumber(flagNumbers));

                    cout << "Gender" << endl;
                    cin >> gender;

                    if (flagAux == 1) //Add User
                    {
                        cout << "Gold Card?" << endl;
                        cout << "Option: 1.yes 0.no " << endl;
                        cin >> isGold;
                        cin.ignore();
                        cout << "Address:" << endl;
                        getline(cin, address);
                        cout << "NIF:" << endl;
                        cin >> flagNumbers;

                        nif = stoi(isNumber(flagNumbers));


                        //Finally register the User
                        try {
                            if (!C.registerUser(spaceAtEnd(name), age, isGold, spaceAtEnd(gender), spaceAtEnd(address),
                                                nif, true))
                                cout << " Error adding User. Try again" << endl;
                        }
                        catch (InvalidNIF &u) {
                            cout << u.what() << endl;
                            cout << " Error adding User. Try again" << endl;
                        }
                        catch (InvalidAge &u) {
                            cout << u.what() << endl;
                            cout << " Error adding User. Try again" << endl;

                        }


                    } else if (flagAux == 2) //Add Teacher
                    { // Or the Teacher
                        if (!(C.registerTeacher(spaceAtEnd(name), age, spaceAtEnd(gender))))
                            cout << " Error adding User. Try again" << endl;
                    }
                }

                //---------------------------------------------------------------------------------
                if (flagAux == 3) { //edit User or Teacher
                    if (editPerson(C))
                        break;
                }
                    //---------------------------------------------------------------------------------
                else if (flagAux == 4) //show information teacher and user
                {
                    if (showPerson(C))
                        break;
                }
                    //---------------------------------------------------------------------------------
                else if (flagAux == 5) //remove user or teacher
                {
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

                    if (flagAux2 == 3)
                        break;

                    flagAux2 = stoi(flagOptions);
                    cin.ignore();
                    cout << "Name: " << endl;
                    getline(cin, name);

                    if (flagAux2 == 1) {
                        try {
                            C.deleteUser(spaceAtEnd(name));
                        }
                        catch (NoUserRegistered &u) {
                            cout << u.what() << endl;
                        }
                    } else if (flagAux2 == 2) {
                        C.removeActiveTeacher(spaceAtEnd(name));
                    }

                } else break;

                break;
            }
            case 2: // reservation
            {
                ///////////////////////////////////////////////////////////////
                cout << "----------------------------------------------" << endl;
                cout << "1.Add Free class" << endl;
                cout << "2.Add Lesson" << endl;
                cout << "3.Edit Reservation" << endl;
                cout << "4.Remove Reservation" << endl;
                cout << "5.Go back" << endl;
                cout << "----------------------------------------------" << endl;

                cin >> flagCase;

                while (flagCase != "1" && flagCase != "2" && flagCase != "3" && flagCase != "4" && flagCase != "5") {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << " Error...Try again: " << endl;
                    cin >> flagCase;
                }
                ///////////////////////////////////////////////////////////////
                flagAux = stoi(flagCase);

                if (flagAux == 1 || flagAux == 2) //Add Lesson or Free Class
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
                    getline(cin, name);

                    if (C.getCourts().empty()) {
                        cout << "Try again... No courts added to the company" << endl;
                        break;
                    }

                    if (flagAux == 1) //Add Free Class
                    {
                        cout << "How many players? " << endl;
                        cin >> flagNumbers;
                        n = stoi(isNumber(flagNumbers));

                        if (n > 4) {
                            cout << "The court can't support that many people" << endl;
                            break;
                        }
                        cout << "Duration" << endl;
                        cout << "(write the number of periods of half an hour)" << endl;
                        cout << "1h --> 2; 2h30 --> 5" << endl;
                        cin >> flagNumbers;
                        duration = stoi(isNumber(flagNumbers));
                        //Tries to make the reservation
                        if (!C.makeFree(m, d, strH, duration, spaceAtEnd(name)))
                            cout << " Error adding Free class. Try again" << endl;

                    } else if (flagAux == 2) //Add Lesson
                    {
                        try {
                            // Tries to make the reservation
                            if (!C.makeLesson(m, d, strH, spaceAtEnd(name)))
                                cout << " Error adding Lesson. Try again" << endl;
                        }
                        catch (NoUserRegistered &u) { // If the user doesn't exist
                            cout << u.what() << endl;
                        }
                    }

                } else if (flagAux == 3) { //edit reservation

                    cin.ignore();
                    cout << "User name: " << endl;
                    getline(cin, name);

                    cout << "Month: " << endl;
                    cin >> flagNumbers;
                    m = stoi(isNumber(flagNumbers));

                    cout << "Day: " << endl;
                    cin >> flagNumbers;
                    d = stoi(isNumber(flagNumbers));

                    cout << "Starting Hour: " << endl;
                    cin >> flagNumbers;
                    strH = stoi(isNumber(flagNumbers));

                    cout << "Duration: " << endl;
                    cin >> flagNumbers;
                    duration = stoi(isNumber(flagNumbers));

                    cout << "New Month: " << endl;
                    cin >> flagNumbers;
                    newm = stoi(isNumber(flagNumbers));

                    cout << "New Day: " << endl;
                    cin >> flagNumbers;
                    newd = stoi(isNumber(flagNumbers));

                    cout << "New Starting Hour: " << endl;
                    cin >> flagNumbers;
                    newstrH = stoi(isNumber(flagNumbers));

                    cout << "New Duration: " << endl;
                    cin >> flagNumbers;
                    newduration = stoi(isNumber(flagNumbers));


                    C.modifyReservation(spaceAtEnd(name), m, d, strH, duration, newm, newd, newstrH, newduration);


                } else if (flagAux == 4) { //delete reservation

                    cin.ignore();
                    cout << "User name: " << endl;
                    getline(cin, name);

                    cout << "Month: " << endl;
                    cin >> flagNumbers;
                    m = stoi(isNumber(flagNumbers));

                    cout << "Day: " << endl;
                    cin >> flagNumbers;
                    d = stoi(isNumber(flagNumbers));

                    cout << "Starting Hour: " << endl;
                    cin >> flagNumbers;
                    strH = stoi(isNumber(flagNumbers));

                    cout << "Duration: " << endl;
                    cin >> flagNumbers;
                    duration = stoi(isNumber(flagNumbers));

                    C.deleteReservation(spaceAtEnd(name), m, d, strH, duration);
                } else if (flagAux == 5) { //go back
                    break;
                }
                break;
            }
            case 3: //Courts
            {

                cout << "---------------------------------------------- " << endl;
                cout << "1.Add Court                               " << endl;
                cout << "2.Show Court                             " << endl;
                cout << "3.Go back                         " << endl;
                cout << "---------------------------------------------- " << endl;

                cin >> flagCase;

                while (flagCase != "1" && flagCase != "2" && flagCase != "3") {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagCase;
                }


                flagAux = stoi(flagCase);

                switch (flagAux) {
                    case 1: {
                        C.createCourt();
                        break;
                    }
                    case 2: {
                        C.showCourts();
                        break;
                    }
                }

                break;
            }
            case 4: //Repair
            {
                cout << "---------------------------------------------- " << endl;
                cout << "1.Add Repairer                                " << endl;
                cout << "2.Edit name" << endl;
                cout << "3.Schedule Repair                             " << endl;
                cout << "4.Reschedule Repair" << endl;
                cout << "5.Unschedule Repair" << endl;
                cout << "6.Show Repairers                              " << endl;
                cout << "7.Delete Repairers                              " << endl;
                cout << "8.Go back" << endl;
                cout << "----------------------------------------------" << endl;

                cin >> flagCase;

                while (flagCase != "1" && flagCase != "2" && flagCase != "3" && flagCase != "4" &&
                       flagCase != "5" && flagCase != "6" && flagCase != "7"  && flagCase != "8") {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagCase;
                }


                flagAux = stoi(flagCase);

                if (flagAux == 3 || flagAux == 4 || flagAux == 5) {
                    cout << "Court ID" << endl;
                    cin >> flagNumbers;
                    id = stoi(isNumber(flagNumbers));

                    cout << "Day" << endl;
                    cin >> flagNumbers;
                    d = stoi(isNumber(flagNumbers));

                    cout << "Month" << endl;
                    cin >> flagNumbers;
                    m = stoi(isNumber(flagNumbers));
                }

                switch (flagAux) {
                    case 1: {
                        cin.ignore();
                        cout << "Name" << endl;
                        getline(cin, name);

                        cout << "Gender" << endl;
                        cin >> gender;

                        C.addRepairer(spaceAtEnd(name), spaceAtEnd(gender));
                        break;
                    }
                    case 2:
                    {
                        cout << "ID" << endl;
                        cin >> flagNumbers;

                        flagAux = stoi(isNumber(flagNumbers));

                        cin.ignore();
                        cout << "New Name" << endl;
                        getline(cin, name);

                        try{
                            C.changeRepairerName(id,name);
                        }
                        catch(NoSupporterID &u)
                        {
                            cout << u.what() << endl;
                        }
                        break;

                    }
                    case 3: {

                        try {
                            C.scheduleRepair(d, m, id);
                        }
                        catch (NoSupporterAvailable &u) {
                            cout << u.what() << endl;
                        }
                        catch(NoCourtID &u)
                        {
                            cout << u.what() << endl;
                        }
                        catch(BadDate &u)
                        {
                            cout << u.what() << endl;
                        }

                        break;
                    }
                    case 5: {
                        try {
                            C.unscheduleRepair(id, m, d);
                        }
                        catch (NoRepair &u) {
                            cout << u.what() << endl;
                        }
                        catch(BadDate &u)
                        {
                            cout << u.what() << endl;
                        }

                        break;
                    }
                    case 4: {
                        cout << "New Day" << endl;
                        cin >> flagNumbers;
                        newd = stoi(isNumber(flagNumbers));

                        cout << "New Month" << endl;
                        cin >> flagNumbers;
                        newm = stoi(isNumber(flagNumbers));


                        C.rescheduleRepair(id, m, d, newd, newm);

                        break;
                    }
                    case 6: {
                        cout << "---------------------------------------------- " << endl;
                        cout << "1. Show all" << endl;
                        cout << "2. Show Until Day" << endl;
                        cout << "---------------------------------------------- " << endl;

                        cin >> flagCase;

                        while (flagCase != "1" && flagCase != "2") {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Error...Try again: " << endl;
                            cin >> flagCase;
                        }

                        flagAux2 = stoi(flagCase);

                        if (flagAux2 == 1)
                            C.listAllRepairers();
                        else {
                            cout << "How many days until available? " << endl;
                            cin >> flagCase;

                            flagAux2 = stoi(flagCase);

                            C.listAvailableRepairers(flagAux2);
                        }
                        break;
                    }
                    case 7: {
                        cout << "Supporter ID" << endl;
                        cin >> flagNumbers;
                        id = stoi(isNumber(flagNumbers));

                        try {
                            C.removeRepairer(id);
                        }
                        catch (NoSupporterID &u) {
                            cout << u.what() << endl;
                        }

                        break;
                    }
                    case 8: {
                        break;
                    }
                }
                break;
            }
            case 5: {
                ++C;
                break;
            }
            case 6: { // Does the user want to save the information?
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

                if (flagAux == 0)
                    return 0;

                else if (C.getCourts().size() == 0) {
                    cout << "Company cant be saved without courts assigned to it" << endl;

                    ofstream outfile;
                    outfile.open((to_string(cardValue) + ".json").c_str());
                    C.storeInfo(outfile, 0);
                    return 0;

                }
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
            while (infile.is_open()) // Checks which name can be used for the Json file
            {
                cardValue++;
                infile.close();
                infile.open((to_string(cardValue) + ".json").c_str());

            }

            while (flag) { // Asks for the current date
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



