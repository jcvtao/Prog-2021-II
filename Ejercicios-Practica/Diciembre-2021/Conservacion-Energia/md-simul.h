#pragma once
#include <iostream>
#include "particle.h"
#include "integrator.h"

// This could on itws own class: Config
const double G = -9.81;
const int NSTEPS = 2000;
const double DT = 0.01; // TIEMPO TOTAL : TF = NSTEPS*DT -> NSTEPS = int(TF/DT)
const double K = 253.57; // we will model the floor as a spring
const double LR = 0.9;
const double LL = -0.25;

/* DT       NSTEPS
 * 1.0      20
 * 0.5      40
 * 0.1      200
 * 0.05     400
 * 0.01     2000
*/ 

// function declarations
void initial_conditions(Particle & body);
void compute_force(Particle & body);
void print(Particle & body, double time);
