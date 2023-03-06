# Better Array C++

## 1. Overview

### 1.1. General Information

Better Array is a library written in C++ used to improve operating on array-like objects by adding bunch of methods, operations and masking. It is based on STL containers and supports STL array-like types.  
NDArray is a library extension for Better Array to implement n-dimensional array-like structure with built-in methods and operations.

> **Very Important!** Library has been written and tested using C++ 11. Author takes **no** responsibility of library malfunction on **older** versions of C++.

### 1.2. Author

Library content has been fully written by DingoMC. Distributed on GitHub with GNU/GPL license.  
Link to my website [here](https://www.dingomc.net).  
Any suggestions to improve this library can be sent via [E-mail](https://www.dingomc.net/contact.html).

### 1.3. Other

Files: better_array.h, ndarray.h  
Latest Version: [0.8](#release-08)  
Created on: 11th Nov 2022  
Latest Update: 06th Mar 2023  
Testing Files: test.cpp, test_ndarray.cpp  
G++ Additional Compiler Flags: `-static-libstdc++`, `-std=c++17`

## 2. Documentation

Documentation for better_array.h can be found [here](https://www.dingomc.net/documentation/better_array.html)
Documentation for ndarray.h can be found [here](https://www.dingomc.net/documentation/ndarray.html)

## 3. Changelog

### Release-0.8

Created new library ndarray.h with class NDArray implementing multi-dimensional array structure.  
Minor bugfixes and changes in better_array.h.

### Release-0.7

Added new constructor using initializer list.  
`append()`, `insert()`, `contains()`, `find()` and `findAll()` support now initializer list.  
Added `argmax()`, `argmin()` and `unique()`.

### Release-0.6

Added `findAll()` for values and sub-arrays.  
Added Files namespace containing operation on Files with Arrays.

### Release-0.5

Replaced `find()` with `contains()` with additional Sub-Array search.  
`findIndex()` is now `find()` and also supports Sub-Array search.  
Added converter between Char Array and String.

### Release-0.4

Added `fill()`, `replace()`, `count()`, `find()`, `findIndex()`.

### Release-0.3

Changed functions containg `From` and `To` parameters from overloaded to single ones using default parameters. Now `From` by default will be 0 and `To` will be set to last Array index.  
Added `max()`, `min()`, `slice()` and `sort()`.  
Invalid `From - To` range will now throw an exception.

### Release-0.2

Added new constructor, that creates Array object using STL Set.  
Added Container namespace with `show` functions to display various containers.  
Added Converter namespace, which contains functions that can convert Array object to other containers.

### Release-0.1

Created class Array with all necessary methods and operators.  
This is the first release.
