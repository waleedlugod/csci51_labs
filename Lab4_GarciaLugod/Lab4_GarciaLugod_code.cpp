#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int multiplicand = atoi(argv[1]);
    int multiplier = atoi(argv[2]);

    int res = 0;
    if (multiplier == 0)
    {
        cout << 0 << endl;
        return 0;
    }

    if (multiplier < 0)
    {
        multiplicand = ~multiplicand + 1;
        multiplier = ~multiplier + 1;
    }

    if (multiplier > 31)
    {
        for (int i = 0; i < multiplier; i++)
        {
            res += multiplicand;
        }
    }
    else
    {
        // Finds the factors of the multiplier as powers of 2, and sums the multiplicand shifted
        // by the powers.
        // Ex: multiplicand = 3, multiplier = 19
        // 19 = 0b10011 = 2**4 + 2**1 + 2**0
        // res = 3<<4 + 3<<1 + 3<<0 = 3*(2**4) + 3*(2**1) + 3*(2**0) = 3*16 + 3*2 + 3*1 = 57
        // The following checks if the current digit (d) has a 1, and adds the multiplicand
        // shifted by digit to res if so. d is then shifted to the left.

        int d = 1;
        while (d <= multiplier)
        {
            if (d & multiplier)
                res += multiplicand << d - 1;
            d <<= 1;
        }
    }

    cout << res << endl;
    return 0;
}