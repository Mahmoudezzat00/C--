#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>


//--- "CONST" INT FOR LOTTO 5,6,7 ETC... ---
unsigned int NbOfLotto;
//--- "CONST" INT FOR # OF LINES IN FILE... ---
unsigned int NumberOfLines;

//File consistency check
void CheckFile(std::ifstream &InputFile)
{
    if(InputFile.is_open())
    {
        std::cout << "\nFile opened successfully!\n\n";
    }
    else
    {
        std::cout << "\nThe file is missing, or corrupted. The program terminates.\n\n";
        exit(EXIT_FAILURE);
    }
}

//Open file
void OpenFile(std::string FileName, std::ifstream &InputFile)
{
    InputFile.open(FileName.c_str());

    //Test for filename
    //std::cout << FileName;

    //Check
    CheckFile(InputFile);
}

//Initialization
std::string Initialization(std::ifstream &InputFile)
{
    std::string FileName;

    //User input
    std::cout << "Please enter the name of the file: ";
    std::cin >> FileName;
    OpenFile(FileName, InputFile);

    std::cout << "Please enter an integer for how many lottery numbers should've been drawn?\n(It could be 5,6,7, etc, for Lottery 5,6,7, etc...)\n";
    std::cout << "Lottery numbers should've been drawn: ";
    std::cin >> NbOfLotto;

    std::cout << '\n';

    return FileName;
}

int* AllocateMemory(int* Vec_Pointer)
{
    //Request memory
    Vec_Pointer = new int[NbOfLotto];

    //Return pointer
    return Vec_Pointer;

}

int* AllocateMemory2D(int* Mtx_Pointer)
{
    //Request memory
    Mtx_Pointer = new int[NbOfLotto * NumberOfLines];

    //Return pointer
    return Mtx_Pointer;
}

//Check if 1-90
int CheckUserNumbersScope(int ActualNumber)
{
    int Test = 1;
    if(ActualNumber < 1 || ActualNumber > 90)
    {
        std::cout << "Your number is not between 1 and 90!\nPlease repeat!\n";
        Test = 0;
    }
/*
        else
        {
            std::cout << " -- your number is OK!\n";
        }
*/

    return Test;
}

// ----- FIRST -----

//Check if only one
int CheckUserNumbersUniqueness(int* UserVector, int i)
{
    int Test = 1;
    for(int j = 0; j < i; j++)
    {
        if(UserVector[i] == UserVector[j])
        {
            std::cout << "Your number's already in your chosen ones. Please choose another one!\n";
            Test = 0;
        }
/*
        else
        {
            std::cout << " -- your number is OK!\n";
        }
*/
    }
    return Test;
}

//std::cin from user (1-90) to vector
int* UserEnterNumber(int* UserVector)
{
    //Test parameter
    int TestScope;
    int TestUniq;

    std::cout << "Please enter " << NbOfLotto << " DIFFERENT integer between 1 and 90.\n";
    for(int i = 0; i < NbOfLotto; i++)
    {
        std::cout << "Number #" << i+1 << " :";
        std::cin >> UserVector[i];

        //Tests the current number. If it's not between 1-90, User should repeat it.
        TestScope = CheckUserNumbersScope(UserVector[i]);
        if(TestScope == 0)
        {
            i--;
        }

        //Tests the current number. If it was already typed, User should write another number.
        TestUniq = CheckUserNumbersUniqueness(UserVector, i);
        if(TestUniq == 0)
        {
            i--;
        }
    }

    std::cout << '\n';

    return UserVector;
}

//Order by size
void OrderInputBySize(int* InputVector)
{
    int Temp;


/*    //Test
    std::cout << "User's vector: ";
    for(int t = 0; t < NbOfLotto; t++)
    {
        std::cout << InputVector[t] << " ";
    }
*/
    //BUBBLE SORT FOR SHORT ARRAY OF NUMBERS
    for(int i = 0; i < NbOfLotto - 1; i++)
    {
        for(int j = 0; j < NbOfLotto - i - 1; j++)
        {
            if(InputVector[j] > InputVector[j+1])
            {
                Temp = InputVector[j];
                InputVector[j] = InputVector[j+1];
                InputVector[j+1] = Temp;
            }
        }
    }

    //Print out array
    std::cout << "[ ";
    for(int k = 0; k < NbOfLotto; k++)
    {
        std::cout << InputVector[k] << " ";
    }
    std::cout<< "]\n";
}

//Randomize vector (1-90)
int* RandomizeVector(int* RandVector)
{
    srand(time(0));
    for(int i = 0; i < NbOfLotto; i++)
    {
        RandVector[i] = (1 + (rand() % 90));
        for(int j = 0; j < i; j++)
        {
            if(RandVector[i] == RandVector[j])
            {
                i--;
            }
        }
    }

    return RandVector;
}

