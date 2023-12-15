#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
//for random
#include <ctime>

//Define new type for vector
typedef std::vector<int> b_vec;


//MAX SIZE OF BOARD
#define Max_Size 15


//Define the size of the game board
b_vec ResizeVector(b_vec GameVector, int Rows, int Columns)
{
    GameVector.resize(Rows * Columns);

    return GameVector;
}

//Define Temp matrix
b_vec Re(b_vec InputMatrix)
{
    InputMatrix.reserve(1);
}

//Generate random numbers for rows and columns
int GenerateRandomRowCol()
{
    int Row_Col = 0;

    //Row_Col could be between 1-Max_Size
    Row_Col = 1 + (rand() % Max_Size);

    return Row_Col;
}

//Generate random data for the game board
b_vec GenerateRandomGameBoard(b_vec GameVector, int Rows, int Columns)
{

    //Counter for points with data in them
    int Counter = 0;

    //Temporary for row and columns index
    int TempRow;
    int TempCol;

    //Double variable for division below
    double Prozent;

    //Random signals, with random distribution
    while(Counter < (Rows * Columns * 0.2))
    {
        //Choose random Rows and Cols
        TempRow = (rand() % Rows);
        TempCol = (rand() % Columns);

        //Fill random elements with ones and zeros
        GameVector[TempRow * Columns + TempCol] = (rand() % 2);

        //Step counter for signals
        if(GameVector[TempRow * Columns + TempCol] == 1)
        {
            Counter++;
        }
    }

    Prozent = (double)Counter / (Rows * Columns);

    std::cout << "Signal count: " << Counter << "\n";
    std::cout << "That's the " << Prozent << "% of the whole board" << "\n\n";

    return GameVector;
}

int FindGreatest(b_vec GameVector, int Rows, int Columns)
{
    int CountUpwards;
    int CountRightside;
    int CountLeftside;

    //False statement indicator to easily break loops
    int TempIndicator = 1;

    //Temporary storage for area
    int TempArea = 0;

    //Storage for largest area
    int LargestArea = 0;

    for(int i = 0; i < Rows; i++)
    {
        for(int j = 0; j < Columns; j++)
        {
            CountUpwards = 0;
            CountRightside = 0;
            CountLeftside = 0;

            if(GameVector[i * Columns + j] == 0)
            {
                //If 0 element found, iterate upwards till the first 1, and count 0s on the way
                for(int k = i; k >= 0; k--)
                {
                    if(GameVector[k * Columns + j] == 0)
                    {
                        CountUpwards++;
                    }
                    else
                    {
                        break;
                    }
                }

                // Extend the vertical line to the right side and check zeros there
                // IF all elements are zeros in that [CountUpwards x 1] sized line, then
                // CountRightside++
                for(int z = j; j < Columns; j++)
                {
                    for(int n = i; n > i - CountUpwards; n--)
                    {
                        if(GameVector[n * Columns + z] == 1)
                        {
                            TempIndicator = 0;
                            break;
                        }
                    }

                    if(TempIndicator == 0)
                    {
                        TempIndicator = 1;
                        break;
                    }
                    else
                    {
                        CountRightside++;
                    }
                }

                //Count zeros on the left side
                for(int p = j; j >= 0; j--)
                {
                    for(int m = i; m > i - CountUpwards; m--)
                    {
                        if(GameVector[m * Columns + p] == 1)
                        {
                            TempIndicator = 0;
                            break;
                        }
                    }

                    if(TempIndicator == 0)
                    {
                        TempIndicator = 1;
                        break;
                    }
                    else
                    {
                        CountLeftside++;
                    }
                }

                //Give value to TempArea
                TempArea = CountUpwards * (CountLeftside + CountRightside - 1);
                std::cout << TempArea << " ";


            }

            //Replace LargestArea with Temp if Temp is greater
            if(TempArea > LargestArea)
            {
                LargestArea = TempArea;
            }
        }
    }

    return LargestArea;
}


// -------- MAIN --------

int main()
{
    //Set ctime the seed for full-random numbers
    srand(time(0));

    //Declare vector for the game board
    b_vec GameVector;

    //Integers for the number of rows and columns of the board
    int Rows;
    int Columns;

    //Largest area
    int LargestArea;

    //Generate random numbers for rows and columns
    Rows = GenerateRandomRowCol();
    Columns = GenerateRandomRowCol();

    //Resize the game board
    GameVector = ResizeVector(GameVector, Rows, Columns);

    //Give random elements to vector
    GameVector = GenerateRandomGameBoard(GameVector, Rows, Columns);


// -------- WRITE OUT DATA --------
    for(int i = 0; i < Rows; i++)
    {
        for(int j = 0; j < Columns; j++)
        {
            std::cout << GameVector[i * Columns + j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nSize of board: " << Rows << "x" << Columns << "\n";
// ----- WRITE OUT DATA END -----

    LargestArea = FindGreatest(GameVector, Rows, Columns);

    std::cout << "Size of the rectangle with the largest area on the board: " << LargestArea;


}
