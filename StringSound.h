#pragma once
// Copyright[2022] <PorchhayBe>

/**
 * stringsound.h - StringSound
 * 
 * Date: 03/29/2022
 * 
 */

#include "CircularBuffer.h"
#include <stdint.h>
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

class StringSound {
 public:
    explicit StringSound(double frequency);
    explicit StringSound(std::vector<sf::Int16> init);
    StringSound (const StringSound &obj) = delete;  // no copy const
    ~StringSound();
    void pluck();
    void tic();
    sf::Int16 sample();
    int time();
 private:
    std::unique_ptr<CircularBuffer> _cb;
    int _time;
    size_t CircularCapacity;
};
