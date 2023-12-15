#include <iostream>
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
void Initialization(std::ifstream &InputFile)
{
    std::string FileName = "zucc.txt";
/*
    //User input
    std::cout << "Please enter the name of the file: ";
    std::cin >> FileName;
*/
    OpenFile(FileName, InputFile);

    std::cout << '\n';

}

int CountData(std::ifstream &InputFile)
{

}

void Output(std::ifstream &InputFile, std::ofstream &OutputFile)
{
    char c;

    int Count = 0;

    while(InputFile.get(c))
    {
        OutputFile << c << " ";
        Count++;

        if(Count == 96)
        {
            OutputFile << "\n";
            Count = 0;
        }
    }

    std::cout << "Program successfully finished!\n\n";

    OutputFile.close();
}
int main()
{
    //Open file with specific file name
    std::ifstream OpenedFile;

    //Specific filename (eg. otos.txt)
    Initialization(OpenedFile);

    //Output file initialization
    std::ofstream OutputFile ("ZuccOut.txt");

    Output(OpenedFile, OutputFile);

}
