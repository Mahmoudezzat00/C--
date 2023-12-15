#include <iostream>

using namespace std;

void IsItIn(int TestArray[], int SizeOfArray, int TestNumber)
{
    int BooleanTemp = 0;
    for(int i = 0; i < SizeOfArray; i++)
    {
        if(TestNumber == TestArray[i])
        {
            BooleanTemp = 1;
            break;
        }
    }
    if(BooleanTemp == 1)
    {
        cout << "Given number is element of given array" << endl;
    }
    else
    {
        cout << "Given number is NOT element of given array" << endl;
    }
}

int SumOfElements(int TestArray[], int SizeOfArray)
{
    int Sum = 0;
    for(int i = 0; i < SizeOfArray; i++)
    {
        Sum += TestArray[i];
    }

    return Sum;
}

int NormalElements(int TestArray[], int SizeOfArray)
{
    for(int i = 0; i < SizeOfArray; i++)
    {
        TestArray[i] = i + 1;
    }
}

int RandElements(int TestArray[], int SizeOfArray)
{

}

int main()
{
    int SizeOfArray = 10;
    int TestArray[SizeOfArray];
    int TestNumber;
    int SumOfArrayElements;

    char SwitchRandOrNorm;
    int Decide;

    cout << "Random elements or normal elements? (R/N)?" << endl;
    cin >> SwitchRandOrNorm;

    switch(SwitchRandOrNorm)
    {
        case 'R':
        case 'r':
        {
            Decide = 0;
        }
        case 'N':
        case 'n':
        {
            Decide = 1;
        }
    }

    if(Decide == 0)
    {
        RandElements(TestArray, SizeOfArray);
    }
    else
    {
        NormalElements(TestArray, SizeOfArray);
    }

    SumOfArrayElements = SumOfElements(TestArray, SizeOfArray);

    cout << "Sum of Array elements is " << SumOfArrayElements << endl;

    cout << "Please enter a number" << endl;
    cin >> TestNumber;

    IsItIn(TestArray, SizeOfArray, TestNumber);
}
