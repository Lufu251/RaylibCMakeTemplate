/*******************************************************************************************
*
* raylib example: Bouncing Ball
*
* This example demonstrates the following raylib features:
* - Window creation and management (InitWindow, WindowShouldClose, CloseWindow)
* - Basic shape drawing (DrawCircle, DrawRectangle)
* - Text drawing (DrawText)
* - Color handling (RAYWHITE, BLUE, RED)
* - Frame timing and control (SetTargetFPS, BeginDrawing, EndDrawing)
* - Basic keyboard input handling (IsKeyDown)
* - Simple animation and physics (updating position and velocity)
*
********************************************************************************************/

#include <raylib.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib example - bouncing ball");

    // Ball properties
    Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 20;

    // Paddle properties
    Rectangle paddle = { (float)screenWidth / 2 - 60, (float)screenHeight - 40, 120, 20 };
    float paddleSpeed = 6.0f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Ball movement logic
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        // Ball collision logic: walls
        if ((ballPosition.x >= (screenWidth - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
        if (ballPosition.y <= ballRadius) ballSpeed.y *= -1.0f;
        
        // Ball collision logic: paddle
        if (CheckCollisionCircleRec(ballPosition, ballRadius, paddle))
        {
            ballSpeed.y *= -1.0f;
            ballPosition.y = paddle.y - ballRadius; // prevent sticking
        }

        // Paddle movement logic
        if (IsKeyDown(KEY_LEFT)) paddle.x -= paddleSpeed;
        if (IsKeyDown(KEY_RIGHT)) paddle.x += paddleSpeed;

        // Paddle boundary check
        if (paddle.x <= 0) paddle.x = 0;
        if (paddle.x + paddle.width >= screenWidth) paddle.x = screenWidth - paddle.width;
        
        // Reset ball if it goes off screen
        if (ballPosition.y > screenHeight) {
            ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
            ballSpeed = { 5.0f, 4.0f };
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            // Draw game objects
            DrawCircleV(ballPosition, ballRadius, MAROON);
            DrawRectangleRec(paddle, BLUE);

            // Draw UI text
            DrawText("Move the paddle with Left and Right arrow keys", 10, 10, 20, LIGHTGRAY);
            DrawFPS(screenWidth - 100, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}