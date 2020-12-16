#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "frac.h"
#include "matrix.h"

using namespace std;

//Zadanie matrix
//Piotr Wasilewski

int main() {
    //konstruktor domyślny
    Matrix<float,4,3> R;
    cout << "Macierz zerowa R:\n" << R << endl;

    //konstruktor jednoargumentowy l
    Matrix<int,4,2> H({ {13, 1}, {12,2}, {3,43}, {-55,67} });
    cout << "Macierz H:\n" << H << endl;

    //konstruktor kopiujący
    Matrix<int,4,2> H1(H);
     cout << "Macierz H1:\n" << H1 << endl;

    //konstruktor konwertujący
    Matrix<double,5,4> H2(H);
    cout << "Macierz H2:\n" << H2 << endl;

    Matrix<string,3,2> S({ {"Ala", "ma"},{"kota","a"},{"kot","ma Ale"} });
    cout << "Macierz S:\n" << S << endl;
    cout << "Ilosc kolumn macierzy S: "<<S.get_nr_columns() << endl;
    cout << "Ilośc wierszy macierz S: "<<S.get_nr_rows() << endl;
    cout << "Wiersz nr 1: " << S[1] << endl;

    //uzupełnianie zerowymi wierszami w konstruktorze
    Matrix<int,5,3> J({  {1,2,3} , {4,5,6}  , {7,8,9}   });
    cout << "Macierz J:\n" <<J << endl;

    //uzupełnianie kolumn i wierszy zerami w konstruktorze
    Matrix<int,6,4> DD({ {}, {1}, {-1, 3}, {2, 7, 5}, {3,4,7,8} });
    cout << "Macierz DD:\n" << DD << endl;

    //dodawanie macierzy różnych typów
    Matrix<double,3> A(get_scalar_matrix<double,3,3>(0.4));
    Matrix<int,3> B = get_id_matrix<int,3,3>();
    cout << "Macierz A:\n" << A << endl;
    cout << "Macierz B:\n" << B << endl;
    auto C = A + B;
    cout << "Suma A + B:\n" << C << endl;

    //macierz ułamków
    Matrix<frac,2,3> E({ {{5,2},{-1,3},{3,2}},{{2,3},{4,-3},{-2,-7}} });
    //konwersja z frac na int
    Matrix <int,2,3> E_int(E);
    Matrix<frac,3,2> F({ {{1,3},{1,4}},{{2,5},{3,4}}, {{5,4},{-5}} });
    //uzupełnienie kolumn zerami
    Matrix<frac,3,4> G(F);

    cout << "Macierz ułamków E:\n" << E << endl;
    cout << "Macierz E_int:\n" << E_int << endl;
    cout << "Macierz ułamków F:\n" << F << endl;
    cout << "Macierz ułamków G:\n" << G << endl;

    //mnożenie macierzy
    cout << "Macierz ExG:\n" << E*G << endl;

    auto HH=get_scalar_matrix<int,4,3>(7);
    cout << "Macierz HH:\n" << HH << endl;

    //mnożenie macierzy przez skalar
    auto HH2 = 2*HH;
    cout << "Macierz 2*HH:\n" << HH2 << endl;

    //mnożymy przez inny typ (konwersja na typ stałej)
    cout << "Macierz 1/2:\n" << frac{1,2}*HH << endl;
    cout << "Macierz 0.5*HH:\n" << (0.5)*HH << endl;
    //zmiana wyrazu
    HH2[0][1] = 5;
    cout << "Macierz 2*HH:\n" << HH2 << endl;

    HH2[1][2] = 7;
    cout << "Macierz 2*HH:\n" << HH2<<endl;

    //zmiana wiersza
    HH2[2] = vector<int>{7,8,9};
    cout << "Macierz 2*HH:\n" << HH2<<endl;

    //dodawanie z konwersją na typ pierwszej macierzy
    Matrix<int, 3,3> C2({ {3,4,1}, {1,2,-5}, {4,-2} });
    Matrix<double,3,3> C1({ {0.1,0.2, 7}, {-0.7,1, -5.5} });
    cout << "Macierz C1:\n" <<C1 << endl;
    cout<<"Macierz C2:\n"<< C2<< endl;
    cout << "Macierz C1+C2:\n" << C1+C2 << endl;

    //dodajemy ułamek do macierzy C1
    auto C3 = frac{1,2} + C2;
    cout << "Macierz 1/2 + C2:\n" << C3 << endl;

    //transpozycja macierzy
    Matrix<int,3,5> JT = J.transpose();
    cout << "Macierz transponowana:\n" <<JT << endl;
    //domyślny operator move
    auto K = move(JT);

    Matrix<int,4,5> L = 4*get_id_matrix<int,3,3>();
    cout << L << endl;
    cout << 1+(4*get_id_matrix<int,3,3>())*K << endl;

    Matrix<int, 3> KW;
    cout << KW;
    //Błędy kompilacji (static_assert)
    //Matrix<0,3,int> X1; //zerowy wymiar
    //Matrix<3,3,bool> X2; //typ Bool
    //Matrix<3,3,string>X3(E); // brak operatora konwersji na typ string
}
