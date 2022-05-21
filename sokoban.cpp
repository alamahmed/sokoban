#include "raylib.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using std::map;
using std::vector;
using std::string;
using std::cout;


// g++ sokoban.cpp -std=c++20 `pkg-config --libs --cflags raylib` -o sokoban
typedef enum GameScreen { TITLE, LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, ENDING } GameScreen;

int score = 0;
const int screenWidth = 1000;
const int screenHeight = 599;
const int gameSize = screenHeight - screenHeight % 100;
const int noOfBoxes = 10;
const int boxSize = gameSize / noOfBoxes;
const int widthDiff = (screenWidth - gameSize) / 2;
const int heightDiff = (screenHeight - gameSize) / 2;


bool flag = 0;

// LOADING TEXTURES
Texture2D player;
Texture2D wall;
Texture2D box;
Texture2D floor;
Texture2D background;
Texture2D boxFinal;
Texture2D goal;


map<char, Texture2D> textureMap;

//Positions Variables
Vector2 playerPos = {0, 0};
vector<vector<int> > goalsPos;
vector<vector<int> > boxesPos;

//Functions Declarations
void update(vector<vector<char> > &level);
vector<vector<char> > readLvl(string levelName);
void renderLevel(std::vector<std::vector<char> > level);
Vector2 findPlayer(vector<vector<char> > level);
vector<vector<int> > findGoals(vector<vector<char> > level);
vector<vector<int> > findBoxes(vector<vector<char> > level);
map<char, Texture2D> createTextureMap();
bool isPlayerOnGoal();


int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Sokoban");
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // Load Textures
    player = LoadTexture("./resources/player.png");
    wall = LoadTexture("./resources/wall.png");
    box = LoadTexture("./resources/crate.png");
    floor = LoadTexture("./resources/floor.png");
    background = LoadTexture("./resources/tree.png");
    boxFinal = LoadTexture("./resources/crateFinal.png");
    goal = LoadTexture("./resources/goal.png");
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

    textureMap = createTextureMap();

    //--------------------------------------------------------------------------------------
    // Set game Frames-per-seconds
    SetTargetFPS(10);
    //--------------------------------------------------------------------------------------
    vector<vector<char> > data = readLvl("lvl1.txt");
    playerPos = findPlayer(data);
    goalsPos = findGoals(data);
    boxesPos = findBoxes(data);
    
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        
        update(data);

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(RAYWHITE);
        renderLevel(data);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization

    UnloadTexture(player);
    UnloadTexture(wall);
    UnloadTexture(box);
    UnloadTexture(background);
    UnloadTexture(background);
    UnloadTexture(goal);
    UnloadTexture(boxFinal);
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

vector<vector<char> > readLvl(string levelName)
{

    std::ifstream level(levelName);

    vector<std::vector<char> > lvl;
    string line;

    while (getline(level, line))
    {
        char char_array[line.length() + 1];
        
        strcpy(char_array, line.c_str());
        
        std::vector <char> temp;

        std::copy(line.begin(), line.end(), std::back_inserter(temp));

        lvl.push_back(temp);
        
    }
    return lvl;
}


void renderLevel(std::vector<std::vector<char> > level)
{

    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);

    //--------------------------------------------------------------------------------------
    // ADDING BACKGROUND COLOR
    DrawRectangle(widthDiff, heightDiff, gameSize, gameSize, BROWN);

    for(int i = 0; i < level.size(); i++)
    {
        for(int j = 0; j < level.at(i).size(); j++)
        {   
            DrawTexture(textureMap[level.at(i).at(j)], i * boxSize + widthDiff, j * boxSize + heightDiff, WHITE);
        }
    }
}


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

    return textureMap;

}

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

vector<vector<int> > findGoals(vector<vector<char> > level)
{
    vector<vector<int> > goals;
    for (int i = 0; i < level.size(); i++)
    {
        for (int j = 0; j < level.at(i).size(); j++)
        {
            if (level.at(i).at(j) == 'F')
            {
                vector<int> temp{i, j};
                goals.push_back(temp);
            }
        }
    }
    return goals;
}

vector<vector<int> > findBoxes(vector<vector<char> > level)
{
    vector<vector<int> > boxes;
    for (int i = 0; i < level.size(); i++)
    {
        for (int j = 0; j < level.at(i).size(); j++)
        {
            if (level.at(i).at(j) == 'F')
            {
                vector<int> temp{i, j};
                boxes.push_back(temp);
            }
        }
    }
    return boxes;
}

void update(vector<vector<char> > &level)
{

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        if(level[playerPos.x][playerPos.y - 1] != '0')
        {
            if(isPlayerOnGoal())
            {
                level[playerPos.x][playerPos.y] = 'F';
                playerPos.y--;
                level[playerPos.x][playerPos.y] = 'P';
            }
            else
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
            if(isPlayerOnGoal())
            {
                level[playerPos.x][playerPos.y] = 'F';
                playerPos.y++;
                level[playerPos.x][playerPos.y] = 'P';
            }
            else
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
            if(isPlayerOnGoal())
            {
                level[playerPos.x][playerPos.y] = 'F';
                playerPos.x--;
                level[playerPos.x][playerPos.y] = 'P';
            }
            else
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
            if(isPlayerOnGoal())
            {
                level[playerPos.x][playerPos.y] = 'F';
                playerPos.x++;
                level[playerPos.x][playerPos.y] = 'P';
            }
            else
            {
                level[playerPos.x][playerPos.y] = '1';
                playerPos.x++;
                level[playerPos.x][playerPos.y] = 'P';
            }
        }
    }
}


bool isPlayerOnGoal()
{
    for (int i = 0; i < goalsPos.size(); i++)
    {
        if(playerPos.x == goalsPos[i][0] && playerPos.y == goalsPos[i][1])//[ 1st brac ([ 2nd brac (0), 1])
            return true;
    }
    return false;
}

bool isBoxAhead()
{
    for (int i = 0; i < boxesPos.size(); i++)
    {
        if(playerPos.x == boxesPos[i][0] && playerPos.y == boxesPos[i][1])//[ 1st brac ([ 2nd brac (0), 1])
            return true;
    }
    return false;
}