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
void HandleModeSelection(bool &modeChosen, bool &difficultyChosen);

void HandleDifficultySelection(bool &difficultyChosen, float &botPaddleSpeed, float &speedIncrement);

/////////////////////////////////////////////////  Rahul  //////////////////////////////////////////////

void HandleGameOver(bool &gameOver, bool &player1Won, bool &modeChosen, bool &difficultyChosen,
                    int &player1Lives, int &player2Lives, int &player1Score, int &player2Score,
                    Vector2 &ballPosition, Vector2 &ballDirection, float &ballSpeed);

////////////////////////////////////////////////  Redowan  ////////////////////////////////////////////////
void UpdateGameLogic(Vector2 &ballPosition, Vector2 &ballDirection, float &ballSpeed,
                     int &player1Lives, int &player2Lives, int &player1Score, int &player2Score,
                     float &player1PaddleY, float &player2PaddleY, bool &gameOver, bool &player1Won);

void DrawGameState(float player1PaddleY, float player2PaddleY, Vector2 ballPosition,
                   int player1Lives, int player2Lives, int player1Score, int player2Score);

///////////////////////////////////////////////  Theo  //////////////////////////////////////////////////////
void ResetBall(Vector2 &ballPosition, Vector2 &ballDirection, float &ballSpeed);

///////////////////////////////////////////////  Hakim  //////////////////////////////////////////////////////
void HandlePaddleMovement(float &player1PaddleY, float &player2PaddleY, const Vector2 &ballPosition);

void HandleBallCollision(Vector2 &ballDirection, float &ballSpeed, int &player1Score, int &player2Score,
                         const float player1PaddleY, const float player2PaddleY, Vector2 &ballPosition);

// ------------------------------------------ Main Function ----------------------------------------------
int main()
{
    InitWindow(WIDTH, HEIGHT, "Brick Ball Game");
    SetTargetFPS(60);

    // Game state variables
    bool modeChosen = false;
    bool difficultyChosen = false;

    // Paddle positions
    float player1PaddleY = (HEIGHT - PADDLE_HEIGHT) / 2;
    float player2PaddleY = (HEIGHT - PADDLE_HEIGHT) / 2;

    // Ball state
    Vector2 ballPosition = {WIDTH / 2, HEIGHT / 2};
    float ballSpeed = INITIAL_BALL_SPEED;
    Vector2 ballDirection = {1.0f, 1.0f};

    // Player stats
    int player1Lives = MAX_LIVES, player2Lives = MAX_LIVES;
    int player1Score = 0, player2Score = 0;

    // Game over state
    bool gameOver = false, player1Won = false;

    while (!WindowShouldClose())
    {
        if (!modeChosen)
        {
            HandleModeSelection(modeChosen, difficultyChosen);
            continue;
        }

        if (gameMode == PLAYER_VS_BOT && !difficultyChosen)
        {
            HandleDifficultySelection(difficultyChosen, botPaddleSpeed, speedIncrement);
            continue;
        }

        if (gameOver)
        {
            HandleGameOver(gameOver, player1Won, modeChosen, difficultyChosen, player1Lives, player2Lives, player1Score, player2Score, ballPosition, ballDirection, ballSpeed);
            continue;
        }

        UpdateGameLogic(ballPosition, ballDirection, ballSpeed, player1Lives, player2Lives, player1Score, player2Score, player1PaddleY, player2PaddleY, gameOver, player1Won);

        // Drawing
        DrawGameState(player1PaddleY, player2PaddleY, ballPosition, player1Lives, player2Lives, player1Score, player2Score);
    }

    CloseWindow();
    return 0;
}

void HandleModeSelection(bool &modeChosen, bool &difficultyChosen)
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Select Game Mode:", WIDTH / 2 - MeasureText("Select Game Mode:", 40) / 2, HEIGHT / 2 - 60, 40, WHITE);
    DrawText("1. Player vs Bot", WIDTH / 2 - MeasureText("1. Player vs Bot", 20) / 2, HEIGHT / 2, 20, GREEN);
    DrawText("2. Player vs Player", WIDTH / 2 - MeasureText("2. Player vs Player", 20) / 2, HEIGHT / 2 + 30, 20, BLUE);

    if (IsKeyPressed(KEY_ONE))
    {
        gameMode = PLAYER_VS_BOT;
        modeChosen = true;
    }
    if (IsKeyPressed(KEY_TWO))
    {
        gameMode = PLAYER_VS_PLAYER;
        modeChosen = true;
        difficultyChosen = true; // Skip difficulty selection for Player vs Player
    }

    EndDrawing();
}

