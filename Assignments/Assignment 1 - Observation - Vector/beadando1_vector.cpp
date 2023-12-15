#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

//typedef vector
typedef std::vector<double> u_vec;


// ----- GENERAL INITIALIZATION -----

//Choose between User defined parameters or parameters from file
bool UserdefinedOrFile()
{
    char Decide;

    std::cout << "Choose whether you want to read data points from a file,\n"
                 "or you want to give the data by yourself, inside the terminal?\n"
                 "Please write (U) for User (terminal) defined parameters\n"
                 "Please write (F) to get data points from a File\n";
    //Defined down in the switch/default case

    for(;;)
    {
        std::cout << "U/F: ";

        std::cin >> Decide;

        switch(Decide)
        {
            case 'U':
            case 'u':
            {
                return true;
            }

            case 'F':
            case 'f':
            {
                return false;
            }
            default:
            {
                std::cout << "\nInvalid option, try again!\n";
            }
        }
    }
}

// ----- GENERAL INITIALIZATION END -----


// ----- INITIALIZATION FOR DATAFILE -----

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
void OpenFile(const std::string &FileName, std::ifstream &InputFile)
{
    InputFile.open(FileName.c_str());

    //Test for filename
    //std::cout << FileName;

    //Check
    CheckFile(InputFile);
}

//Initialization file name
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

u_vec ReserveSpaceForVectors(u_vec InputVector, int LengthTotal)
{
    InputVector.reserve(LengthTotal);

    return InputVector;
}

int CountIntegersInFile(std::ifstream &InputFile, int LengthTotal)
{
    //Index for counting integers
    int Count = 0;

    //Temporary storage for each integer number
    int Num;

    while(InputFile.good())
    {
        InputFile >> Num;
        Count++;
    }

    LengthTotal = Count;

    InputFile.close();

    return LengthTotal;
}

u_vec ReadInDataFromFile(u_vec UserVector, const std::string &FileName, std::ifstream &InputFile, int LengthTotal)
{
    InputFile.open(FileName.c_str());

    int Temp;

    //Reading in file to UserVector array

    for(int i = 0; i < LengthTotal; i++)
    {
        InputFile >> Temp;
        UserVector.push_back(Temp);
    }

    std::cout << "INPUT VECTOR: [ ";
    for(int z = 0; z < LengthTotal; z++)
    {
        std::cout << UserVector[z] << " ";
    }
    std::cout << "]\n";

    return UserVector;
}

// ----- INITIALIZATION FOR DATAFILE END -----


// ----- INITIALIZATION FOR TERMINAL INPUT -----

//Define number of data points
int LengthOfFlight(int LengthTotal)
{
    std::cout << "How long was the flight (number of data points)?\nPlease enter an integer larger, than 0: ";
    std::cin >> LengthTotal;

    return LengthTotal;
}

//Input from User read from terminal
u_vec InputFromCin(u_vec UserVector, int LengthTotal)
{
    double Temp;

    std::cout << "Please enter the data values (integers)!\n";
    for(int i = 0; i < LengthTotal; i++)
    {
        std::cout << i+1 << ".: ";
        std::cin >> Temp;
        UserVector.push_back(Temp);
    }

    return UserVector;
}

// ----- INITIALIZATION FOR TERMINAL INPUT END -----


// ----- CALCULATIONS -----

//Find maximum
int MaximumHeight(u_vec const &UserVector, int LengthTotal)
{
    int TempMaximum = UserVector[0];

    for(int i = 0; i < LengthTotal; i++)
    {
        if(UserVector[i] > TempMaximum)
        {
            TempMaximum = UserVector[i];
        }
    }

    return TempMaximum;
}

//Highest point underwater
int MaximumHeightUnderwater(u_vec const &UserVector, int LengthTotal)
{
    int MaximumUnderwater = 0;

    for(int i = 0; i < LengthTotal; i++)
    {
        if(UserVector[i] < 0)
        {
            MaximumUnderwater = UserVector[i];
            break;
        }
    }

    for(int j = 0; j < LengthTotal; j++)
    {
        if(UserVector[j] < 0 && UserVector[j] > MaximumUnderwater)
        {
            MaximumUnderwater = UserVector[j];
        }
    }

    return MaximumUnderwater;
}

//Longest desert
int LongestDesertOnLand(u_vec const &UserVector, int LengthTotal)
{
    int LongestLengthCount = 1;
    int CurrentLength = 1;

    for(int i = 0; i < LengthTotal - 1; i++)
    {
        if(UserVector[i] == UserVector[i+1] && UserVector[i] > 0)
        {
            CurrentLength++;
        }
        else
        {
            CurrentLength = 1;
        }

        if(LongestLengthCount < CurrentLength)
        {
            LongestLengthCount = CurrentLength;
        }
    }

    return LongestLengthCount;
}

