/**
 * @file better_array.h
 * @author DingoMC (www.dingomc.net)
 * @brief Better Arrays for C++. Manage array calculations in more modern and convenient way.
 * @version 0.8
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) DingoMC Systems 2022
 * @warning Library written and tested on C++11. Using older C++ Versions may cause malfunction!
 * @note Full documentation https://dingomc.net/documentation/better_array.html
 */
#ifndef BETTER_ARRAY_H
#define BETTER_ARRAY_H
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <list>
#include <set>
#include <map>
#pragma GCC optimize("O3")
#define MAX_S(a, b) a > b ? a : b
#define ArrayBegin 0                // Min index available
#define ArrayEnd 2147483647         // Max index available
using namespace std;
template <class T> class Array;     // Main Array Class
typedef Array<bool> ArrayMask;      // ArrayMask as Array<bool>
enum Order {ASC = 1, DESC = -1};    // Sorting Order
enum Direction {TOP = 0, BOTTOM = 1, RIGHT = 2, LEFT = 3}; // Expansion Direction
/**
 * @brief Container namespace for printing functions
 */
namespace Container {
    // Printing Functions
    template<class T> void show(T Elem, bool = false, bool = false);
    template<class T> void show(T* Array, int, bool showType = false, bool = false);
    template<class T> void show(T** Array, int, int, bool showType = false, bool = false);
    template<class T> void show(const Array < T > &Arr, bool showType = false, bool = false);
    template<class T> void show(const vector < T > &STL_Vec, bool showType = false, bool = false);
    template<class T> void show(const list < T > &STL_List, bool showType = false, bool = false);
    template<class T> void show(const set < T > &STL_Set, bool showType = false, bool = false);
    template<class T, class U> void show(const map<T, U> &Map, bool showType = false, bool = false);
    template <class T> void show (T Elem, bool showType, bool fromRecursion) {cout<<Elem;}
    template <class T> void show (T* Array, int arraySize, bool showType, bool fromRecursion) {
        if (arraySize < 0) throw std::invalid_argument("arraySize must be a positive integer!");
        if (showType) cout<<"`DynArray` ";
        cout<<"[";
        for (unsigned i = 0; i < arraySize; i++) {
            show(Array[i], showType, true);
            if (i < arraySize - 1) cout<<", ";
        }
        cout<<"]";
        if (!fromRecursion) cout<<endl;
    }
    template<class T> void show (T** Array, int arraySize1, int arraySize2, bool showType, bool fromRecursion) {
        if (arraySize1 < 0 || arraySize2 < 0) throw std::invalid_argument("arraySize must be a positive integer!");
        if (showType) cout<<"`DynArray` ";
        cout<<"[";
        for (unsigned i = 0; i < arraySize1; i++) {
            show(Array[i], arraySize2, showType, true);
            if (i < arraySize1 - 1) cout<<", ";
        }
        cout<<"]";
        if (!fromRecursion) cout<<endl;
    }
    template<class T> void show (const Array < T > &Arr, bool showType, bool fromRecursion) {
        unsigned A_size = Arr.size();
        if (showType) cout<<"`Array` ";
        cout<<"[";
        for (unsigned i = 0; i < A_size; i++) {
            show(Arr[i], showType, true);
            if (i < A_size - 1) cout<<", ";
        }
        cout<<"]";
        if (!fromRecursion) cout<<endl;
    }
    template<class T> void show (const vector < T > &STL_Vec, bool showType, bool fromRecursion) {
        unsigned V_size = STL_Vec.size();
        if (showType) cout<<"`Vector` ";
        cout<<"[";
        for (unsigned i = 0; i < V_size; i++) {
            show(STL_Vec[i], showType, true);
            if (i < V_size - 1) cout<<", ";
        }
        cout<<"]";
        if (!fromRecursion) cout<<endl;
    }
    template<class T> void show (const list < T > &STL_List, bool showType, bool fromRecursion) {
        if (showType) cout<<"`List` ";
        cout<<"[";
        for (auto it = STL_List.cbegin(); it != STL_List.cend(); it++) {
            if (it != STL_List.cbegin()) cout<<", ";
            show(*it, showType, true);
        }
        cout<<"]";
        if (!fromRecursion) cout<<endl;
    }
    template<class T> void show (const set < T > &STL_Set, bool showType, bool fromRecursion) {
        if (showType) cout<<"`Set` ";
        cout<<"{";
        for (auto it = STL_Set.cbegin(); it != STL_Set.cend(); it++) {
            if (it != STL_Set.cbegin()) cout<<", ";
            show(*it, showType, true);
        }
        cout<<"}";
        if (!fromRecursion) cout<<endl;
    }
    template<class T, class U> void show(const map<T, U> &Map, bool showType, bool fromRecursion) {
        if (showType) cout<<"`Map` ";
        cout<<"{";
        for (typename map<T, U>::const_iterator it = Map.begin(); it != Map.end(); ++it) {
            if (it != Map.cbegin()) cout<<", ";
            show(it->first, showType, true);
            cout<<": ";
            show(it->second, showType, true);
        }
        cout<<"}";
        if (!fromRecursion) cout<<endl;
    }
}
template <class T>
// Main Array Class
class Array {
    private:
        vector < T > A;
        unsigned S;
        int Idx (int index) const {
            if (index < -(int) (this->S) || index >= (int) this->S) throw std::invalid_argument("Invalid Array Index!");
            if (index >= 0) return index;
            return index + (int) this->S;
        }
        void CheckRange (int From, int To) {
            int width = Idx(To) - Idx(From) + 1;
            if (width < 1 || width > (int) this->S) throw std::invalid_argument("Invalid From-To Range");
            return;
        }
    public:
        // CONSTRUCTORS
        /**
         * @brief Construct a new empty Array object
         * 
         */
        Array () {
            this->S = 0;
        }
        /**
         * @brief Construct a new empty Array object with given size
         * 
         * @param s Size of new array
         */
        explicit Array (unsigned s) {
            this->S = s;
            this->A.resize(this->S);
        }
        /**
         * @brief Construct a new Array object using Vector
         * 
         * @param STL_Vector Initializing Vector
         */
        explicit Array (const vector < T > &STL_Vector) {
            this->S = STL_Vector.size();
            this->A.resize(this->S);
            for (unsigned i = 0; i < this->S; i++) this->A[i] = STL_Vector[i];
        }
        /**
         * @brief Construct a new Array object using List
         * 
         * @param STL_List Initializing List
         */
        explicit Array (const list < T > &STL_List) {
            this->S = STL_List.size();
            for (auto it = STL_List.cbegin(); it != STL_List.cend(); it++) this->A.push_back(*it);
        }
        /**
         * @brief Construct a new Array object using dynamic Array
         * 
         * @param dynamicArray Dynamic Array
         * @param arraySize Array Size
         */
        Array (const T* dynamicArray, unsigned arraySize) {
            this->S = arraySize;
            this->A.resize(this->S);
            for (unsigned i = 0; i < this->S; i++) this->A[i] = dynamicArray[i];
        }
        /**
         * @brief Construct a new Array object using Set
         * 
         * @param STL_Set Initializing Set
         */
        explicit Array (const set < T > &STL_Set) {
            this->S = STL_Set.size();
            for (auto it = STL_Set.cbegin(); it != STL_Set.cend(); it++) this->A.push_back(*it);
        }
        /**
         * @brief Construct a new Array object using Initializer List
         * 
         * @param InitValues Initial values
         */
        explicit Array (initializer_list<T> InitValues) {
            this->S = 0;
            this->A.resize(this->S);
            for (auto it = InitValues.begin(); it != InitValues.end(); ++it) {
                this->S++;
                this->A.push_back(*it);
            }
        }
        // FUNCTIONS
        /**
         * @brief Get the size of an Array
         * @return unsigned Size
         */
        unsigned size () {return this->S;}
        unsigned size () const {return S;}
        /**
         * @brief Show Array
         * @param showType Default to false: If true - it additionally shows type
         */
        void show (bool showType = false) {
            Container::show(Array<T>(this->A), showType);
        }
        /**
         * @brief Add element to the end of an Array
         * @param Elem 
         */
        void append (const T& Elem) {
            this->S++;
            this->A.push_back(Elem);
        }
        /**
         * @brief Add another Array to the end of an Array
         * @param arr 
         */
        void append (Array <T> arr) {
            for (unsigned i = 0; i < arr.size(); i++) {
                this->S++;
                this->A.push_back(arr[i]);
            }
        }
        /**
         * @brief Add values to the end of an Array
         * 
         * @param Values Initializer list
         */
        void append (initializer_list<T> Values) {
            for (auto it = Values.begin(); it != Values.end(); ++it) {
                this->S++;
                this->A.push_back(*it);
            }
        }
        /**
         * @brief Remove last element from an Array
         */
        void pop () {
            if (this->S > 0) {
                this->S--;
                this->A.pop_back();
            }
        }
        /**
         * @brief Insert element in n-th index to Array
         * @param Where n-th index (negative index supported)
         * @param Elem
         */
        void insert (int Where, T Elem) {
            this->S++;
            this->A.insert(this->A.begin() + Idx(Where), Elem);
        }
        /**
         * @brief Insert another Array begging from n-th index to Array
         * @param Where n-th index (negative index supported)
         * @param arr Array
         */
        void insert (int Where, Array<T> arr) {
            for (int i = 0; i < arr.size(); i++) {
                this->S++;
                this->A.insert(this->A.begin() + Idx(Where) + i, arr[i]);
            }
        }
        void insert (int Where, initializer_list<T> Values) {
            int i = 0;
            for (auto it = Values.begin(); it != Values.end(); ++it) {
                this->S++;
                this->A.insert(this->A.begin() + Idx(Where) + i, *it);
                i++;
            }
        }
        /**
         * @brief Remove element at n-th index from Array
         * @param Which n-th index (negative index supported)
         */
        void erase (int Which) {
            if (this->S > 0) {
                this->A.erase(this->A.begin() + Idx(Which));
                this->S--;
            }
        }
        /**
         * @brief Remove elements begging from i-th index to j-th index (both inclusive)
         * @param From i-th index (negative index supported)
         * @param To j-th index (negative index supported, j >= i)
         */
        void erase (int From, int To) {
            CheckRange(From, To);
            int width = Idx(To) - Idx(From) + 1;
            for (int i = 0; i < width; i++) {
                this->A.erase(this->A.begin() + Idx(From));
                this->S--;
            }
        }
        /**
         * @brief Reverse elements in Array
         */
        void reverse () {
            for (unsigned i = 0; i < this->S / 2; i++) {
                swap(this->A[i], this->A[this->S - i - 1]);
            }
        }
        /**
         * @brief Mask Array values using boolean mask
         * @param Mask vector<bool> type mask
         * @return Array<T> Masked Array
         */
        Array<T> masked (const ArrayMask &Mask) {
            Array<T> X;
            for (unsigned i = 0; i < this->S; i++) {
                if (i >= Mask.size()) X.append(this->A[i]);
                else {
                    if (Mask[i]) X.append(this->A[i]);
                }
            }
            return X;
        }
        /**
         * @brief Mask Array values using using custom comparator function
         * @param custom_comparator Comparator function. Must return bool, must have one argument (which is considered as array element)
         * @return Array<T> Masked Array
         */
        Array<T> masked (bool (*custom_comparator)(T)) {
            Array<T> X;
            for (unsigned i = 0; i < this->S; i++) {
                if (custom_comparator(this->A[i])) X.append(this->A[i]);
            }
            return X;
        }
        /**
         * @brief Get maximum value of Array
         * @param From Starting Index (Inclusive). Default to 0
         * @param To End Index (Inclusive). Default to Array End
         * @return T MAX
         */
        T max (int From = ArrayBegin, int To = ArrayEnd) {
            if (To == ArrayEnd && (int) this->S < ArrayEnd) To = this->S - 1;
            CheckRange(From, To);
            T M = this->A[Idx(From)];
            for (unsigned i = Idx(From) + 1; i <= Idx(To); i++) if (this->A[i] > M) M = this->A[i];
            return M;
        }
        /**
         * @brief Get minimum value of Array
         * @param From Starting Index (Inclusive). Default to 0
         * @param To End Index (Inclusive). Default to Array End
         * @return T MIN
         */
        T min (int From = ArrayBegin, int To = ArrayEnd) {
            if (To == ArrayEnd && (int) this->S < ArrayEnd) To = this->S - 1;
            CheckRange(From, To);
            T M = this->A[Idx(From)];
            for (unsigned i = Idx(From) + 1; i <= Idx(To); i++) if (this->A[i] < M) M = this->A[i];
            return M;
        }
        /**
         * @brief Get indices of maximum values in Array
         * @param From Starting Index (Inclusive). Default to 0
         * @param To End Index (Inclusive). Default to Array End
         * @return Array<int> Maximum indices Array
         */
        Array<int> argmax (int From = ArrayBegin, int To = ArrayEnd) {
            if (To == ArrayEnd && (int) this->S < ArrayEnd) To = this->S - 1;
            CheckRange(From, To);
            T M = this->max(From, To);
            Array<int> X;
            for (unsigned i = Idx(From); i <= Idx(To); i++) if (this->A[i] == M) X.append(i);
            return X;
        }
        /**
         * @brief Get indices of minimum values in Array
         * @param From Starting Index (Inclusive). Default to 0
         * @param To End Index (Inclusive). Default to Array End
         * @return Array<int> Minimum indices Array
         */
        Array<int> argmin (int From = ArrayBegin, int To = ArrayEnd) {
            if (To == ArrayEnd && (int) this->S < ArrayEnd) To = this->S - 1;
            CheckRange(From, To);
            T M = this->min(From, To);
            Array<int> X;
            for (unsigned i = Idx(From); i <= Idx(To); i++) if (this->A[i] == M) X.append(i);
            return X;
        }
        /**
         * @brief Get average of Array
         * @param From Starting Index (Inclusive). Default to 0
         * @param To End Index (Inclusive). Default to Array End
         * @return double Average
         */
        double mean (int From = ArrayBegin, int To = ArrayEnd) {
            if (To == ArrayEnd && (int) this->S < ArrayEnd) To = this->S - 1;
            CheckRange(From, To);
            double M = 0.0;
            int range = Idx(To) - Idx(From) + 1;
            for (unsigned i = Idx(From); i <= Idx(To); i++) M += (double) this->A[i];
            return M / (double) (range);
        }
        /**
         * @brief Get Array Slice
         * @param From Starting Index (Inclusive). Default to 0
         * @param To End Index (Inclusive). Default to Array End
         * @return Array<T> Array Slice
         */
        Array<T> slice (int From = ArrayBegin, int To = ArrayEnd) {
            if (To == ArrayEnd && (int) this->S < ArrayEnd) To = this->S - 1;
            CheckRange(From, To);
            Array<T> X;
            for (unsigned i = Idx(From); i <= Idx(To); i++) X.append(this->A[i]);
            return X;
        }
        /**
         * @brief Sorts an Array
         * @param SOrder ASCending = 1, DESCending = -1. Default ASC
         * @param From Starting Index (Inclusive). Default to 0
         * @param To End Index (Inclusive). Default to Array End
         */
        void sort (Order SOrder = ASC, int From = ArrayBegin, int To = ArrayEnd) {
            if (To == ArrayEnd && (int) this->S < ArrayEnd) To = this->S - 1;
            unsigned i_max = Idx(To) - Idx(From);
            for (unsigned i = 0; i < i_max; i++) {
                bool swapped = false;
                for (unsigned j = Idx(From); j < Idx(To) - i; j++) {
                    if ((SOrder == ASC && this->A[j] > this->A[j+1]) || (SOrder == DESC && this->A[j] < this->A[j+1])) {
                        swap(this->A[j], this->A[j+1]);
                        swapped = true;
                    }
                }
                if (!swapped) break;
            }
        }
        /**
         * @brief Sorts an Array using custom comparison function
         * @param sorting_comparator Comparator function. Must return bool, must have two arguments (which are first and second element in order)
         * @param From Starting Index (Inclusive). Default to 0
         * @param To End Index (Inclusive). Default to Array End
         */
        void sort (bool (*sorting_comparator)(T, T), int From = ArrayBegin, int To = ArrayEnd) {
            if (To == ArrayEnd && (int) this->S < ArrayEnd) To = this->S - 1;
            unsigned i_max = Idx(To) - Idx(From);
            for (unsigned i = 0; i < i_max; i++) {
                bool swapped = false;
                for (unsigned j = Idx(From); j < Idx(To) - i; j++) {
                    if (sorting_comparator(this->A[j], this->A[j+1])) {
                        swap(this->A[j], this->A[j+1]);
                        swapped = true;
                    }
                }
                if (!swapped) break;
            }
        }
        /**
         * @brief Fill Array with values
         * @param Val Constant
         * @param From Starting Index (Inclusive). Default to 0
         * @param To End Index (Inclusive). Default to Array End
         */
        void fill (const T& Val, int From = ArrayBegin, int To = ArrayEnd) {
            if (To == ArrayEnd && (int) this->S < ArrayEnd) To = this->S - 1;
            for (unsigned i = Idx(From); i <= Idx(To); i++) this->A[i] = Val;
        }
        /**
         * @brief Replace all values in Array with new ones
         * @param Val_Which Value to be replaced
         * @param Val_With New Value
         */
        void replace (const T& Val_Which, const T& Val_With) {
            for (unsigned i = 0; i < this->S; i++) if (this->A[i] == Val_Which) this->A[i] = Val_With;
        }
        /**
         * @brief Returns value count in an Array
         * @param Count_Val Counted Value
         * @return unsigned Value Count
         */
        unsigned count (const T& Count_Val) {
            unsigned cnt = 0;
            for (unsigned i = 0; i < this->S; i++) if (this->A[i] == Count_Val) cnt++;
            return cnt;
        }
        /**
         * @brief Check if Array contains a value
         * @param Val Value to be searched for
         * @return true - Value found
         * @return false - Value not found
         */
        bool contains (const T& Val) {
            for (unsigned i = 0; i < this->S; i++) if (this->A[i] == Val) return true;
            return false;
        }
        /**
         * @brief Check if Array contains Sub-Array
         * @param SubArray Sub-Array to be searched for
         * @return true - Sub-Array found
         * @return false - Sub-Array not found
         */
        bool contains (const Array <T> &SubArray) {
            if (this->S < SubArray.S) return false;
            int current_search = 0;
            for (unsigned i = 0; i < this->S; i++) {
                if (this->A[i] == SubArray[current_search]) current_search++;
                else current_search = 0;
                if (current_search == SubArray.S) return true;
            }
            return false;
        }
        /**
         * @brief Check if Array contains values in order
         * 
         * @param Values Values to be searched for
         * @return true
         * @return false 
         */
        bool contains (initializer_list<T> Values) {
            if (this->S < Values.size()) return false;
            Array<T> SubArray(Values);
            int current_search = 0;
            for (unsigned i = 0; i < this->S; i++) {
                if (this->A[i] == SubArray[current_search]) current_search++;
                else current_search = 0;
                if (current_search == SubArray.S) return true;
            }
            return false;
        }
        /**
         * @brief Find array index of first value occurance
         * @param Val Value to be searched for
         * @return int - first found index, if not found it returns ArrayEnd = 2147483647
         */
        int find (const T& Val) {
            for (unsigned i = 0; i < this->S; i++) if (this->A[i] == Val) return i;
            return ArrayEnd;
        }
        /**
         * @brief Find array index of first Sub-Array occurance
         * @param SubArray Sub-Array to be searched for
         * @return int - first found index, if not found it returns ArrayEnd = 2147483647
         */
        int find (const Array <T> &SubArray) {
            if (this->S < SubArray.S);
            int current_search = 0, found_index = 0;
            for (unsigned i = 0; i < this->S; i++) {
                if (current_search == 0) found_index = i;
                if (this->A[i] == SubArray[current_search]) current_search++;
                else current_search = 0;
                if (current_search == SubArray.S) return found_index;
            }
            return ArrayEnd;
        }
        /**
         * @brief Find array index of first values list occurance
         * @param Values Values list to be searched for
         * @return int - first found index, if not found it returns ArrayEnd = 2147483647
         */
        int find (initializer_list<T> Values) {
            if (this->S < Values.size()) return false;
            Array<T> SubArray(Values);
            int current_search = 0, found_index = 0;
            for (unsigned i = 0; i < this->S; i++) {
                if (current_search == 0) found_index = i;
                if (this->A[i] == SubArray[current_search]) current_search++;
                else current_search = 0;
                if (current_search == SubArray.S) return found_index;
            }
            return ArrayEnd;
        }
        /**
         * @brief Find all array indices where value occurs
         * @param Val Value to be searched for
         * @return Array<int> Array of indices
         */
        Array<int> findAll (const T& Val) {
            Array<int> X;
            for (unsigned i = 0; i < this->S; i++) if (this->A[i] == Val) X.append(i);
            return X;
        }
        /**
         * @brief Find all array indices where sub-array begins
         * @param SubArray Sub-Array to be searched for
         * @return Array<int> Array of indices
         */
        Array<int> findAll (const Array <T> &SubArray) {
            Array<int> X;
            if (this->S < SubArray.S) return X;
            int current_search = 0, iter_index = 0;
            for (unsigned i = 0; i < this->S; i++) {
                if (current_search == 0) iter_index = i;
                if (this->A[i] == SubArray[current_search]) current_search++;
                else current_search = 0;
                if (current_search == SubArray.S) {
                    X.append(iter_index);
                    current_search = 0;
                }
            }
            return X;
        }
        /**
         * @brief Find all array indices where value list begins
         * @param Values Value list to be searched for
         * @return Array<int> Array of indices
         */
        Array<int> findAll (initializer_list<T> Values) {
            Array<int> X;
            if (this->S < Values.size()) return X;
            Array<T> SubArray(Values);
            int current_search = 0, iter_index = 0;
            for (unsigned i = 0; i < this->S; i++) {
                if (current_search == 0) iter_index = i;
                if (this->A[i] == SubArray[current_search]) current_search++;
                else current_search = 0;
                if (current_search == SubArray.S) {
                    X.append(iter_index);
                    current_search = 0;
                }
            }
            return X;
        }
        /**
         * @brief Return Array with removed duplicates
         * @return Array<T> 
         */
        Array<T> unique () {
            Array<T> X;
            for (unsigned i = 0; i < this->S; i++) {
                if (!X.contains(this->A[i])) X.append(this->A[i]);
            }
            return X;
        }
        /*
            OPERATORS OVERLOADING
        */
        // Non-accessible and accessible subscripts
        T& operator[] (int index) {return A[Idx(index)];}
        T operator[] (int index) const {return A.at(Idx(index));}