void HandleDifficultySelection(bool &difficultyChosen, float &botPaddleSpeed, float &speedIncrement)
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Select Difficulty:", WIDTH / 2 - MeasureText("Select Difficulty:", 40) / 2, HEIGHT / 2 - 60, 40, WHITE);
    DrawText("1. Easy", WIDTH / 2 - MeasureText("1. Easy", 20) / 2, HEIGHT / 2, 20, GREEN);
    DrawText("2. Medium", WIDTH / 2 - MeasureText("2. Medium", 20) / 2, HEIGHT / 2 + 30, 20, YELLOW);
    DrawText("3. Hard", WIDTH / 2 - MeasureText("3. Hard", 20) / 2, HEIGHT / 2 + 60, 20, RED);

    if (IsKeyPressed(KEY_ONE))
    {
        botPaddleSpeed = 2.0f;
        speedIncrement = 10.0f;
        difficultyChosen = true;
    }
    if (IsKeyPressed(KEY_TWO))
    {
        botPaddleSpeed = 3.0f;
        speedIncrement = 20.0f;
        difficultyChosen = true;
    }
    if (IsKeyPressed(KEY_THREE))
    {
        botPaddleSpeed = 4.5f;
        speedIncrement = 30.0f;
        difficultyChosen = true;
    }

    EndDrawing();
}

void HandleGameOver(bool &gameOver, bool &player1Won, bool &modeChosen, bool &difficultyChosen,
                            int &player1Lives, int &player2Lives, int &player1Score, int &player2Score,
                                         Vector2 &ballPosition, Vector2 &ballDirection, float &ballSpeed)
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (player1Won)
    {
        DrawText("Player 1 Wins!", WIDTH / 2 - MeasureText("Player 1 Wins!", 40) / 2, HEIGHT / 2 - 20, 40, GREEN);
    }
    else
    {
        DrawText("Player 2 Wins!", WIDTH / 2 - MeasureText("Player 2 Wins!", 40) / 2, HEIGHT / 2 - 20, 40, BLUE);
    }
    DrawText("Press ENTER to Play Again", WIDTH / 2 - MeasureText("Press ENTER to Play Again", 20) / 2, HEIGHT / 2 + 50, 20, WHITE);

    if (IsKeyPressed(KEY_ENTER))
    {
        // Reset game
        player1Lives = MAX_LIVES;
        player2Lives = MAX_LIVES;
        player1Score = 0;
        player2Score = 0;
        gameOver = false;

        // Reset ball position
        ResetBall(ballPosition, ballDirection, ballSpeed);

        // Allow mode & difficulty selection again
        modeChosen = false;
        difficultyChosen = false;
    }

    EndDrawing();
}


void UpdateGameLogic(Vector2 &ballPosition, Vector2 &ballDirection, float &ballSpeed,
                     int &player1Lives, int &player2Lives, int &player1Score, int &player2Score,
                     float &player1PaddleY, float &player2PaddleY, bool &gameOver, bool &player1Won)
{
    // Ball's movement Handling
    ballPosition.x += ballDirection.x * ballSpeed * GetFrameTime();
    ballPosition.y += ballDirection.y * ballSpeed * GetFrameTime();

    // Paddle's movement Handling
    HandlePaddleMovement(player1PaddleY, player2PaddleY, ballPosition);

    // Collision Handling
    HandleBallCollision(ballDirection, ballSpeed, player1Score, player2Score, player1PaddleY, player2PaddleY, ballPosition);

    // Checking if the ball goes out of bounds
    if (ballPosition.x < 0)
    {
        player1Lives--;
        ResetBall(ballPosition, ballDirection, ballSpeed);
    }
    else if (ballPosition.x > WIDTH)
    {
        player2Lives--;
        ResetBall(ballPosition, ballDirection, ballSpeed);
    }

    // Checking for game over
    if (player1Lives == 0 || player2Lives == 0)
    {
        gameOver = true;
        player1Won = player1Lives > 0;
    }
}