//Compare user defined and randomized vector
void CompareVectors(int* UserVector, int* RandVector)
{
    int Conformity = 0;

    for(int i = 0; i < NbOfLotto; i++)
    {
        for(int j = 0; j < NbOfLotto; j++)
        {
            if(RandVector[j] == UserVector[i])
            {
                Conformity += 1;
            }
        }
    }

    std::cout << "You've just found " << Conformity << " matches with the random array. ";

    switch(Conformity)
    {
        case 0:
            std::cout << ":((\n";
            break;
        case 1:
            std::cout << ":/\n";
            break;
        case 2:
            std::cout << ":))\n";
            break;
        case 3:
            std::cout << "Wow:O\n";
            break;
        case 4:
            std::cout << "No way, wooow :OOO\n";
            break;
        case 5:
            std::cout << "Actually WTF :DDD\n";
            break;
    }

    std::cout << '\n';
}


// ----- SECOND -----

void CountLinesInFile(std::ifstream &InputFile)
{
    std::string nbLines;

    //Read in the first line into string
    getline(InputFile, nbLines);

    //Convert string to int
    NumberOfLines = atoi(nbLines.c_str());

    //Test
    //std::cout << NumberOfLines;
}

int* WriteFileIntoMatrix(std::ifstream &InputFile, int* LineMatrix)
{
    //Test
    //std::cout << NumberOfLines;

    for(int i = 0; i < NumberOfLines; i++)
    {
        for(int j = 0; j < NbOfLotto; j++)
        {
            InputFile >> LineMatrix[i * NbOfLotto + j];
        }
    }

    //Test
    //std::cout << NumberOfLines << '\n';

/*    //Test
    for(int p = 0; p < NumberOfLines; p++)
    {
        for(int q = 0; q < NbOfLotto; q++)
        {
            std::cout << LineMatrix[p * NbOfLotto + q] << " ";
        }
        std::cout << '\n';
    }
*/
    return LineMatrix;
}

void CompareFileAndUserInput(int* UserVector, int* LineMatrix, std::ifstream &InputFile, std::ofstream &OutputFile)
{
/*
    //Test
    for(int p = 0; p < NumberOfLines; p++)
    {
        for(int q = 0; q < NbOfLotto; q++)
        {
            OutputFile << LineMatrix[p * NbOfLotto + q] << " ";
        }
        OutputFile << '\n';
    }
*/
    //Counting index for matches
    int Conformity = 0;

    //Counting index for weeks
    int Weeks = 10;

    //Counting current years
    int CurrentYear = 1957;

    //Counting index for years (for leap years)
    int Years = 4;

    //Vector for counting conformities
    int NumberOfConf[NbOfLotto+1];

    //DECLARING EVERY ELEMENT 0
    for(int dec = 0; dec <= NbOfLotto; dec++)
    {
        NumberOfConf[dec] = 0;
    }
/*
    //Test
    for(int m = 0; m <= NbOfLotto; m++)
    {
        std::cout << m << ": " << NumberOfConf[m];
    }
    std::cout << '\n';
*/
    //Running through lines
    for(int i = 0; i < NumberOfLines; i++)
    {
        //Running through elements of lines
        for(int j = 0; j < NbOfLotto; j++)
        {
            for(int k = 0; k < NbOfLotto; k++)
            {
                if(LineMatrix[i * NbOfLotto + k] == UserVector[j])
                {
                    Conformity += 1;
                }
            }
        }

        OutputFile << CurrentYear << ", Week #" << Weeks << ": You've just found " << Conformity << " matches. ";

        //Step weeks
        Weeks++;

        //Step years
        //EVERY 4TH YEAR HAVE A 53TH LOTTERY GAME
        if(Years != 4)
        {
            if(Weeks == 53)
            {
                CurrentYear++;
                Years++;
                Weeks = 1;
            }
        }
        else
        {
            if(Weeks == 54)
            {
                CurrentYear++;
                Years = 1;
                Weeks = 1;
            }
        }

        switch(Conformity)
        {
            case 0:
                OutputFile << ":((\n";
                break;
            case 1:
                OutputFile << ":/\n";
                break;
            case 2:
                OutputFile << ":))\n";
                break;
            case 3:
                OutputFile << "Wow:O\n";
                break;
            case 4:
                OutputFile << "No way, wooow :OOO\n";
                break;
            case 5:
                OutputFile << "Actually WTF :DDD\n";
                break;
            default:
                OutputFile << "That's pretty impressive o.O";
                break;
        }

        //Counting the number of conformities
        (NumberOfConf[Conformity])++;

        //Starting the counting again at every line (=week)
        Conformity = 0;
    }
/*
    //Test
    for(int m = 0; m <= NbOfLotto; m++)
    {
        std::cout << m << ": " << NumberOfConf[m];
    }
    std::cout << '\n';
*/
    //Writing number of matches
    std::cout << "Throughout the years, with these numbers, you would've had:\n";
    for (int p = 0; p <= NbOfLotto; p++)
    {
         std::cout << NumberOfConf[p] << "pcs matches with " << p << " numbers.\n";
    }

    OutputFile.close();
}


