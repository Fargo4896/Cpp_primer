#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

int main()
{
    /*
    cout << "default format: " << 100 * sqrt(2.0) << endl
    << "scientific: " << scientific << 100 * sqrt(2.0) << endl
    << "fixed decimal: " << fixed << 100 * sqrt(2.0) << endl
    << "hexidecimal: " << uppercase << 100 * sqrt(2.0) << endl
    << "use defaults: " << defaultfloat << 100 * sqrt(2.0) << endl
    << endl;
    */
    cout << left <<setw(15) << "default format:" <<setw(25)<< right<< 100 * sqrt(2.0) << '\n'
	<< left << setw(15) << "scientific:" << scientific << setw(25) << right << 100 * sqrt(2.0) << '\n'
	<< left << setw(15) << "fixed decimal:" << setw(25) << fixed << right << 100 * sqrt(2.0) << '\n'
	<< left << setw(15) << "hexidecimal:" << setw(25) << uppercase << hexfloat << right << 100 * sqrt(2.0) << '\n'
	<< left << setw(15) << "use defaults:" << setw(25) << defaultfloat << right << 100 * sqrt(2.0)
	<< "\n\n";
    return 0;
}