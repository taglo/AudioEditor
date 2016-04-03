/* 
 * File:   Noise.cpp
 * Author: tglo
 * 
 * Created on 30 janvier 2016, 06:57
 */


#include <random>
#include <ctime>
#include "Noise.h"

Noise::Noise(double amplitude) {
    std::uniform_real_distribution<double> unif(-amplitude, amplitude);
    std::mt19937_64 re((std::time(0)));
}
double Noise::tick() {
    return rng(distribution);
}
Noise::~Noise() {
}

