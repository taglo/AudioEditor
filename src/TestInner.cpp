
#include "Sample.h"
#include "TestInner.h"
#include <iostream>

using namespace std;

void Sample::TestInner::testMethod() {
    cout << "test" << endl;

    cout << "dataL[0] " << dataL[0] << endl;
    cout << "tempo" << Sample::tempo << endl;
}
