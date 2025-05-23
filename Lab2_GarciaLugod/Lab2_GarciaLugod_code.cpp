// I hereby attest to the truth of the following facts:
// I have not discussed the c++ code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
// I have not used c++ code obtained from another student, or any other unauthorized source, whether modified or unmodified.
// If any c++ code or documentation used in my program was obtained from another source, it has been clearly noted with citations in the comments of my program.
#include <iostream>
using namespace std;

int main(void)
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;

        // get the rest of the string
        string s;
        // remove leading whitespace with cin >> ws
        getline(cin >> ws, s);
        // remove trailing whitespace
        size_t w = s.find_last_not_of(" \t\f\v\n\r");
        if (w != string::npos)
            s.erase(w + 1);

        printf("Agent#%d is at (%d, %d)\n", i + 1, a, b);
        printf("Says: %s\n", s.c_str());
    }
    return 0;
}