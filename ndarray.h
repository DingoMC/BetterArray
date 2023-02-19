/**
 * @file ndarray.h
 * @author DingoMC (www.dingomc.net)
 * @brief NDArrays for C++. Manage array calculations in more modern and convenient way.
 * @version 0.1
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) DingoMC Systems 2023
 * @warning Library written and tested on C++11. Using older C++ Versions may cause malfunction!
 * @note Full documentation https://github.com/DingoMC/BetterArray/README.md
 */
#ifndef NDARRAY_H
#define NDARRAY_H
#include <iostream>
#include <string>
#include <stdexcept>
#include "better_array.h"
#pragma GCC optimize("O3")
using namespace std;
// Handling colored_text.h if included
#ifdef COLORED_TEXT_H
    const char dimColors[12] = {'c', 'a', 'b', 'd', 'e', '9', '5', '6', '1', '4', '3', '2'};
#endif // COLORED_TEXT_H
// Main N-Dimensional Array Class
template <class T>
class NDArray {
    private:
        unsigned dims;
        Array < unsigned > dimSizes;
        Array < T > N;
        unsigned Idx (Array<int> NDIndex) const {
            if (NDIndex.size() != dims) throw std::invalid_argument("Index must have same amount of dimesions as NDArray it refers to!");
            for (unsigned i = 0; i < dims; i++) {
                if (NDIndex[i] < 0) NDIndex[i] += (int) dimSizes[i];
                if (NDIndex[i] >= (int) dimSizes[i]) throw std::invalid_argument("NDArray Index out of range!");
            }
            unsigned trueIndex = 0;
            for (unsigned i = 0; i < dims; i++) {
                unsigned mul = 1;
                for (unsigned j = i + 1; j < dims; j++) mul *= dimSizes[j];
                trueIndex += NDIndex[i] * mul;
            }
            return trueIndex;
        }
        unsigned DimIdx (int Index, unsigned axis) {
            if (Index < 0) Index += (int) dimSizes[axis];
            if (Index >= (int) dimSizes[axis]) throw std::invalid_argument("Dimension Index out of range!");
            return Index;
        }
        void AxisError (unsigned axis) {
            if (axis >= this->dims) throw std::invalid_argument("Axis does not exist!");
        }
        void InsertionError (NDArray<T> NDArr, unsigned axis) {
            if (NDArr.dimension() < this->dims - 1) throw std::invalid_argument("Not enough dimensions to insert!");
            if (NDArr.dimension() > this->dims) throw std::invalid_argument("Too many dimensions to insert!");
            if (NDArr.dimension() == this->dims) {
                for (unsigned i = 0; i < dims; i++) {
                    if (i != axis && NDArr.shape(i) != this->dimSizes[i]) throw std::invalid_argument("Invalid dimension shapes!");
                }
            }
            else {
                unsigned s = 0;
                for (unsigned i = 0; i < dims - 1; i++) {
                    if (i == axis) s++;
                    if (NDArr.shape(i) != this->dimSizes[i + s]) throw std::invalid_argument("Invalid dimension shapes!");
                }
            }
        }
        void InsertAt (unsigned dimIdx, NDArray<T> NDArr, unsigned axis) {
            Array<T> F = NDArr.flatten();
            unsigned sP = 1;
            for (unsigned i = axis; i < dims; i++) sP *= this->dimSizes[i];
            unsigned skip = sP;
            if (axis == 0) skip = 0;
            unsigned startPoint = dimIdx * (sP / this->dimSizes[axis]);
            unsigned skipEvery = 1;
            for (unsigned i = axis + 1; i < dims; i++) skipEvery *= this->dimSizes[i];
            if (NDArr.dimension() == this->dims) skipEvery *= NDArr.shape(axis);
            if (axis == 0) skipEvery = 0;
            unsigned insertionIndex = startPoint;
            for (unsigned i = 0; i < F.size(); i++) {
                if (skipEvery > 0) {
                    if (i > 0 && i % skipEvery == 0) insertionIndex += skip;
                }
                this->N.insert(insertionIndex, F[i]);
                insertionIndex++;
            }
            if (NDArr.dimension() == this->dims) this->dimSizes[axis] += NDArr.shape(axis);
            else this->dimSizes[axis]++;
        }
        void CheckRange (int From, int To, unsigned dim) {
            unsigned trueFrom = DimIdx(From, dim), trueTo = DimIdx(To, dim);
            if (trueFrom > trueTo) throw std::invalid_argument("Invalid index range!");
        }
        void dimCout (unsigned dim, const string &what) {
            #ifdef COLORED_TEXT_H
                string tf = "";
                tf += (char) ct::Executor;
                tf += (char) dimColors[dim % 12];
                tf += what;
                tf += (char) ct::Executor;
                tf += 'f';
                ctext::text(tf);
            #else
                cout<<what;
            #endif // COLORED_TEXT_H
        }
    public:
        // CONSTRUCTORS
        NDArray () {
            this->dims = 1;
            this->dimSizes.append(0);
        }
        explicit NDArray (unsigned Dimensions) {
            this->dims = Dimensions;
            for (unsigned i = 0; i < this->dims; i++) this->dimSizes.append(0);
        }
        explicit NDArray (unsigned Dimensions, Array<unsigned> Sizes) {
            if (Dimensions != Sizes.size()) throw std::invalid_argument("Sizes Array must be the same as dimension count!");
            this->dims = Dimensions;
            unsigned count = 1;
            for (unsigned i = 0; i < this->dims; i++) {
                this->dimSizes.append(Sizes[i]);
                count *= Sizes[i];
            }
            this->N = Array<T>(count);
        }
        explicit NDArray (unsigned Dimensions, initializer_list<unsigned> SizeList) {
            Array<unsigned> Sizes(SizeList);
            if (Dimensions != Sizes.size()) throw std::invalid_argument("Sizes Array must be the same as dimension count!");
            this->dims = Dimensions;
            unsigned count = 1;
            for (unsigned i = 0; i < this->dims; i++) {
                this->dimSizes.append(Sizes[i]);
                count *= Sizes[i];
            }
            this->N = Array<T>(count);
        }
        // Built-in functions
        /**
         * @brief Display NDArray
         */
        void show () {
            Array<unsigned> dim_counter(this->dims);
            dim_counter.fill(0);
            for (int j = this->dims - 1; j >= 0; j--) dimCout(j, "[");
            for (unsigned i = 0; i < this->N.size(); i++) {
                cout<<this->N[i];
                for (int j = this->dims - 1; j >= 0; j--) {
                    if (j == this->dims - 1) { if (dim_counter[j] == this->dimSizes[j] - 1) dimCout(this->dims - j - 1, "]"); }
                    else {
                        int changeCnt = 0;
                        for (int k = j; k < this->dims; k++) if (dim_counter[k] == this->dimSizes[k] - 1) changeCnt++;
                        if (changeCnt == this->dims - j) dimCout(this->dims - j - 1, "]");
                    }
                }
                if (i < this->N.size() - 1) {
                    for (int j = 0; j < this->dims; j++) {
                        if (dim_counter[j] < this->dimSizes[j] - 1) {
                            if (j == this->dims - 1) dimCout(this->dims - j - 1, ",");
                            else {
                                int changeCnt = 0;
                                for (int k = j + 1; k < this->dims; k++) if (dim_counter[k] == this->dimSizes[k] - 1) changeCnt++;
                                if (changeCnt == this->dims - j - 1) dimCout(this->dims - j - 1, ",");
                            }
                        }
                    }
                    for (int j = 1; j < this->dims; j++) {
                        int changeCnt = 0;
                        for (int k = j; k < this->dims; k++) if (dim_counter[k] == this->dimSizes[k] - 1) changeCnt++;
                        if (changeCnt == this->dims - j) dimCout(this->dims - j - 1, "[");
                    }
                }
                // Update counters
                dim_counter[this->dims - 1]++;
                for (int j = this->dims - 1; j >= 0; j--) {
                    if (dim_counter[j] >= this->dimSizes[j]) {
                        dim_counter[j] = 0;
                        if (j > 0) dim_counter[j-1]++;
                    }
                }
            }
            cout<<endl;
        }
        /**
         * @brief Get number of NDArray dimensions
         * @return unsigned - dimensions count
         */
        unsigned dimension () {return this->dims;}
        unsigned dimension () const {return dims;}
        /**
         * @brief Get NDArray shape
         * @return Array<unsigned> - Dimensions shape (length)
         */
        Array<unsigned> shape () {return this->dimSizes;}
        /**
         * @brief Get shape of one of NDArray dimensions
         * @param dim Dimension Index
         * @return unsigned - Dimension shape (length)
         */
        unsigned shape (unsigned dim) {
            AxisError(dim);
            return this->dimSizes[dim];
        }
        /**
         * @brief Get full size of NDArray
         * @return unsigned - NDArray capacity
         */
        unsigned fullSize () {return this->N.size();}
        /**
         * @brief Return 1D representation of NDArray
         * @return Array<T> 
         */
        Array<T> flatten () {return this->N;}
        /**
         * @brief Fill NDArray with same value
         * @param value Fill value
         */
        void fill (T value) { for (unsigned i = 0; i < this->N.size(); i++) this->N[i] = value; }
        /**
         * @brief Fill NDArray with value pattern
         * @param pattern Pattern Array
         * @param axis Pattern flow axis
         */
        void fill (const Array<T> &pattern, unsigned axis = 0) {
            AxisError(axis);
            if (pattern.size() == 0) throw std::invalid_argument("Pattern must be at least length: 1!");
            Array<unsigned> switched = this->dimSizes;
            if (axis > 0) {
                switched.erase(axis);
                switched.insert(0, this->dimSizes[axis]);
            }
            Array<int> counter(this->dims);
            counter.fill(0);
            for (unsigned i = 0; i < this->fullSize(); i++) {
                Array<int> id = counter;
                if (axis > 0) {
                    id.erase(0);
                    id.insert(axis, counter[0]);
                }
                this->N[Idx(id)] = pattern[i % pattern.size()];
                counter[this->dims - 1]++;
                for (int j = (int) this->dims - 1; j >= 0; j--) {
                    if (counter[j] >= switched[j]) {
                        counter[j] = 0;
                        if (j > 0) counter[j-1]++;
                    }
                }
            }
        }
        /**
         * @brief Fill NDArray with value pattern
         * @param pattern Pattern
         * @param axis Pattern flow axis
         */
        void fill (initializer_list<T> pattern, unsigned axis = 0) { this->fill(Array<T>(pattern), axis); }
        /**
         * @brief Expand dimension size
         * @param axis Dimension
         * @param count Expansion size
         */
        void expand (unsigned axis = 0, unsigned count = 1) {
            AxisError(axis);
            Array<unsigned> Sizes;
            for (unsigned i = 0; i < this->dims; i++) {
                if (i == axis) Sizes.append(count);
                else Sizes.append(this->dimSizes[i]);
            }
            NDArray<T> NDArr(this->dims, Sizes);
            NDArr.fill(0);
            InsertAt(this->dimSizes[axis], NDArr, axis);
        }
        /**
         * @brief Append elements to NDArray
         * @param NDArr Elements to Append
         * @param axis Appending axis (default = 0)
         */
        void append (const NDArray<T> &NDArr, unsigned axis = 0) {
            AxisError(axis);
            InsertionError(NDArr, axis);
            InsertAt(this->dimSizes[axis], NDArr, axis);
        }
        /**
         * @brief Insert Elements into ND Array at given index
         * @param Where Axis Index
         * @param NDArr Elements to insert
         * @param axis Dimension (default = 0)
         */
        void insert (int Where, const NDArray<T> &NDArr, unsigned axis = 0) {
            AxisError(axis);
            InsertionError(NDArr, axis);
            InsertAt(DimIdx(Where, axis), NDArr, axis);
        }
        /**
         * @brief Reshape NDArray
         * @param newShape New NDArray Shape
         */
        void reshape (const Array<unsigned> &newShape) {
            unsigned full_size = 1;
            for (unsigned i = 0; i < newShape.size(); i++) full_size *= newShape[i];
            if (full_size != this->fullSize()) throw std::invalid_argument("Cannot convert this NDArray to new shape!");
            this->dimSizes = newShape;
            this->dims = newShape.size();
        }
        /**
         * @brief Reshape NDArray
         * @param newShape New NDArray Shape
         */
        void reshape (initializer_list<unsigned> newShape) { this->reshape(Array<unsigned>(newShape)); }
        /**
         * @brief Get NDArray slice through axis
         * @param From Starting Axis Index (Inclusive). Default to 0
         * @param To End Axis Index (Inclusive). Default to Array End
         * @param axis Slice Dimension (default = 0)
         * @return NDArray<T> NDArray Slice
         */
        NDArray<T> slice (int From = ArrayBegin, int To = ArrayEnd, unsigned axis = 0) {
            if (To == ArrayEnd && (int) this->dimSizes[axis] < ArrayEnd) To = this->dimSizes[axis] - 1;
            CheckRange(From, To, axis);
            Array<unsigned> sliceShape;
            for (unsigned i = 0; i < this->dims; i++) {
                if (i == axis) sliceShape.append(To - From + 1);
                else sliceShape.append(this->dimSizes[i]);
            }
            NDArray<T> newSlice(this->dims, sliceShape);
            Array<unsigned> switched = this->dimSizes;
            switched[axis] = DimIdx(To, axis) + 1;
            if (axis > 0) {
                switched.erase(axis);
                switched.insert(0, this->dimSizes[axis]);
            }
            Array<int> counter(this->dims);
            counter.fill(0);
            counter[0] = DimIdx(From, axis);
            for (unsigned i = 0; i < newSlice.fullSize(); i++) {
                Array<int> id = counter;
                if (axis > 0) {
                    id.erase(0);
                    id.insert(axis, counter[0]);
                }
                Array<int> dest_id = id;
                dest_id[axis] -= DimIdx(From, axis);
                newSlice[dest_id] = this->operator[](id);
                counter[this->dims - 1]++;
                for (int j = (int) this->dims - 1; j >= 0; j--) {
                    if (counter[j] >= switched[j]) {
                        if (j == 0) counter[j] = DimIdx(From, axis);
                        else counter[j] = 0;
                        if (j > 0) counter[j-1]++;
                    }
                }
            }
            return newSlice;
        }
        /**
         * @brief Reshape NDArray by collapsing dimensions with length = 1
         */
        void collapse () {
            Array<unsigned> newShape;
            for (unsigned i = 0; i < this->dims; i++) {
                if (this->dimSizes[i] > 1) newShape.append(this->dimSizes[i]);
            }
            if (newShape.size() == 0) newShape.append(1); // If all dimensions collapsed, leave 1 dimension with size 1
            this->dimSizes = newShape;
            this->dims = newShape.size();
        }
        /*
            OPERATORS OVERLOADING
        */
        // Non-accessible and accessible subscripts
        T& operator[] (initializer_list<int> NDIndex) {return N[Idx(Array<int>(NDIndex))];}
        T& operator[] (const Array<int> &NDIndex) {return N[Idx(NDIndex)];}

};
#endif // !NDARRAY_H