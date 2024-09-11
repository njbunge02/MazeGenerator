//Nick Bunge 
//March 11 2022

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace  std;

const int w = (62) * 3 + 2;     //width of maze
const int h = (500) * 3 + 2;    //height of maze
const char WALL = 'X';
const char SUBPOINTS = 'X';
const char STEMS = 'X'; 
const bool REMOVE = true;  //determines if you want to remove loops or not
const int scale = 1;


//distribution of how many walls are connected to each subpoint
const double oneWall = .5;
const double twoWall = .5;
const double threeWall = 0;
const double fourWall = 0;



struct coord
{
    int x;
    int y;
};

struct display
{
    bool isWall {false};
    bool isBorder {false};
    bool isSubPoint {false};
    bool isStem {false};
    char wall;
};

struct TwoD
{
    display y[h];
};



const int subLength = ((w - 2) / 3)*((h-2) / 3);
coord subCoord[subLength];
void initalizeBaseMaze(TwoD x[w]);
string printMaze(TwoD dis[w]);
void generateRandWalls(TwoD x[w]);
void removeLoops(TwoD x[w]);
void coverSpace(TwoD x[w]);

int main()
{
    TwoD dis[w];
    srand (time(NULL));

    initalizeBaseMaze(dis);
    generateRandWalls(dis);
    removeLoops(dis);
    coverSpace(dis);

   
    ofstream file("maze.txt"); 
    if (file.is_open())
    {
    
    file << printMaze(dis);

    } else
    {
        cout << "Error opening output file.";
        return 1;
    } 

    file.close();
    return 0;
}

//prints maze
string printMaze(TwoD dis[w])
{
     string maze;
     
     for (int i = 0; i < h; ++i)
    {
        for (int z = 0; z < scale; ++z)
        {
            for (int x = 0; x < w; ++x)
            {   
                for (int u = 0; u < scale; ++u)
                {
                maze += dis[x].y[i].wall;
                }
            }
        maze += '\n';
    }   }

    return maze;
}


//sets initialized values for the base square and sets subpoints
void initalizeBaseMaze(TwoD dis[w])
{
    int subCount = 0;

    for (int i = 0; i < h; ++i)
    {
        for (int x = 0; x < w; ++x)
        {
            //makes the square border
            if (i == 0 || i == h - 1)
            {
                dis[x].y[i].wall = WALL;
                dis[x].y[i].isWall = true;
                dis[x].y[i].isBorder = true;

            } else if (x == 0 || x == w - 1)
            {
                dis[x].y[i].wall = WALL;
                dis[x].y[i].isWall = true;
                dis[x].y[i].isBorder = true;
            } else
            {
                dis[x].y[i].wall = ' ';
                dis[x].y[i].isWall = false;
            }

            //checks for if it is subpoint
            if ((i + 1) % 3 == 0 && (x + 1)% 3 == 0)
            {
                dis[x].y[i].wall = SUBPOINTS;
                dis[x].y[i].isSubPoint = true;
                subCoord[subCount].x = x;
                subCoord[subCount].y = i;
                subCount += 1;
            }
        }
    }


}

