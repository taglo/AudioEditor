/* 
 * File:   main.cpp
 * Author: tglo
 *
 * Created on 9 janvier 2016, 15:12
 */
#pragma once
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "Sample.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Sample spla(3000);
    spla.setConstant(1).fadeOut().saveToFile("test.wav");



    printf("Hello world !\n");

    return EXIT_SUCCESS;
}

