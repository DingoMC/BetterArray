#include <iostream>
#include "better_array.h"
using namespace std;
bool CustomMask (int Array_Elem) {
    return Array_Elem < 2 || Array_Elem > 6;
}
int main () {
    Array < int > A;
    Array < int > B;
    for (int i = 0; i < 5; i++) A.append(i);
    for (int i = 5; i < 10; i++) B.append(i);
    vector < int > v1 = {1, 2, 5};
    A.pop();
    A.insert(1, 1);
    A.insert(-2, 2);
    A.erase(1);
    A.erase(-1);
    A.append(Array<int>(v1));
    A.insert(1, Array<int>(v1));
    A.erase(1, 3);
    cout<<"A: ";
    A.show();
    cout<<"B: ";
    B.show();
    cout<<"A -= 2 (modifies Array): ";
    A -= 2;
    A.show();
    cout<<"A + 2 (does not modify Array): ";
    (A + 2).show();
    cout<<"A + B (does not modify Arrays): ";
    (A + B).show();
    cout<<"A += B (modifies Array A only): ";
    A += B;
    A.show();
    cout<<"B: ";
    B.show();
    cout<<"Array A Masked with A <= 5 (does not modify A): ";
    A.masked(A <= 5).show();
    cout<<"Array A Masked with A == B (does not modify A): ";
    A.masked(A == B).show();
    cout<<"Array A Masked with custom mask A < 2 or A > 6 (does not modify A): ";
    A.masked(CustomMask).show();
    cin.ignore();
    cin.get();
    return 0;
}