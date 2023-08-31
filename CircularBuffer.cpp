// Copyright[2022] <PorchhayBe>

/**
 * test.cpp - CircularBuffer
 * 
 * Date: 02/21/2022
 * 
 */

#include "CircularBuffer.h"
#include <stdint.h>
#include <functional>
#include <stdexcept>

CircularBuffer::CircularBuffer(size_t capacity) {
  // Throw invalid error if capacity is less than 1
  if (capacity == 0) {
    throw std::invalid_argument
    ("CircularBuffer constructor: capacity must be greater than zero");
  }
  Capacity = capacity;
  front = Capacity/2;  // array start from middle index
  next_index = front;
  arr = new int16_t[Capacity];
  Size = 0;
}

size_t CircularBuffer::size() {
  return Size;
}

bool CircularBuffer::isEmpty() {
  if (Size == 0) {
    return true;
  }
  return false;
}

bool CircularBuffer::isFull() {
  if (Size == Capacity) {
    return true;
  }
  return false;
}

void CircularBuffer::enqueue(int16_t x) {
  if (isEmpty()) {  // if array empty, set value to front index
    arr[front] = x;
    next_index++;
  } else if (isFull()) {  // if array is full, then throw exception
    throw std::runtime_error("enqueue: can't enqueue to a full ring");
  } else if (next_index >= Capacity) {  // if array reach the end
    // modular to the index by caoacity to cut off
    size_t index = next_index % Capacity;
    arr[index] = x;
    next_index++;
  } else {  // assign array index to a value, if everything normal
    arr[next_index] = x;
    next_index++;
  }
  Size++;
}

int16_t CircularBuffer::dequeue() {
  if (isEmpty()) {  // if dq an empty array, throw
    throw std::runtime_error("queue is empty, cannot dq");
  }
  // set new front after dq
  int16_t dqfront = arr[front];
  arr[front] = 0;
  front++;
  Size--;

  if (front >= Capacity) {
    front = front % Capacity;
  }

  return dqfront;
}

int16_t CircularBuffer::peek() {
  if (isEmpty()) {  // throw error for peek an empty array
    throw std::runtime_error("queue is empty, cannot peek");
  }
  return arr[front];
}

void CircularBuffer::Empty() {
  Size = 0;
}
