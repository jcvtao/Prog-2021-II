#pragma once // avoids multiple inclusions
struct Particle
{
  double rad = 0.0;
  double mass = 0.0;
  double Rx = 0.0, Ry = 0.0, Rz = 0.0;
  double Vx = 0.0, Vy = 0.0, Vz = 0.0;
  double Fx = 0.0, Fy = 0.0, Fz = 0.0;

  double EU = 0.0; // Energía potencial
  double EK = 0.0; // Energía cinética
  double EM = 0.0; // Energía mecánica
  double EMI = 0.0; // Energía mecánica inicial
  double DE = 0.0; // Conservación energía mecánica
};
