#include "raylib.h"
#include <iostream>
#include <fstream>

// g++ sokoban.cpp -std=c++20 `pkg-config --libs --cflags raylib` -o sokoban

typedef enum GameScreen { TITLE, LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, ENDING } GameScreen;

int score = 0;
const int screenWidth = 1000;
const int screenHeight = 599;
const int rem = screenHeight % 100;
const int gameSize = screenHeight - rem;
const int noOfBoxes = 10;
const int boxSize = gameSize / noOfBoxes;
const int widthDiff = (screenWidth - gameSize) / 2;
const int heightDiff = (screenHeight - gameSize) / 2;


bool flag = 0;
bool success = false;

int wallCount = 0;
int boxCount = 0;
int targetCount = 0;

int playerX;
int playerY;


Vector2 playerPos = {0, 0};
Vector2 wallPos[50] = {0, 0};
Vector2 boxPos[5] = {0, 0};
Vector2 targetPos[5] = {0, 0};

int row(int i);
int column(int j);
void levels(char lvl[][10], Texture2D player, Texture2D wall, Texture2D box, Texture2D goal, Texture2D background, Texture2D boxFinal, Texture2D grass);
void updates(char lvl[][noOfBoxes]);


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Sokoban");
    //--------------------------------------------------------------------------------------

    GameScreen currentScreen = TITLE;
    char lvl1[noOfBoxes][noOfBoxes], lvl2[noOfBoxes][noOfBoxes], lvl3[noOfBoxes][noOfBoxes], lvl4[noOfBoxes][noOfBoxes], lvl5[noOfBoxes][noOfBoxes];
    std::ifstream level1("lvl1.txt"), level2("lvl2.txt"), level3("lvl3.txt"), level4("lvl4.txt"), level5("lvl5.txt");

    //--------------------------------------------------------------------------------------
    // LEVEL 1
    for (int i = 0; i < noOfBoxes; i++)
    {
        for (int j = 0; j < noOfBoxes; j++)
        {
            level1 >> lvl1[i][j];
        }
    }
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // LEVEL 2
    for (int i = 0; i < noOfBoxes; i++)
    {
        for (int j = 0; j < noOfBoxes; j++)
        {
            level2 >> lvl2[i][j];
        }
    }
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // LEVEL 3
    for (int i = 0; i < noOfBoxes; i++)
    {
        for (int j = 0; j < noOfBoxes; j++)
        {
            level3 >> lvl3[i][j];
        }
    }
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // LEVEL 4
    for (int i = 0; i < noOfBoxes; i++)
    {
        for (int j = 0; j < noOfBoxes; j++)
        {
            level4 >> lvl4[i][j];
        }
    }
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // LEVEL 5
    for (int i = 0; i < noOfBoxes; i++)
    {
        for (int j = 0; j < noOfBoxes; j++)
        {
            level5 >> lvl5[i][j];
        }
    }
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // LOADING TEXTURES
    Texture2D player = LoadTexture("./resources/player.png");
    Texture2D wall = LoadTexture("./resources/wall02.png");
    Texture2D box = LoadTexture("./resources/crate.png");
    Texture2D background = LoadTexture("./resources/floor.png");
    Texture2D grass = LoadTexture("./resources/tree.png");
    Texture2D boxFinal = LoadTexture("./resources/crateFinal.png");
    Texture2D goal = LoadTexture("./resources/goal.png");
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // Changing Size of the Texture
    
    wall.width = boxSize;
    wall.height = boxSize;
    player.width = boxSize;
    player.height = boxSize;
    box.width = boxSize;
    box.height = boxSize;
    background.width = boxSize;
    background.height = boxSize;
    grass.width = boxSize;
    grass.height = boxSize;
    goal.width = boxSize;
    goal.height = boxSize;
    boxFinal.width = boxSize;
    boxFinal.height = boxSize;

    //--------------------------------------------------------------------------------------
    // Set game Frames-per-seconds
    SetTargetFPS(10);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case TITLE:
                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = LEVEL1;
                }
                break;
            case LEVEL1:
                updates(lvl1);
                if (score == 1)
                {
                    wallCount = 0;
                    success = false;
                    currentScreen = LEVEL2;
                }
                break;
            case LEVEL2:
                if (score == 2)
                {
                    wallCount = 0;
                    success = false;
                    currentScreen = LEVEL3;
                }
                break;
            case LEVEL3:
                if (score == 3)
                {
                    wallCount = 0;
                    success = false;
                    currentScreen = LEVEL4;
                }
                break;
            case LEVEL4:
                if (score == 4)
                {
                    wallCount = 0;
                    success = false;
                    currentScreen = LEVEL5;
                }
                break;
            case LEVEL5:
                if (score == 5)
                {
                    wallCount = 0;
                    success = false;
                    currentScreen = ENDING;
                }
                break;
            case ENDING:
                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = TITLE;
                }
                break;
            default: break;
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch(currentScreen)
            {
                case TITLE:
                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", widthDiff, screenHeight / 2, 20, DARKGREEN);
                    break;

                case LEVEL1:

                    //--------------------------------------------------------------------------------------
                    // LEVEL 1
                    // levels(lvl1, playerPos, player, wall, box, goal, background, boxFinal, grass);
                    levels(lvl1, player, wall, box, goal, background, boxFinal, grass);
                    break;

                case LEVEL2:

                    //--------------------------------------------------------------------------------------
                    // LEVEL 2
                    levels(lvl2, player, wall, box, goal, background, boxFinal, grass);
                    break;

                case LEVEL3:

                    //--------------------------------------------------------------------------------------
                    // LEVEL 3
                    levels(lvl3, player, wall, box, goal, background, boxFinal, grass);
                    break;

                case LEVEL4:

                    //--------------------------------------------------------------------------------------
                    // LEVEL 4
                    levels(lvl4, player, wall, box, goal, background, boxFinal, grass);
                    break;

                case LEVEL5:

                    //--------------------------------------------------------------------------------------
                    // LEVEL 5
                    levels(lvl5, player, wall, box, goal, background, boxFinal, grass);
                    break;

                case ENDING:
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
                    break;

                default: break;
            }




        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization

    UnloadTexture(player);
    UnloadTexture(wall);
    UnloadTexture(box);
    UnloadTexture(grass);
    UnloadTexture(background);
    UnloadTexture(goal);
    UnloadTexture(boxFinal);
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//Function to map texture on game row
int row(int i)
{
    return i * boxSize + widthDiff;
}

