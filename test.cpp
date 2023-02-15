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
    Array < int > A({0, 1, 2, 3, 4});
    Array < int > B({5, 6, 7, 8, 9});
    A.pop();                    // 0, 1, 2, 3
    A.insert(1, 5);             // 0, 5, 1, 2, 3
    A.insert(-2, 4);            // 0, 5, 1, 2, 4, 3
    A.erase(1);                 // 0, 1, 2, 4, 3
    A.erase(-1);                // 0, 1, 2, 4
    A.append({1, 2, 5});        // 0, 1, 2, 4, 1, 2, 5
    A.insert(1, {1, 2, 5});     // 0, 1, 2, 5, 1, 2, 4, 1, 2, 5
    A.erase(1, 3);              // 0, 1, 2, 4, 1, 2, 5
    cout<<"A: ";
    A.show();
    cout<<"B: ";
    B.show();
    cout<<"Unique A: ";
    A.unique().show();
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
    cout<<A.max()<<" - ";
    A.argmax().show();
    cout<<A.min()<<" - ";
    A.argmin().show();
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
    cout<<"Check if value 3 exists: "<<A.contains(3)<<endl;
    cout<<"Count occurences of value 3: "<<A.count(3)<<endl;
    cout<<"Find first index of value 3 occurence: "<<A.find(3)<<endl;
    cout<<"Find all indices where 3 occurs: ";
    A.findAll(3).show();
    cout<<"Sub-array checking: "<<A.contains({7, 8, 10})<<endl;
    cout<<"Find first index where list begins: "<<A.find({7, 8, 10})<<endl;
    A.findAll({7, 8, 10}).show();
    vector<char> CV = {'A', 'B', 'C'};
    Array<char> C(CV);
    string conv_string = Converter::toString(C);
    cout<<conv_string<<endl;
    Converter::toCharArray(conv_string).show(true);
    /*Files::saveArray(A, "A.txt");
    Files::appendArray(A, "A.txt");
    Files::readArray<int>("A.txt").show();*/
    cin.ignore();
    cin.get();
    return 0;
}