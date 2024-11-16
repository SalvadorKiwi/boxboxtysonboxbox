#include "mikeTyson.h"
#include <glut.h>

// Global variables for Mike Tyson's position and movement speed
float xPos = 0.0f, zPos = 0.0f;  // Position of Mike Tyson on the x and z axes
float moveSpeed = 0.1f;           // Movement speed
bool isRotating = false;          // Rotation flag for the character
bool isOpponent = false;          // Track whether the referee looks like an opponent
int view = 0;  // View mode (1: Top, 2: Side, 3: First-person)
float cameraX = 0.0f;
float cameraY = 10.0f;
float cameraZ = 10.0f;
float dumbbellPosition = 6.0f; // Initial position of the dumbbell
bool isDumbbellMoving = false;
bool isPulsing = false;


float facingAngle = 0.0f;


void handleKeypress(unsigned char key, int x, int y) {
    // Save the original position before movement
    float prevX = xPos;
    float prevZ = zPos;

    // Update position and facing angle based on key input
    switch (key) {
    case 's':  // Move down (backward)
        zPos += moveSpeed;
        facingAngle = 180.0f;  // Facing backward
        break;
    case 'w':  // Move up (forward)
        zPos -= moveSpeed;
        facingAngle = 0.0f;    // Facing forward
        break;
    case 'a':  // Move left (along x-axis)
        xPos -= moveSpeed;
        facingAngle = 90.0f;   // Facing left
        break;
    case 'd':  // Move right (along x-axis)
        xPos += moveSpeed;
        facingAngle = -90.0f;  // Facing right
        break;
    case 'p':
        isRotating = !isRotating;  // Toggle rotation state
        break;
    case 'o':
        isOpponent = !isOpponent;  // Toggle opponent state
        break;
    case '1':
        view = 0;  // Top view
        break;
    case '2':
        view = 1;  // Side view
        break;
    case '3':
        view = 2;  // First-person view
        break;
    case 'x':
        view = 5;
        cameraX += 1.0f;  // Move right along the x-axis
        break;
    case 'X':
        view = 5;
        cameraX -= 1.0f;  // Move left along the x-axis
        break;
    case 'y':
        view = 5;
        cameraY += 1.0f;  // Move up along the y-axis
        break;
    case 'Y':
        view = 5;
        cameraY -= 1.0f;  // Move down along the y-axis
        break;
    case 'z':
        view = 5;
        cameraZ += 1.0f;  // Move forward along the z-axis
        break;
    case 'Z':
        view = 5;
        cameraZ -= 1.0f;  // Move backward along the z-axis
        break;
    case 'i':
        isDumbbellMoving = !isDumbbellMoving;  // Toggle dumbbell movement
        break;
    case 'e':
        isPulsing = !isPulsing;  // Toggle dumbbell pulsing
        break;
    default:
        break;
    }

    // Boundary collision detection (adjust for ring size and rope thickness)
    float ringBoundary = 7.0f;  // Outer boundary of the ring (matches rope positions)
    float buffer = 0.5f;       // Buffer for collision detection (half-width of the rope)

    // Check if Mike Tyson goes out of bounds
    if (xPos < -ringBoundary + buffer || xPos > ringBoundary - buffer ||
        zPos < -ringBoundary + buffer || zPos > ringBoundary - buffer) {
        // Revert position to previous if out of bounds
        xPos = prevX;
        zPos = prevZ;
    }

    glutPostRedisplay();  // Request a redraw of the screen
}


// Function to draw Mike Tyson (character model)
void drawMike() {
    glPushMatrix();
    glTranslatef(xPos, 0.0f, zPos);  // Apply movement translation (xPos, zPos)

    glRotatef(facingAngle, 0.0f, 1.0f, 0.0f);


    // Head
    glPushMatrix();
    glColor3f(0.8f, 0.6f, 0.4f);  // Skin color
    glTranslatef(0.0f, 3.5f, 0.0f);
    glutSolidSphere(0.5, 20, 20);  // Head
    glPopMatrix();

    // Torso (striped shirt or shirtless)
    glPushMatrix();

    // Shirtless torso
    glColor3f(0.8f, 0.6f, 0.4f);  // Skin color for upper body
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(1.0f, 1.3f, 0.8f);  // Scale to form the torso
    glutSolidCube(1.0);

    glPopMatrix();

    // Shorts or pants
    glPushMatrix();


    glColor3f(0.0f, 0.0f, 0.0f);  // Referee pants (black)

    glTranslatef(0.0f, 1.5f, 0.0f);
    glScalef(1.1f, 1.0f, 0.5f);  // Scale to form the pants/shorts
    glutSolidCube(1.0);
    glPopMatrix();

    // Arms
    for (float x = -0.7f; x <= 0.7f; x += 1.4f) {
        glPushMatrix();
        glColor3f(0.8f, 0.6f, 0.4f);  // Skin color
        glTranslatef(x, 2.8f, 0.0f);
        glScalef(0.2f, 0.8f, 0.2f);  // Scale to form the arms
        glutSolidCube(1.0);
        glPopMatrix();


        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);  // Red gloves
        glTranslatef(x, 2.2f, 0.0f);  // Position near the hands
        glutSolidSphere(0.3, 20, 20); // Glove as a sphere
        glPopMatrix();

    }

    // Legs
    for (float x = -0.4f; x <= 0.4f; x += 0.8f) {
        glPushMatrix();
        glColor3f(0.8f, 0.6f, 0.4f);  // Skin color
        glTranslatef(x, 0.8f, 0.0f);
        glScalef(0.2f, 1.0f, 0.2f);  // Scale to form the legs
        glutSolidCube(1.0);
        glPopMatrix();
    }

    glPopMatrix();  // End of referee model

}
