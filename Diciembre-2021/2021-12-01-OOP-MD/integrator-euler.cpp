#include "integrator.h"
void start_integration(Particle & body, const double & dt)
{
  // not needed for euler
}

void time_integration(Particle & body, const double & dt)
{
  // euler
  body.Rx = body.Rx + body.Vx*dt + body.Fx*dt*dt*0.5/body.mass;
  body.Ry = body.Ry + body.Vy*dt + body.Fy*dt*dt*0.5/body.mass;
  body.Rz = body.Rz + body.Vz*dt + body.Fz*dt*dt*0.5/body.mass;
  body.Vx = body.Vx + body.Fx*dt/body.mass;
  body.Vy = body.Vy + body.Fy*dt/body.mass;
  body.Vz = body.Vz + body.Fz*dt/body.mass;
}
