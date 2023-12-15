#include <iostream> //std::cout
#include <string>   //std::string
#include <bitset>   //std::bitset
#include <sstream>  //std::sstream
#include <algorithm>//std::algorithm

//using namespace std;

void ReadInText()
{
    //Variables for function
    std::string Text2Binary;
    char Letter;

    //Information on Terminal
    std::cout << "Write here the translatable text:\n";

    //Read in translatable text
    std::getline(std::cin >> std::ws, Text2Binary);

    //TEST
    //std::cout << "Input text: " << Text2Binary << "\n";

    //Terminal information
    std::cout << "In Binary: ";

    for(int i = 0; i < Text2Binary.size(); i++)
    {
        Letter = Text2Binary[i];
        std::bitset <8> binaryCode(Letter);
        std::cout << binaryCode << " ";
    }
}

void ReadInBinary()
{
    //Variables for function
    std::string Binary2Text;
    std::string OutputText;

    //information on Terminal
    std::cout << "Write here the translatable binary code: ";

    //Read in translatable binary code
    std::getline(std::cin >> std::ws, Binary2Text);

    //Erase possible whitespaces
    Binary2Text.erase(std::remove(Binary2Text.begin(), Binary2Text.end(), ' '), Binary2Text.end());

    //Input to stream
    std::stringstream StreamText(Binary2Text);

    //TEST
    //std::cout << "\nInput binary string: " << Binary2Text << "\n";

    //Terminal information
    std::cout << "Binary in ASCII text: ";

    while(StreamText.good())
    {
        for(int j = 0; j < 8; j++)
        {
            std::bitset<8> binaryCode;
            StreamText >> binaryCode;
            char Letter = char(binaryCode.to_ulong());
            OutputText += Letter;
        }
    }

    std::cout << OutputText;
}

int main()
{
    //Information on Terminal
    std::cout << "### Binary-Text Converter ###";

    //Variable for switch below
    char SwitchOption;

    std::cout << "Choose, whether convert text to binary, or binary to text\n" <<
            "1. Write T for Text to Binary\n" <<
            "2. Write B for Binary to Text\n";
    std::cout << "Choose function (T/B): " << "\n";

    //Read in user's input for switch below
    std::cin >> SwitchOption;

    switch(SwitchOption)
    {
        case 'T':
        case 't':
        {
            ReadInText();
            break;
        }
        case 'B':
        case 'b':
        {
            ReadInBinary();
            break;
        }
        default:
        {
            std::cout << "Enter a valid option!!!!\n";
            break;
        }
    }
}
