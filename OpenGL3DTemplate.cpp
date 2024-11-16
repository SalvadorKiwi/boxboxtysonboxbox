#include <glut.h>
#include "mikeTyson.h"
#include "ring.h"
#include "collectible.h"  // Include the collectible class
#include <math.h>
#include <stdio.h>

collectible glove;  // Create an instance of the collectible glove
static int score = 0;  // Initialize the score to 0
float chairRotationAngle = 0.0f; // Rotation angle in degrees
bool isDumbbellMovingForward = true; // Flag to control dumbbell movement direction
float pulseScale = 1.0f; // Current scale factor for pulsing
bool increasingPulse = true; // Direction of pulsing scale change

float gameTime = 60.0f; // Game time in seconds (60 seconds)
bool gameOver = false;  // Flag to check if the game is over
bool gameWon = false;   // Flag to check if the game is won



void changeScene() {
	// do a scene changeto a game won screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 800, 0, 600);  // Set the 2D orthographic view
        glMatrixMode(GL_MODELVIEW);

        glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color for the message
        glRasterPos2i(350, 300);  // Position the text in the center
        char message[50];
        if (gameWon) {
       
            sprintf(message, "GAME WIN!");
		}
		else {
			sprintf(message, "GAME OVER!");
		}
        for (int i = 0; message[i] != '\0'; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);  // Display each character
        }

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

    
	}


void drawBoxingBell() {
    glPushMatrix();
    glTranslatef(-6.0f, 0.5f, 6.0f); // Position the bell in the fourth corner

    // Bell base (Cylinder)
    glPushMatrix();
	if (isOpponent){
		glColor3f(1.0f, 1.0f, 0.0f); // 
		}
    else {
        glColor3f(0.0f, 1.0f, 0.3f); // Grey color for the base
    }
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotate to align the base with the ground
    GLUquadric* quad = gluNewQuadric(); // Create quadric object for the cylinder
    gluCylinder(quad, 0.6f, 0.6f, 0.2f, 30, 30); // Base cylinder
    glPopMatrix();

    // Bell body (Disk)
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.0f); // Golden color for the bell
    glTranslatef(0.0f, 0.2f, 0.0f); // Raise the bell body slightly above the base
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate to align with the base
    gluDisk(quad, 0.0f, 0.5f, 30, 1); // Disk for the bell
    glPopMatrix();

    gluDeleteQuadric(quad); // Clean up quadric object
    glPopMatrix();
}
void drawHammer() {
    glPushMatrix();

    // Hammer handle (Cylinder)
    glPushMatrix();
    glColor3f(0.4f, 0.2f, 0.1f); // Brown color for the wooden handle
    glTranslatef(-5.5f, 0.3f, 6.0f); // Position the handle next to the bell
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotate to align vertically
    GLUquadric* quad = gluNewQuadric(); // Create a quadric object for the cylinder
    gluCylinder(quad, 0.05f, 0.05f, 1.0f, 20, 20); // Thin cylinder for handle
    gluDeleteQuadric(quad);
    glPopMatrix();

    // Hammerhead (Cube)
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f); // Dark grey for the metallic hammerhead
    glTranslatef(-5.5f, 0.8f, 6.0f); // Position on top of the handle
    glScalef(0.5f, 0.2f, 0.2f); // Scale to form a rectangular hammerhead
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}



void updatePulse() {
    if (isPulsing) {
        if (increasingPulse) {
            pulseScale += 0.02f; // Increase scale
            if (pulseScale >= 1.2f) { // Maximum scale factor
                increasingPulse = false; // Reverse direction
            }
        }
        else {
            pulseScale -= 0.02f; // Decrease scale
            if (pulseScale <= 0.8f) { // Minimum scale factor
                increasingPulse = true; // Reverse direction
            }
        }
    }
    else {
        pulseScale = 1.0f; // Reset to normal size when not pulsing
    }
}

void drawDumbbell() {
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);  // Gray color for the dumbbell
    glTranslatef(dumbbellPosition, 0.5f, -6.0f);  // Place in a third corner

    // Draw handles
    glPushMatrix();
    glScalef(0.2f, 0.2f, 1.5f);  // Long handle
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw weights
    for (float offset = -0.8f; offset <= 0.8f; offset += 1.6f) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, offset);
        glScalef(0.6f, 0.6f, 0.2f);  // Weights at the ends
        glutSolidCube(1.0);
        glPopMatrix();
    }

    glPopMatrix();
}


