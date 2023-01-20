#include <iostream>

#include "TestMethods.h"

using namespace std;

int main() {
    srand( (unsigned)time( NULL ) );
    random_device rd;
    mt19937 gen(rd());
    //firstTest();
    testAllFiles();
    //cout<<"One max : " << oneMax(1000)<<endl;
    return 0;
}
