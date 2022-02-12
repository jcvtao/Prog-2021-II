// INCLUDE OpenGL LIBRARY
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// INCLUDE STANDARD LIBRARIES
#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <string.h>
#include <cmath>

// INCLUDE SIMULATION HEADERS
#include "classes/constants.h"
#include "classes/ball.h"
#include "classes/world_generation.h"
#include "classes/vector3.h"

// =============================================

// ### GLOBAL VARIABLES ###

// ## ANIMATION VARIABLES ##

// # Position vectors for each coordinate #
std::vector<GLfloat> xPos(NO_BALLS, 0.0);
std::vector<GLfloat> yPos(NO_BALLS, 0.0);
std::vector<GLfloat> zPos(NO_BALLS, 0.0);

// # Color vectors for each RGB value #
std::vector<GLfloat> RED(NO_BALLS, 1.0);
std::vector<GLfloat> GREEN(NO_BALLS, 1.0);
std::vector<GLfloat> BLUE(NO_BALLS, 1.0);

GLfloat xAngle, yAngle, zAngle;	       // Rotation angles
GLfloat L_ALPHA, R_ALPHA, T_ALPHA,     // Alpha values
		BOT_ALPHA, F_ALPHA, BAC_ALPHA;

// ### PERSPECTIVE VARIABLES ###
GLdouble zNear; // Near clipping plane
GLfloat	DEPTH; 	// Fixed depth
GLdouble zFar;  // Far clipping plance

// =============================================

// ### DECLARATIONS ###

// ## OpenGL ##
void display(void);			// Display function
void timer(int);			// Timer function
void init(void);			// Initial values function
void reshape(int x, int y); // Reshape function

// ## SIMULATION ##
void calculate_forces(Ball &particle);
void check_collitions(Ball &p1, Ball &p2);
void print_results(double time, Ball particle);

// =============================================
// =============================================

// ### MAIN FUNCTION ###
int main(int argc, char *argv[])
{
	// ### SIMULATION ###

	// CHECK IF PARAMETERS INPUT IS DONE CORRECTLY
    if ( ((argc - 1) % 2) != 0  )
    {
        std::cout << "INVALID PARAMETERS INPUT, SHOULD BE \" -parameter parameter_value \". \n "
        " Example: \" source.exe -radius 10 \" " << std::endl;

        return 1;
    }

    // GENERATE THE SCENARIO DEPENDING ON THE INPUTS GIVEN IN THE CONSOLE
    generate_world(argc, argv);

	// RESIZE POSITIONS VECTORS
	xPos.resize(NO_BALLS); yPos.resize(NO_BALLS); zPos.resize(NO_BALLS);

	// RESIZE RGB VALUES VECTORS
	RED.resize(NO_BALLS); GREEN.resize(NO_BALLS); BLUE.resize(NO_BALLS);

	// UPDATE PERSPECTIVE VARIABLE VALUES
	zNear = 0.5; 						  // Near clipping plane
	DEPTH = -(zNear + WORLD_DEPTH + 4.5); // Fixed depth
	zFar = -(DEPTH + -WORLD_DEPTH - 5.0); // Far clipping plane

	// =============================================

	// ### OpenGL ###

	// ## Initialize GLUT ##
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(30, 10); 							  // Window (initial) position
	glutInitWindowSize(1280, 720);	  							  // Window (initial) size
	glutCreateWindow("OpenGL - Bouncing Ball Animation");		  // Window title

	// # OpenGL functions setup #
	glutDisplayFunc(display);   // Set "display" function
	glutReshapeFunc(reshape);   // Set "reshape" function
	glutTimerFunc(0, timer, 0); // Set "timer" function
	init();					    // Set initial values

	glutMainLoop(); 		    // Start render loop


	return 1;
}

// =============================================
// =============================================

// ### OPENGL DEFINITIONS ###

