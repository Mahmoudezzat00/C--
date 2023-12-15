#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int ceil_number;
    int i;
    int j;
    int boolean;
    int ceil_mod = floor(sqrt(ceil_number));

    cout << "Enter a positive Z number, which is 2, or greater:" << endl;
    cin >> ceil_number;

    for(j = 2; j <= ceil_number; j++)
    {
        boolean = 1;
        for(i = 2; i <= ceil_mod; i ++)
        {
            if((ceil_number % ceil_mod) == 0)
            {
                boolean = 0;
                return 1;
            }
        }

        if(boolean == 1)
        {
            cout << j << endl;
        }
    }
    return 0;
}

int collatz(int x)
{
    int hossz = 1;

    while (x != 1)
    {
        if (x % 2 == 0)
        {
            x = x / 2;
        }
        else
        {
            x = 3 * x + 1;
        }

        hossz++;
    }

    return hossz;
}