        // Arithmetic operations with constants (keeping the Array)
        Array<T> operator+ (const T& Num) const {
            Array <T> X(this->S);
            for (unsigned i = 0; i < this->S; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += this->A[i] + Num;
            return X;
        }
        Array<T> operator- (const T& Num) const {
            Array <T> X(this->S);
            for (unsigned i = 0; i < this->S; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += this->A[i] - Num;
            return X;
        }
        Array<T> operator* (const T& Num) const {
            Array <T> X(this->S);
            for (unsigned i = 0; i < this->S; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += (this->A[i] * Num);
            return X;
        }
        Array<T> operator/ (const T& Num) const {
            Array <T> X(this->S);
            for (unsigned i = 0; i < this->S; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += (this->A[i] / Num);
            return X;
        }
        Array<T> operator% (const T& Num) const {
            Array <T> X(this->S);
            for (unsigned i = 0; i < this->S; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += (this->A[i] % Num);
            return X;
        }
        // Arithmetic operations with arrays (keeping the Arrays)
        Array<T> operator+ (const Array<T>& Arr) const {
            unsigned max_size = MAX_S(this->S, Arr.S);
            Array <T> X(max_size);
            for (unsigned i = 0; i < max_size; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += this->A[i];
            for (unsigned i = 0; i < Arr.S; i++) X[i] += Arr[i];
            return X;
        }
        Array<T> operator- (const Array<T>& Arr) const {
            unsigned max_size = MAX_S(this->S, Arr.S);
            Array <T> X(max_size);
            for (unsigned i = 0; i < max_size; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += this->A[i];
            for (unsigned i = 0; i < Arr.S; i++) X[i] -= Arr[i];
            return X;
        }
        Array<T> operator* (const Array<T>& Arr) const {
            unsigned max_size = MAX_S(this->S, Arr.S);
            Array <T> X(max_size);
            for (unsigned i = 0; i < max_size; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += this->A[i];
            for (unsigned i = 0; i < Arr.S; i++) X[i] *= Arr[i];
            return X;
        }
        Array<T> operator/ (const Array<T>& Arr) const {
            unsigned max_size = MAX_S(this->S, Arr.S);
            Array <T> X(max_size);
            for (unsigned i = 0; i < max_size; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += this->A[i];
            for (unsigned i = 0; i < Arr.S; i++) X[i] /= Arr[i];
            return X;
        }
        Array<T> operator% (const Array<T>& Arr) const {
            unsigned max_size = MAX_S(this->S, Arr.S);
            Array <T> X(max_size);
            for (unsigned i = 0; i < max_size; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += this->A[i];
            for (unsigned i = 0; i < Arr.S; i++) X[i] %= Arr[i];
            return X;
        }
        // Arithmetic operations with constants (modifying the Array)
        Array<T> operator+= (const T& Num) {
            for (unsigned i = 0; i < this->S; i++) this->A[i] += Num;
            return Array<T>(this->A);
        }
        Array<T> operator-= (const T& Num) {
            for (unsigned i = 0; i < this->S; i++) this->A[i] -= Num;
            return Array<T>(this->A);
        }
        Array<T> operator*= (const T& Num) {
            for (unsigned i = 0; i < this->S; i++) this->A[i] *= Num;
            return Array<T>(this->A);
        }
        Array<T> operator/= (const T& Num) {
            for (unsigned i = 0; i < this->S; i++) this->A[i] /= Num;
            return Array<T>(this->A);
        }
        Array<T> operator%= (const T& Num) {
            for (unsigned i = 0; i < this->S; i++) this->A[i] %= Num;
            return Array<T>(this->A);
        }
        // Arithmetic operations with other arrays (modifying the first Array)
        Array<T> operator+= (const Array<T> &Arr) {
            for (unsigned i = this->S; i < Arr.S; i++) append(0);
            for (unsigned i = 0; i < Arr.S; i++) this->A[i] += Arr[i];
            return Array<T>(this->A);
        }
        Array<T> operator-= (const Array<T> &Arr) {
            for (unsigned i = this->S; i < Arr.S; i++) append(0);
            for (unsigned i = 0; i < Arr.S; i++) this->A[i] -= Arr[i];
            return Array<T>(this->A);
        }
        Array<T> operator*= (const Array<T> &Arr) {
            for (unsigned i = this->S; i < Arr.S; i++) append(0);
            for (unsigned i = 0; i < Arr.S; i++) this->A[i] *= Arr[i];
            return Array<T>(this->A);
        }
        Array<T> operator/= (const Array<T> &Arr) {
            for (unsigned i = this->S; i < Arr.S; i++) append(0);
            for (unsigned i = 0; i < Arr.S; i++) this->A[i] /= Arr[i];
            return Array<T>(this->A);
        }
        Array<T> operator%= (const Array<T> &Arr) {
            for (unsigned i = this->S; i < Arr.S; i++) append(0);
            for (unsigned i = 0; i < Arr.S; i++) this->A[i] %= Arr[i];
            return Array<T>(this->A);
        }
        // Array Masking with comparison operators (comparing to constant)
        ArrayMask operator== (const T& Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] == Value_1);
            return X;
        }
        ArrayMask operator>= (const T& Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] >= Value_1);
            return X;
        }
        ArrayMask operator<= (const T& Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] <= Value_1);
            return X;
        }
        ArrayMask operator> (const T& Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] > Value_1);
            return X;
        }
        ArrayMask operator< (const T& Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] < Value_1);
            return X;
        }
        ArrayMask operator!= (const T& Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] != Value_1);
            return X;
        }
        // Array Masking with comparison operators (comparing to another array)
        ArrayMask operator== (const Array<T> &Arr) {
            ArrayMask X;
            unsigned max_size = MAX_S(this->S, Arr.S);
            for (unsigned i = 0; i < max_size; i++) {
                if (i >= this->S || i >= Arr.S) X.append(false);
                else X.append(this->A[i] == Arr[i]);
            }
            return X;
        }
        ArrayMask operator>= (const Array<T> &Arr) {
            ArrayMask X;
            unsigned max_size = MAX_S(this->S, Arr.S);
            for (unsigned i = 0; i < max_size; i++) {
                if (i >= this->S || i >= Arr.S) X.append(false);
                else X.append(this->A[i] >= Arr[i]);
            }
            return X;
        }
        ArrayMask operator<= (const Array<T> &Arr) {
            ArrayMask X;
            unsigned max_size = MAX_S(this->S, Arr.S);
            for (unsigned i = 0; i < max_size; i++) {
                if (i >= this->S || i >= Arr.S) X.append(false);
                else X.append(this->A[i] <= Arr[i]);
            }
            return X;
        }
        ArrayMask operator> (const Array<T> &Arr) {
            ArrayMask X;
            unsigned max_size = MAX_S(this->S, Arr.S);
            for (unsigned i = 0; i < max_size; i++) {
                if (i >= this->S || i >= Arr.S) X.append(false);
                else X.append(this->A[i] > Arr[i]);
            }
            return X;
        }
        ArrayMask operator< (const Array<T> &Arr) {
            ArrayMask X;
            unsigned max_size = MAX_S(this->S, Arr.S);
            for (unsigned i = 0; i < max_size; i++) {
                if (i >= this->S || i >= Arr.S) X.append(false);
                else X.append(this->A[i] < Arr[i]);
            }
            return X;
        }
        ArrayMask operator!= (const Array<T> &Arr) {
            ArrayMask X;
            unsigned max_size = MAX_S(this->S, Arr.S);
            for (unsigned i = 0; i < max_size; i++) {
                if (i >= this->S || i >= Arr.S) X.append(false);
                else X.append(this->A[i] != Arr[i]);
            }
            return X;
        }
        // Boolean operators for Array Masks (Keeping inital ArrayMasks)
        ArrayMask operator! () const {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(!this->A[i]);
            return X;
        }
        ArrayMask operator| (const ArrayMask &Mask) const {
            unsigned max_size = MAX_S(this->S, Mask.S);
            ArrayMask X(max_size);
            for (unsigned i = 0; i < max_size; i++) X.A[i] = false;
            for (unsigned i = 0; i < this->S; i++) X.A[i] = (bool) X.A[i] | (bool) A[i];
            for (unsigned i = 0; i < Mask.S; i++) X.A[i] = (bool) X.A[i] | (bool) Mask.A[i];
            return X;
        }
        ArrayMask operator& (const ArrayMask &Mask) const {
            unsigned max_size = MAX_S(this->S, Mask.S);
            ArrayMask X(max_size);
            for (unsigned i = 0; i < max_size; i++) X.A[i] = false;
            for (unsigned i = 0; i < this->S; i++) X.A[i] = (bool) X.A[i] & (bool) A[i];
            for (unsigned i = 0; i < Mask.S; i++) X.A[i] = (bool) X.A[i] & (bool) Mask.A[i];
            return X;
        }
        ArrayMask operator^ (const ArrayMask &Mask) const {
            unsigned max_size = MAX_S(this->S, Mask.S);
            ArrayMask X(max_size);
            for (unsigned i = 0; i < max_size; i++) X.A[i] = false;
            for (unsigned i = 0; i < this->S; i++) X.A[i] = (bool) X.A[i] ^ (bool) A[i];
            for (unsigned i = 0; i < Mask.S; i++) X.A[i] = (bool) X.A[i] ^ (bool) Mask.A[i];
            return X;
        }
        // Boolean operators for Array Masks (with constants, keeping initial ArrayMask) 
        ArrayMask operator| (bool Boolean) const {
            ArrayMask X(this->S);
            for (unsigned i = 0; i < this->S; i++) X.A[i] = (bool) A[i] | Boolean;
            return X;
        }
        ArrayMask operator& (bool Boolean) const {
            ArrayMask X(this->S);
            for (unsigned i = 0; i < this->S; i++) X.A[i] = (bool) A[i] & Boolean;
            return X;
        }
        ArrayMask operator^ (bool Boolean) const {
            ArrayMask X(this->S);
            for (unsigned i = 0; i < this->S; i++) X.A[i] = (bool) A[i] ^ Boolean;
            return X;
        }
        // Boolean operators for Array Masks (modifying result ArrayMask)
        ArrayMask operator|= (const ArrayMask &Mask) {
            unsigned max_size = MAX_S(this->S, Mask.S);
            for (unsigned i = this->S; i < max_size; i++) append(false);
            for (unsigned i = 0; i < Mask.S; i++) this->A[i] = (bool) A[i] | (bool) Mask.A[i];
            return ArrayMask(this->A);
        }
        ArrayMask operator&= (const ArrayMask &Mask) {
            unsigned max_size = MAX_S(this->S, Mask.S);
            for (unsigned i = this->S; i < max_size; i++) append(false);
            for (unsigned i = 0; i < Mask.S; i++) this->A[i] = (bool) A[i] & (bool) Mask.A[i];
            return ArrayMask(this->A);
        }
        ArrayMask operator^= (const ArrayMask &Mask) {
            unsigned max_size = MAX_S(this->S, Mask.S);
            for (unsigned i = this->S; i < max_size; i++) append(false);
            for (unsigned i = 0; i < Mask.S; i++) this->A[i] = (bool) A[i] ^ (bool) Mask.A[i];
            return ArrayMask(this->A);
        }
};
/**
 * @brief Converter namespace for Array conversions and more
 */
