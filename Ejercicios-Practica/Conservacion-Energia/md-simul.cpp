#include "md-simul.h"
#include <cmath>

void initial_conditions(Particle & body)
{
  body.Ry = 1.6598;
  body.Vx = 0.23698;

  body.rad = 0.235;
  body.mass = 0.29698;

  // Energía potencial inicial
  body.EU = body.mass * -G * body.Ry; // U = m *g * y_0  // -G = +9.8

  // Energía cinética inicial
  double velocidad = std::sqrt(body.Vx*body.Vx + body.Vy*body.Vy + body.Vz*body.Vz); // v = sqrt(x^2 + y^2 + z^2)
  body.EK = 0.5 * body.mass * velocidad*velocidad; // K = 0.5 * m * v^2

  // Energía mecánica inicial
  body.EMI = body.EU + body.EK;
}

void compute_force(Particle & body)
{
  // reset force (and energy)
  body.Fx = body.Fy = body.Fz = body.EU = body.EK = 0.0;

  // gravitational force
  body.Fy += body.mass*G;

  // floor
  double delta = body.rad - body.Ry;
  if (delta > 0) {
    body.Fy += K*delta;
  }

  // Right wall
  delta = body.Rx + body.rad - LR;
  if (delta > 0) {
    body.Fx -= K*delta;
    body.EU += (K*delta*delta)/2; // Energía potencial [U = (k * delta^2) / 2]
  }

  // Left wall
  delta = LL - body.Rx + body.rad;
  if (delta > 0) {
    body.Fx += K*delta;
    body.EU += (K*delta*delta)/2; // Energía potencial [U = (k * delta^2) / 2]
  }

  // Energía potencial (posición)
  body.EU = body.mass * -G * body.Ry; // U = m * g * y  //  -G = +9.8

  // Energía cinética
  double velocidad = std::sqrt(body.Vx*body.Vx + body.Vy*body.Vy + body.Vz*body.Vz); // v = sqrt(x^2 + y^2 + z^2)
  body.EK = 0.5* body.mass * velocidad*velocidad; // K = 0.5 * m * v^2

  // Conservación energía mecánica
  body.EM = body.EU + body.EK; // E = U + K
  body.DE = std::fabs(body.EM - body.EMI) / body.EMI; // dE = |E(t)-E(0)|/E(0)
}

void print(Particle & body, double time)
{
  std::cout << time << "\t"
            << body.Rx << "\t"
            << body.Ry << "\t"
            << body.Rz << "\t"
            << body.Vx << "\t"
            << body.Vy << "\t"
            << body.Vz << "\t"
            << body.DE << "\n"; // Conservación energía mecánica
}