// DISPLAY FUNCTION: Renders the shapes to the screen using the values provided; main OpenGL function for the animation
void display(void)
{
	// ### GLUT SETUP ###
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// =============================================

	/* ### BALL (SPHERE) ###
	 * The ball, our main shape in the animation, is a wire sphere which is translated through the world
	 * using different OpenGL functions which update its position matrix on every renderization. Moreover,
	 * it has a slight arbitrary rotational effect added to give a more realistic look to the animation, and
	 * its color changes every time it bounces with a wall (or the floor) to the respective color of that surface.
	 * 
	 * The RADIUS of the sphere can be set when executing the progam (using "-radious <value>"), otherwise its
	 * default value is 0.25 (see classes/constants.h); the number of slices and stacks of the sphere are 20 by
	 * default and can be changed in the present code (see # Render the ball #).
	*/
	for (int ii = 0; ii < NO_BALLS; ++ii)
	{
		glLoadIdentity();

		// # Translation of ball #
		glTranslatef(xPos[ii], yPos[ii], zPos[ii] + DEPTH); // (x, y, z)

		// # Rotation of ball #
		glRotatef(xAngle, 1.0, 0.0, 0.0); // x axis
		glRotatef(yAngle, 0.0, 1.0, 0.0); // y axis
		glRotatef(zAngle, 0.0, 0.0, 1.0); // z axis

		// # Size and color of ball #
		glScalef(1.0, 1.0, 1.0);
		glColor3f(RED[ii], GREEN[ii], BLUE[ii]);
		
		// # Render the ball #
		glutWireSphere(RADIUS, 20, 20); // (RADIUS, slices, stacks)
	}

	// =============================================	

	/* ### WORLD (CUBE) ###
	 * The first cube only has visible its edges (lines) and creates the perspective of a box (the 'world').
	 * The second cube only has visible its sides (walls) every time the ball bounces on one of them; this
	 * effect is generated by updating the alpha value in its color momentarily whenever a ball reaches a wall.
	*/

	// ## WORLD (LINES) ##
	glLoadIdentity();
	glTranslatef(0.0, 0.0, DEPTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Lines mode
	
	// # Vertices #
	glBegin(GL_QUADS);

		// Front
		glColor4f(0.0, 1.0, 0.0, 1.0); // Green
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);

		// Back
		glColor4f(0.0, 0.0, 1.0, 1.0); // Blue
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);

		// Right
		glColor4f(1.0, 0.0, 0.0, 1.0); // Red
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);

		// left
		glColor4f(1.0, 0.35, 0.0, 1.0); // Orange
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);

		// Top
		glColor4f(1.0, 1.0, 1.0, 1.0); // White
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);

		// Bottom
		glColor4f(1.0, 1.0, 0.0, 1.0); // Yellow
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);

	glEnd();

	// ## WORLD (WALLS) ##
	glLoadIdentity();
	glTranslatef(0.0, 0.0, DEPTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Fill mode
	
	// # Vertices #
	glBegin(GL_QUADS);

		// Front
		glColor4f(0.0, 1.0, 0.0, F_ALPHA); // Green
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);

		// Back
		glColor4f(0.0, 0.0, 1.0, BAC_ALPHA); // Blue
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);

		// Right
		glColor4f(1.0, 0.0, 0.0, R_ALPHA); // Red
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);

		// left
		glColor4f(1.0, 0.35, 0.0, L_ALPHA); // Orange
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);

		// Top
		glColor4f(1.0, 1.0, 1.0, T_ALPHA); // White
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, WORLD_HEIGHT, -WORLD_DEPTH);

		// Bottom
		glColor4f(1.0, 1.0, 0.0, BOT_ALPHA); // Yellow
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);
		glVertex3f(-WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, WORLD_DEPTH);
		glVertex3f(WORLD_WIDTH, -WORLD_HEIGHT, -WORLD_DEPTH);

	glEnd();

	// =============================================

	// Swap buffers (render)
	glutSwapBuffers();
}