void moveDumbbell() {
    if(isDumbbellMoving){
        if (isDumbbellMovingForward) {
            dumbbellPosition += 0.1f;
            if (dumbbellPosition >= 7.0f) {
                isDumbbellMovingForward = false;
            }
        }
        else {
            dumbbellPosition -= 0.1f;
            if (dumbbellPosition <= 5.0f) {
                isDumbbellMovingForward = true;
            }
        }
	}
    glutPostRedisplay();
}


void drawTowel() {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.8f); // Light beige color for the towel
    glTranslatef(6.0f, 0.5f, 6.0f); // Place in the opposite corner of the chair
    glScalef(1.5f * pulseScale, 0.05f * pulseScale, 0.5f * pulseScale); // Apply pulsing scale
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawWaterBottle() {
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 1.0f); // Blue color for the water bottle
    glTranslatef(6.0f, 0.75f, 6.5f); // Place near the towel
    glScalef(0.2f * pulseScale, 0.6f * pulseScale, 0.2f * pulseScale); // Apply pulsing scale
    glutSolidCube(1.0);

    // Bottle cap
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.0f, 0.55f, 0.0f);
    glScalef(0.15f, 0.1f, 0.15f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

void drawReferee() {
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 2.0f);  // Position the referee slightly off-center in the ring

    // Head
    glPushMatrix();
    glColor3f(0.8f, 0.6f, 0.4f);  // Skin color
    glTranslatef(0.0f, 3.5f, 0.0f);
    glutSolidSphere(0.5, 20, 20);  // Head
    glPopMatrix();

    // Torso (striped shirt or shirtless)
    glPushMatrix();
    if (isOpponent) {
        // Shirtless torso
        glColor3f(0.8f, 0.6f, 0.4f);  // Skin color for upper body
        glTranslatef(0.0f, 2.5f, 0.0f);
        glScalef(1.0f, 1.5f, 0.5f);  // Scale to form the torso
        glutSolidCube(1.0);
    }
    else {
        glColor3f(1.8f, 1.6f, 1.4f);  // Skin color for upper body
        glTranslatef(0.0f, 2.5f, 0.0f);
        glScalef(1.0f, 1.5f, 0.5f);  // Scale to form the torso
        glutSolidCube(1.0);
    }
    glPopMatrix();

    // Shorts or pants
    glPushMatrix();
    if (isOpponent) {
        glColor3f(1.0f, 0.0f, 0.0f);  // Opponent shorts (red)
    }
    else {
        glColor3f(0.0f, 0.0f, 0.0f);  // Referee pants (black)
    }
    glTranslatef(0.0f, 1.5f, 0.0f);
    glScalef(1.0f, 1.0f, 0.5f);  // Scale to form the pants/shorts
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

        // Gloves (only in opponent mode)
        if (isOpponent) {
            glPushMatrix();
            glColor3f(1.0f, 0.0f, 0.0f);  // Red gloves
            glTranslatef(x, 2.2f, 0.0f);  // Position near the hands
            glutSolidSphere(0.3, 20, 20); // Glove as a sphere
            glPopMatrix();
        }
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






void drawChair() {
    // Seat
    glPushMatrix();
    glColor3f(0.5f, 0.35f, 0.05f);  // Brown color for wood
    glTranslatef(0.0f, 0.5f, 0.0f); // Raise seat off the ground
    glScalef(1.0f, 0.1f, 1.0f);     // Flatten to make a seat
    glutSolidCube(1.0);
    glPopMatrix();

    // Backrest
    glPushMatrix();
    glColor3f(0.5f, 0.35f, 0.05f);
    glTranslatef(0.0f, 1.0f, -0.45f); // Position behind the seat
    glScalef(1.0f, 1.0f, 0.1f);       // Thin backrest
    glutSolidCube(1.0);
    glPopMatrix();

    // Legs (4 legs)
    for (float x = -0.4f; x <= 0.4f; x += 0.8f) {
        for (float z = -0.4f; z <= 0.4f; z += 0.8f) {
            glPushMatrix();
            glColor3f(0.5f, 0.35f, 0.05f);
            glTranslatef(x, 0.25f, z); // Position at corners of the seat
            glScalef(0.1f, 0.5f, 0.1f); // Thin legs
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
}

void rotateChair() {
    if (isRotating) {
        chairRotationAngle += 2.0f; // Increment rotation angle
        if (chairRotationAngle >= 360.0f) {
            chairRotationAngle -= 360.0f; // Keep angle in range
        }
    }
}


void drawRotatingChair() {
    glPushMatrix();
    glTranslatef(-6.0f, 0.0f, -6.0f); // Position the chair in the back-left corner
    glRotatef(chairRotationAngle, 0.0f, 1.0f, 0.0f); // Apply rotation around Y-axis
    drawChair();
    glPopMatrix();
}

void visualizeScoreInGame() {
    // Display the current score in the game window
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);  // Set the 2D orthographic view
    glMatrixMode(GL_MODELVIEW);

    // Display the score at the top-left corner of the window
    glColor3f(1.0f, 1.0f, 1.0f);  // White text color
    glRasterPos2i(10, 580);  // Position the text
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);  // Format the score text
    for (int i = 0; scoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreText[i]);  // Display each character
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void collectGlove() {
    // Check if the glove is close to Mike Tyson (within a certain distance)
    float distance = sqrt((glove.x - xPos) * (glove.x - xPos) + (glove.z - zPos) * (glove.z - zPos));
    if (distance < 1.0f) {
        // If the glove is close enough, collect it
        glove.isCollected = true;
        score++;  // Increment the score
        glove.spawn();  // Respawn the glove at a new random location
    }
}


void visualizeTime() {
    if (!gameOver) {
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 800, 0, 600);  // Set the 2D orthographic view
        glMatrixMode(GL_MODELVIEW);

        // Display the timer at the top-right corner
        glColor3f(1.0f, 1.0f, 1.0f);  // White text color
        glRasterPos2i(700, 580);  // Position the text
        char timeText[50];
        sprintf(timeText, "Time: %.2f", gameTime);  // Format the time text
        for (int i = 0; timeText[i] != '\0'; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, timeText[i]);  // Display each character
        }

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }
}




