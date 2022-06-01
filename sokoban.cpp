//==========================================================================//
//          USE ENTER TO START THE GAME AND TO RESET THE LEVEL              //
//==========================================================================//


#include "raylib.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using std::to_string;
using std::map;
using std::vector;
using std::string;
using std::copy;
using std::ifstream;
using std::back_inserter;

//Command Used to Compile the Code
// g++ sokoban.cpp -std=c++20 `pkg-config --libs --cflags raylib` -o sokoban

//CONSTANTS
const int noOfLevels = 10;
const int screenWidth = 1199;
const int screenHeight = 590;
const int gameSize = screenHeight - screenHeight % 100;
const int noOfBoxes = 10;
const int boxSize = gameSize / noOfBoxes;
const int widthDiff = (screenWidth - gameSize) / 2;
const int heightDiff = (screenHeight - gameSize) / 2;
int score = 0;
int boxIndex = 0;

//bool variables
bool flag = true;
bool title = true;

// Textures Declaration
Texture2D player, wall, box, floor, background, boxFinal, goal, boundary, landingPage;




//Positions Variables
Vector2 playerPos = {0, 0};
vector<vector<int> > goalsPos;
vector<vector<int> > boxesPos;

//Data Variables
vector<vector<char> > data;

//Functions Declarations
map<char, Texture2D> textureMap;
void update(vector<vector<char> > &level);
void renderLevel(std::vector<std::vector<char> > level);
void changeLevels();
Vector2 findPlayer(vector<vector<char> > level);
vector<vector<char> > readLvl(string levelName);
vector<vector<int> > findGoals(vector<vector<char> > level);
vector<vector<int> > findBoxes(vector<vector<char> > level);
vector<vector<int> > findEndBoxes(vector<vector<char> > level);
map<char, Texture2D> createTextureMap();
bool isPlayerOnGoal();
bool isBoxAhead(int choice, vector<vector<char> > &level);
bool isLevelCleared(vector<vector<char> > &level);
bool canPlayerMove(int choice, vector<vector<char> > &level);
int updateBoxSprite(vector<vector<char> > &level);


//--------------------------------------------------------------------------------------
//MAIN FUNCTION
//--------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Sokoban");
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // Loading Textures
    player = LoadTexture("./resources/player.png");
    wall = LoadTexture("./resources/wall.png");
    box = LoadTexture("./resources/crate.png");
    floor = LoadTexture("./resources/floor.png");
    background = LoadTexture("./resources/tree.png");
    boxFinal = LoadTexture("./resources/crateFinal.png");
    goal = LoadTexture("./resources/goal.png");
    boundary = LoadTexture("./resources/fence.png");
    landingPage = LoadTexture("./resources/SokobanTitleScreen.png");
    
    //--------------------------------------------------------------------------------------
    

    //--------------------------------------------------------------------------------------
    // Changing Size of the Texture
    
    wall.width = boxSize;
    wall.height = boxSize;
    player.width = boxSize;
    player.height = boxSize;
    box.width = boxSize;
    box.height = boxSize;
    floor.width = boxSize;
    floor.height = boxSize;
    background.width = boxSize;
    background.height = boxSize;
    goal.width = boxSize;
    goal.height = boxSize;
    boxFinal.width = boxSize;
    boxFinal.height = boxSize;
    boundary.width = boxSize;
    boundary.height = boxSize;

    landingPage.width = screenWidth;
    landingPage.height = screenHeight;
    
    //--------------------------------------------------------------------------------------
    //Calling Texture Map
    textureMap = createTextureMap();

    //--------------------------------------------------------------------------------------
    // Set game Frames-per-seconds (FPS)
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        // if(IsKeyPressed(KEY_N))
        // {
            if(isLevelCleared(data) || flag)
            {
                changeLevels();
            }
        // }
        
        update(data);
        updateBoxSprite(data);

        //----------------------------------------------------------------------------------


        //----------------------------------------------------------------------------------
        // Start Drawing
        BeginDrawing();

        if(IsKeyDown(KEY_ENTER))
        {   
            title = false;
        }
        if(title){
            DrawTexture(landingPage, 0, 0, WHITE);
        }
        else if(!title)
        {
            renderLevel(data);

        }

        EndDrawing();
        // Stop Drawing
        //----------------------------------------------------------------------------------
    }

    // Unload Textures To Free Up memory

    UnloadTexture(player);
    UnloadTexture(wall);
    UnloadTexture(box);
    UnloadTexture(background);
    UnloadTexture(background);
    UnloadTexture(goal);
    UnloadTexture(boxFinal);
    UnloadTexture(boundary);
    UnloadTexture(landingPage);


    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


