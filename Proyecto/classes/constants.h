#pragma once

// WORLD CONSTANTS: define the *default* behavior of the world
double G = -3.3;
double WORLD_HEIGHT = 4.0;
double WORLD_WIDTH = 8.0;
double WORLD_DEPTH = 6.0;
double TIME = 0.0;
double DT = 0.01;
double SEC = 10;
double FPS = 450;

// OTHER CONSTANTS NEEDED FOR THE SIMULATOR
unsigned int NO_BALLS = 1;
double RADIUS = 0.25;
double K = 75000.0;

bool DISIPATION_FLAG = false;
double DISIPATION_CONSTANT = 100.0;