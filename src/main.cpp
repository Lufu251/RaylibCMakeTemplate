#include <raylib.h>

int main(void){
    // Declaration ----------------------------------------------------------------------
    // Screen dimensions
    const int screenWidth = 800;
    const int screenHeight = 600;

    // 1. Declare RenderTexture2D objects
    RenderTexture2D gameRenderTexture;
    RenderTexture2D debugRenderTexture;
    RenderTexture2D guiRenderTexture;

    bool showDebug = true;

    // Initialization -------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "DungeonSweeper");
    SetTargetFPS(60);

    // Initialize RenderTexture2D objects
    // Make sure they have the same dimensions as your screen or desired render area
    gameRenderTexture = LoadRenderTexture(screenWidth, screenHeight);
    debugRenderTexture = LoadRenderTexture(screenWidth, screenHeight);
    guiRenderTexture = LoadRenderTexture(screenWidth, screenHeight);

    while (!WindowShouldClose()){
        // Update ---------------------------------------------------------------------------
        if (IsKeyPressed(KEY_D)) showDebug = !showDebug;
        
        // Draw -----------------------------------------------------------------------------
        // Render to gameRenderTexture
        BeginTextureMode(gameRenderTexture);
            ClearBackground(DARKBLUE);
            DrawText("Game World", 10, 10, 20, WHITE);
        EndTextureMode();

        // Render to debugRenderTexture
        BeginTextureMode(debugRenderTexture);
            ClearBackground(BLANK);
            if (showDebug)
            {
                // Draw debug elements
                DrawFPS(screenWidth - 100, 10);
            }
        EndTextureMode();

        // Render to guiRenderTexture
        BeginTextureMode(guiRenderTexture);
            ClearBackground(BLANK);
            // Draw GUI elements
            DrawRectangle(0, screenHeight - 50, screenWidth, 50, Fade(BLUE, 0.5f));
            DrawText("Press 'D' for Debug Info", 10, screenHeight - 40, 20, YELLOW);
            DrawText("Simple GUI", screenWidth - 150, screenHeight - 40, 20, YELLOW);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RAYWHITE); // Clear the main screen background

            // Draw game texture
            DrawTextureRec(gameRenderTexture.texture, (Rectangle){ 0, 0, (float)gameRenderTexture.texture.width, (float)-gameRenderTexture.texture.height }, (Vector2){ 0, 0 }, WHITE);

            // Draw debug texture (on top of game)
            DrawTextureRec(debugRenderTexture.texture, (Rectangle){ 0, 0, (float)debugRenderTexture.texture.width, (float)-debugRenderTexture.texture.height }, (Vector2){ 0, 0 }, WHITE);

            // Draw GUI texture (on top of everything)
            DrawTextureRec(guiRenderTexture.texture, (Rectangle){ 0, 0, (float)guiRenderTexture.texture.width, (float)-guiRenderTexture.texture.height }, (Vector2){ 0, 0 }, WHITE);

            // Draw directly to screen

        EndDrawing();
    }

    // De-Initialization ----------------------------------------------------------------
    // Unload textures when done
    UnloadRenderTexture(gameRenderTexture);
    UnloadRenderTexture(debugRenderTexture);
    UnloadRenderTexture(guiRenderTexture);

    CloseWindow(); // Close window and OpenGL context

    return 0;
}