//Function to Map Sprites On Characters to Use It in render
map<char, Texture2D> createTextureMap()
{

    map<char, Texture2D> textureMap;
    textureMap.insert(std::pair<char, Texture2D>('B', box));
    textureMap.insert(std::pair<char, Texture2D>('P', player));
    textureMap.insert(std::pair<char, Texture2D>('0', wall));
    textureMap.insert(std::pair<char, Texture2D>('L', boxFinal));
    textureMap.insert(std::pair<char, Texture2D>('1', floor));
    textureMap.insert(std::pair<char, Texture2D>('X', background));
    textureMap.insert(std::pair<char, Texture2D>('F', goal));
    textureMap.insert(std::pair<char, Texture2D>('N', boundary));

    return textureMap;

}

//Function To Read Data With Filing
vector<vector<char> > readLvl(string levelName)
{

    ifstream level(levelName);

    vector<vector<char> > lvl;
    string line;

    while (getline(level, line))
    {
        
        vector <char> temp;

        copy(line.begin(), line.end(), back_inserter(temp));

        lvl.push_back(temp);
        
    }
    return lvl;
}

//Function To Find Position of Player
Vector2 findPlayer(vector<vector<char> > level)
{
    for (int i = 0; i < level.size(); i++)
    {
        for (int j = 0; j < level.at(i).size(); j++)
        {
            if (level.at(i).at(j) == 'P')
            {
                return {(float)i, (float)j};
            }
        }
    }
    return {-1, -1};
}

//Function To Find Position of all the Target Position of Boxes
vector<vector<int> > findGoals(vector<vector<char> > level)
{
    vector<vector<int> > goals;
    for (int i = 0; i < level.size(); i++)
    {
        for (int j = 0; j < level.at(i).size(); j++)
        {
            if (level.at(i).at(j) == 'F' || level.at(i).at(j) == 'L')
            {
                vector<int> temp{i, j};
                goals.push_back(temp);
            }
        }
    }
    return goals;
}

//Function To Find Position Of all the Boxes
vector<vector<int> > findBoxes(vector<vector<char> > level)
{
    vector<vector<int> > boxes;
    for (int i = 0; i < level.size(); i++)
    {
        for (int j = 0; j < level.at(i).size(); j++)
        {
            if (level.at(i).at(j) == 'B' || level.at(i).at(j) == 'L')
            {
                vector<int> temp{i, j};
                boxes.push_back(temp);
            }
        }
    }
    return boxes;
}

//Function To render Level with Sprites
void renderLevel(std::vector<std::vector<char> > level)
{

    //--------------------------------------------------------------------------------------
    ClearBackground(RAYWHITE);
    // ADDING BACKGROUND COLOR
    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    //DRAW LEVEL
    string levelName = "LEVEL " + to_string(score);
    DrawText(levelName.c_str(), 0, 0, 50, WHITE);
    
    for(int i = 0; i < level.size(); i++)
    {
        for(int j = 0; j < level.at(i).size(); j++)
        {   
            DrawTexture(textureMap[level.at(i).at(j)], i * boxSize + widthDiff, j * boxSize + heightDiff, WHITE);
        }
    }

    for (int i = 0; i < boxesPos.size(); i++)
    {
        int tempRow = boxesPos[i][0];
        int tempCol = boxesPos[i][1];
        DrawTexture(textureMap[level.at(tempRow).at(tempCol)], tempRow * boxSize + widthDiff, tempCol * boxSize + heightDiff, WHITE);
    }

    DrawTexture(textureMap[level.at(playerPos.x).at(playerPos.y)], playerPos.x * boxSize + widthDiff, playerPos.y * boxSize + heightDiff, WHITE);

}

