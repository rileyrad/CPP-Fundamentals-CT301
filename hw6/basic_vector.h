#ifndef BASIC_VECTOR_H_INCLUDED
#define BASIC_VECTOR_H_INCLUDED

#include <stdio.h>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <cstddef>

template <typename T>
class basic_vector {
    std::size_t size_;
    std::size_t capacity_;
    T* data_;

public:

    // Constructors

    /*basic_vector*/
    // Input: None
    // Output: A basic_vector object initialized with default values.
    // The default constructor which assigns size to 0, capacity to 1, and instantiates an array with a capacity of 1.
    basic_vector() : size_(0), capacity_(1), data_(new T[capacity_]) {}

    /*basic_vector*/
    // Input: The desired capacity of the vector (size_t)
    // Output: A basic_vector object initialized with a desired capacity
    // Like the default constructor, which assigns size to 0, but instead instantiates the array with the capacity parameter.
    basic_vector(std::size_t capacity) : size_(0), capacity_(capacity),  data_(new T[capacity]) {}

    /*basic_vector*/
    // Input: The basic_vector to be copied (rhs)
    // Output: A basic_vector object that is a copy of rhs
    // The copy constructor which assigns the size, capacity, and data to whichever basic_vector is in rhs. Utilizes the std::copy function.
    basic_vector(const basic_vector& rhs) : size_(rhs.size_), capacity_(rhs.capacity_), data_(new T[rhs.capacity_]) {
        std::copy(rhs.data_, rhs.data_ + size_, data_);
    }

    /*operator=*/
    // Input: The basic_vector to be copied (rhs)
    // Output: A basic_vector object that is a copy of rhs
    // The copy assignment operator which replaces all the data of the current basic_vector with the one stored in rhs.
    basic_vector& operator=(const basic_vector& rhs) {
        if (this != &rhs) {
            delete[] data_;
            size_ = rhs.size_;
            capacity_ = rhs.capacity_;
            data_ = new T[capacity_];
            std::copy(rhs.data_, rhs.data_ + size_, data_);
        }
        return *this;
    }

    // Capacity Methods

    /*size*/
    // Input: None
    // Output: The size of the vector (size_t)
    // A simple getter to fetch the size of the vector.
    std::size_t size() const {
        return size_; 
    }

    /*max_size*/
    // Input: None
    // Output: The maximum number of elements the vector can hold (size_t)
    // Returns the max size of the vector which is 2^32 divided by the size of T minus 1.
    std::size_t max_size() const {
        return pow(2, 32) / sizeof(T) - 1;
    }

    /*capacity*/
    // Input: None
    // Output: The capacity of the vector (size_t)
    // A simple getter to fetch the capacity of the vector.
    std::size_t capacity() const {
        return capacity_;
    }

    /*resize*/
    // Input: The number to resize the vector to (size_t)
    // Output: None
    // Resizes the vector to the size of n and defaults the new values if n is larger than the current size.
    // Otherwise, the size is set to n, which would cut off the elements outside of the bounds.
    void resize(std::size_t n) {
        if (n > size_) {
            reserve(n);
            for (std::size_t i = size_; i < n; i++) { 
                data_[i] = T();
            } 
            if (n > capacity_) {
                capacity_ = n;
            }
        }
        size_ = n;
    }

    /*resize*/
    // Input: The number to resize the vector to (size_t) and the default value (const T&)
    // Output: None
    // Resizes the vector to the size of n and defaults the new values to val if n is larger than the current size.
    // Otherwise, the size is set to n, which would cut off the elements outside of the bounds.
    void resize(std::size_t n, const T& val) {
        if (n > size_) {
            reserve(n);
            for (std::size_t i = size_; i < n; i++) { 
                data_[i] = val;
            } 
            if (n > capacity_) {
                capacity_ = n;
            }
        }
        size_ = n;
    }

    /*empty*/
    // Input: None
    // Output: bool
    // Returns true if the vector is empty, i.e., size is zero.
    bool empty() {
        return size_ == 0;
    }

    /*reserve*/
    // Input: The size that the vector will reserve (size_t)
    // Output: None
    // Reserves the vector to the size of n if n is greater than capacity.
    void reserve(std::size_t n) {
        if (n > capacity_) { 
            T* new_data = new T[n];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = n;
        }
    }

    /*shrink_to_fit*/
    // Input: None
    // Output: None
    // Shrinks the vector to the size of the vector if they are not already the same. Has practically the same implementation as reserve()
    // except that it uses the size_ instead of n.
    void shrink_to_fit() {
        if (size_ < capacity_) {
            T* new_data = new T[size_];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = size_;
        }
    }

    // Element Access
    
    /*operator[]*/
    // Input: The index of the desired value (size_t)
    // Output: The desired value (T)
    // Returns the value at index n without handling errors.
    T& operator[](std::size_t n) {
        return data_[n];
    }

    /*at*/
    // Input: The index of the desired value (size_t)
    // Output: The desired value (T)
    // Returns the value at index n while handling a range error.
    T& at(std::size_t n) {
        if (n >= size_) {
            throw std::out_of_range("Index out of range for index: " + std::to_string(n) + 
                                    ". Should be less than " + std::to_string(size_) + ".\n");
        }
        return data_[n];
    }

    /*front*/
    // Input: None
    // Output: The element's reference (T)
    // Returns a reference to the first element in the vector.
    T& front() {
        return data_[0];
    }

    /*back*/
    // Input: None
    // Output: The element's reference (T)
    // Returns the last element of the vector.
    T& back() {
        return data_[size_ - 1];
    }

    /*data*/
    // Input: None
    // Output: A pointer to the data array (T)
    // Returns all of the data of the vector.
    T* data() {
        return data_;
    }

    // Modifiers

    /*push_back*/
    // Input: The desired element (T)
    // Output: None
    // Adds an element to the end of the vector.
    void push_back(const T& val) {
        if (size_ == capacity_) {
            if (capacity_ == 0) {
                reserve(1);
            } else {
                reserve(capacity_ * 2);
            }
        }
        data_[size_] = val;
        ++size_;
    }

    /*pop_back*/
    // Input: None
    // Output: None
    // Removes the last element of the vector.
    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    /*swap*/
    // Input: The basic_vector object to swap.
    // Output: None
    // Swaps a vector with another vector.
    void swap(basic_vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    
    /*clear*/
    // Input: None
    // Output: None
    // Clears the vector to have nothing.
    void clear() {
        size_ = 0;
    }

};
#endif