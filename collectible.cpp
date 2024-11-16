#include "collectible.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <glut.h>
#include <cmath>    // For sin() and cos()

// Constructor to initialize position and state
collectible::collectible() : x(0.0f), y(0.0f), z(0.0f), rotationAngle(0.0f), isCollected(false), shakeTime(0.0f) {
    spawn();  // Randomly place the glove inside the ring
}

// Function to spawn the glove at a random position inside the ring
void collectible::spawn() {
    // Random x, z coordinates inside the ring (assuming a simple square area for the ring)
    x = static_cast<float>(rand() % 10 - 5);  // Random number between -5 and 5
    z = static_cast<float>(rand() % 10 - 5);  // Random number between -5 and 5
    isCollected = false;
}

// Function to animate the glove (shake effect)
void collectible::animate() {
    shakeTime += 0.1f;  // Increment shake time for smooth animation

    // Create a shake effect by oscillating the glove's position along the Y axis
    // Sinusoidal movement will make the glove shake back and forth
    float shakeAmplitude = 0.1f;  // The amount of shake (adjust for stronger/weaker shake)
    float shakeSpeed = 2.0f;      // Speed of the shake (higher means faster shaking)

    // Apply shaking to the glove's position along the Y-axis (vertical shake)
    y = shakeAmplitude * sin(shakeTime * shakeSpeed);  // Oscillates back and forth in the Y direction
}

// Function to render the glove with design
void collectible::render() {
    glPushMatrix();
    glTranslatef(x, 1.5f + y, z);  // Position glove at (x, 1.5f + y, z), with shaking added on the Y-axis

    // Rotate the glove so that the palm is facing down initially
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  // Tilt the glove to have the palm facing down

    // Draw the glove body (using a combination of spheres and cubes to approximate the glove)
    glColor3f(1.0f, 0.2f, 0.2f);  // Red color for the glove (use the color you want)

    // Draw the main body of the glove (big rounded shape for the hand part)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glutSolidSphere(0.3f, 20, 20);  // The main glove shape
    glPopMatrix();

    // Draw the thumb of the glove (a small sphere attached to the main body)
    glPushMatrix();
    glTranslatef(0.35f, 0.0f, 0.0f);  // Thumb position
    glutSolidSphere(0.15f, 20, 20);   // Thumb sphere
    glPopMatrix();

    // Draw the lines on the glove as if they are printed on the surface (not just 3D stitching)
    glColor3f(0.1f, 0.1f, 0.1f);  // Dark color for the design/lines (printed)

    // Draw vertical design lines (simulating logo or pattern)
    glBegin(GL_LINES);
    for (float i = -0.2f; i < 0.2f; i += 0.05f) {
        glVertex3f(i, 0.25f, 0.2f);   // Starting point on the surface of the glove
        glVertex3f(i, 0.25f, -0.2f);  // Ending point
    }

    // Draw some horizontal lines (wrapping the glove like stripes)
    for (float j = -0.2f; j < 0.2f; j += 0.05f) {
        glVertex3f(-0.3f, 0.25f, j);  // Starting point of a horizontal line
        glVertex3f(0.3f, 0.25f, j);   // Ending point of the horizontal line
    }
    glEnd();

    glPopMatrix();
}

// Function to check if Mike Tyson has collected the glove
bool collectible::checkCollection(float mikeX, float mikeZ) {
    float collectionDistance = 0.5f;  // The radius within which the glove can be collected
    if (!isCollected && (fabs(mikeX - x) < collectionDistance && fabs(mikeZ - z) < collectionDistance)) {
        isCollected = true;  // Mark as collected
        return true;  // Collection successful
    }
    return false;  // Not collected
}
