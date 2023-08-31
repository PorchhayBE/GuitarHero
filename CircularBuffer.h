// Copyright[2022] <PorchhayBe>

/**
 * test.cpp - CircularBuffer
 * 
 * Date: 02/21/2022
 * 
 */

#pragma once
#include<stdint.h>
#include <functional>

class CircularBuffer {
 private:
    size_t Size;
    size_t Capacity;
    size_t front;
    size_t next_index;
    int16_t *arr;
 public:
    // Create an Empty ring buffer, with given max
                                    // capacity
    CircularBuffer(size_t capacity); // NOLINT
    // return number of items currently in the buffer
    size_t size();
    // is the buffer empty (size equals zero)?
    bool isEmpty();
    // is the buffer full ( size equals capacity)?
    bool isFull();
    // add items x to the end
    void enqueue(int16_t x);
    // delete and return item from the front
    int16_t dequeue();
    // return (but do not delete) item from the front
    int16_t peek();
    void Empty();
};