// ----- THIRD (BONUS) -----

void GeneratingNextWeekLotteryNumbers(int* LineMatrix)
{
    //Array to store numbers
    int NumberArray[90];
    int NumberArrayIndexes[90];
    int BestNumbers[NbOfLotto];

    //Temporary storage
    int Temp;

    //Temporary storage for smallest
    int TempMin;
    int TempMinIndex;

    //Declare every element 0 at t=0
    for(int n = 0; n < 90; n++)
    {
        NumberArray[n] = 0;
        NumberArrayIndexes[n] = n+1;
    }

    for(int i = 0; i < NumberOfLines; i++)
    {
        for(int j = 0; j < NbOfLotto; j++)
        {
            Temp = LineMatrix[i * NbOfLotto + j];
            (NumberArray[Temp-1])++;
        }
    }

    TempMin = NumberArray[0];

    //BUBBLE SORT FOR ARRAY OF NUMBERS
    for(int i = 0; i < 90 - 1; i++)
    {
        for(int j = 0; j < 90 - i - 1; j++)
        {
            if(NumberArray[j] > NumberArray[j+1])
            {
                TempMin = NumberArray[j];
                TempMinIndex = NumberArrayIndexes[j];

                NumberArray[j] = NumberArray[j+1];
                NumberArrayIndexes[j] = NumberArrayIndexes[j+1];

                NumberArray[j+1] = TempMin;
                NumberArrayIndexes[j+1] = TempMinIndex;
            }
        }
    }

    //Listing numbers and how many times they've been drawn
    std::cout << "\nNumbers listed by their appearance in increasing order:\n[ ";
    for (int p = 0; p < 90; p++)
    {
         std::cout << NumberArrayIndexes[p] << ":" << NumberArray[p] << "pcs ";
    }
    std::cout << "]\n\n";

    std::cout << "Rarest number is " << NumberArrayIndexes[0] << "\n";
    std::cout << "Most frequent number is " << NumberArrayIndexes[89] << "\n\n";

    //Best i numbers
    for(int i = 0; i < NbOfLotto; i++)
    {
        BestNumbers[i] = NumberArrayIndexes[i];
    }

    //Bubblesort
    std::cout << "Best numbers to play next week are: ";
    OrderInputBySize(BestNumbers);
}


// ----- MAIN -----

int main()
{

//--------------0TH PART OF PROGRAM: DECLARATION/INITIALIZATION--------------

    //1D dynamic memory allocated arrays
    int* UserVector;
    int* RandVector;
    int* LineMatrix;

    //Open file with specific file name
    std::ifstream OpenedFile;

    //Specific filename (eg. otos.txt)
    std::string FileName = Initialization(OpenedFile);

    //Output file initialization
    std::ofstream OutputFile ("OutputMatches.txt");


//--------------1ST PART OF PROGRAM: WORKING WITH USER DEFINED AND RANDOM VECTOR--------------

    //Allocate dynamic memory for vectors
    UserVector = AllocateMemory(UserVector);
    RandVector = AllocateMemory(RandVector);

    //Operations on user's vector
    UserVector = UserEnterNumber(UserVector);
    std::cout << "User vector: ";
    OrderInputBySize(UserVector);

    //Create random vector
    RandVector = RandomizeVector(RandVector);
    std::cout << "Random vector: ";
    OrderInputBySize(RandVector);

    //Check matches between user input and random
    CompareVectors(UserVector, RandVector);

//--------------2ND PART OF PROGRAM: WORKING WITH THE FILE--------------

    //"Count" lines in file
    CountLinesInFile(OpenedFile);

    //Allocate dynamic memory for 2D array of file
    LineMatrix = AllocateMemory2D(LineMatrix);

    //Read in file onto array
    LineMatrix = WriteFileIntoMatrix(OpenedFile, LineMatrix);

    //Check File and User input
    CompareFileAndUserInput(UserVector, LineMatrix, OpenedFile, OutputFile);

//--------------3RD PART OF PROGRAM: JUST FOR FUN--------------

    //The best numbers for next week
    GeneratingNextWeekLotteryNumbers(LineMatrix);

    return 0;
}
