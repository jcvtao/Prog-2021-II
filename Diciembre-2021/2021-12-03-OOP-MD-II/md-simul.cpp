#include "md-simul.h"

void initial_conditions(Particle & body)
{
  body.Ry = 1.6598;
  body.Vx = 0.23698;

  body.rad = 0.235;
  body.mass = 0.29698;
}

void compute_force(Particle & body)
{
  // reset force
  body.Fx = body.Fy = body.Fz = 0.0;

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
  }

  // Left wall
  delta = LL - body.Rx + body.rad;
  if (delta > 0) {
    body.Fx += K*delta;
  }
}

void print(Particle & body, double time)
{
  std::cout << time << "  "
            << body.Rx << "  "
            << body.Ry << "  "
            << body.Rz << "  "
            << body.Vx << "  "
            << body.Vy << "  "
            << body.Vz << "  "
            << "\n";
}
