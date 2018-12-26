#include "Calendar.h"
#include "Company.h"
using namespace std;


int main() {
    tabTeach hash;
    Teacher t1("Pedro",12,"peixe");
    hash.insert(t1);
    std::string st1 = t1.getName() + t1.getGender() + std::to_string(t1.getAge()) + std::to_string(t1.getnStudents());
    cout << picosha2::hash256_hex_string(st1) << endl;
    Teacher null("",0,"");
    cout << hash.max_size() << endl;
    Company c1;
    stringstream s1;
    bool active = true;
    cout << "Working at the company currently: " << (active ? "True" : "False") << endl;

    return 0;
}
