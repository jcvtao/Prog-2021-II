#pragma once // avois multiple inclusion
#include "particle.h"
void time_integration(Particle & body, const double & dt);
void start_integration(Particle & body, const double & dt);
