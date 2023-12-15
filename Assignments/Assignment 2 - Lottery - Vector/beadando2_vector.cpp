#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <vector>

//Define vector
typedef std::vector<int> u_vec;

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

    std::cout << '\n';

    return FileName;
}

int DefineNbOfLotto(int NbOfLotto)
{
    std::cout << "Please enter an integer for how many lottery numbers should've been drawn?\n(It could be 5,6,7, etc, for Lottery 5,6,7, etc...)\n";
    std::cout << "Lottery numbers should've been drawn: ";

    std::cin >> NbOfLotto;

    std::cout << '\n';

    return NbOfLotto;
}

u_vec ReserveSpaceForVectors(u_vec InputVector, int NbOfLotto)
{
    InputVector.resize(NbOfLotto);

    return InputVector;
}

u_vec ReserveSpace2D(u_vec Vec_2D, int NbOfLotto, int NumberOfLines)
{
    //
    Vec_2D.resize(NbOfLotto * NumberOfLines);

    //Return pointer
    return Vec_2D;
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
int CheckUserNumbersUniqueness(u_vec UserVector, int i)
{
    std::cout << "\nActual Number: " << UserVector[i] << "\n";
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
u_vec UserEnterNumber(u_vec UserVector, int NbOfLotto)
{
    //Test parameter
    int TestScope;
    int TestUniq;

    //Temporary storage
    int Temp;

    //TEST
/*    std::cout << "Input vector: [ ";
    for(int k = 0; k < NbOfLotto; k++)
    {
        std::cout << UserVector[k] << " ";
    }
    std::cout << "]\n";
*/
    std::cout << "Please enter " << NbOfLotto << " DIFFERENT integer between 1 and 90.\n";
    for(int i = 0; i < NbOfLotto; i++)
    {

        std::cout << "Number #" << i+1 << " : ";
        std::cin >> Temp;
        UserVector.at(i) = Temp;

        //Write UserVector numbers
        std::cout << UserVector[i];

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
void OrderInputBySize(u_vec InputVector, int NbOfLotto)
{

/*    //Test
    std::cout << "User's vector: ";
    for(int t = 0; t < NbOfLotto; t++)
    {
        std::cout << InputVector[t] << " ";
    }
*/
    std::sort(InputVector.begin(), InputVector.end());

    //Print out array
    std::cout << "[ ";
    for(int k = 0; k < NbOfLotto; k++)
    {
        std::cout << InputVector[k] << " ";
    }
    std::cout<< "]\n";
}

//Randomize vector (1-90)
u_vec RandomizeVector(u_vec RandVector, int NbOfLotto)
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
void CompareVectors(u_vec UserVector, u_vec RandVector, int NbOfLotto)
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

int CountLinesInFile(std::ifstream &InputFile, int NumberOfLines)
{
    std::string nbLines;

    //Read in the first line into string
    getline(InputFile, nbLines);

    //Convert string to int
    NumberOfLines = atoi(nbLines.c_str());

    //Test
    //std::cout << NumberOfLines;

    return NumberOfLines;
}

u_vec WriteFileIntoMatrix(std::ifstream &InputFile, u_vec LineMatrix, int NbOfLotto, int NumberOfLines)
{
    //Temporary storage for elements of file
    int Temp;

    //Test
    //std::cout << NumberOfLines;

    for(int i = 0; i < NumberOfLines; i++)
    {
        for(int j = 0; j < NbOfLotto; j++)
        {
            InputFile >> Temp;
            LineMatrix[i * NbOfLotto + j] = Temp;
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

void CompareFileAndUserInput(u_vec UserVector, u_vec LineMatrix, std::ifstream &InputFile, std::ofstream &OutputFile, int NbOfLotto, int NumberOfLines)
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

void GeneratingNextWeekLotteryNumbers(u_vec LineMatrix, int NbOfLotto, int NumberOfLines)
{
    //Array to store numbers
    u_vec NumberArray(90);
    u_vec NumberArrayIndexes(90);
    u_vec BestNumbers(NbOfLotto);

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

    //BUBBLE SORT FOR INDEXES (PYTHON DICT....)
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

    //Sort elements
    std::cout << "Best numbers to play next week are: ";
    OrderInputBySize(BestNumbers, NbOfLotto);
}


// ----- MAIN -----

int main()
{

//--------------0TH PART OF PROGRAM: DECLARATION/INITIALIZATION--------------


    //--- "CONST" INT FOR LOTTO 5,6,7 ETC... ---
    int NbOfLotto;
    //--- "CONST" INT FOR # OF LINES IN FILE... ---
    int NumberOfLines;

    //1D vectors
    u_vec UserVector;
    u_vec RandVector;
    u_vec LineMatrix;

    //Open file with specific file name
    std::ifstream OpenedFile;

    //Specific filename (eg. otos.txt)
    std::string FileName = Initialization(OpenedFile);

    //Output file initialization
    std::ofstream OutputFile ("OutputMatches.txt");

    //Numbers drawn
    NbOfLotto = DefineNbOfLotto(NbOfLotto);

    //Reserve space for vectors
    UserVector = ReserveSpaceForVectors(UserVector, NbOfLotto);
    RandVector = ReserveSpaceForVectors(RandVector, NbOfLotto);

//--------------1ST PART OF PROGRAM: WORKING WITH USER DEFINED AND RANDOM VECTOR--------------

    //Operations on user's vector
    UserVector = UserEnterNumber(UserVector, NbOfLotto);
    std::cout << "User vector: ";
    OrderInputBySize(UserVector, NbOfLotto);

    //Create random vector
    RandVector = RandomizeVector(RandVector, NbOfLotto);
    std::cout << "Random vector: ";
    OrderInputBySize(RandVector, NbOfLotto);

    //Check matches between user input and random
    CompareVectors(UserVector, RandVector, NbOfLotto);

//--------------2ND PART OF PROGRAM: WORKING WITH THE FILE--------------

    //"Count" lines in file
    NumberOfLines = CountLinesInFile(OpenedFile, NumberOfLines);

    //Allocate dynamic memory for 2D array of file
    LineMatrix = ReserveSpace2D(LineMatrix, NbOfLotto, NumberOfLines);

    //Read in file onto array
    LineMatrix = WriteFileIntoMatrix(OpenedFile, LineMatrix, NbOfLotto, NumberOfLines);

    //Check File and User input
    CompareFileAndUserInput(UserVector, LineMatrix, OpenedFile, OutputFile, NbOfLotto, NumberOfLines);

//--------------3RD PART OF PROGRAM: JUST FOR FUN--------------

    //The best numbers for next week
    GeneratingNextWeekLotteryNumbers(LineMatrix, NbOfLotto, NumberOfLines);

    return 0;
}
