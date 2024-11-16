#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

class collectible {
public:
    float x, y, z;          // Position of the glove
    float rotationAngle;    // Rotation angle for animation
    bool isCollected;       // Whether the glove has been collected
	float shakeTime;        // Time for the shake animation

    // Constructor
    collectible();

    // Function to spawn the glove at a random position inside the ring
    void spawn();

    // Function to animate the glove (rotation in this case)
    void animate();

    // Function to render the glove
    void render();

    bool checkCollection(float mikeX, float mikeZ);

};

#endif
