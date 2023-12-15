#include <iostream>

using namespace std;

void fib(int ceil_number)
{
    int i_last = 1;
    int i_next = 1;
    int Temp;

    cout << '1' << endl;
    cout << '1' << endl;

    for(int i = 3; i <= ceil_number; i++)
    {
        Temp = i_next;
        i_next += i_last;
        i_last = Temp;
        cout << i_next << endl;
    }
}

int main()
{
    int n;
    cout << "Enter a positive Z number, bigger than 3" << endl;
    cin >> n;
    fib(n);
}
