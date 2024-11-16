#include "ring.h"
#include <cstdlib>  // For rand()
#include <glut.h>


float ropeColorR = 1.0f;
float ropeColorG = 0.0f;
float ropeColorB = 0.0f;



void drawRing() {
    // Base Platform
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.8f);  // Light gray color for the base
    glScalef(15.0f, 0.5f, 15.0f);  // Scale to create a larger platform
    glutSolidCube(1.0);  // Cube as the base
    glPopMatrix();

    // Corner Posts (Trimmed from top)
    float postPositions[4][2] = { {-7.0f, -7.0f}, {7.0f, -7.0f}, {7.0f, 7.0f}, {-7.0f, 7.0f} };
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);  // Dark gray posts
        glTranslatef(postPositions[i][0], 1.0f, postPositions[i][1]);  // Adjusted height for shorter posts
        glScalef(0.3f, 2.0f, 0.3f);  // Scale to make shorter, thicker posts (height trimmed)
        glutSolidCube(1.0);
        glPopMatrix();
    }

    // Ropes
    for (float y = 0.5f; y <= 1.5f; y += 0.5f) {  // Three heights for the ropes
        // Ropes along the four sides of the ring
        float ropePositions[4][3] = {
            {0.0f, y, -7.0f},  // Bottom side
            {7.0f, y, 0.0f},   // Right side
            {0.0f, y, 7.0f},   // Top side
            {-7.0f, y, 0.0f}   // Left side
        };

        for (int i = 0; i < 4; ++i) {
            glPushMatrix();
            glColor3f(ropeColorR, ropeColorG, ropeColorB);
            glTranslatef(ropePositions[i][0], ropePositions[i][1], ropePositions[i][2]);

            if (i % 2 == 0) {  // Horizontal sides
                glScalef(15.0f, 0.1f, 0.1f);
            }
            else {  // Vertical sides
                glScalef(0.1f, 0.1f, 15.0f);
            }

            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
}
