#ifndef __FRAC
#define __FRAC

#include <string>
using namespace std;

//klasa reprezentująca ułamki
class frac {
public:
    int x;
    int y;

//konstruktory
    frac();
    frac(int);
    frac(int, int);
    frac(const frac &u);

//destruktor

    ~frac();

//operator przypisania
    frac & operator= (const frac &a);

//operator konwersji
    operator int() const;

//operator +=
void operator +=(const frac &a);

//funkcje
    int suma();
    void present();
    void skroc();
};

frac operator+ (const frac &a, const frac &b);
frac operator* (const frac &a, const frac &b);
ostream & operator<<(ostream &out, const frac& u);


#endif// __FRAC