//Generates the random walls 
void generateRandWalls(TwoD x[w])
{
    int walls;
    int max;
    for (int i = 0; i < subLength; ++i)
    {
        
        //determines how many walls for that specific subpoint
        max = rand() % 100 + 1;
        if (max < oneWall * 100)
        {
            max = 1;
        } else if (max < twoWall * 100 + oneWall * 100)
        {
            max = 2;
        } else if (max < twoWall * 100 + oneWall * 100 + threeWall * 100)
        {
            max = 3;
        }else
        {max = 4;}

        //determine whether up,right,down,left wall is chosen to be the random wall
        for (int z = 0; z < max; ++z){
             walls = rand() % 100 + 1;
            //top Wall
            if (walls < 25 && !x[subCoord[i].x].y[subCoord[i].y - 1].isWall) 
            {
                x[subCoord[i].x].y[subCoord[i].y - 1].wall = WALL;
                x[subCoord[i].x].y[subCoord[i].y - 1].isWall = true;
                continue;
            //right wall
            } 
            if (walls < 50  && !x[subCoord[i].x + 1].y[subCoord[i].y].isWall)
            {
                x[subCoord[i].x + 1].y[subCoord[i].y].wall = WALL;
                x[subCoord[i].x + 1].y[subCoord[i].y].isWall = true;
                continue;
            //bottom wall
            }
            if (walls < 75  && !x[subCoord[i].x].y[subCoord[i].y + 1].isWall)
            {
                x[subCoord[i].x].y[subCoord[i].y + 1].wall = WALL;
                x[subCoord[i].x].y[subCoord[i].y + 1].isWall = true;
                continue;
            //left wall
            }
            if (walls < 100 && !x[subCoord[i].x -1].y[subCoord[i].y].isWall)
            {
                x[subCoord[i].x -1].y[subCoord[i].y].wall = WALL;
                x[subCoord[i].x - 1].y[subCoord[i].y].isWall = true;
                continue;
            }
        }
    }
        //checks for if theres any 2x2 area gaps
        for (int i = 0; i < subLength; ++i)
        {
                if (!x[subCoord[i].x].y[subCoord[i].y - 1].isWall && !x[subCoord[i].x].y[subCoord[i].y - 2].isWall)
                {
                    x[subCoord[i].x].y[subCoord[i].y - 1].wall = WALL;
                    x[subCoord[i].x].y[subCoord[i].y - 1].isWall = true;
                }
                if (!x[subCoord[i].x + 1].y[subCoord[i].y].isWall && !x[subCoord[i].x + 2].y[subCoord[i].y].isWall)
                {
                    x[subCoord[i].x + 1].y[subCoord[i].y].wall = WALL;
                    x[subCoord[i].x + 1].y[subCoord[i].y].isWall = true;
                }
                if (!x[subCoord[i].x].y[subCoord[i].y + 1].isWall && !x[subCoord[i].x].y[subCoord[i].y + 2].isWall)
                {
                    x[subCoord[i].x].y[subCoord[i].y + 1].wall = WALL;
                    x[subCoord[i].x].y[subCoord[i].y + 1].isWall = true;
                }
                if (!x[subCoord[i].x - 1].y[subCoord[i].y].isWall && !x[subCoord[i].x - 2].y[subCoord[i].y].isWall)
                {
                    x[subCoord[i].x - 1].y[subCoord[i].y].wall = WALL;
                    x[subCoord[i].x -= 1].y[subCoord[i].y].isWall = true;
                }
            }
}