// ----------------------- Function Definitions -----------------------
void UpdateGameLogic(Vector2 &ballPosition, Vector2 &ballDirection, float &ballSpeed,
                     int &player1Lives, int &player2Lives, int &player1Score, int &player2Score,
                     float &player1PaddleY, float &player2PaddleY, bool &gameOver, bool &player1Won)
{
    // Ball's movement Handling
    ballPosition.x += ballDirection.x * ballSpeed * GetFrameTime();
    ballPosition.y += ballDirection.y * ballSpeed * GetFrameTime();

    // Paddle's movement Handling
    HandlePaddleMovement(player1PaddleY, player2PaddleY, ballPosition);

    // Collision Handling
    HandleBallCollision(ballDirection, ballSpeed, player1Score, player2Score, player1PaddleY, player2PaddleY, ballPosition);

    // Checking if the ball goes out of bounds
    if (ballPosition.x < 0)
    {
        player1Lives--;
        ResetBall(ballPosition, ballDirection, ballSpeed);
    }
    else if (ballPosition.x > WIDTH)
    {
        player2Lives--;
        ResetBall(ballPosition, ballDirection, ballSpeed);
    }

    // Checking for game over
    if (player1Lives == 0 || player2Lives == 0)
    {
        gameOver = true;
        player1Won = player1Lives > 0;
    }
}

void DrawGameState(float player1PaddleY, float player2PaddleY, Vector2 ballPosition, int player1Lives, int player2Lives, int player1Score, int player2Score)
{
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw paddles and ball
    DrawRectangle(0, player1PaddleY, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
    DrawRectangle(WIDTH - PADDLE_WIDTH, player2PaddleY, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
    DrawCircle(ballPosition.x, ballPosition.y, BALL_SIZE, WHITE);

    // Draw scores and lives
    DrawText(TextFormat("P1 Lives: %d", player1Lives), 20, 20, 20, GREEN);
    DrawText(TextFormat("P1 Score: %d", player1Score), 20, 50, 20, GREEN);
    DrawText(TextFormat("P2 Lives: %d", player2Lives), WIDTH - 140, 20, 20, BLUE);
    DrawText(TextFormat("P2 Score: %d", player2Score), WIDTH - 140, 50, 20, BLUE);

    EndDrawing();
}

void ResetBall(Vector2 &ballPosition, Vector2 &ballDirection, float &ballSpeed)
{
    ballPosition = {WIDTH / 2, HEIGHT / 2};
    ballDirection = {ballDirection.x, ballDirection.y > 0 ? 1.0f : -1.0f};
    ballSpeed = INITIAL_BALL_SPEED;
}

void HandleBallCollision(Vector2 &ballDirection, float &ballSpeed, int &player1Score, int &player2Score, const float player1PaddleY, const float player2PaddleY, Vector2 &ballPosition)
{
    if (ballPosition.y < 0 || ballPosition.y > HEIGHT)
        ballDirection.y = -ballDirection.y;
    if (ballPosition.x < PADDLE_WIDTH && ballPosition.y > player1PaddleY && ballPosition.y < player1PaddleY + PADDLE_HEIGHT)
    {
        ballDirection.x = fabs(ballDirection.x);
        player1Score += HIT_SCORE;
    }
    if (ballPosition.x > WIDTH - PADDLE_WIDTH - BALL_SIZE && ballPosition.y > player2PaddleY && ballPosition.y < player2PaddleY + PADDLE_HEIGHT)
    {
        ballDirection.x = -fabs(ballDirection.x);
        player2Score += HIT_SCORE;
    }
}
void HandlePaddleMovement(float &player1PaddleY, float &player2PaddleY, const Vector2 &ballPosition)
{ // Player 1 movement
    if (IsKeyDown(KEY_W) && player1PaddleY > 0)
        player1PaddleY -= 5.0f;
    if (IsKeyDown(KEY_S) && player1PaddleY < HEIGHT - PADDLE_HEIGHT)
        player1PaddleY += 5.0f;
    // Player 2 or Bot movement
    if (gameMode == PLAYER_VS_PLAYER)
    {
        if (IsKeyDown(KEY_UP) && player2PaddleY > 0)
            player2PaddleY -= 5.0f;
        if (IsKeyDown(KEY_DOWN) && player2PaddleY < HEIGHT - PADDLE_HEIGHT)
            player2PaddleY += 5.0f;
    }
    else
    {
        // Movement Logic for Bot AI
        if (player2PaddleY + PADDLE_HEIGHT / 2 < ballPosition.y)
            player2PaddleY += botPaddleSpeed;
        if (player2PaddleY + PADDLE_HEIGHT / 2 > ballPosition.y)
            player2PaddleY -= botPaddleSpeed;
        if (player2PaddleY < 0)
            player2PaddleY = 0;
        if (player2PaddleY > HEIGHT - PADDLE_HEIGHT)
            player2PaddleY = HEIGHT - PADDLE_HEIGHT;
    }
}