//Function to map texture on game column
int column(int j)
{
    return j * boxSize + heightDiff;
}

//Function to create levels
// void levels(char lvl[][10], Vector2 playerPos, Texture2D player, Texture2D wall, Texture2D box, Texture2D goal, Texture2D background, Texture2D boxFinal, Texture2D grass){
void levels(char lvl[][10], Texture2D player, Texture2D wall, Texture2D box, Texture2D goal, Texture2D background, Texture2D boxFinal, Texture2D grass){
    
    
    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);

    //--------------------------------------------------------------------------------------
    // ADDING BACKGROUND COLOR
    DrawRectangle(widthDiff, heightDiff, gameSize, gameSize, BROWN);

    //--------------------------------------------------------------------------------------
    // LEVEL 1

    for (int i = 0; i < noOfBoxes; i++)
    {

        for (int j = 0; j < noOfBoxes; j++)
        {

            if (lvl[i][j] == 'B')
            {
                DrawTexture(background, row(i), column(j), WHITE);
                DrawTexture(box, row(i), column(j), WHITE);
                if(!flag){

                    // boxPos[boxCount].x = row(i);
                    // boxPos[boxCount].y = column(j);
                    // boxCount++;
                }
            }
            else if (lvl[i][j] == 'P')
            {
                DrawTexture(background, row(i), column(j), WHITE);
                if (!flag)
                {
                    // playerPos.x = row(i);
                    // playerPos.y = column(j);
                    playerPos.x = i;
                    playerPos.y = j;

                }
                // DrawTexture(player, playerPos.x, playerPos.y, WHITE);

            }
            else if (lvl[i][j] == 'F')
            {
                DrawTexture(goal, row(i), column(j), WHITE);
                if(!flag){

                    // targetPos[targetCount].x = row(i);
                    // targetPos[targetCount].y = column(j);
                    // targetCount++;
                }
            }
            else if (lvl[i][j] == '1')
            {
                DrawTexture(background, row(i), column(j), WHITE);
            }
            else if (lvl[i][j] == 'L')
            {
                DrawTexture(boxFinal, row(i), column(j), WHITE);
                if(!flag){
                    // targetPos[targetCount].x = row(i);
                    // targetPos[targetCount].y = column(j);
                    // targetCount++;
                    // boxPos[boxCount].x = row(i);
                    // boxPos[boxCount].y = column(j);
                    // boxCount++;
                }
            }
            else if (lvl[i][j] == 'X')
            {
                DrawTexture(grass, row(i), column(j), WHITE);
            }
            else if (lvl[i][j] == 'N')
            {
                DrawRectangle(row(i), column(j), boxSize, boxSize, MAROON);
            }
            else if (lvl[i][j] == '0')
            {
                DrawTexture(wall, row(i), column(j), WHITE);
                if(!flag){
                    wallPos[wallCount].x = row(i);
                    wallPos[wallCount].y = column(j);
                    wallCount++;
                }
            }
            else
            {
                DrawRectangle(row(i), column(j), boxSize, boxSize, PURPLE);
            }
        }
    }

    flag = 1;
    DrawTexture(player, row(playerPos.x), column(playerPos.y), WHITE);

    for (int i = 0; i < boxCount; i++){
        if(boxPos[i].x == targetPos[i].x && boxPos[i].y == targetPos[i].y)
        {
            success = true;
        }
        else
        {
            success = false;
            break;
        }
    }
    if (success)
    {
        score++;
    }
}

void updates(char lvl[][noOfBoxes])
{

    playerX = playerPos.x;
    playerY = playerPos.y;


    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        if (lvl[playerX][playerY - 1] != '0')
        {
            if(lvl[playerX][playerY - 1] == 'B' || lvl[playerX][playerY - 1] == 'L')
            {

            }
            playerPos.y --;
        }
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        if (lvl[playerX][playerY + 1] != '0')
        {
            playerPos.y ++;
        }
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        if (lvl[playerX - 1][playerY] != '0')
        {
            playerPos.x --;
        }
    }

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        if (lvl[playerX + 1][playerY] != '0')
        {
            playerPos.x ++;
        }
    }
}