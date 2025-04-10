// I hereby attest to the truth of the following facts:
// I have not discussed the c++ code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
// I have not used c++ code obtained from another student, or any other unauthorized source, whether modified or unmodified.
// If any c++ code or documentation used in my program was obtained from another source, it has been clearly noted with citations in the comments of my program.
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

        int *distance = new int[lines - 1];

        int x, y, z;
        if (!(cin >> x >> y >> z))
            return 1;

        for (int j = 1; j < lines; j++)
        {
            int next_x, next_y, next_z;
            if (!(cin >> next_x >> next_y >> next_z))
                return 1;

            distance[j - 1] = abs(x - next_x) + abs(y - next_y) + abs(z - next_z);

            x = next_x;
            y = next_y;
            z = next_z;
        }

        for (int j = 0; j < lines - 1; j++)
        {
            cout << distance[j] << endl;
        }
        if (i != cases - 1)
        {
            cout << endl;
        }

        delete[] distance;
    }
    return 0;
}