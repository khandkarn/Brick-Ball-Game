#include <raylib.h>

// Function declarations
void InitGame();         // Initializes the game
void UpdateInput(float deltaTime); // Handles player input
void UpdateGame(float deltaTime);  // Updates the game logic
void DrawGame();         // Renders the game
void CloseGame();        // Cleans up resources

int main()
{
     InitGame();

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        UpdateInput(deltaTime);
        UpdateGame(deltaTime);
        DrawGame();
    }

    CloseGame();

    return 0;
}
