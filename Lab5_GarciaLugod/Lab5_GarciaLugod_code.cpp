#include <iostream>
using namespace std;

int main(void)
{
    int cases;
    if (!(cin >> cases))
        return 1;
    for (int i = 0; i < cases; i++)
    {
        int lines;
        if (!(cin >> lines))
            return 1;

        int distance[lines - 1] = {};

        int x = 0, y = 0, z = 0;
        for (int j = 0; j < lines; j++)
        {
            if (!(cin >> x >> y >> z))
                return 1;
        }
    }
}