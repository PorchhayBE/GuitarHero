// Copyright[2022] <PorchhayBe>

/**
 * stringsound.cpp - StringSound
 * 
 * Date: 03/29/2022
 * 
 */

#include "StringSound.h"
#include <stdint.h>
#include <random>
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

StringSound::StringSound(double frequency) {
    // calculate the size of sample
    CircularCapacity = ceil(44100 / frequency);
    _time = 0;
    // inialize object
    _cb = std::make_unique<CircularBuffer>
                            (CircularCapacity);
}

StringSound::StringSound(std::vector<sf::Int16> init) {
    _time = 0;
    _cb = std::make_unique<CircularBuffer>(init.size());
}

void StringSound::pluck() {
    // random seem algo
    unsigned int seed =
        std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g1(seed);
    std::uniform_int_distribution<int16_t>dist(-32768, 32767);
    // empty Circular buffer before add random
    _cb->Empty();

    // assign rand value in Circular Buffer
    while (!_cb->isFull()) {
        int16_t random = dist(g1);
        _cb->enqueue(random);
    }
}

void StringSound::tic() {
    // throw exception if Circular is empty
    if (_cb->isEmpty()) {
        throw std::runtime_error("CircularBuffer is empty");
    }
    // dequeue and assign value to front
    int16_t front = _cb->dequeue();
    int16_t nFront = _cb->peek();  // peek new front after delete
    // lambda expression to calculate algorithm
    auto sampleAlgo = [](int x, int y) {return .996 * ((x + y)/2);};
    // enqueue result from algorithm
    _cb->enqueue(sampleAlgo(front, nFront));
    _time++;
}

int StringSound::time() {
    return _time;
}

sf::Int16 StringSound::sample() {
    if (_cb->isEmpty()) {
        throw std::runtime_error("CircularBuffer is empty, can't peek");
    }
    return _cb->peek();
}

StringSound::~StringSound() {
}