//identifies and removes loops
void removeLoops(TwoD x[w])
{
    bool flag = true; 
    int wallCount = 0;
    int randWall = 0;
    
    while (flag){
    for (int z = 0; z <w; ++z){
    for (int i = 0; i < subLength; ++i)
    {
            
            wallCount = 0;
                
                
                if (x[subCoord[i].x].y[subCoord[i].y - 1].isWall && (!x[subCoord[i].x].y[subCoord[i].y - 2].isWall ||  x[subCoord[i].x].y[subCoord[i].y - 2].isStem))
                {
                    x[subCoord[i].x].y[subCoord[i].y - 1].wall = STEMS;
                    x[subCoord[i].x].y[subCoord[i].y - 1].isStem = true;
                    
                } 
                if (x[subCoord[i].x + 1].y[subCoord[i].y].isWall && (!x[subCoord[i].x + 2].y[subCoord[i].y].isWall ||  x[subCoord[i].x + 2].y[subCoord[i].y].isStem))
                {
                    x[subCoord[i].x + 1].y[subCoord[i].y].wall = STEMS;
                    x[subCoord[i].x + 1].y[subCoord[i].y].isStem = true;
                    
                }
                if (x[subCoord[i].x].y[subCoord[i].y + 1].isWall && (!x[subCoord[i].x].y[subCoord[i].y + 2].isWall ||  x[subCoord[i].x].y[subCoord[i].y + 2].isStem))
                {
                    x[subCoord[i].x].y[subCoord[i].y + 1].wall = STEMS;
                    x[subCoord[i].x].y[subCoord[i].y + 1].isStem = true;
                    
                }
                if (x[subCoord[i].x - 1].y[subCoord[i].y].isWall && (!x[subCoord[i].x - 2].y[subCoord[i].y].isWall ||x[subCoord[i].x - 2].y[subCoord[i].y].isStem))
                {
                    x[subCoord[i].x - 1].y[subCoord[i].y].wall = STEMS;
                    x[subCoord[i].x - 1].y[subCoord[i].y].isStem = true;
                    
                }

                if (x[subCoord[i].x].y[subCoord[i].y - 1].isWall && !x[subCoord[i].x].y[subCoord[i].y - 1].isStem)
                {wallCount += 1;}
                if (x[subCoord[i].x].y[subCoord[i].y + 1].isWall && !x[subCoord[i].x].y[subCoord[i].y + 1].isStem)
                {wallCount += 1;}
                if (x[subCoord[i].x + 1].y[subCoord[i].y].isWall && !x[subCoord[i].x + 1].y[subCoord[i].y].isStem)
                {wallCount += 1;}
                if (x[subCoord[i].x - 1].y[subCoord[i].y ].isWall && !x[subCoord[i].x - 1].y[subCoord[i].y].isStem)
                {wallCount += 1;}
                
                if (wallCount <= 1)
                {
                    x[subCoord[i].x].y[subCoord[i].y].wall = STEMS;
                    x[subCoord[i].x].y[subCoord[i].y].isStem = true;
                    

                    if (x[subCoord[i].x].y[subCoord[i].y - 1].isWall)
                    {
                    x[subCoord[i].x].y[subCoord[i].y - 1].wall = STEMS;
                    x[subCoord[i].x].y[subCoord[i].y - 1].isStem = true;
                    }
                    
                    if (x[subCoord[i].x].y[subCoord[i].y + 1].isWall)
                    {
                    x[subCoord[i].x].y[subCoord[i].y + 1].wall = STEMS;
                    x[subCoord[i].x].y[subCoord[i].y + 1].isStem = true;
                    }
                    
                    if (x[subCoord[i].x + 1].y[subCoord[i].y].isWall)
                    {
                    x[subCoord[i].x + 1].y[subCoord[i].y].wall = STEMS;
                    x[subCoord[i].x + 1].y[subCoord[i].y].isStem = true;
                    }

                    if ( x[subCoord[i].x - 1].y[subCoord[i].y].isWall)
                    {
                    x[subCoord[i].x - 1].y[subCoord[i].y].wall = STEMS;
                    x[subCoord[i].x - 1].y[subCoord[i].y].isStem = true;
                    }
                }
        }
        }

    flag = true;
    bool loopFlag = false;
 
    for (int i = 0; i < subLength; ++i)
    {
       
        if (REMOVE){
        if (!x[subCoord[i].x].y[subCoord[i].y].isStem)
        {
            loopFlag =  true;
            randWall = rand() % 4 + 1;
            if (randWall == 1 )
            {
                
                x[subCoord[i].x].y[subCoord[i].y + 1].isStem = false;
                x[subCoord[i].x].y[subCoord[i].y + 1].isWall = false;
                x[subCoord[i].x].y[subCoord[i].y + 1].wall = ' ';
           
               
            
            }
            if (randWall == 2)
            {
                
                x[subCoord[i].x].y[subCoord[i].y - 1].isStem = false;
                x[subCoord[i].x].y[subCoord[i].y - 1].isWall = false;
                x[subCoord[i].x].y[subCoord[i].y - 1].wall = ' ';
             
               
            }
            if (randWall == 3)
            {
                
                x[subCoord[i].x + 1].y[subCoord[i].y].isStem = false;
                x[subCoord[i].x + 1].y[subCoord[i].y].isWall = false;
                x[subCoord[i].x + 1].y[subCoord[i].y].wall = ' ';
               
            }
            if (randWall == 4)
            {
                
                x[subCoord[i].x - 1].y[subCoord[i].y].isStem = false;
                x[subCoord[i].x - 1].y[subCoord[i].y].isWall = false;
                x[subCoord[i].x - 1].y[subCoord[i].y].wall = ' ';
                
            }
            break; 
        } } 
    }
    if (!loopFlag)
    {
        flag = false;
    }

    }
    }

//adds walls to extra space 
void coverSpace(TwoD x[w])
{
for (int i = 0; i < subLength; ++i)
{
    if (!x[subCoord[i].x].y[subCoord[i].y + 1].isWall && !x[subCoord[i].x].y[subCoord[i].y + 2].isWall)
    {
        x[subCoord[i].x].y[subCoord[i].y + 1].isWall = true;
        x[subCoord[i].x].y[subCoord[i].y + 1].wall = WALL;
    }

    if (!x[subCoord[i].x].y[subCoord[i].y - 1].isWall && !x[subCoord[i].x].y[subCoord[i].y - 2].isWall)
    {
        x[subCoord[i].x].y[subCoord[i].y - 1].isWall = true;
        x[subCoord[i].x].y[subCoord[i].y - 1].wall = WALL;
    }

    if (!x[subCoord[i].x + 1].y[subCoord[i].y].isWall && !x[subCoord[i].x + 2].y[subCoord[i].y].isWall)
    {
        x[subCoord[i].x + 1].y[subCoord[i].y].isWall = true;
        x[subCoord[i].x + 1].y[subCoord[i].y].wall = WALL;
    }

     if (!x[subCoord[i].x - 1].y[subCoord[i].y].isWall && !x[subCoord[i].x - 2].y[subCoord[i].y].isWall)
    {
        x[subCoord[i].x - 1].y[subCoord[i].y].isWall = true;
        x[subCoord[i].x - 1].y[subCoord[i].y].wall = WALL;
    }
}



}

