#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <ctime>

//New type for string vector
typedef std::vector<std::string> s_vec;



// -------- INITIALIZE FILE --------

void CheckFile(const std::ifstream &InputFile)
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
// -------- INITIALIZE FILE END --------


// -------- INITIALIZE VECTORS --------
int CountRowsInFile(int Rows, std::ifstream &InputFile)
{
    int RowCount = 0;

    std::string TempString;

    while(std::getline(InputFile, TempString))
    {
        RowCount++;
    }

    Rows = RowCount;

    std::cout << "Number of measurements: "  << Rows << "\n";

    InputFile.close();

    return Rows;
}

//Resize InputVector
s_vec ReserveSpaceForVectors(s_vec InputVector)
{
    InputVector.resize(4);

    return InputVector;
}


// -------- READING IN DATA --------
void CountVehicleTypes(s_vec Dataline, int &CountMotorbikes, int &CountVans, int &CountBuses, int &CountPKWs)
{
    std::string LicensePlate = Dataline[3];

    //Type of vehicle (first character of license plate)
    char Type = LicensePlate[0];

    switch(Type)
    {
        case 'M':
        {
            CountMotorbikes++;
            break;
        }
        case 'K':
        {
            CountVans++;
            break;
        }
        case 'B':
        {
            CountBuses++;
            break;
        }
        default:
        {
            CountPKWs++;
            break;
        }
    }

}


s_vec ReadInDataline(s_vec Dataline, std::ifstream &InputFile)
{
    //File elements
    std::string Hours;
    std::string Minutes;
    std::string Seconds;
    std::string LicensePlate;

    //Read in line
    InputFile >> Hours >> Minutes >> Seconds >> LicensePlate;

    //Add ActualLine to string vector
    Dataline[0] = Hours;
    Dataline[1] = Minutes;
    Dataline[2] = Seconds;
    Dataline[3] = LicensePlate;

    return Dataline;
}

int FirstInTheHour(s_vec Datafile, int FirstInHour)
{
    if(atoi(Datafile[0].c_str()) > FirstInHour)
    {
        FirstInHour = atoi(Datafile[0].c_str());
        std::cout << "First car in the " << FirstInHour << ".th hour is the " << Datafile[3] << "\t";
    }

    return FirstInHour;
}

int CountBusiestHour(int TempHourActual, int TempHourBack, int HourCounterTemp)
{
    if(TempHourActual == TempHourBack)
    {
        HourCounterTemp++;
    }

    return HourCounterTemp;
}

void ReadInDatalinesLoop(s_vec Dataline, std::ifstream &InputFile)
{
    int FirstInHour = 0;

    //Busiest hour
    int TempHourActual;
    int TempHourBack = 0;
    int HourCounterTempMax = 0;
    int HourCounterMax = 0;
    int BusiestHour;

    //NB OF TYPES
    int CountMotorbikes = 0;
    int CountVans = 0;
    int CountBuses = 0;
    int CountPKWs = 0;

    //LOOP THROUGH FILE
    while(!InputFile.eof())
    {
        //Read in data line by line
        Dataline = ReadInDataline(Dataline, InputFile);

        /*//TEST (print lines)
        for(int i = 0; i < 4; i++)
        {
            std::cout << Dataline[i] << " ";
        }
        std::cout << "\n";
        */


        //BUSIEST HOUR
        //Actual hour in the loop (8,8,8,8,....9,9,9,9...)
        TempHourActual = atoi(Dataline[0].c_str());

        //Initial condition
        if(TempHourBack == 0)
        {
            TempHourBack = TempHourActual;
        }

        //Counting measurements in the "TempHourActual".th hour
        HourCounterTempMax = CountBusiestHour(TempHourActual, TempHourBack, HourCounterTempMax);
        //std::cout << HourCounterTempMax << " ";

        //If greater maximum:
        if(HourCounterTempMax > HourCounterMax)
        {
            HourCounterMax = HourCounterTempMax;
            BusiestHour = TempHourBack;
        }

        //If next hour:
        if(TempHourActual != TempHourBack || InputFile.eof())
        {
            std::cout << "Number of cars in the " << TempHourBack << ".th hour: " << HourCounterTempMax << "\n";
            TempHourBack = TempHourActual;
            HourCounterTempMax = 1;
        }

        //FIRST HOUR VEHICLES
        FirstInHour = FirstInTheHour(Dataline, FirstInHour);

        //NB OF TYPES
        CountVehicleTypes(Dataline, CountMotorbikes, CountVans, CountBuses, CountPKWs);
    }

    std::cout << "\nNumber of vehicles by type:\n" << "Motorbikes: " << CountMotorbikes << "\n"
              << "Vans: " << CountVans << "\n"
              << "Buses: " << CountBuses << "\n"
              << "PKWs: " << CountPKWs << "\n";

    std::cout << "\nNumber of cars in the busiest hour (" << BusiestHour << " hour): " << HourCounterMax << "\n";

    std::cout << "\nAHhhhHHhhhhhhHhH";

}

// -------- READING IN DATA END --------


int main()
{
    //Open file with specific file name
    std::ifstream InputFile;

    //Initialize File
    std::string FileName = Initialization(InputFile);

    //Output file initialization
    std::ofstream OutputFile ("OutputMatches.txt");


    //Define variables
    //Vector
    s_vec LineVector;
    //Counters
    int Rows;

    //Resize vector
    //Rows = CountRowsInFile(Rows, InputFile);
    LineVector = ReserveSpaceForVectors(LineVector);

    //Reopen closed File
    //InputFile.open(FileName.c_str());

    //Read in
    ReadInDatalinesLoop(LineVector, InputFile);

    std::cout << "\nTest1";

    InputFile.close();

    std::cout << "\nTest2";

    return 0;
}