//Function To Update Position Of Player
void update(vector<vector<char> > &level)
{

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        if(level[playerPos.x][playerPos.y - 1] != '0')
        {
            if(isBoxAhead(1, level))
            {
                if(isPlayerOnGoal())
                    level[playerPos.x][playerPos.y] = 'F';
                else
                    level[playerPos.x][playerPos.y] = '1';
                
                level[boxesPos[boxIndex][0]][boxesPos[boxIndex][1]] = 'P';
                playerPos.y = boxesPos[boxIndex][1];
                boxesPos[boxIndex][1]--;
                level[boxesPos[boxIndex][0]][boxesPos[boxIndex][1]] = 'B';
            }
            else if(isPlayerOnGoal() && !isBoxAhead(1, level) && !canPlayerMove(1, level))
            {
                level[playerPos.x][playerPos.y] = 'P';
            }
            else if(isPlayerOnGoal())
            {
                level[playerPos.x][playerPos.y] = 'F';
                playerPos.y--;
                level[playerPos.x][playerPos.y] = 'P';
            }
            else if(canPlayerMove(1, level))
            {
                level[playerPos.x][playerPos.y] = '1';
                playerPos.y--;
                level[playerPos.x][playerPos.y] = 'P';
            }
        }
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
    {
        if(level[playerPos.x][playerPos.y + 1] != '0')
        {
            if(isBoxAhead(2, level))
            {
                if(isPlayerOnGoal())
                    level[playerPos.x][playerPos.y] = 'F';
                else
                    level[playerPos.x][playerPos.y] = '1';

                level[boxesPos[boxIndex][0]][boxesPos[boxIndex][1]] = 'P';
                playerPos.y = boxesPos[boxIndex][1];
                boxesPos[boxIndex][1]++;
                level[boxesPos[boxIndex][0]][boxesPos[boxIndex][1]] = 'B';
            }
            else if(isPlayerOnGoal() && !isBoxAhead(2, level) && !canPlayerMove(2, level))
            {
                level[playerPos.x][playerPos.y] = 'P';
            }
            else if(isPlayerOnGoal())
            {
                level[playerPos.x][playerPos.y] = 'F';
                playerPos.y++;
                level[playerPos.x][playerPos.y] = 'P';
            }
            else if(canPlayerMove(2, level))
            {
                level[playerPos.x][playerPos.y] = '1';
                playerPos.y++;
                level[playerPos.x][playerPos.y] = 'P';
            }
        }
    }
    
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        if(level[playerPos.x - 1][playerPos.y] != '0')
        {
            if(isBoxAhead(3, level))
            {
                if(isPlayerOnGoal())
                    level[playerPos.x][playerPos.y] = 'F';
                else
                    level[playerPos.x][playerPos.y] = '1';

                level[boxesPos[boxIndex][0]][boxesPos[boxIndex][1]] = 'P';
                playerPos.x = boxesPos[boxIndex][0];
                boxesPos[boxIndex][0]--;
                level[boxesPos[boxIndex][0]][boxesPos[boxIndex][1]] = 'B';
            }
            else if(isPlayerOnGoal() && !isBoxAhead(3, level) && !canPlayerMove(3, level))
            {
                level[playerPos.x][playerPos.y] = 'P';
            }
            else if(isPlayerOnGoal())
            {
                level[playerPos.x][playerPos.y] = 'F';
                playerPos.x--;
                level[playerPos.x][playerPos.y] = 'P';
            }
            else if(canPlayerMove(3, level))
            {
                level[playerPos.x][playerPos.y] = '1';
                playerPos.x--;
                level[playerPos.x][playerPos.y] = 'P';
            }
        }
    }

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        if(level[playerPos.x + 1][playerPos.y] != '0')
        {
            if(isBoxAhead(4, level))
            {
                if(isPlayerOnGoal())
                    level[playerPos.x][playerPos.y] = 'F';
                else
                    level[playerPos.x][playerPos.y] = '1';
                
                
                level[boxesPos[boxIndex][0]][boxesPos[boxIndex][1]] = 'P';
                playerPos.x = boxesPos[boxIndex][0];
                boxesPos[boxIndex][0]++;
                level[boxesPos[boxIndex][0]][boxesPos[boxIndex][1]] = 'B';
            }
            else if(isPlayerOnGoal() && !isBoxAhead(4, level) && !canPlayerMove(4, level))
            {
                level[playerPos.x][playerPos.y] = 'P';
            }
            else if(isPlayerOnGoal())
            {
                level[playerPos.x][playerPos.y] = 'F';
                playerPos.x++;
                level[playerPos.x][playerPos.y] = 'P';
            }
            else if(canPlayerMove(4, level))
            {
                level[playerPos.x][playerPos.y] = '1';
                playerPos.x++;
                level[playerPos.x][playerPos.y] = 'P';
            }
        }
    }

    if(IsKeyDown(KEY_ENTER))
    {
        flag = true;
    }
}