void setupLights() {
    GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
    GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
    GLfloat shininess[] = { 50 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
    GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}




void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 640.0 / 480.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set different views based on the 'view' variable
    if (view == 0) {
        // Top View
        gluLookAt(0.0, 20.0, 0.1,  // Eye position (above the scene)
            0.0, 0.0, 0.0,  // Look at the center of the ring
            0.0, 0.0, -1.0); // Up direction (toward the negative z-axis)
    }
    else if (view == 1) {
        // Side View
        gluLookAt(15.0, 5.0, 0.0,  // Eye position (side of the scene)
            0.0, 0.0, 0.0,   // Look at the center of the ring
            0.0, 1.0, 0.0);  // Up direction
    }
    else if (view == 2) {
        // Front View
        gluLookAt(0.0, 5.0, 15.0,  // Eye position (front of the scene)
            0.0, 0.0, 0.0,   // Look at the center of the ring
            0.0, 1.0, 0.0);  // Up direction
    }
    else {
        // Custom camera position for free movement
        gluLookAt(cameraX, cameraY, cameraZ,  // Eye position (movable)
            0.0, 0.0, 0.0,             // Look at the center of the ring
            0.0, 1.0, 0.0);            // Up direction
    }
}


void Display() {
    setupLights();
    setupCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    drawRing();         // Render the boxing ring
    drawReferee();
    drawRotatingChair(); // Render the rotating chair
	drawTowel();        // Render the towel
	drawWaterBottle();  // Render the water bottle
	drawDumbbell();     // Render the dumbbell
    drawBoxingBell();         // Render the bell
	drawHammer();         // Render the hammer
    drawMike();         // Render Mike Tyson

    glove.animate();    // Animate the glove (e.g., rotating)
    glove.render();     // Render the glove

    visualizeScoreInGame();  // Display the score after rendering the 3D scene
	visualizeTime();         // Display the time after rendering the 3D scene

    glFlush();
}

void updateGame(int value) {

    if (!gameOver) {  // Only update the game if it's not over
        // Decrease the time each frame
        gameTime -= 0.016f;  // 60 FPS, so decrease by ~1/60

        // Check if time has run out
        if (gameTime <= 0) {
            gameOver = true;
            changeScene();
			return;
            // If the player collected enough gloves, it's a win
            if (score >= 1) {
                gameWon = true;
                changeScene();
				return;
            }
            else {
                printf("Game Over! You lost the game.\n");
                // Display the 'GAME LOSE' screen here
            }
        }
    }


    rotateChair();       // Update the chair's rotation
    drawReferee();
    collectGlove();      // Check for glove collection
    glove.animate();     // Animate glove movement
	moveDumbbell();      // Move the dumbbell back and forth
	updatePulse();       // Update the pulsing effect
    //gameWin();           // Check for game win condition
    glutPostRedisplay(); // Request re-drawing to update the display
    glutTimerFunc(16, updateGame, 0); // Call this function every 16 ms (roughly 60 FPS)
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("3D Boxing Game");

    glutDisplayFunc(Display);              // Register display function
    glutKeyboardFunc(handleKeypress); // Register chair rotation key handler

    glutTimerFunc(16, updateGame, 0);      // Start the game loop

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glutMainLoop();  // Start the main loop
    return 0;
}
