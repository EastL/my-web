#include <iostream>
#include <string>
#include <cstdlib>
#include <complex>
#include <math.h>

#define size 8
#define pi 3.14159
#define e 2.71828

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::complex;

complex<double> *FFT(long long *input)
{
    complex<double> *output = (complex<double> *)malloc(size * sizeof(complex<double>));
    
    for(int i = 0; i < size; i++)
    {
        double real = 0, image = 0;
        for(int j = 0; j < size; j++)
        {
            real += input[j] * cos( -2 * pi * i * j / size);
            image += input[j] * sin(-2 * pi * i * j / size); 
        }
        
        output[i] = complex<double>(real, image);
    }
    return output;
}

long long *IDFT(complex<double> *input)
{ 
    long long *output = (long long *)malloc(size * sizeof(long long));

    for(int i = 0; i < size; i++)
    {
        double real = 0, image = 0;
        complex<double> Complex(0, 0);
        for(int j = 0; j < size; j++)
        {
            real = cos(2* pi * i * j / size);
            image = sin(2* pi * i * j / size);
            Complex += complex<double>(real, image) * input[j];
        }

        output[i] = Complex.real()/size;
    }
    return output;

}

int main()
{
    long long *InputTest = (long long *)malloc(size * sizeof(long long));
    complex<double> *OutputTest = (complex<double> *)malloc(size * sizeof(complex<double>));

    cout << "Please input eight real number:\n";
    for(int i = 0; i < size; i++)
        cin >> *(InputTest + i);
    cout << endl;

    OutputTest = FFT(InputTest);
    InputTest = IDFT(OutputTest);

    for(int i = 0; i < size; i++)
        cout << *(InputTest + i) << ' ';
    cout << endl;

    return 0;
}
