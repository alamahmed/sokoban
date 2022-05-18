#include "raylib.h"
#include <iostream>
#include <fstream>

// g++ sokoban.cpp -std=c++20 `pkg-config --libs --cflags raylib` -o sokoban

typedef enum GameScreen { TITLE, LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, ENDING } GameScreen;

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

Vector2 playerPos = {0, 0};
Vector2 wallPos = {0, 0};
Vector2 boxPos = {0, 0};

int row(int i);
int column(int j);
void checker(Vector2 playerPos, int i, int j);
// void levels(char lvl1[][10], Vector2 playerPos, Texture2D player, Texture2D wall, Texture2D box, Texture2D goal, Texture2D background, Texture2D boxFinal, Texture2D grass);
void levels(char lvl1[][10], Texture2D player, Texture2D wall, Texture2D box, Texture2D goal, Texture2D background, Texture2D boxFinal, Texture2D grass);
void updates ();


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Sokoban");
    //--------------------------------------------------------------------------------------

    GameScreen currentScreen = TITLE;
    char lvl1[noOfBoxes][noOfBoxes], lvl2[noOfBoxes][noOfBoxes], lvl3[noOfBoxes][noOfBoxes], lvl4[noOfBoxes][noOfBoxes], lvl5[noOfBoxes][noOfBoxes];

    //--------------------------------------------------------------------------------------
    // LEVEL 1
    std::ifstream level1("lvl1.txt");
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
    std::ifstream level2("lvl2.txt");
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
    std::ifstream level3("lvl3.txt");
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
    std::ifstream level4("lvl4.txt");
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
    std::ifstream level5("lvl5.txt");
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

    SetTargetFPS(10); // Set game Frames-per-seconds
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        // if (!up)
        // {
        //     if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        //         playerPos.y -= boxSize;
        // }
        // if (!down)
        // {
        //     if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        //         playerPos.y += boxSize;
        // }
        // if (!left)
        // {
        //     if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        //         playerPos.x -= boxSize;
        // }
        // if (!right)
        // {
        //     if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        //         playerPos.x += boxSize;
        // }


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
                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = LEVEL2;
                }
                break;
            case LEVEL2:
                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = LEVEL3;
                }
                break;
            case LEVEL3:
                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = LEVEL4;
                }
                break;
            case LEVEL4:
                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = LEVEL5;
                }
                break;
            case LEVEL5:
                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = ENDING;
                }
                break;
            case ENDING:
                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
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
                    flag = 0;
                    break;

                case LEVEL2:

                    //--------------------------------------------------------------------------------------
                    // LEVEL 2
                    // levels(lvl2, playerPos, player, wall, box, goal, background, boxFinal, grass);
                    levels(lvl2, player, wall, box, goal, background, boxFinal, grass);
                    flag = 0;
                    break;

                case LEVEL3:

                    //--------------------------------------------------------------------------------------
                    // LEVEL 3
                    // levels(lvl3, playerPos, player, wall, box, goal, background, boxFinal, grass);
                    levels(lvl3, player, wall, box, goal, background, boxFinal, grass);
                    flag = 0;
                    break;

                case LEVEL4:

                    //--------------------------------------------------------------------------------------
                    // LEVEL 4
                    // levels(lvl4, playerPos, player, wall, box, goal, background, boxFinal, grass);
                    levels(lvl4, player, wall, box, goal, background, boxFinal, grass);
                    flag = 0;
                    break;

                case LEVEL5:

                    //--------------------------------------------------------------------------------------
                    // LEVEL 5
                    // levels(lvl5, playerPos, player, wall, box, goal, background, boxFinal, grass);
                    levels(lvl5, player, wall, box, goal, background, boxFinal, grass);
                    flag = 0;
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

//Function to Check Player Position
void checker(Vector2 playerPos, int i, int j)
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

//Function to create levels
// void levels(char lvl1[][10], Vector2 playerPos, Texture2D player, Texture2D wall, Texture2D box, Texture2D goal, Texture2D background, Texture2D boxFinal, Texture2D grass){
void levels(char lvl1[][10], Texture2D player, Texture2D wall, Texture2D box, Texture2D goal, Texture2D background, Texture2D boxFinal, Texture2D grass){
    
    
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

            if (lvl1[i][j] == 'B')
            {
                DrawTexture(box, row(i), column(j), WHITE);
                checker(playerPos, row(i), column(j));
            }
            else if (lvl1[i][j] == 'P')
            {
                DrawTexture(background, row(i), column(j), WHITE);
                if (flag == 0)
                {
                    playerPos.x = row(i);
                    playerPos.y = column(j);
                    flag = 1;
                }
                DrawTexture(player, playerPos.x, playerPos.y, WHITE);

            }
            else if (lvl1[i][j] == 'F')
            {
                DrawTexture(goal, row(i), column(j), WHITE);
                checker(playerPos, row(i), column(j));
            }
            else if (lvl1[i][j] == '1')
            {
                DrawTexture(background, row(i), column(j), WHITE);
            }
            else if (lvl1[i][j] == 'L')
            {
                DrawTexture(boxFinal, row(i), column(j), WHITE);
            }
            else if (lvl1[i][j] == 'X')
            {
                DrawTexture(grass, row(i), column(j), WHITE);
            }
            else if (lvl1[i][j] == 'N')
            {
                DrawRectangle(row(i), column(j), boxSize, boxSize, MAROON);
            }
            else if (lvl1[i][j] == '0')
            {
                DrawTexture(wall, row(i), column(j), WHITE);
                checker(playerPos, row(i), column(j));
            }
            else
            {
                DrawRectangle(row(i), column(j), boxSize, boxSize, PURPLE);
            }
        }
    }
    updates();
    // DrawTexture(player, playerPos.x, playerPos.y, WHITE);
}

void updates ()
{
    if (!up)
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
            playerPos.y -= boxSize;
    }
    if (!down)
    {
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
            playerPos.y += boxSize;
    }
    if (!left)
    {
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
            playerPos.x -= boxSize;
    }
    if (!right)
    {
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
            playerPos.x += boxSize;
    }
}