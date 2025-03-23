#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[])
{
    if (fork() == 0)
    {
    }
    else
    {
        int count = 0;
        while (true)
        {
            time_t t = time(NULL);
            cout << put_time(localtime(&t), "[%Y-%m-%d] %H:%M:%S") << endl;
            if (count == 2)
            {
                cout << "“This program has gone on for far too long. Type Ctrl+C to abort this timer application.”" << endl;
            }
            count = (count + 1) % 3;
            sleep(1);
        }
    }
}
