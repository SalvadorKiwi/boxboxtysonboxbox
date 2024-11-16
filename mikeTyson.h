
#ifndef MIKE_TYSON_H
#define MIKE_TYSON_H

// Structure to represent each glove's position


// Global variables for character position
extern float xPos, zPos;  // Position of Mike Tyson
extern float moveSpeed;    // Movement speed



//since en ana 7atet el handleKeypress f mikeTyson.cpp fa ha7ot all flags hena T_T


extern bool isRotating;   // Rotation flag for the character
extern bool isOpponent;  // Track whether the referee looks like an opponent
extern int view;
extern float cameraX;
extern float cameraY;
extern float cameraZ;
extern float dumbbellPosition;
extern bool isDumbbellMoving;
extern bool isPulsing
;


// Function declarations
void drawMike();
void handleKeypress(unsigned char key, int x, int y);  // Handle WASD keys for movement





#endif