//Function To Check Weather Player is standing on Goal
bool isPlayerOnGoal()
{
    for (int i = 0; i < goalsPos.size(); i++)
    {
        //[ 1st brac ([ 2nd brac (0), 1 ], [ 0, 0 ], [ 0, 0 ], [ 0, 0 ])

        if(playerPos.x == goalsPos[i][0] && playerPos.y == goalsPos[i][1])
            return true;
    }
    return false;
}

//Function To check Is Box ahead and can be moved
bool isBoxAhead(int choice, vector<vector<char> > &level)
{
    for (int i = 0; i < boxesPos.size(); i++)
    {
        switch (choice)
        {
        case 1:
            if(playerPos.x == boxesPos[i][0] && playerPos.y - 1 == boxesPos[i][1] && level[playerPos.x][playerPos.y - 2] != '0' && (level[playerPos.x][playerPos.y - 2] != 'B' && level[playerPos.x][playerPos.y - 2] != 'L'))
            {
                boxIndex = i;
                return true;
            }
            break;
        
        case 2:
            if(playerPos.x == boxesPos[i][0] && playerPos.y + 1 == boxesPos[i][1] && level[playerPos.x][playerPos.y + 2] != '0' && (level[playerPos.x][playerPos.y + 2] != 'B' && level[playerPos.x][playerPos.y + 2] != 'L'))
            {
                boxIndex = i;
                return true;
            }
            break;

        case 3:
            if(playerPos.x - 1 == boxesPos[i][0] && playerPos.y == boxesPos[i][1] && level[playerPos.x - 2][playerPos.y] != '0' && (level[playerPos.x - 2][playerPos.y] != 'B' && level[playerPos.x - 2][playerPos.y] != 'L'))
            {
                boxIndex = i;
                return true;
            }
            break;

        case 4:
            if(playerPos.x + 1 == boxesPos[i][0] && playerPos.y == boxesPos[i][1] && level[playerPos.x + 2][playerPos.y] != '0' && (level[playerPos.x + 2][playerPos.y] != 'B' && level[playerPos.x + 2][playerPos.y] != 'L'))
            {
                boxIndex = i;
                return true;
            }
            break;

        default:
            return false;
            break;
        }
    }
    return false;
}

//Function To Check Status of Level
bool isLevelCleared(vector<vector<char> > &level)
{
    int count = updateBoxSprite(level);
    if(count == boxesPos.size())
    {
        if(score == noOfLevels)
        {
            score = 1;
            flag = true;
            title = true;
        }
        else
        {
            score++;
            flag = true;
        }
        return true;
    }
    return false;

}

//Function To Check Weather Player Can Move Or Not
bool canPlayerMove(int choice, vector<vector<char> > &level)
{
    switch (choice)
    {
    case 1:
        if(level[playerPos.x][playerPos.y - 1] == '1' || level[playerPos.x][playerPos.y - 1] == 'F' && level[playerPos.x][playerPos.y - 1] != 'L')
        {
            return true;
        }
        break;
    
    case 2:
        if(level[playerPos.x][playerPos.y + 1] == '1' || level[playerPos.x][playerPos.y + 1] == 'F' && level[playerPos.x][playerPos.y + 1] != 'L')
        {
            return true;
        }
        break;

    case 3:
        if(level[playerPos.x - 1][playerPos.y] == '1' || level[playerPos.x - 1][playerPos.y] == 'F' && level[playerPos.x - 1][playerPos.y] != 'L')
        {
            return true;
        }
        break;

    case 4:
        if(level[playerPos.x + 1][playerPos.y] == '1' || level[playerPos.x + 1][playerPos.y] == 'F' && level[playerPos.x + 1][playerPos.y] != 'L')
        {
            return true;
        }
        break;

    default:
        return false;
        break;
    }
    return false;
}

//Function To Change Levels
void changeLevels()
{
    if(flag)
    {
        data = readLvl("lvl" + std::to_string(score) + ".txt");
        playerPos = findPlayer(data);
        goalsPos = findGoals(data);
        boxesPos = findBoxes(data);
    }
    flag = false;
}

// Function to Update Box Sprite
int updateBoxSprite(vector<vector<char> > &level)
{
    int count = 0; 
    for (int i = 0; i < goalsPos.size(); i++)
    {
        for (int j = 0; j < boxesPos.size(); j++)
        {
            if(goalsPos[i][0] == boxesPos[j][0] && goalsPos[i][1] == boxesPos[j][1])
            {
                count++;
                level[goalsPos[i][0]][goalsPos[i][1]] = 'L';
                break;

            }
        }
    }
    return count;
}