// TIMER FUNCTION: Updates the values of the animation every frame; called every (int)1000/FPS miliseconds during the the animation
void timer(int)
{
	//glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, 0); // Recall timer function every (int)1000/FPS miliseconds

	// ### BALL'S CHANGES ###
	
	// ## Update ball's rotation ##
	xAngle += 0.05;
	yAngle += 0.05;
	zAngle += 0.05;

	// # Update balls data #
	int ii = 0;
	for (auto &particle : particles)
    {
		particle.check_pos();		// Check position

		calculate_forces(particle); // Forces
		particle.calculate_vel(DT); // Velocity
		particle.calculate_pos(DT); // Position
	
		// # Update position values #
		xPos[ii] = particle.x; // x axis: Left to Right
		yPos[ii] = particle.y; // y axis: Bottom to Top
		zPos[ii] = particle.z; // z axis: Back to Front

		++ii; // Increase vectors' index counter
	}

	// =============================================

	// ### WORLD'S CHANGES ###
	
	// ## Change color on bounce! ##
	
	// # Reset alpha values #
	L_ALPHA = R_ALPHA = T_ALPHA = 0.0;
	BOT_ALPHA = F_ALPHA = BAC_ALPHA = 0.0;
	
	// # Conditionals (for every world's wall and for every ball) #
	for (int jj = 0; jj < NO_BALLS; ++jj)
	{
		if (xPos[jj] + RADIUS >= WORLD_WIDTH) // Right - Red
		{
			R_ALPHA = 0.5;
		}
		else if (yPos[jj] + RADIUS >= WORLD_HEIGHT) // Top - White
		{
			T_ALPHA = 0.5;
		}
		else if (zPos[jj] + RADIUS >= WORLD_DEPTH) // Front - Green
		{
			F_ALPHA = 0.5;
		}
		else if (xPos[jj] - RADIUS <= -WORLD_WIDTH) // Left - Orange
		{
			L_ALPHA = 0.5;
		}
		else if (yPos[jj] - RADIUS <= -WORLD_HEIGHT) // Bottom - Yellow
		{
			BOT_ALPHA = 0.5;
		}
		else if (zPos[jj] - RADIUS <= -WORLD_DEPTH) // Back - Blue
		{
			BAC_ALPHA = 0.5;
		}
	}


	glutPostRedisplay();
}

// INITIAL VALUES FUNCTION: Sets the initial values of the animation
void init(void)
{
	// ## Initial rotation angle(s) [in degrees] ##
	xAngle = yAngle = zAngle = 0.0;

	// ## Initial translation position ##
	for (int ii = 0; ii < NO_BALLS; ++ii)
	{
		xPos[ii] = particles[ii].x;
		yPos[ii] = particles[ii].y;
		zPos[ii] = particles[ii].z;
	}

	// ## Set colors to each ball
	if (NO_BALLS > 1)
	{
		for (int ii = 0; ii < NO_BALLS; ++ii)
		{
			if ((ii + 1) >= 7) // For +7 balls
			{
				RED[ii] = 1.0; GREEN [ii] = 1.0; BLUE[ii] = 1.0; // (White)
			}
			else if ((ii + 1) % 6 == 0)
			{
				RED[ii] = 1.0; GREEN [ii] = 0.0; BLUE[ii] = 0.0; // (Red)
			}
			else if ((ii+1) % 5 == 0)
			{
				RED[ii] = 0.0; GREEN [ii] = 1.0; BLUE[ii] = 0.0; // (Green)
			}
			else if ((ii+1) % 4 == 0)
			{
				RED[ii] = 0.0; GREEN [ii] = 1.0; BLUE[ii] = 1.0; // (Cyan)
			}
			else if ((ii+1) % 3 == 0)
			{
				RED[ii] = 1.0; GREEN [ii] = 0.0; BLUE[ii] = 1.0; // (Magenta)
			}
			else if ((ii+1) % 2 == 0)
			{
				RED[ii] = 1.0; GREEN [ii] = 1.0; BLUE[ii] = 0.0; // (Yellow)
			}
			else
			{
				RED[ii] = 1.0; GREEN [ii] = 1.0; BLUE[ii] = 1.0; // (White)
			}
		}
	}

	// ## Initial alpha values ##
	L_ALPHA = R_ALPHA = T_ALPHA = 0.0;
	BOT_ALPHA = F_ALPHA = BAC_ALPHA = 0.0;

	// ## Coloring setup ##
	glClearColor(0.0, 0.0, 0.0, 1.0); 					// Sets background color (Black)
	glEnable(GL_BLEND);				  					// Enable transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Enable alpha values
}

