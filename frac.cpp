#include <iostream>
#include <cstring>
#include "frac.h"

using namespace std;

//największy wspólny dzielnik
int nwd(int a, int b) {
    int c;
    while(b) {
        c = a;
        a = b;
        b = c % b;
    }
    return a;
}

//konstruktor domniemany
frac::frac() {
    //cout << "Pracuje konstruktor domniemany" << endl;
    x = 0;
    y = 1;
}

frac::frac(int a) {
    //cout << "Pracuje konstruktor jednoargumentowy" << endl;
    x = a;
    y = 1;
}

frac::frac(int a , int b) {
    //cout << "Pracuje konstruktor dwuargumentowy" << endl;
    x = a;
    y = b;
}

frac::frac(const frac &u) {
    //cout << "Pracuje konstruktor kopiujący" << endl;
    x = u.x;
    y = u.y;
}

//desktruktor
frac::~frac() {
    //cout << "Działa desktruktor" << endl;
}

int frac::suma() {
    int wynik = this->x + this->y;
    return wynik;
}

void frac::present() {
    cout << "Licznik ułamka wynosi: " << this->x << endl;
    cout << "Mianownik ułamka wynosi: " << this->y << endl;
}

void frac::skroc() {
    int x_tmp = x;
    this->x /=  nwd(x_tmp, this->y);
    this->y /=  nwd(x_tmp, this->y);
}

frac operator+(const frac &a, const frac &b) {
    frac u;
    u.x = (a.x) * (b.y) + (a.y) * (b.x);
    u.y = (a.y) * (b.y);
    u.skroc();
    return u;
}

frac operator*(const frac &a, const frac &b) {
    frac u;
    u.x = (a.x) * (b.x);
    u.y = (a.y) * (b.y);
    u.skroc();
    return u;
}

frac & frac::operator=(const frac &a) {
    //cout << "Pracuje operator przypisania" << endl;
    this->x = a.x;
    this->y = a.y;
    return *this;
}

frac::operator int() const {
    return x/y;
}
void frac::operator +=(const frac &a) {
    *this = *this + a;
}

ostream & operator<<(ostream &out, const frac& u) {
    if(u.y == 1) out << u.x;
    else if (u.y == -1) out << -u.x;
    else if((u.x >= 0 && u.y > 0))  out << u.x << "/" << u.y;
    else if((u.x < 0 && u.y < 0))  out << -u.x << "/" << -u.y;
    else if((u.x > 0 && u.y < 0))  out << -u.x << "/" << -u.y;
    else if((u.x < 0 && u.y > 0))  out << u.x << "/" << u.y;

    return out;
}
