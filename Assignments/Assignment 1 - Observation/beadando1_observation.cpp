#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

//Global for length of data stream
unsigned int LengthTotal;


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

//Allocating memory for input
signed int* AllocatingMemory(signed int* UserVector)
{
    //Request memory
    UserVector = new signed int[LengthTotal];

    //Return pointer
    return UserVector;
}

//Copying UserVector
signed int* CopyVector(signed int* UserVector, signed int* UserVectorCopy)
{

    for(int i = 0; i < LengthTotal; i++)
    {
        //std::cout << i+1 << ".: ";
        //std::cout << UserVector[i] << " = ";
        UserVectorCopy[i] = UserVector[i];
        //std::cout << UserVectorCopy[i] << "\n";
    }

    return UserVectorCopy;
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
void OpenFile(std::string FileName, std::ifstream &InputFile)
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

void CountIntegersInFile(std::ifstream &InputFile)
{
    //Index for counting integers
    unsigned int Count = 0;

    //Temporary storage for each integer number
    int Num;

    while(InputFile.good())
    {
        InputFile >> Num;
        Count++;
    }

    LengthTotal = Count;

    InputFile.close();
}

signed int* ReadInDataFromFile(signed int* UserVector, std::string FileName, std::ifstream &InputFile)
{
    signed int Num;

    InputFile.open(FileName.c_str());

    //Reading in file to UserVector array

    for(int i = 0; i < LengthTotal; i++)
    {
        InputFile >> UserVector[i];
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
void LengthOfFlight()
{
    std::cout << "How long was the flight (number of data points)?\nPlease enter an integer larger, than 0: ";
    std::cin >> LengthTotal;
}

//Input from User read from terminal
signed int* InputFromCin(signed int* UserVector)
{
    std::cout << "Please enter the data values (integers)!\n";
    for(unsigned int i = 0; i < LengthTotal; i++)
    {
        std::cout << i+1 << ".: ";
        std::cin >> UserVector[i];
    }

    return UserVector;
}

// ----- INITIALIZATION FOR TERMINAL INPUT END -----


// ----- CALCULATIONS -----

//Bubblesort elements
void Bubblesort(signed int* UserVector)
{
    //Temporary storage
    int Temp;

    //BUBBLESORT
    for(unsigned int i = 0; i < LengthTotal - 1; i++)
    {
        for(unsigned int j = 0; j < LengthTotal - i - 1; j++)
        {
            if(UserVector[j] > UserVector[j+1])
            {
                Temp = UserVector[j];
                UserVector[j] = UserVector[j+1];
                UserVector[j+1] = Temp;
            }
        }
    }
}

//SPECIAL BUBBLESORT FOR 5TH QUESTION
void BubblesortWITHINDEX(signed int* UserVector, int IndexArray[])
{
    //Temporary storage
    int Temp;
    int TempIndex;

    //BUBBLESORT
    for(unsigned int i = 0; i < LengthTotal - 1; i++)
    {
        for(unsigned int j = 0; j < LengthTotal - i - 1; j++)
        {
            if(UserVector[j] > UserVector[j+1])
            {
                Temp = UserVector[j];
                TempIndex = IndexArray[j];

                UserVector[j] = UserVector[j+1];
                IndexArray[j] = IndexArray[j+1];

                UserVector[j+1] = Temp;
                IndexArray[j+1] = TempIndex;
            }
        }
    }
}

//Find maximum
int MaximumHeight(signed int* UserVector)
{
    //Storage for maximum
    int Maximum;

    //Defined above
    Bubblesort(UserVector);

    Maximum = UserVector[LengthTotal-1];

    return Maximum;
}

//Find maximum with method #2
int MaximumHeight2(signed int* UserVector)
{
    int TempMaximum = UserVector[0];

    for(unsigned int i = 0; i < LengthTotal; i++)
    {
        if(UserVector[i] > TempMaximum)
        {
            TempMaximum = UserVector[i];
        }
    }

    return TempMaximum;
}

//Highest point underwater
int MaximumHeightUnderwater(signed int* UserVector)
{
    int MaximumUnderwater = 0;

    //Defined above
    Bubblesort(UserVector);

    for(unsigned int k = 0; k < LengthTotal; k++)
    {
        if(UserVector[k] >= 0)
        {
            if(k > 1)
            {
                MaximumUnderwater = UserVector[k-1];
                break;
            }
            else
            {
                break;
            }
        }
    }

    return MaximumUnderwater;
}

//Highest point underwater
int MaximumHeightUnderwater2(signed int* UserVector)
{
    int MaximumUnderwater2;

    int Temp;

    for(unsigned int i = 0; i < LengthTotal; i++)
    {
        if(UserVector[i] < 0)
        {
            Temp = UserVector[i];

            if(UserVector[i] >= Temp)
            {
                MaximumUnderwater2 = UserVector[i];
            }
        }
    }

    return MaximumUnderwater2;
}

//Longest desert
int LongestDesertOnLand(signed int* UserVector)
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
int LongestUphillOnLand(signed int* UserVector)
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
int LongestUphillWithUnderwater(int* UserVector)
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
int HighestPeak(int* UserVector)
{
    //Storage for highest element
    int Highest;

    //Index array
    int IndexArray[LengthTotal];

    for(int m = 0; m < LengthTotal; m++)
    {
        IndexArray[m] = m+1;
    }

    BubblesortWITHINDEX(UserVector, IndexArray);

    for(int g = LengthTotal - 1; g > 0; g--)
    {
        if(UserVector[g] > UserVector[g-1] && UserVector[g] != UserVector[g+1])
        {
            Highest = IndexArray[g];
            break;
        }
    }

    return Highest;
}

// ----- CALCULATIONS END -----



// ----- MAIN -----

int main()
{
    //Variables for asked data
    int Maximum;
    int Maximum2;
    int MaximumUnderwater;
    int MaximumUnderwater2;
    int LongestDesert;
    int LongestUphill;
    int LongestUphillWithUW;
    int Highest;

    //int UserVector[10] = {2,3,5,4,8,8,2,-3,-1,1};
    //int UserVectorCopy[10] = {2,3,5,4,8,8,2,-3,-1,1};
    //LengthTotal = 10;

    //User defined input
    signed int* UserVector;
    signed int* UserVectorCopy;

    //Choosing between UD or F
    if(UserdefinedOrFile() == false)
    {
        //Open file with specific file name
        std::ifstream OpenedFile;

        //Finding specific file
        std::string FileName = Initialization(OpenedFile);

        //Finding data points
        CountIntegersInFile(OpenedFile);

        //Test
        //std::cout << LengthTotal << "\n";

        //Memory allocation
        UserVector = AllocatingMemory(UserVector);
        UserVectorCopy = AllocatingMemory(UserVectorCopy);

        //Read data from file
        UserVector = ReadInDataFromFile(UserVector, FileName, OpenedFile);
        UserVectorCopy = CopyVector(UserVector, UserVectorCopy);

        OpenedFile.close();

    }
    else
    {
        LengthOfFlight();

        //Memory allocation
        UserVector = AllocatingMemory(UserVector);
        UserVectorCopy = AllocatingMemory(UserVectorCopy);

        //User enters values from cin.
        UserVector = InputFromCin(UserVector);
        UserVectorCopy = CopyVector(UserVector, UserVectorCopy);
    }

    //std::cout << sizeof(UserVector) << "\n";


    //1.
    //Find maximum
    Maximum = MaximumHeight(UserVector);
    std::cout << "Maximum height: " << Maximum << "\n";
    Maximum2 = MaximumHeight2(UserVectorCopy);
    std::cout << "Maximum height (without modifying the original array): " << Maximum2 << "\n";

    //2.
    //Find the underwater maximum
    MaximumUnderwater = MaximumHeightUnderwater(UserVector);
    if(MaximumUnderwater != 0)
    {
        std::cout << "Maximum height underwater: " << MaximumUnderwater << "\n";
    }
    else
    {
        std::cout << "There are no underwater points!!\n";
    }

    //Method 2
    MaximumUnderwater2 = MaximumHeightUnderwater2(UserVectorCopy);
    std::cout << "Maximum height underwater (without modifying the original array): " << MaximumUnderwater2 << "\n";

    //TEST
    std::cout << "Modified array: [ ";
    for(int i = 0; i < LengthTotal; i++)
    {
        std::cout << UserVector[i] << " ";
    }
    std::cout << "]\n\n";

    std::cout << "Unmodified array: [ ";
    for(int j = 0; j < LengthTotal; j++)
    {
        std::cout << UserVectorCopy[j] << " ";
    }
    std::cout << "]\n\n";

    //3.
    //Find longest desert
    LongestDesert = LongestDesertOnLand(UserVectorCopy);
    std::cout << "The longest plain/desert is " << LongestDesert << " km long.\n";

    //4.
    //Longest Uphill without and with the underwater uphills
    LongestUphill = LongestUphillOnLand(UserVectorCopy);
    LongestUphillWithUW = LongestUphillWithUnderwater(UserVectorCopy);
    std::cout << "The longest uphill on the land is " << LongestUphill << " km long.\n";
    std::cout << "The longest uphill, including both underwater and land uphills is " << LongestUphillWithUW << " km long.\n";

    //5.
    //Highest peak among the surface
    Highest = HighestPeak(UserVectorCopy);
    std::cout << "The highest peak is at the position of the " << Highest << ". km.\n";

    delete UserVector;
    delete UserVectorCopy;
}
