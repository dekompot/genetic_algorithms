#include <iostream>

#include "TestMethods.h"

using namespace std;

int main() {
    srand( (unsigned)time( NULL ) );
    firstTest();
    testAllFiles();
    cout<<"One max : " << oneMax(1000)<<endl;
    return 0;
}
