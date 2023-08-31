// Copyright[2022] <PorchhayBe>

/**
 * KSGuitarSim.cpp - StringSound
 * 
 * Date: 03/29/2022
 * 
 */

#include <math.h>
#include <limits.h>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "StringSound.h"

#define CONCERT_A 440.0
#define SAMPLES_PER_SEC 44100
#define total_key 44


std::vector<sf::Int16> makeSamples(StringSound* gs);
std::map<int, unsigned int> KeyDict();

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 200),
    "SFML Plucked String Sound Lite");
    sf::Event event;

    // audio sample
    // vector holds audio from stringsound
    std::vector <std::vector<sf::Int16>> samples;
    for (int i = 0; i < total_key; i++) {
        // Guitar string frequency for each key
        double freq = CONCERT_A * pow(2, (i - 24.0) / 12.0);

        // Piano String frequency 
        // double freq = pow(2, (i - 49.0) / 12.0) * CONCERT_A;



        StringSound *gs = new StringSound(freq);
        samples.push_back(makeSamples(gs));
    }

    // sound buffer sample
    // vector hold vector of audio sample
    std::vector<sf::SoundBuffer> sound_buffers;
    for (size_t i = 0; i < samples.size(); i++) {
        sf::SoundBuffer buf1;
        if (!buf1.loadFromSamples(&(samples.at(i))[0], samples.at(0).size(),
        2, SAMPLES_PER_SEC)) {
            throw std::runtime_error(
            "sf::SoundBuffer: failed to load from samples.");
        }
        sound_buffers.push_back(buf1);
    }

    // sf sound
    // vector of sf sound hold a sound buffer object
    std::vector<sf::Sound> soundvect;
    for (size_t i = 0; i < sound_buffers.size(); i++) {
        sf::Sound sound;
        sound.setBuffer(sound_buffers.at(i));
        soundvect.push_back(sound);
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
           if (event.type == sf::Event::Closed) {
               window.close();
           } else if (event.type == sf::Event::KeyPressed) {
               if (KeyDict().count(event.key.code) > 0) {
                    soundvect.at(KeyDict().find(event.key.code)->second).play();
               } else {
                   std::cout << "invalid key\n";
               }
           }
            window.clear();
            window.display();
        }
    }
    return 0;
}

std::vector<sf::Int16> makeSamples(StringSound* gs) {
    std::vector<sf::Int16> samples;

    gs->pluck();
    int duration = 8;  // seconds
    int i;
    for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs->tic();
        samples.push_back(gs->sample());
    }

    return samples;
}

std::map<int, unsigned int> KeyDict() {
    std::map<int, unsigned int> key;

  key.insert(std::pair<int, unsigned int>(1,  26));
  key.insert(std::pair<int, unsigned int>(2,  22));
  key.insert(std::pair<int, unsigned int>(3,  21));
  key.insert(std::pair<int, unsigned int>(4,  3));
  key.insert(std::pair<int, unsigned int>(5,  23));
  key.insert(std::pair<int, unsigned int>(6,  25));
  key.insert(std::pair<int, unsigned int>(8,  12));
  key.insert(std::pair<int, unsigned int>(9,  28));
  key.insert(std::pair<int, unsigned int>(10, 30));
  key.insert(std::pair<int, unsigned int>(12, 29));
  key.insert(std::pair<int, unsigned int>(13, 27));
  key.insert(std::pair<int, unsigned int>(14, 14));
  key.insert(std::pair<int, unsigned int>(15, 15));
  key.insert(std::pair<int, unsigned int>(16, 0));
  key.insert(std::pair<int, unsigned int>(17, 5));
  key.insert(std::pair<int, unsigned int>(19, 7));
  key.insert(std::pair<int, unsigned int>(28, 1));
  key.insert(std::pair<int, unsigned int>(22, 2));
  key.insert(std::pair<int, unsigned int>(30, 4));
  key.insert(std::pair<int, unsigned int>(31, 6));
  key.insert(std::pair<int, unsigned int>(24, 8));
  key.insert(std::pair<int, unsigned int>(20, 10));
  key.insert(std::pair<int, unsigned int>(33, 9));
  key.insert(std::pair<int, unsigned int>(34, 11));
  key.insert(std::pair<int, unsigned int>(35, 13));
  key.insert(std::pair<int, unsigned int>(56, 16));
  key.insert(std::pair<int, unsigned int>(46, 17));
  key.insert(std::pair<int, unsigned int>(55, 18));
  key.insert(std::pair<int, unsigned int>(25, 19));
  key.insert(std::pair<int, unsigned int>(23, 20));
  key.insert(std::pair<int, unsigned int>(21, 24));
  key.insert(std::pair<int, unsigned int>(49, 31));
  key.insert(std::pair<int, unsigned int>(50, 32));
  key.insert(std::pair<int, unsigned int>(48, 33));
  key.insert(std::pair<int, unsigned int>(52, 34));
  key.insert(std::pair<int, unsigned int>(51, 35));
  key.insert(std::pair<int, unsigned int>(57, 36));

  return key;
}