// RESHAPE FUNCTION: Sets the perspective of the animation every time the window is resized/reshaped
void reshape(int x, int y)
{
	if (y == 0 || x == 0)
		return;

	glViewport(0, 0, x, y);

	// ## Set perspective ##
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)x / (GLdouble)y, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
}

// =============================================

// ### SIMULATION DEFINITIONS ###
void calculate_forces(Ball &particle)
{
    // Reset the forces of the particle
    particle.reset_forces();

    // All time, the particle is interacting with gravity, so one force
    // acting constantly is gravity

    if (particle.y - particle.radio > -WORLD_HEIGHT)
    {
        particle.fy += particle.mass * G;
    }

    // Now lets check if the particle is interacting with any of the walls
    double delta;

    // For left wall
    delta = particle.x - particle.radio + WORLD_WIDTH;
    if (delta < 0)
    {
        particle.fx += -K * delta; 

		if (DISIPATION_FLAG)
		{
			particle.fx -= DISIPATION_CONSTANT * particle.vx;
		}
    }

    // For right wall
    delta = particle.x + particle.radio - WORLD_WIDTH;
    if (delta > 0)
    {
        particle.fx += -K * delta;

		if (DISIPATION_FLAG)
		{
			particle.fx -= DISIPATION_CONSTANT * particle.vx;
		}
    }

	//For the roof
    delta = particle.y - particle.radio + WORLD_HEIGHT;
    if (delta < 0)
    {
        particle.fy += -K * delta;

		if (DISIPATION_FLAG)
		{
			particle.fy -= DISIPATION_CONSTANT * particle.vy;
			
			
			particle.fx -= DISIPATION_CONSTANT * particle.vx;
			particle.fz -= DISIPATION_CONSTANT * particle.vz;
		}
    }

	//For the roof
    delta = particle.y + particle.radio - WORLD_HEIGHT;
    if (delta > 0)
    {
        particle.fy += -K * delta;

		if (DISIPATION_FLAG)
		{
			particle.fy -= DISIPATION_CONSTANT * particle.vy;
		}
    }

    // For the front wall
    delta = particle.z + particle.radio - WORLD_DEPTH;
    if (delta > 0)
    {
        particle.fz += -K * delta;

		if (DISIPATION_FLAG)
		{
			particle.fz -= DISIPATION_CONSTANT * particle.vz;
		}
    }

    // For the back wall
    delta = particle.z - particle.radio + WORLD_DEPTH;
    if (delta < 0)
    {
        particle.fz += -K * delta;

		if (DISIPATION_FLAG)
		{
			particle.fz -= DISIPATION_CONSTANT * particle.vz;
		}
    }

    // Check for collitions with other balls
    for (auto &p1 : particles)
    {
        for (auto &p2 : particles)
        {   
            // if both parti les are the same, jut continue
            if (&p1 == &p2)
            {
                continue;
            } else
            {
                // Else, check if there's a collition
                check_collitions(p1, p2);
            }
        }
    }

}

// Function that checks if 2 particles are colliding with each other and calculate it's forces
void check_collitions(Ball &p1, Ball &p2)
{
    // check the distance between the center of the spheres
    double dist = std::sqrt( std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2) + std::pow((p1.z - p2.z), 2) );

    // if the distance is less than the sum of the radios, both balls are touching
    if (dist < (p1.radio + p2.radio))
    {
        //std::cout << "COLITION\n";
        Vector3 vec2_1 = { (p1.x - p2.x), (p1.y - p2.y), (p1.z - p2.z) };
        vec2_1 = vec2_1.normalize();

        double delta = dist - p1.radio - p2.radio;
        double force = -K * delta;

        Vector3 forceP1 = force * vec2_1;
        Vector3 forceP2 = force * (-1.0 * vec2_1);

        p1.fx = forceP1.a;
        p1.fy = forceP1.b;
        p1.fz = forceP1.c;
        
        p2.fx = forceP2.a;
        p2.fy = forceP2.b;
        p2.fz = forceP2.c;
    }
}

void print_results(double time, Ball particle)
{
    std::cout << time << "\t"
    << particle.x << "\t" 
    << particle.y << "\t"
    << particle.z << std::endl;
}

// =============================================