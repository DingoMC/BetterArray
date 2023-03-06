#include <iostream>
#include "ndarray.h"
using namespace std;
int main () {
    NDArray<int> A(3, {3, 2, 4});
    A.fill({1, 2, 3, 4, 5, 6, 7, 8, 9}, 2);
    A.show();
    cout<<"Dimensions: "<<A.dimension()<<endl;
    cout<<"Shape: ";
    A.shape().show();
    cout<<"Shape[2]: "<<A.shape(2)<<endl;
    cout<<"Full size: "<<A.fullSize()<<endl;
    NDArray<int> B(3, {3, 2, 1});
    B.fill({9, 0, 9, 0});
    A.append(B, 2);
    A.insert(2, B, 2);
    A.expand(2, 2);
    A.show();
    cout<<"New shape: ";
    A.shape().show();
    A.reshape({3, 2, 4, 2});
    A.show();
    cout<<"After Reshape: ";
    A.shape().show();
    A = A.slice(1, 2, 2).slice(1, 1, 3);
    A.collapse();
    A.show();
    cin.ignore();
    cin.get();
    return 0;
}
