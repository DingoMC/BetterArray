#include <iostream>
#include <vector>
#include <list>
#include "better_array.h"
using namespace std;
bool CustomMask (int Array_Elem) {
    return Array_Elem < 2 || Array_Elem > 6;
}
bool CustomComp (int V1, int V2) {
    return V1 + V2 > 5;
}
int main () {
    Array < int > A;
    Array < int > B;
    for (int i = 0; i < 5; i++) A.append(i);
    for (int i = 5; i < 10; i++) B.append(i);
    vector < int > v1 = {1, 2, 5};
    A.pop();
    A.insert(1, 5);
    A.insert(-2, 4);
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
    A.reverse();
    cout<<"Reverse A: ";
    A.show();
    ArrayMask Mask1(A == B);
    ArrayMask Mask2(A < B);
    cout<<"A == B Mask: ";
    Mask1.show();
    cout<<"!(A == B) Mask (A != B): ";
    (!Mask1).show();
    cout<<"A < B Mask: ";
    Mask2.show();
    cout<<"A < B | A == B Mask: ";
    (Mask1 | Mask2).show();
    cout<<"A < B & A == B Mask: ";
    (Mask1 & Mask2).show();
    cout<<"A < B ^ A == B Mask: ";
    (Mask1 ^ Mask2).show();
    cout<<"(A == B) ^ 1 Mask: ";
    (Mask1 ^ true).show();
    int* DynArr;
    int DynArr_size;
    DynArr = Converter::toDynArray(A, DynArr_size);
    Container::show(DynArr, DynArr_size, true);
    Container::show(Converter::toVector(A), true);
    Container::show(Converter::toList(A), true);
    Container::show(Converter::toSet(A), true);
    vector<char> keys = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    Container::show(Converter::toMap(Array<char>(keys), A), true);
    cout<<A.max()<<endl;
    cout<<A.min()<<endl;
    cout<<A.mean()<<endl;
    cout<<A.max(-3, -1)<<endl;
    cout<<A.min(-3, -1)<<endl;
    cout<<A.mean(1, -2)<<endl;
    cout<<"Array slice: ";
    A.slice(1, -2).show();
    A.sort(Order::DESC, 2, -3);
    cout<<"Partially sorted Array: ";
    A.show();
    A.sort(CustomComp);
    cout<<"Fully sorted Array using custom comparison: ";
    A.show();
    cout<<A.count(3)<<endl;
    cout<<A.contains(3)<<endl;
    cout<<A.find(3)<<endl;
    vector<int> check = {7, 8, 10};
    cout<<A.contains(Array<int>(check))<<endl;
    cout<<A.find(Array<int>(check))<<endl;
    vector<char> CV = {'A', 'B', 'C'};
    Array<char> C(CV);
    string conv_string = Converter::toString(C);
    cout<<conv_string<<endl;
    Converter::toCharArray(conv_string).show(true);
    cin.ignore();
    cin.get();
    return 0;
}