namespace Converter {
    /**
     * @brief Convert Array to Dynamic Pointer Array
     * @tparam T Any
     * @param Arr Array object
     * @param new_size Size returned by reference
     * @return T* Dynamic Array
     */
    template <class T>
    T* toDynArray (const Array<T> &Arr, int &new_size) {
        new_size = (int) Arr.size();
        T* NewContainer = new T[new_size];
        for (unsigned i = 0; i < Arr.size(); i++) NewContainer[i] = Arr[i];
        return NewContainer;
    }
    /**
     * @brief Convert Array to STL Vector
     * @tparam T Any
     * @param Arr Array object
     * @return vector<T> 
     */
    template <class T>
    vector<T> toVector (const Array<T> &Arr) {
        vector<T> NewContainer;
        for (unsigned i = 0; i < Arr.size(); i++) NewContainer.push_back(Arr[i]);
        return NewContainer;
    }
    /**
     * @brief Convert Array to STL List
     * @tparam T Any
     * @param Arr Array object
     * @return list<T> 
     */
    template <class T>
    list<T> toList (const Array<T> &Arr) {
        list<T> NewContainer;
        for (unsigned i = 0; i < Arr.size(); i++) NewContainer.push_back(Arr[i]);
        return NewContainer;
    }
    /**
     * @brief Convert Array to STL Set
     * @tparam T Any
     * @param Arr Array object
     * @return set<T> 
     */
    template <class T>
    set<T> toSet (const Array<T> &Arr) {
        set<T> NewContainer;
        for (unsigned i = 0; i < Arr.size(); i++) NewContainer.insert(Arr[i]);
        return NewContainer;
    }
    /**
     * @brief Convert Array to STL Map
     * @tparam T Any
     * @tparam U Any
     * @param Keys Array object - map keys
     * @param Values Array object - map values
     * @return map<T, U> 
     */
    template <class T, class U>
    map<T, U> toMap (const Array<T> &Keys, const Array<U> &Values) {
        if (Keys.size() != Values.size()) throw std::invalid_argument("Keys and Values length must be the same!");
        map<T, U> NewContainer;
        for (unsigned i = 0; i < Keys.size(); i++) NewContainer.insert(make_pair(Keys[i], Values[i]));
        return NewContainer;
    }
    /**
     * @brief Convert Char Array to STD string
     * @param Char_Array 
     * @return string 
     */
    string toString (const Array<char> &Char_Array) {
        string s = "";
        for (int i = 0; i < Char_Array.size(); i++) s += Char_Array[i];
        return s;
    }
    /**
     * @brief Convert STD string to Char Array
     * @param STD_String 
     * @return Array<char> 
     */
    Array<char> toCharArray (const string &STD_String) {
        Array<char> A;
        for (unsigned i = 0; i < STD_String.length(); i++) A.append(STD_String.at(i));
        return A;
    }
}
namespace Files {
    /**
     * @brief Save Array to a file
     * @tparam T Any
     * @param Arr Array
     * @param FileName File Name
     */
    template <class T>
    void saveArray (const Array<T> &Arr, const string &FileName) {
        fstream f;
        f.open(FileName, ios::out);
        for (unsigned i = 0; i < Arr.size(); i++) f<<Arr[i]<<endl;
        f.close();
    }
    /**
     * @brief Append array to an existing file
     * @tparam T Any
     * @param Arr Array
     * @param FileName File Name
     */
    template <class T>
    void appendArray (const Array<T> &Arr, const string &FileName) {
        fstream f;
        f.open(FileName, ios::app);
        for (unsigned i = 0; i < Arr.size(); i++) f<<Arr[i]<<endl;
        f.close();
    }
    /**
     * @brief Get Array from File
     * @tparam T Array Type
     * @param FileName File Name
     * @return Array<T> 
     */
    template <class T>
    Array<T> readArray (const string &FileName) {
        Array<T> X;
        fstream f;
        f.open(FileName, ios::in);
        while (!f.eof()) {
            T val;
            f>>val;
            X.append(val);
        }
        X.pop();
        f.close();
        return X;
    }
}
#endif // !BETTER_ARRAY_H