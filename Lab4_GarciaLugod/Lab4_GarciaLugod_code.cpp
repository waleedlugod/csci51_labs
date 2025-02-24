// I hereby attest to the truth of the following facts:
// I have not discussed the c++ code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
// I have not used c++ code obtained from another student, or any other unauthorized source, whether modified or unmodified.
// If any c++ code or documentation used in my program was obtained from another source, it has been clearly noted with citations in the comments of my program.
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int multiplicand = atoi(argv[1]);
    int multiplier = atoi(argv[2]);

    int res = 0;
    if (multiplicand == 0 || multiplier == 0)
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

        int bindigit = 1; // 0b...001
        int power = 0;
        while (bindigit <= multiplier)
        {
            if (bindigit & multiplier)
                res += multiplicand << power;
            power++;
            bindigit <<= 1;
        }
    }

    cout << res << endl;
    return 0;
}