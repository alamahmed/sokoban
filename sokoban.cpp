#include "raylib.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

// g++ sokoban.cpp -std=c++20 `pkg-config --libs --cflags raylib` -o sokoban

const int screenWidth = 1000;
const int screenHeight = 599;
const int rem = screenHeight % 100;
const int gameSize = screenHeight - rem;
const int noOfBoxes = 10;
const int boxSize = gameSize / noOfBoxes;
const int widthDiff = (screenWidth - gameSize) / 2;
const int heightDiff = (screenHeight - gameSize) / 2;

bool flag = 0;
bool up = false;
bool down = false;
bool left = false;
bool right = false;


int row(int i)
{
    return i * boxSize + widthDiff;
}

int column(int j)
{
    return j * boxSize + heightDiff;
}

void checker (Vector2 playerPos, int i, int j)
{
    if (playerPos.x + boxSize == i)
        right = true;
    else
        right = false;

    if (playerPos.x - boxSize == i)
        left = true;
    else
        left = false;

    if (playerPos.y + boxSize == j)
        down = true;
    else
        down = false;

    if (playerPos.y - boxSize == j)
        up = true;
    else
        up = false;
}


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------


    InitWindow(screenWidth, screenHeight, "Sokoban");

    //--------------------------------------------------------------------------------------
    //LEVEL 1
    char lvl1[noOfBoxes][noOfBoxes];
    std::ifstream level1("lvl1.txt");
    for (int i = 0; i < noOfBoxes; i++){
        for (int j = 0; j < noOfBoxes; j++){
            level1 >> lvl1[i][j];
        }
    }

    for(int i = 0; i < noOfBoxes; i++){
        for(int j = 0; j < noOfBoxes; j++){
            std::cout << lvl1[i][j];
        }
        std::cout << "\n";
    }
    //--------------------------------------------------------------------------------------


    //--------------------------------------------------------------------------------------
    //LEVEL 2
    char lvl2[noOfBoxes][noOfBoxes];
    std::ifstream level2("lvl2.txt");
    for (int i = 0; i < noOfBoxes; i++){
        for (int j = 0; j < noOfBoxes; j++){
            level2 >> lvl2[i][j];
        }
    }
    //--------------------------------------------------------------------------------------


    //--------------------------------------------------------------------------------------
    //LOADING TEXTURES
    Texture2D player = LoadTexture("./resources/player.png");
    Texture2D wall = LoadTexture("./resources/wall02.png");
    Texture2D box = LoadTexture("./resources/crate.png");
    Texture2D backgorund = LoadTexture("./resources/floor.png");
    Texture2D grass = LoadTexture("./resources/tree.png");
    Texture2D boxFinal = LoadTexture("./resources/crateFinal.png");
    Texture2D goal = LoadTexture("./resources/goal.png");
    //--------------------------------------------------------------------------------------


    //--------------------------------------------------------------------------------------
    //Changing Size of the Texture
    wall.width = boxSize;
    wall.height = boxSize;
    player.width = boxSize;
    player.height = boxSize;
    box.width = boxSize;
    box.height = boxSize;
    backgorund.width = boxSize;
    backgorund.height = boxSize;
    grass.width = boxSize;
    grass.height = boxSize;
    goal.width = boxSize;
    goal.height = boxSize;
    boxFinal.width = boxSize;
    boxFinal.height = boxSize;
    //--------------------------------------------------------------------------------------


    SetTargetFPS(10); // Set game Frames-per-seconds
    //--------------------------------------------------------------------------------------

    Vector2 playerPos = {0, 0}; 

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        if (!down)
        {
            if (IsKeyPressed(KEY_DOWN))
                playerPos.y += boxSize; 
        }
        if (!up) 
        {
            if (IsKeyPressed(KEY_UP))
                playerPos.y -= boxSize;  
        }
        if (!right)
        {
            if(IsKeyPressed(KEY_RIGHT))
                playerPos.x += boxSize;  
        }
        if (!left)
        {
            if (IsKeyPressed(KEY_LEFT))
                playerPos.x -= boxSize;  
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(RAYWHITE);

        //--------------------------------------------------------------------------------------
        //ADDING BACKGROUND COLOR
        
        DrawRectangle(widthDiff, heightDiff, gameSize, gameSize, BROWN);

        //--------------------------------------------------------------------------------------
        //LEVEL 1
        

        for (int i = 0; i < noOfBoxes; i++){
            
            for (int j = 0; j < noOfBoxes; j++){
                
                if (lvl1[i][j] == 'B'){
                    DrawTexture(box, row(i), column(j), WHITE);
                    checker(playerPos, row(i), column(j));
                }
                else if (lvl1[i][j] == 'P'){
                    DrawTexture(backgorund, row(i), column(j), WHITE);
                    if (flag == 0)
                    {
                        playerPos.x = row(i);
                        playerPos.y = column(j);
                        flag = 1;
                    }
                }
                else if (lvl1[i][j] == 'F'){
                    DrawTexture(goal, row(i), column(j), WHITE);
                    checker(playerPos, row(i), column(j));
                }
                else if (lvl1[i][j] == '1'){
                    DrawTexture(backgorund, row(i), column(j), WHITE);
                }
                else if(lvl1[i][j] == 'L'){
                    DrawTexture(boxFinal, row(i), column(j), WHITE);
                }
                else if (lvl1[i][j] == 'X'){
                    DrawTexture(grass, row(i), column(j), WHITE);
                }
                else if(lvl1[i][j] == 'N'){
                    DrawRectangle(row(i), column(j), boxSize, boxSize, MAROON);
                }
                else if (lvl1[i][j] == '0'){
                    DrawTexture(wall, row(i), column(j), WHITE);
                    checker(playerPos, row(i), column(j));
                    
                }
                else{
                    DrawRectangle(row(i), column(j), boxSize, boxSize, RAYWHITE);
                }
            }
        }

        DrawTexture(player, playerPos.x, playerPos.y, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization

    UnloadTexture(player);
    UnloadTexture(wall);
    UnloadTexture(box);
    UnloadTexture(grass);
    UnloadTexture(backgorund);
    UnloadTexture(goal);
    UnloadTexture(boxFinal);
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}