/*******************************************************************************************
*
* raylib/raygui example: Message Box
*
* This example demonstrates the following raylib and raygui features:
* - Window creation and management (InitWindow, WindowShouldClose, CloseWindow)
* - Frame timing and control (SetTargetFPS, BeginDrawing, EndDrawing)
* - Integration of raygui for user interface elements
* - Retrieving UI style properties (GuiGetStyle) for background color
* - Creation and interaction with a GUI button (GuiButton)
* - Displaying and handling a GUI message box (GuiMessageBox)
* - Basic UI state management (showing/hiding elements based on a boolean flag)
*
********************************************************************************************/

#include <raylib.h> // Required for raylib functions (window, drawing, etc.)

#define RAYGUI_IMPLEMENTATION // This macro makes raygui include its implementation directly
#include <raygui.h>           // Required for raygui functions (buttons, message boxes, etc.)

// Main entry point of the program
int main()
{
    // Initialize the window with a specific size and title
    InitWindow(400, 200, "raygui - controls test suite");
    // Set the target frames per second to 60 for smooth rendering
    SetTargetFPS(60);

    // Declare a boolean variable to control the visibility of the message box
    bool showMessageBox = false;

    // Main game loop: continues as long as the window is not requested to close
    while (!WindowShouldClose())
    {
        // Drawing phase
        //----------------------------------------------------------------------------------
        BeginDrawing(); // Start drawing operations

            // Clear the background of the window
            // The background color is dynamically retrieved from the current raygui style
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // Create a GUI button at a specific position and size with text
            // The "#191#" is a raygui icon code for a message icon
            // If the button is pressed, set showMessageBox to true
            if (GuiButton({ 24, 24, 120, 30 }, "#191#Show Message")) showMessageBox = true;

            // If showMessageBox is true, display the message box
            if (showMessageBox)
            {
                // Create a GUI message box at a specific position and size
                // It has a title, message, and two options separated by a semicolon
                // The return value (result) indicates which option was selected (0 for first, 1 for second, -1 for closed without selection)
                int result = GuiMessageBox({ 85, 70, 250, 100 },
                    "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

                // If any button inside the message box is pressed (result is 0 or greater)
                // then hide the message box by setting showMessageBox to false
                if (result >= 0) showMessageBox = false;
            }

        EndDrawing(); // End drawing operations and display the rendered frame
    }

    // Close the window and free up resources
    CloseWindow();
    // Return 0 to indicate successful program execution
    return 0;
}