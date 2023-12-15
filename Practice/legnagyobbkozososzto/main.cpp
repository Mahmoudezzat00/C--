#include <iostream>

using namespace std;

int GreatestComDiv(int First, int Second)
{
    int Temp;
    while(Second > 0)
    {
        Temp = Second;
        Second = First%Second;
        First = Temp;
    }
    return First;
}

int main()
{
    int First;
    int Second;
    int GCD;

    cout << "Enter two Z numbers" << endl;
    cin >> First;
    cin >> Second;

    GCD = GreatestComDiv(First, Second);

    cout << "GCD of " << First << " and " << Second << " is " << GCD << endl;
}
