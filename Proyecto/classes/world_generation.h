#pragma once

#include <string.h> 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <ctime>

#include "constants.h"
#include "ball.h"

// --------- EDIT FOR NEW INPUTS ------------
// array with all the correct possible inputs
std::string valid_inputs[] = {"-radius", "-wheight", "-wwidth", "-gravity", "-restitution", "-np", "-wdepth", "-time", "-dt", "-sec", "-fps", "-disp_flag", "-disp_c"};

// array that will store incorrect input (if there's any) to show in the console
std::vector<std::string> incorrect_inputs;

// keeps track if there's an invalid input
bool incorrect_input_boolean = false;

// array that contains all the balls
std::vector<Ball> particles;


// ------------ EDIT FOR NEW INPUTS ----------------------------
// Function that recieves a string with the parameter name and overwrites the constant with 
// the one in the input
void write_parameter(std::string param, const char* value)
{
    if (param == "-radius")
    {
        RADIUS = std::atof(value);
    }

    if (param == "-wheight")
    {
        double height = std::atof(value);
        
        if (height > 2.5)
        {
            return;
        }

        WORLD_HEIGHT = height;
    }

    if (param == "-wwidth")
    {
        WORLD_WIDTH = std::atof(value);
    }

    if (param == "-gravity")
    {
        G = std::atof(value);
    }

    if (param == "-restitution")
    {
        K = std::atof(value);   
    }

    if (param == "-np")
    {
        NO_BALLS = std::atoi(value);
    }

    if (param == "-wdepth")
    {
        WORLD_DEPTH = std::atof(value);
    }

    if (param == "-time")
    {
        TIME = std::atof(value);
    }

    if (param == "-dt")
    {
        DT = std::atof(value);
    }

    if (param == "-sec")
    {
        SEC = std::atof(value);
    }

    if (param == "-fps")
    {
        FPS = std::atoi(value);
    }

    if (param == "-disp_flag")
    {
        DISIPATION_FLAG = value;
    }

    if (param == "-disp_c")
    {
        DISIPATION_CONSTANT = std::atof(value);
    }
}


// GENERATES A RANDOM PLACED BALL
Ball generate_ball(int n)
{
    double x, y, z, vx, vy, vz, mass;
    
    srand(time(0) + (n * rand()));

    x = rand() % (int)WORLD_WIDTH - WORLD_WIDTH / 2;
    y = rand() % (int)WORLD_DEPTH - WORLD_DEPTH / 2;
    z = rand() % (int)WORLD_HEIGHT - WORLD_HEIGHT / 2;

    while (x > WORLD_WIDTH)
    {
        x = (rand() % (int)WORLD_WIDTH);
    }

    vx = (rand() % (int)WORLD_WIDTH + WORLD_WIDTH) / WORLD_WIDTH;
    vy = (rand() % (int)WORLD_DEPTH + WORLD_DEPTH) / WORLD_DEPTH;
    vz = (rand() % (int)WORLD_HEIGHT + WORLD_HEIGHT) / WORLD_HEIGHT;

    mass = 100;

    return (Ball(RADIUS, x, y, z, vx, vy, vz, mass));
}

// Function that takes the console inputs and proccess it in order to overwrite the constants 
// and generates the world
void generate_world(int argc, char *argv[])
{
    // CHECK IF INPUT IS CORRECT
    for (int i = 1; i < argc; i += 2)
    {   
        // flag to know if the input is valid or not
        bool valid = false;

        // check if the input matches with any of the valid inputs
        for (auto par : valid_inputs)
        {
            if (par == argv[i])
            {
                valid = true;
                break;
            }
        }
        
        // if there's a match, overwrite the constant
        if (valid)
        {
            write_parameter(argv[i], argv[i + 1]);
        }
        else // if not, activate the incorrect input flag and add the string to the
        {    // array of incorrect inputs
            incorrect_input_boolean = true;
            incorrect_inputs.push_back(argv[i]);
        }
    }

    // PRINT ANIMATION INFORMTION
    std::cout << "Running Bouncing Ball Animation using OpenGL..." << "\n"
              << "FPS: " << FPS << "\n"
              << "NO_BALLS: " << NO_BALLS << "\n"
              << "RADIUS: " << RADIUS << "\n"
              << "GRAVITY: " << G << "\n"
              << "----------------\n\n";

    // if there are incorrect inputs, print them on the screen so the user
    // knows where's the mistake
    if (incorrect_inputs.size() > 0)
    {

        std::cout << "INVALID PARAMETERS INPUT: \n";

        for (auto inco : incorrect_inputs)
        {
            std::cout << inco << std::endl;
        }

        // and also print all the correct possible inputs
        std::cout << "TRY USING CORRECT PARAMETERS INSTEAD: \n";

        for (auto corr : valid_inputs)
        {
            std::cout << corr << std::endl;
        }

    }

    WORLD_WIDTH /= 2;
    WORLD_HEIGHT /= 2;
    WORLD_DEPTH /= 2;

    // generate all the balls to play with
    for (int i = 1; i <= NO_BALLS; i++)
    {
        particles.push_back(generate_ball(i));
    }

}
