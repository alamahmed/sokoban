#include "raylib.h"
#include <iostream>
#include <fstream>

// cc sokoban.cpp -std=c++20 `pkg-config --libs --cflags raylib` -o sokoban

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    const int boxWidth = 50;
    const int boxHeight = 50;

    int width1 = 8, height1 = 8;
    char lvl1[width1][height1];

    InitWindow(screenWidth, screenHeight, "Sokoban");

    std::ifstream level1("lvl1.txt");

    if (!level1)
    {
        std::cout << "Error, file couldn't be opened\n";
        return 1;
    }

    for (int i = 0; i < width1; i++)
    {
        for (int j = 0; j < height1; j++)
        {
            level1 >> lvl1[i][j];
            if (!level1)
            {
                std::cout << "Error reading file for element " << i << "," << j << "\n";
                return 1;
            }
        }
    }

    Texture2D head = LoadTexture("/Users/ahmedalam/Documents/Programming/C++/Project01/sokoban/resources/player.png");
    Texture2D wall = LoadTexture("/Users/ahmedalam/Documents/Programming/C++/Project01/sokoban/resources/wall.png");
    Texture2D box = LoadTexture("/Users/ahmedalam/Documents/Programming/C++/Project01/sokoban/resources/crate.png");

    Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
    Vector2 headPosition = {(float)screenWidth / 2, (float)screenHeight / 2};

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    head.width = boxWidth;
    head.height = boxHeight;
    wall.width = boxWidth;
    wall.height = boxHeight + 10;
    box.width = boxWidth + 18.5;
    box.height = boxHeight + 15.5;

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
        for (int i = 0; i < width1; i++)
        {
            for (int j = 0; j < height1; j++)
            {

                if (lvl1[i][j] == '0')
                {
                    DrawTexture(wall, i * boxWidth, j * boxHeight, WHITE);
                }
                else if (lvl1[i][j] == 'B')
                {
                    DrawTexture(box, i * boxWidth, j * boxHeight, WHITE);
                }
                else if (lvl1[i][j] == 'P')
                {
                    DrawTexture(head, i * boxWidth, j * boxHeight, WHITE);
                }
                else if (lvl1[i][j] == 'F')
                {
                    DrawRectangle(i * boxWidth, j * boxHeight, boxWidth, boxHeight, BLUE);
                }
                else if (lvl1[i][j] == '1')
                {
                    DrawRectangle(i * boxWidth, j * boxHeight, boxWidth, boxHeight, GREEN);
                }
                else if (lvl1[i][j] == 'X')
                {
                    DrawRectangle(i * boxWidth, j * boxHeight, boxWidth, boxHeight, RAYWHITE);
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