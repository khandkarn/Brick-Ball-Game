// --------------------------------- Header Files -------------------------------
#include <bits/stdc++.h>
#include <raylib.h>

// ---------------------------------- Constants ---------------------------------
const int WIDTH = 1200;
const int HEIGHT = 700;
const float PADDLE_WIDTH = 10;
const float PADDLE_HEIGHT = 100;
const float BALL_SIZE = 10;
const float MAX_BOUNCE_ANGLE = 60 * (PI / 180.0f); // Max bounce angle in radians
const float INITIAL_BALL_SPEED = 300.0f;

// Game settings
const int MAX_LIVES = 3;
const int HIT_SCORE = 5;

// ------------------------------------ Enums ------------------------------------
enum GameMode
{
    PLAYER_VS_BOT,
    PLAYER_VS_PLAYER
};

enum Difficulty
{
    EASY,
    MEDIUM,
    HARD
};

// ------------------------------- Global Variables ------------------------------
GameMode gameMode = PLAYER_VS_BOT;
float botPaddleSpeed = 0.0f;
float speedIncrement = 0.0f;

// ---------------------------- Function Declarations ----------------------------


/////////////////////////////////////////////////  Nishad  //////////////////////////////////////////////
void HandleModeSelection();

void HandleDifficultySelection();

/////////////////////////////////////////////////  Rahul  //////////////////////////////////////////////
void HandleGameOver();


////////////////////////////////////////////////  Redowan  ////////////////////////////////////////////////
void UpdateGameLogic();


void DrawGameState();

///////////////////////////////////////////////  Theo  //////////////////////////////////////////////////////
void ResetBall(Vector2 &ballPosition, Vector2 &ballDirection, float &ballSpeed);

///////////////////////////////////////////////  Hakim  //////////////////////////////////////////////////////
void HandlePaddleMovement();
                        
void HandleBallCollision();


// ------------------------------------------ Main Function ----------------------------------------------
int main()
{
    return 0;
}

// ----------------------- Function Definitions -----------------------

void ResetBall(Vector2 &ballPosition, Vector2 &ballDirection, float &ballSpeed)
{
    ballPosition = {WIDTH / 2, HEIGHT / 2};
    ballDirection = {ballDirection.x, ballDirection.y > 0 ? 1.0f : -1.0f};
    ballSpeed = INITIAL_BALL_SPEED;
}