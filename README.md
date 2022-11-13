# Better Array C++

## Table Of Contents

1. [Overview](#1-overview)
    1) [General Information](#11-general-information)
    2) [Author](#12-author)
    3) [Other](#13-other)
2. [Class Array](#2-class-array)
    1) [Constructors](#21-constructors)
    2) [Array Indexing](#22-array-indexing)
    3) [Built-in methods](#23-built-in-methods)
    4) [Arithmetic operations](#24-arithmetic-operations)
        - [Array with constant](#241-array-with-constant)
        - [Array with another array](#242-array-with-another-array)
        - [Modifying array with constant](#243-modifying-array-with-constant)
        - [Modifying array with another array](#244-modifying-array-with-another-array)
    5) [Array Masking](#25-array-masking)
        - [ArrayMask Type](#251-arraymask-type)
        - [Masking using ArrayMask](#252-masking-using-arraymask)
        - [Masking using custom comparator](#253-masking-using-custom-comparator)
    6) [Array Mask operations](#26-array-mask-operations)
        - [Getting Mask comparing Array to constant](#261-getting-mask-comparing-array-to-constant)
        - [Getting Mask comparing Array to another Array](#262-getting-mask-comparing-array-to-another-array)
        - [Boolean operations on Array Masks](#263-boolean-operations-on-array-masks)
        - [Boolean operations on Array Mask and constant](#264-boolean-operations-on-array-mask-and-constant)
        - [Boolean operations modifying Array Mask](#265-boolean-operations-modifying-array-mask)
3. [Container Namespace](#3-container-namespace)
    1) [Show Containers](#31-show-containers)
4. [Converter Namespace](#4-converter-namespace)
    1) [Convert Array to other containers](#41-convert-array-to-other-containers)
5. [Changelog](#5-changelog)
    - [Release-0.3](#release-03)
    - [Release-0.2](#release-02)
    - [Release-0.1](#release-01)

## 1. Overview

### 1.1. General Information

Better Array is a library written in C++ used to improve operating on array-like objects by adding bunch of methods, operations and masking. It is based on STL containers and supports STL array-like types.

> **Very Important!** Library has been written and tested using C++ 11. Author takes **no** responsibility of library malfunction on **older** versions of C++.

### 1.2. Author

Library content has been fully written by DingoMC. Distributed on GitHub with GNU/GPL license.  
Link to my website [here](https://www.dingomc.net).  
Any suggestions to improve this library can be sent via [E-mail](https://www.dingomc.net/contact.html).

### 1.3. Other

File: better_array.h  
Latest Version: [0.3](#release-03)  
Created on: 11th Nov 2022  
Latest Update: 13th Nov 2022  
Testing File: test.cpp  
G++ Additional Compiler Flags: `-static-libstdc++`, `-std=c++17`

## 2. Class Array

### 2.1. Constructors

- New empty Array object `v.0.1+`

    ```c++
    Array<T>::Array();
    ```  

    Example:  

    ```c++
    Array<int> A;
    ```

- New empty Array object with reserved array length `v.0.1+`

    ```c++
    Array<T>::Array(unsigned int s);
    ```  

    Example:  

    ```c++
    Array<int> A(5);
    ```  

- Create Array using STL Vector `v.0.1+`

    ```c++
    Array<T>::Array(const std::vector<T> &STL_Vector);
    ```  

    Example:  

    ```c++
    std::vector<int> V = {1, 2, 3};
    Array<int> A(V);
    ```  

- Create Array using STL List `v.0.1+`

    ```c++
    Array<T>::Array(const std::list<T> &STL_List);
    ```  

    Example:  

    ```c++
    std::list<int> L = {1, 2, 3};
    Array<int> A(L);
    ```  

- Create Array using dynamic array `v.0.1+`

    ```c++
    Array<T>::Array(const T *dynamicArray, unsigned int arraySize);
    ```  

    Example:  

    ```c++
    int *T = new int[5];
    for (int i = 0; i < 5; i++) T[i] = i;
    Array<int> A(T, 5);
    ```

- Create Array using STL Set `v.0.2+`

    ```c++
    Array<T>::Array(const std::set<T> &STL_Set)
    ```  

    Example:  

    ```c++
    std::set<int> S = {1, 2, 3};
    Array<int> A(S);
    ```

### 2.2. Array Indexing

`v.0.1+`

Array elements can be accessed via [] operator. Index can be regular or negative.  
Table of Array indexing

| Array Elements      |  6  |  9  |  1  |  0  |  3  |
| ------------------- | --- | --- | --- | --- | --- |
| Regular Index       |  0  |  1  |  2  |  3  |  4  |
| Negative Index      | -5  | -4  | -3  | -2  | -1  |

Example:

```c++
std::vector<int> V = {6, 9, 1, 0, 3};
Array<int> A(V);
std::cout<<A[1]<<std::endl; // Will print 9
std::cout<<A[-2]<<std::endl; // Will print 0
```

### 2.3. Built-in methods

- Get length of Array `v.0.1+`

    ```c++
    unsigned int Array<T>::size() const;
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    int s = A.size(); // s = 5
    ```

- Show Array `v.0.1+`

    ```c++
    void Array<T>::show(bool showType = false);
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    A.show();       // Will print: [6, 9, 1, 0, 3]
    A.show(true);   // Will print: `Array` [6, 9, 1, 0, 3]
    ```

- Add Element to the end of Array `v.0.1+`

    ```c++
    void Array<T>::append(T Elem);
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    A.append(7);    // A = [6, 9, 1, 0, 3, >7<]
    ```

- Add another array to the end of Array `v.0.1+`

    ```c++
    void Array<T>::append(Array<T> arr);
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    std::vector<int> V2 = {5, 0, 8};
    Array<int> A(V);
    Array<int> B(V2);
    A.append(B);    // A = [6, 9, 1, 0, 3, >5, 0, 8<]
    ```

- Remove last element of an Array `v.0.1+`

    ```c++
    void Array<T>::pop();
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    A.pop();    // A = [6, 9, 1, 0]
    ```

- Insert element into Array at given index `v.0.1+`

    ```c++
    void Array<T>::insert(int Where, T Elem);
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    A.insert(-2, 5);    // A = [6, 9, 1, 0, >5<, 3]
    ```

- Insert another Array into Array at given index `v.0.1+`

    ```c++
    void Array<T>::insert(int Where, Array<T> arr);
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    std::vector<int> V2 = {5, 0, 8};
    Array<int> A(V);
    Array<int> B(V2);
    A.insert(1, B);     // A = [6, >5, 0, 8<, 9, 1, 0, 5, 3]
    ```

- Remove element at given index from Array `v.0.1+`

    ```c++
    void Array<T>::erase(int Which);
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    A.erase(2);    // A = [6, 9, 0, 3]
    ```

- Remove elements from Array in given index range `v.0.1+`

    ```c++
    void Array<T>::erase(int From, int To);
    ```  

    Example:

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    A.erase(1, -2);    // A = [6, 3]
    ```

    > **Important!** Parameter `From` should always be the first index and `To` second. They are non-commutative (i.e. `erase(3, 1)` is not going to work cause `3` is further in order than `1`).

- Reverse an Array `v.0.1+`

    ```c++
    void Array<T>::reverse();
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    A.reverse();    // A = [3, 0, 1, 9, 6]
    ```

- Get Maximum value from Array `v.0.3+`

    ```c++
    T Array<T>::max(int From = 0, int To = 2147483647)
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    cout<<A.max()<<endl; // Will print 9
    // Getting Max from range A[2] to A[4] (both inclusive)
    cout<<A.max(2, -1)<<endl; // Will print 3
    ```

- Get Minimum value from Array `v.0.3+`

    ```c++
    T Array<T>::max(int From = 0, int To = 2147483647)
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 3};
    Array<int> A(V);
    cout<<A.min()<<endl; // Will print 0
    // Getting Max from range A[0] to A[2] (both inclusive)
    cout<<A.min(0, 2)<<endl; // Will print 1
    ```

- Get Arithmetic Average of Array `v.0.3+`

    ```c++
    double Array<T>::mean(int From = 0, int To = 2147483647)
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 4};
    Array<int> A(V);
    cout<<A.mean()<<endl; // Will print 4
    // Getting Mean from range A[0] to A[3] (both inclusive)
    cout<<A.mean(0, -2)<<endl; // Will print 4 = (6+9+1+0)/4
    ```

- Get Array Slice `v.0.3+`

    ```c++
    Array<T> Array<T>::slice(int From = 0, int To = 2147483647)
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 4};
    Array<int> A(V);
    A.slice().show(); // No parameters will print whole Array
    A.slice(1, -2).show(); // Will print [9, 1, 0]
    ```

- Sort an Array `v.0.3+`

    ```c++
    void Array<T>::sort(Order SOrder = ASC, int From = 0, int To = 2147483647)
    ```  

    Example:  

    ```c++
    std::vector<int> V = {6, 9, 1, 0, 4};
    Array<int> A(V);
    A.sort(); // No parameters will sort Array ascending
    A.show(); // Will print [0, 1, 4, 6, 9]
    A.sort(Order::DESC); // Will sort Array descending
    A.show(); // Will print [9, 6, 4, 1, 0]
    A.sort(Order::ASC, 1, -2); // Will sort ascending from A[1] to A[3] (both inclusive)
    A.show(); // Will print [9, 1, 4, 6, 0]
    ```

    > Ascending order: `Order::ASC = 1`  
    Descending order: `Order::DESC = -1`  
    **Important**: Sorting modifies the array itself

- Sort an Array using custom comparator function `v.0.3+`

    ```c++
    void Array<T>::sort(bool (*sorting_comparator)(T, T), int From = 0, int To = 2147483647)
    ```  

    Example:  

    ```c++
    bool CustomComp (int V1, int V2) {
        return V1 + V2 > 5; // Swap neighbor elements if sum is > 5 
    }
    ...
    std::vector<int> V = {6, 9, 1, 0, 4};
    Array<int> A(V);
    A.sort(CustomComp); // sort array using custom comparison
    /* Comparison working (using bubble sort):
    6, 9, 1, 0, 4
    ^--^
    9, 6, 1, 0, 4
       ^--^
    9, 1, 6, 0, 4
          ^--^
    9, 1, 0, 6, 4
             ^--^
    9, 1, 0, 4, 6
    ^--^
    1, 9, 0, 4, 6
       ^--^
    1, 0, 9, 4, 6
          ^--^
    1, 0, 4, 9, 6
    ^--^
       ^--^
    ^--^
    */
    A.show(); // Will print [1, 0, 4, 9, 6]
    ```

### 2.4. Arithmetic operations

#### 2.4.1. Array with constant

`v.0.1+`

Executes arithmetic operation with constant on **all** Array elements.  
Example Code:

```c++
std::vector<int> V = {6, 9, 1, 0, 3};
Array<int> A(V);
(A + 2).show(); // Will print: [8, 11, 3, 2, 5]
(A - 2).show(); // Will print: [4, 7, -1, -2, 1]
(A * 2).show(); // Will print: [12, 18, 2, 0, 6]
(A / 2).show(); // Will print: [3, 4, 0, 0, 1]
(A % 2).show(); // Will print: [0, 1, 1, 0, 1]
```

#### 2.4.2. Array with another Array

`v.0.1+`

```c++
std::vector<int> V = {6, 9, 1, 0, 3};
std::vector<int> V2 = {5, 2, 8, 9, 7, 2};
Array<int> A(V);
Array<int> B(V2);
(A + B).show(); // Will print: [11, 11, 9, 9, 10, 2]
(A - B).show(); // Will print: [1, 7, -7, -9, -4, -2]
(A * B).show(); // Will print: [30, 18, 9, 0, 21, 0]
(A / B).show(); // Will print: [1, 4, 0, 0, 0, 0]
(A % B).show(); // Will print: [1, 1, 1, 0, 3, 0]
```

> Important! If Arrays are unequal in length, empty space while operating on two arrays will be treated as 0. Therefore, dividing bigger array by smaller array will result in division by 0 (same thing for modulus).

#### 2.4.3. Modifying Array with constant

`v.0.1+`

```c++
std::vector<int> V = {6, 9, 1, 0, 3};
Array<int> A(V);
A += 2; // A = [8, 11, 3, 2, 5]
A -= 2; // A = [4, 7, -1, -2, 1]
A *= 2; // A = [12, 18, 2, 0, 6]
A /= 2; // A = [3, 4, 0, 0, 1]
A %= 2; // A = [0, 1, 1, 0, 1]
```

#### 2.4.4. Modifying Array with another Array

`v.0.1+`

```c++
std::vector<int> V = {6, 9, 1, 0, 3};
std::vector<int> V2 = {5, 2, 8, 9, 7, 2};
Array<int> A(V);
Array<int> B(V2);
A += B; // A = [11, 11, 9, 9, 10, 2]
A -= B; // A = [1, 7, -7, -9, -4, -2]
A *= B; // A = [30, 18, 9, 0, 21, 0]
A /= B; // A = [1, 4, 0, 0, 0, 0]
A %= B; // A = [1, 1, 1, 0, 3, 0]
```

> Important! These operations modify Array size. Read more [here](#242-array-with-another-array).

### 2.5. Array Masking

#### 2.5.1. ArrayMask Type

`v.0.1+`

```c++
typedef Array<bool> ArrayMask;
```

ArrayMask has specific purposes for selecting elements from Array aka masking.  
Masking is a process of translating regular Array to Mask, that contains only 1's and 0's, which are boolean results of checking condition (true/false), which applies to all of the elements of the Array.  
Masked Array contains only the elements that were assigned to 1, while checking boolean condition.

#### 2.5.2. Masking using ArrayMask

`v.0.1+`

```c++
Array<T>::masked(const ArrayMask &Mask);
```  

Example:  

```c++
std::vector<int> V = {6, 9, 1, 0, 3};
std::vector<bool> VM = {1, 0, 1, 0, 1};
Array<int> A(V);
Array<bool> Mask(VM);
A.masked(Mask).show(); // Will print [6, 1, 3]
```

> Note: `masked` method does **not** modifiy the Array.

#### 2.5.3 Masking using custom comparator

`v.0.1+`

```c++
Array<T>::masked(bool (*custom_comparator)(T));
```

`custom_comparator` must be a function, that passes as argument Array Element and returns **boolean** value.  
`masked` function will use `custom_comparator` as a function, that checks all of the elements in Array and return those for which `custom_comparator` returned **true**.

Example:

```c++
// Function returns true if Elem is greate than 5 or equal 0
bool custom_function (int Elem) {
    if (Elem == 0) return true;
    if (Elem > 5) return true;
    return false;
}
std::vector<int> V = {6, 9, 1, 0, 3};
Array<int> A(V);
A.masked(custom_function).show(); // Will print [6, 9, 0]
```

### 2.6. Array Mask operations

#### 2.6.1 Getting Mask comparing Array to constant

`v.0.1+`

```c++
std::vector<int> V = {6, 9, 1, 0, 3};
Array<int> A(V);
ArrayMask Mask;
Mask = (A == 3); // Mask = [0, 0, 0, 0, 1]
Mask = (A != 3); // Mask = [1, 1, 1, 1, 0]
Mask = (A >= 3); // Mask = [1, 1, 0, 0, 1]
Mask = (A <= 3); // Mask = [0, 0, 1, 1, 1]
Mask = (A > 3); // Mask = [1, 1, 0, 0, 0]
Mask = (A < 3); // Mask = [0, 0, 1, 1, 0]
```

#### 2.6.2 Getting Mask comparing Array to another Array

`v.0.1+`

```c++
std::vector<int> V = {6, 9, 1, 0, 3};
std::vector<int> V2 = {5, 2, 8, 9, 7, 2};
Array<int> A(V);
Array<int> B(V2);
ArrayMask Mask;
Mask = (A == B); // Mask = [0, 0, 0, 0, 0, 0]
Mask = (A != B); // Mask = [1, 1, 1, 1, 1, 1]
Mask = (A >= B); // Mask = [1, 1, 0, 0, 0, 0]
Mask = (A <= B); // Mask = [0, 0, 1, 1, 1, 1]
Mask = (A > B); // Mask = [1, 1, 0, 0, 0, 0]
Mask = (A < B); // Mask = [0, 0, 1, 1, 1, 1]
```

#### 2.6.3 Boolean operations on Array Masks

`v.0.1+`

```c++
std::vector<bool> VM = {0, 0, 1, 1};
std::vector<bool> VM2 = {0, 1, 0, 1, 1};
ArrayMask Mask1(VM);
ArrayMask Mask2(VM2);
ArrayMask Mask3;
Mask3 = !Mask1;         // Mask3 = [1, 1, 0, 0]
Mask3 = Mask1 | Mask2;  // Mask3 = [0, 1, 1, 1, 1]
Mask3 = Mask1 & Mask2;  // Mask3 = [0, 0, 0, 1, 0]
Mask3 = Mask1 ^ Mask2;  // Mask3 = [0, 1, 1, 0, 1]
```

#### 2.6.4 Boolean operations on Array Mask and constant

`v.0.1+`

```c++
std::vector<bool> VM = {0, 0, 1, 1};
ArrayMask Mask1(VM);
ArrayMask Mask2;
Mask2 = Mask1 | 1;  // Mask2 = [1, 1, 1, 1]
Mask2 = Mask1 & 0;  // Mask2 = [0, 0, 0, 0]
Mask2 = Mask1 ^ 1;  // Mask2 = [1, 1, 0, 0]
```

#### 2.6.5 Boolean operations modifying Array Mask

`v.0.1+`

```c++
std::vector<bool> VM = {0, 0, 1, 1};
std::vector<bool> VM2 = {0, 1, 0, 1, 1};
ArrayMask Mask1(VM);
ArrayMask Mask2(VM2);
Mask2 |= Mask1; // Mask2 = [0, 1, 1, 1, 1]
Mask2 &= Mask1; // Mask2 = [0, 0, 1, 1, 0]
Mask2 ^= Mask1; // Mask2 = [0, 0, 0, 0, 0]
```

## 3. Container Namespace

### 3.1. Show containers

`v.0.2+`  

Function `show` can display various containers along with their type and even nested containers.

Function parameters:  
First parameter is **always** a container. Can be dynamic array, Array Class object or STL Container.

> **Important**: For dynamic arrays next parameters should be their sizes.

Second parameter is optional boolean `showType` by default set to false. If set manually to true it will display container type before printing its contents.

Typical Examples:

```c++
int* D = new int[4];
for (int i = 0; i < 4; i++) D[i] = i;
Container::show(D, 4); // Will print [0, 1, 2, 3]
Container::show(D, 4, true); // Will print `DynArray` [0, 1, 2, 3]
int **D2 = new int*[2];
for (int i = 0; i < 2; i++) D2[i] = new int[2];
for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) D2[i][j] = i+j;
Container::show(D2, 2, 2); // Will print [[0, 1], [1, 2]]
std::vector<int> V = {0, 1, 2, 3};
Container::show(V, true); // Will print `Vector` [0, 1, 2, 3]
std::list<int> L = {0, 1, 2, 3};
Container::show(L, true); // Will print `List` [0, 1, 2, 3]
std::set<int> S = {0, 1, 2, 3};
Container::show(S, true); // Will print `Set` {0, 1, 2, 3}
std::map <char, int> M;
for (int i = 0; i < 3; i++) M.insert(make_pair((char) (i + 65), i));
Container::show(M, true); // Will print `Map` {A: 0, B: 1, C: 2}
Array<int> A(V);
Container::show(A, true); // Will print `Array` [0, 1, 2, 3]
```

## 4. Converter Namespace

### 4.1. Convert Array to other containers

`v.0.2+`

Converter Namespace provides functions that can convert Array class object to: Vector, List, Set or Dynamic Array.
> Note: While converting to dynamic array, its size is passed by reference as second function parameter.  
Conversion to set will remove duplicates and order the array.

Two Arrays can be used as keys and values to create a map.
> **Important!**: Conversion to map requires Key and Value Array to have **the same size**  

Examples:

```c++
std::vector<int> Init = {1, 2, 3, 4};
std::vector<int> Init2 = {'A', 'B', 'C', 'D'};
Array<int> A(Init);
// Conversion to STL List
std::list<int> = Converter::toList(A);
// Conversion to STL Set
std::set<int> = Converter::toSet(A);
// Conversion to STL Vector
std::vector<int> = Converter::toVector(A);
int* DynArr;
int DynArr_size;
// Conversion to dynamic Array
DynArr = Converter::toDynArray(A, DynArr_size);
Array<int> Keys(Init2);
// Conversion to STL Map: {A: 1, B: 2, C: 3, D: 4}
std::map<char, int> = Converter::toMap(Keys, A);
```

## 5. Changelog

### Release-0.3

Changed functions containg `From` and `To` parameters from overloaded to single ones using default parameters. Now `From` by default will be 0 and `To` will be set to last Array index.  
Added `max()`, `min()`, `slice()` and `sort()`.  
Invalid `From - To` range will now throw an exception.

### Release-0.2

Added new constructor, that creates Array object using STL Set.  
Added [Container namespace](#3-container-namespace) with `show` functions to display various containers.  
Added [Converter namespace](#4-converter-namespace), which contains functions that can convert Array object to other containers.

### Release-0.1

Created [class Array](#2-class-array) with all necessary methods and operators.  
This is the first release.
