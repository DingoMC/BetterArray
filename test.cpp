#include <iostream>
#include "better_array.h"
using namespace std;
int main () {
    Array < int > A;
    for (int i = 0; i < 5; i++) A.append(i);
    A.show();
    A.pop();
    A.show();
    A.insert(1, 10);
    A.show();
    A.insert(-2, 20);
    A.show();
    A.erase(3);
    A.show();
    A.erase(-2);
    A.show();
    cin.ignore();
    cin.get();
    return 0;
}