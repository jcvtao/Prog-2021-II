#pragma once

class Ball
{
    public:
        
        // values of each one of the balls
        double radio, x, y, z;
        double vx, vy, vz;
        double ax, ay, az;
        double fx, fy, fz;
        double mass;

        // contructor function, sets the position and different velocities of the ball


        Ball(double r, double _x, double _y, double _z, double _vx, double _vy, double _vz, double mass)
        {
            radio = r;
            
            this->x = _x; this->y = _y; this->z = _z;
            this->vx = _vx;  this->vy = _vy; this->vz = _vz; 
            this->mass = mass;
        }

        // function that resets the forces
        void reset_forces()
        {
            this->fx = 0; this->fy = 0; this->fz = 0;
        }

        void calculate_vel(double dt)
        {
            this->vx += this->fx*dt/this->mass;
            this->vy += this->fy*dt/this->mass;
            this->vz += this->fz*dt/this->mass;
        }

        void calculate_pos(double dt)
        {
            this->x += this->vx * dt;
            this->y += this->vy * dt;
            this->z += this->vz * dt;
        }

        void check_pos()
        {
            if (x > WORLD_WIDTH || x < -WORLD_WIDTH)
            {
                x = WORLD_WIDTH / 2;
            }

            if (y > WORLD_HEIGHT || y < -WORLD_HEIGHT - 1)
            {
                y = WORLD_HEIGHT /2;
            }

            if (z > WORLD_DEPTH || z < -WORLD_DEPTH)
            {
                z = WORLD_DEPTH /2;
            }
        }

};