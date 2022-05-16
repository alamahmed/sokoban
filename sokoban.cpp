#include "raylib.h"
#include <iostream>
#include <fstream>

// g++ sokoban.cpp -std=c++20 `pkg-config --libs --cflags raylib` -o sokoban

const int gameSize = 400;
const int noOfBoxes = 9;
const int boxSize = gameSize / noOfBoxes;


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    int width1 = 9, height1 = 9;
    char lvl1[width1][height1];

    InitWindow(screenWidth, screenHeight, "Sokoban");

    std::ifstream level1("lvl1.txt");

    for (int i = 0; i < width1; i++)
    {
        for (int j = 0; j < height1; j++)
        {
            level1 >> lvl1[i][j];
        }
    }

    Texture2D head = LoadTexture("/Users/ahmedalam/Documents/Programming/C++/Project01/sokoban/resources/player.png");
    Texture2D wall = LoadTexture("/Users/ahmedalam/Documents/Programming/C++/Project01/sokoban/resources/wall.png");
    Texture2D box = LoadTexture("/Users/ahmedalam/Documents/Programming/C++/Project01/sokoban/resources/Crate.png");
    Texture2D backgorund = LoadTexture("/Users/ahmedalam/Documents/Programming/C++/Project01/sokoban/resources/BG.png");
    Texture2D grass = LoadTexture("/Users/ahmedalam/Documents/Programming/C++/Project01/sokoban/resources/grass.png");

    Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
    wall.width = boxSize + 15;
    wall.height = boxSize + 15;
    head.width = boxSize;
    head.height = boxSize;
    box.width = boxSize + 15;
    box.height = boxSize + 15;
    backgorund.width = boxSize + 15;
    backgorund.height = boxSize + 15;
    grass.width = boxSize + 15;
    grass.height = boxSize + 15;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT))
            ballPosition.x += 1.0f;
        if (IsKeyDown(KEY_LEFT))
            ballPosition.x -= 1.0f;
        if (IsKeyDown(KEY_UP))
            ballPosition.y -= 1.0f;
        if (IsKeyDown(KEY_DOWN))
            ballPosition.y += 1.0f;
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        int widthDiff = (screenWidth - gameSize) / 2;
        int heightDiff = (screenHeight - gameSize) / 2;

        // DrawRectangle(widthDiff, heightDiff, gameSize, gameSize, BROWN);

        for (int i = 0; i < noOfBoxes; i++){
            
            for (int j = 0; j < noOfBoxes; j++){
                              
                if (lvl1[i][j] == '0')
                {
                    DrawRectangle(i * boxSize + widthDiff, j * boxSize + heightDiff, boxSize, boxSize, MAROON);
                    // DrawTexture(wall, i * boxSize + widthDiff, j * boxSize + heightDiff, WHITE);
                }
                else if (lvl1[i][j] == 'B')
                {
                    DrawRectangle(i * boxSize + widthDiff, j * boxSize + heightDiff, boxSize, boxSize, BROWN);
                    // DrawTexture(box, i * boxSize + widthDiff, j * boxSize + heightDiff, WHITE);
                }
                else if (lvl1[i][j] == 'P')
                {
                    DrawRectangle(i * boxSize + widthDiff, j * boxSize + heightDiff, boxSize, boxSize, BLACK);
                    // DrawTexture(head, i * boxSize + widthDiff, j * boxSize + heightDiff, WHITE);
                }
                else if (lvl1[i][j] == 'F')
                {
                    DrawRectangle(i * boxSize + widthDiff, j * boxSize + heightDiff, boxSize, boxSize, BLUE);
                    // DrawTexture(grass, i * boxSize + widthDiff, j * boxSize + heightDiff, WHITE);
                }
                else if (lvl1[i][j] == '1')
                {
                    DrawRectangle(i * boxSize + widthDiff, j * boxSize + heightDiff, boxSize, boxSize, GREEN);
                    // DrawTexture(grass, i * boxSize + widthDiff, j * boxSize + heightDiff, WHITE);
                }
                else if (lvl1[i][j] == 'X' || lvl1[i][j] == 'N')
                {
                    DrawRectangle(i * boxSize + widthDiff, j * boxSize + heightDiff, boxSize, boxSize, RAYWHITE);
                    // DrawTexture(backgorund, i * boxSize + widthDiff, j * boxSize + heightDiff, WHITE);
                }
            }

        }


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization

    UnloadTexture(head);
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}