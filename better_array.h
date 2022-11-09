#ifndef BETTER_ARRAY_H
#define BETTER_ARRAY_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#define MAX_S(a, b) a > b ? a : b
using namespace std;
template <class T> class Array;
class ArrayMask {
    public:
        vector < bool > M;
        unsigned S;
        bool operator[] (int index) const {return M.at(index);}
        ArrayMask () { this->S = 0;}
        ArrayMask (unsigned s) {
            this->S = s;
            this->M.resize(this->S);
        }
        ArrayMask (const vector < bool > &STL_Vector) {
            this->S = STL_Vector.size();
            this->M.resize(this->S);
            for (unsigned i = 0; i < this->S; i++) this->M[i] = STL_Vector[i];
        }
        ArrayMask (const list < bool > &STL_list) {
            this->S = STL_list.size();
            for (auto it = STL_list.cbegin(); it != STL_list.cend(); it++) this->M.push_back(*it);
        }
        ArrayMask (const bool* dynamicArray, unsigned arraySize) {
            this->S = arraySize;
            this->M.resize(this->S);
            for (unsigned i = 0; i < this->S; i++) this->M[i] = dynamicArray[i];
        }
        void append (bool MaskElem) {
            this->S++;
            this->M.push_back(MaskElem);
        }
};
template <class T>
class Array {
    private:
        vector < T > A;
        unsigned S;
        int correctIndex (int index) const {
            if (index < -(int) (this->S) || index >= (int) this->S) throw std::invalid_argument("Invalid Array Index!");
            if (index >= 0) return index;
            return index + (int) this->S;
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
        Array (unsigned s) {
            this->S = s;
            this->A.resize(this->S);
        }
        /**
         * @brief Construct a new Array object using Vector
         * 
         * @param STL_Vector Initializing Vector
         */
        Array (const vector < T > &STL_Vector) {
            this->S = STL_Vector.size();
            this->A.resize(this->S);
            for (unsigned i = 0; i < this->S; i++) this->A[i] = STL_Vector[i];
        }
        /**
         * @brief Construct a new Array object using List
         * 
         * @param STL_list Initializing List
         */
        Array (const list < T > &STL_list) {
            this->S = STL_list.size();
            for (auto it = STL_list.cbegin(); it != STL_list.cend(); it++) this->A.push_back(*it);
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
        // FUNCTIONS
        /**
         * @brief Get the size of an Array
         * @return unsigned Size
         */
        unsigned size () {return this->S;}
        /**
         * @brief Show Array
         * @param showType Default to false: If true - it additionally shows type
         */
        void show (bool showType = false) {
            if (showType) cout<<"`Array` ";
            cout<<"[";
            for (unsigned i = 0; i < this->S; i++) {
                cout<<this->A[i];
                if (i < this->S - 1) cout<<", ";
            }
            cout<<"]"<<endl;
        }
        /**
         * @brief Add element to the end of an Array
         * @param Elem 
         */
        void append (T Elem) {
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
            this->A.insert(this->A.begin() + correctIndex(Where), Elem);
        }
        /**
         * @brief Insert another Array begging from n-th index to Array
         * @param Where n-th index (negative index supported)
         * @param arr Array
         */
        void insert (int Where, Array<T> arr) {
            for (int i = 0; i < arr.size(); i++) {
                this->S++;
                this->A.insert(this->A.begin() + correctIndex(Where) + i, arr[i]);
            }
        }
        /**
         * @brief Remove element at n-th index from Array
         * @param Which n-th index (negative index supported)
         */
        void erase (int Which) {
            if (this->S > 0) {
                this->A.erase(this->A.begin() + correctIndex(Which));
                this->S--;
            }
        }
        /**
         * @brief Remove elements begging from i-th index to j-th index
         * @param From i-th index (negative index supported)
         * @param To j-th index (negative index supported, j >= i)
         */
        void erase (int From, int To) {
            int width = correctIndex(To) - correctIndex(From) + 1;
            if ((int) this->S >= width && width > 0) {
                for (int i = 0; i < width; i++) {
                    this->A.erase(this->A.begin() + correctIndex(From));
                    this->S--;
                }
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
                if (i >= Mask.S) X.append(this->A[i]);
                else {
                    if (Mask[i]) X.append(this->A[i]);
                }
            }
            return X;
        }
        Array<T> masked (bool (*custom_comparator)(T)) {
            Array<T> X;
            for (unsigned i = 0; i < this->S; i++) {
                if (custom_comparator(this->A[i])) X.append(this->A[i]);
            }
            return X;
        }
        /*
            OPERATORS OVERLOADING
        */
        // Non-accessible and accessible subscripts
        T& operator[] (int index) {return A[correctIndex(index)];}
        T operator[] (int index) const {return A.at(correctIndex(index));}
        // Arithmetic operations with constants (keeping the Array)
        Array<T> operator+ (T Num) const {
            Array <T> X(this->S);
            for (unsigned i = 0; i < this->S; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += this->A[i] + Num;
            return X;
        }
        Array<T> operator- (T Num) const {
            Array <T> X(this->S);
            for (unsigned i = 0; i < this->S; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += this->A[i] - Num;
            return X;
        }
        Array<T> operator* (T Num) const {
            Array <T> X(this->S);
            for (unsigned i = 0; i < this->S; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += (this->A[i] * Num);
            return X;
        }
        Array<T> operator/ (T Num) const {
            Array <T> X(this->S);
            for (unsigned i = 0; i < this->S; i++) X[i] = 0;
            for (unsigned i = 0; i < this->S; i++) X[i] += (this->A[i] / Num);
            return X;
        }
        Array<T> operator% (T Num) const {
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
        Array<T> operator+= (T Num) {
            for (unsigned i = 0; i < this->S; i++) this->A[i] += Num;
            return Array<T>(this->A);
        }
        Array<T> operator-= (T Num) {
            for (unsigned i = 0; i < this->S; i++) this->A[i] -= Num;
            return Array<T>(this->A);
        }
        Array<T> operator*= (T Num) {
            for (unsigned i = 0; i < this->S; i++) this->A[i] *= Num;
            return Array<T>(this->A);
        }
        Array<T> operator/= (T Num) {
            for (unsigned i = 0; i < this->S; i++) this->A[i] /= Num;
            return Array<T>(this->A);
        }
        Array<T> operator%= (T Num) {
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
        ArrayMask operator== (T Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] == Value_1);
            return X;
        }
        ArrayMask operator>= (T Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] >= Value_1);
            return X;
        }
        ArrayMask operator<= (T Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] <= Value_1);
            return X;
        }
        ArrayMask operator> (T Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] > Value_1);
            return X;
        }
        ArrayMask operator< (T Value_1) {
            ArrayMask X;
            for (unsigned i = 0; i < this->S; i++) X.append(this->A[i] < Value_1);
            return X;
        }
        ArrayMask operator!= (T Value_1) {
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
};
#endif // !BETTER_ARRAY_H