//Longest uphill (Increasing order of numbers)
int LongestUphillOnLand(u_vec const &UserVector, int LengthTotal)
{
    int LongestLengthCount = 1;
    int CurrentLength = 1;

    for(int i = 0; i < LengthTotal - 1; i++)
    {
        if(UserVector[i] < UserVector[i+1] && UserVector[i] >= 0)
        {
            CurrentLength++;
        }
        else
        {
            CurrentLength = 1;
        }

        if(LongestLengthCount < CurrentLength)
        {
            LongestLengthCount = CurrentLength;
        }
    }

    return LongestLengthCount;
}

//Longest uphill, counting underwater uphills too
int LongestUphillWithUnderwater(u_vec const &UserVector, int LengthTotal)
{
    int LongestLength = 1;
    int CurrentLength = 1;

    for(int i = 0; i < LengthTotal - 1; i++)
    {
        if(UserVector[i] < UserVector[i+1])
        {
            CurrentLength++;
        }
        else
        {
            CurrentLength = 1;
        }

        if(LongestLength < CurrentLength)
        {
            LongestLength = CurrentLength;
        }
    }

    return LongestLength;
}
//Which element is the highest peak?
int HighestPeak(u_vec UserVector, int LengthTotal)
{
    //Storage for highest element
    double HighestData = UserVector[0];
    int HighestPosition;

    for(int i = 1; i < LengthTotal-1; i++)
    {
        if(UserVector[i] > UserVector[i-1] && UserVector[i] > UserVector[i+1] && UserVector[i] > HighestData)
        {
            HighestData = UserVector[i];
            HighestPosition = i+1;
        }
    }

    if(UserVector[LengthTotal-1] > HighestData && UserVector[LengthTotal-1] != UserVector[LengthTotal-2])
    {
        HighestData = UserVector[LengthTotal-1];
        HighestPosition = LengthTotal;
    }

    return HighestPosition;
}

// ----- CALCULATIONS END -----



// ----- MAIN -----

int main()
{
    //Variable for length of data stream
    int LengthTotal;

    //Variables for asked data
    int Maximum;
    int MaximumUnderwater;
    int LongestDesert;
    int LongestUphill;
    int LongestUphillWithUW;
    int Highest;

    //User defined input
    u_vec UserVector;

    //Choosing between UD or F
    if(UserdefinedOrFile() == false)
    {
        //Open file with specific file name
        std::ifstream OpenedFile;

        //Finding specific file
        std::string FileName = Initialization(OpenedFile);

        //Finding data points
        LengthTotal = CountIntegersInFile(OpenedFile, LengthTotal);

        //Reserve
        UserVector = ReserveSpaceForVectors(UserVector, LengthTotal);

        //Read data from file
        UserVector = ReadInDataFromFile(UserVector, FileName, OpenedFile, LengthTotal);

        OpenedFile.close();

    }
    else
    {
        //Determine length of flight
        LengthTotal = LengthOfFlight(LengthTotal);

        //Reserve
        UserVector = ReserveSpaceForVectors(UserVector, LengthTotal);

        //User enters values from cin.
        UserVector = InputFromCin(UserVector, LengthTotal);
    }

    std::cout << "\n\nMeasurement data:\n";
    //0.
    //Length of observational line
    std::cout << "0.  Length of the observation: " << LengthTotal << " km" << "\n";

    //1.
    //Find maximum
    Maximum = MaximumHeight(UserVector, LengthTotal);
    std::cout << "1.  Maximum height: " << Maximum << "\n";

    //2.
    //Find the underwater maximum
    MaximumUnderwater = MaximumHeightUnderwater(UserVector, LengthTotal);
    if(MaximumUnderwater != 0)
    {
        std::cout << "2.  Maximum height underwater: " << MaximumUnderwater << "\n";
    }
    else
    {
        std::cout << "2.  There are no underwater points!\n";
    }

    //3.
    //Find longest desert
    LongestDesert = LongestDesertOnLand(UserVector, LengthTotal);
    std::cout << "3.  The longest plain/desert is " << LongestDesert << " km long.\n";

    //4.
    //Longest Uphill without and with the underwater uphills
    LongestUphill = LongestUphillOnLand(UserVector, LengthTotal);
    LongestUphillWithUW = LongestUphillWithUnderwater(UserVector, LengthTotal);
    std::cout << "4a.  The longest uphill on the land is " << LongestUphill << " km long.\n";
    std::cout << "4b.  The longest uphill, including both underwater and land is " << LongestUphillWithUW << " km long.\n";

    //5.
    //Highest peak among the surface
    Highest = HighestPeak(UserVector, LengthTotal);
    std::cout << "5.  The highest peak is at the position of the " << Highest << ". km.\n";
}
