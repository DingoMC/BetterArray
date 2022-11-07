#ifndef BETTER_ARRAY_H
#define BETTER_ARRAY_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
using namespace std;
template <class T>
class Array {
    private:
        vector < T > A;
        unsigned S;
        int correctIndex (int index) {
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
        unsigned size () {return this->S;}
        void show (bool showType = false) {
            if (showType) cout<<"`Array` ";
            cout<<"[";
            for (unsigned i = 0; i < this->S; i++) {
                cout<<this->A[i];
                if (i < this->S - 1) cout<<", ";
            }
            cout<<"]"<<endl;
        }
        void append (T Elem) {
            this->S++;
            this->A.push_back(Elem);
        }
        void append (Array <T> arr) {
            for (unsigned i = 0; i < arr.size(); i++) {
                this->S++;
                this->A.push_back(arr[i]);
            }
        }
        void pop () {
            if (this->S > 0) {
                this->S--;
                this->A.pop_back();
            }
        }
        void insert (int Where, T Elem) {
            this->S++;
            this->A.insert(this->A.begin() + correctIndex(Where), Elem);
        }
        void insert (int Where, Array<T> arr) {
            for (int i = 0; i < arr.size(); i++) {
                this->S++;
                this->A.insert(this->A.begin() + correctIndex(Where) + i, arr[i]);
            }
        }
        void erase (int Which) {
            if (this->S > 0) {
                this->A.erase(this->A.begin() + correctIndex(Which));
                this->S--;
            }
        }
        // OPERATORS
        T& operator[] (int index) {return this->A[correctIndex(index)];}
};
#endif // !BETTER_ARRAY_H