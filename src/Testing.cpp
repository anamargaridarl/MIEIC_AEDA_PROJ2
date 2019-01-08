//
// Created by andrefmrocha on 10/30/18.
//

#include "Court.h"
#include "Person.h"
#include "Date.h"
#include "Company.h"
#include <ostream>

using namespace std;
int main()
{

    ofstream outfile("Reservation.json");
    ofstream out("Reservation1.json");
    ifstream infile("Reservation.json");
    Lesson l(10, 2, 10, 50, 2, "Meias");
    l.storeInfo(outfile, 0);
    Lesson l1;
    l1.readInfo(infile);
    l1.storeInfo(out, 0);
}