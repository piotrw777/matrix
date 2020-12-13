#ifndef __MATRIX
#define __MATRIX

#include <string>
#include <vector>
#include <algorithm>

#define CCC 0 //komentarze konstruktorów (1=ON, reszta=OFF)
using namespace std;

//Funkcje pomocnicze drukujące wektory
template <typename Typ>
void print(const vector<Typ>& V) {
    for(const auto& i: V) {cout << i << "\t";}
    cout << endl;
}
template <typename Typ>
ostream & operator<<(ostream &out, const vector<Typ>& V) {
    print(V);
    return out;
}

//deklaracja szablonu klas Matrix
template <size_t N, size_t M, typename Typ>
class Matrix;

/*template<size_t N, typename Typ>
class Matrix<N, N, Typ>;
*/

//*****************************************
//szablony funkcji zaprzyjaźnionych
//*****************************************

template <size_t N, size_t M, typename Typ>
auto get_id_matrix();

template <size_t N, size_t M, typename Typ>
auto get_scalar_matrix(Typ t);

template <size_t N, size_t M, typename Typ>
ostream & operator<<(ostream &out, Matrix<N, M, Typ> MM);

//operator dodawania macierzy
template <size_t N1, size_t M1,typename Typ1,typename Typ2>
Matrix<N1,M1,Typ1> operator+(const Matrix<N1, M1, Typ1> &A, const Matrix<N1, M1, Typ2> &B);

//operator mnożenia macierzy
template <size_t N1, size_t M1, size_t N2, size_t M2, typename Typ1,typename Typ2>
Matrix<N1,M2,Typ1> operator*(const Matrix<N1, M1, Typ1> &A, const Matrix<N2, M2, Typ2> &B);

//operator mnożenia macierzy przez stałą t*A
template <size_t N1, size_t M1, typename Typ1,typename Typ2>
Matrix<N1,M1,Typ2> operator*(const Typ2 &t, const Matrix<N1, M1, Typ1> &A);

//operator dodawania stałej do macierzy t+A
template <size_t N1, size_t M1, typename Typ1,typename Typ2>
Matrix<N1,M1,Typ2> operator+(const Typ2 &t, const Matrix<N1, M1, Typ1> &A);

//szablon klas macierzy NxM o wyrazach typu Typ
template <size_t N, size_t M, typename Typ>
class Matrix {

private:
    const static size_t nr_rows = N;
    const static size_t nr_columns = M;
    vector<vector<Typ> > Mat;

public:
    //konstruktor bezparametrowy - tworzy macierz zerową
    Matrix(){
        static_assert(!is_same<Typ, bool>::value, "T cannot be bool type!");
        static_assert(N > 0 && M > 0, "Matrix dimension cannot be zero");
        #if(CCC==1)
        cout << "Konstruktor bezparametrowy\n";
        #endif
        vector<Typ> pom(M, Typ{});
        Mat.assign(N, pom);
    }

    //konstruktor jednoargumentowy
    //użycie: Matrix<n,m,float> my_matrix({ {wiersz1}, {wiersz2},...  })
    Matrix(const vector<vector<Typ> > &vec) {
        static_assert(!is_same<Typ, bool>::value, "T cannot be bool type!");
        static_assert(N > 0 && M > 0, "Matrix dimensions cannot be equal to zero");

        #if(CCC==1)
        cout << "Konstruktor z vec\n";
        #endif

        size_t n = vec.size();
        vector<Typ> zero_vec(M, Typ{});

        for(size_t k = 0; k < min(N,n); k++) {
            if(vec[k].size() > M) exit(3);
            Mat.push_back(vec[k]);
            Mat.back().insert((Mat.back()).end(), M - vec[k].size(), Typ{});
        }
        //uzupełniamy wektorami zerowymi
        for(size_t k = 0; k < N - min(N,n); k++)
            Mat.push_back(zero_vec);
    }

    //konstruktor kopiujący
    template<size_t N1, size_t M1, typename Typ1>
    Matrix(const Matrix<N1, M1,Typ1>& MM) {
        static_assert(N > 0 && M > 0, "Matrix dimension cannot be zero");
        static_assert(N1<=N && M1<=M , "INEQUALITIES");
        static_assert(is_convertible<Typ1, Typ>::value, "No conversion operator in copy constructor!");

        #if(CCC==1)
        cout << "Konstruktor kopiujący\n";
        #endif

        vector<Typ> zero_vec(M, Typ{});

        //kopiujemy wyrazy macierzy M (z konwersją na Typ1 -> Typ)
        for(const auto &v : MM.Mat) {
            Mat.push_back(vector<Typ>(v.begin(), v.end()));
        }
        //uzupełniamy kolumny zerami
        for(auto &v : Mat) {
            v.insert(v.end(), M - M1, Typ{});
        }
        //uzupełniamy wiersze zerami
        Mat.insert(Mat.end(), N - N1, zero_vec);
    }

    size_t get_nr_rows() {return N;}
    size_t get_nr_columns() {return M;}

    void print() {
        for_each(Mat.begin(), Mat.end(), [](const vector<Typ> &v){cout << v;});
    }
    void present_type() {
        cout << "Macierz o " << N << " wierszach i " << M << " kolumnach" << endl;
    }
    auto & operator[](int k)  {
        return Mat[k];
    }
    auto & operator[](int k) const {
        return Mat[k];
    }
    Matrix<M, N, Typ>  transpose() {
        Matrix<M, N, Typ> A;

        for(size_t i = 0; i < M; i++) {
            for(size_t j = 0; j < N; j++ ) {
                A[i][j] = Mat[j][i];
            }
        }
        return A;
    }
    //deklaracje przyjaźni
    friend auto get_id_matrix<N, M, Typ>();
    friend auto get_scalar_matrix<N, M, Typ>(Typ t);
    friend ostream & operator<< <> (ostream &out, Matrix<N, M, Typ> MM);

    template <size_t N1, size_t M1, typename Typ1,typename Typ2>
    friend Matrix<N1,M1,Typ1> operator+(const Matrix<N1, M1, Typ1> &A, const Matrix<N1, M1, Typ2> &B);

    template <size_t N1, size_t M1, size_t N2, size_t M2, typename Typ1,typename Typ2>
    friend Matrix<N1,M2,Typ1> operator*(const Matrix<N1, M1, Typ1> &A, const Matrix<N2, M2, Typ2> &B);

    template <size_t N1, size_t M1, typename Typ1,typename Typ2>
    friend Matrix<N1,M1,Typ2> operator*(const Typ2 &t, const Matrix<N1, M1, Typ1> &A);

    template <size_t N1, size_t M1, typename Typ1,typename Typ2>
    friend Matrix<N1,M1,Typ2> operator+(const Typ2 &t, const Matrix<N1, M1, Typ1> &A);

    template <size_t N3, size_t M3, typename Typ3>
    friend class Matrix;
}; //koniec definicji klasy

//dodawanie macierzy
template <size_t N1, size_t M1, typename Typ1,typename Typ2>
Matrix<N1,M1,Typ1> operator+(const Matrix<N1, M1, Typ1> &A, const Matrix<N1, M1, Typ2> &B) {
    static_assert(is_convertible<Typ2, Typ1>::value, "No conversion operator in addition operator!");
    Matrix<N1, M1, Typ1> Pom;
    for(size_t i = 0; i < N1; i++) {
        for(size_t j = 0; j < M1; j++ ) {
            Pom[i][j] = A[i][j] + static_cast<Typ1>(B[i][j]);
        }
    }
    return Pom;
}
//mnożenie macierzy
template <size_t N1, size_t M1, size_t N2, size_t M2, typename Typ1,typename Typ2>
Matrix<N1,M2,Typ1> operator*(const Matrix<N1, M1, Typ1> &A, const Matrix<N2, M2, Typ2> &B) {
    static_assert(M1==N2 , "Wrong dimensions in matrix multiplication");
    static_assert(is_convertible<Typ2, Typ1>::value, "No conversion operator in multiplication operator!");

    Matrix<N1, M2, Typ1> C;
    for(size_t w = 0; w < N1; w++) {
        for(size_t k = 0; k < M2; k++){
            Typ1 t{};
            for(size_t i = 0; i < M1; i++) {
                t += A[w][i] * static_cast<Typ1>(B[i][k]);
            }
            C[w][k] = t;
        }
    }
    return C;
}
//mnożenie przez stałą
template <size_t N1, size_t M1, typename Typ1,typename Typ2>
Matrix<N1,M1,Typ2> operator*(const Typ2 &t, const Matrix<N1, M1, Typ1> &A) {
static_assert(is_convertible<Typ1, Typ2>::value, "No conversion operator in multiplication operator!");

    Matrix<N1, M1, Typ2> B;
    for(size_t i = 0; i < N1; i++) {
       for(size_t j = 0; j < M1; j++) {
            B[i][j] = t*static_cast<Typ2>(A[i][j]);
       }
    }
    return B;
}

//dodawanie stałej
template <size_t N1, size_t M1, typename Typ1,typename Typ2>
Matrix<N1,M1,Typ2> operator+(const Typ2 &t, const Matrix<N1, M1, Typ1> &A) {
    static_assert(is_convertible<Typ1, Typ2>::value, "No conversion operator in multiplication operator!");

    Matrix<N1, M1, Typ2> B;
    for(size_t i = 0; i < N1; i++) {
       for(size_t j = 0; j < M1; j++) {
            B[i][j] = t+static_cast<Typ2>(A[i][j]);
       }
    }
    return B;
}

//tworzenie macierzy jednostkowej
template <size_t N, size_t M, typename Typ>
auto get_id_matrix() {
    Matrix<N, M, Typ> M1;

    for(size_t i = 0; i < min(N, M); i++) {
        M1[i][i] = static_cast<Typ>(1);
    }
    return M1;
}
//tworzenie macierzy o tych samych wyrazach
template <size_t N, size_t M, typename Typ>
auto get_scalar_matrix(Typ t) {
    Matrix<N, M, Typ> M1;
    vector<Typ> pom(M, t);

    for_each(M1.Mat.begin(), M1.Mat.end(), [pom](vector<Typ> &v){v = pom;});
    return M1;
}

template <size_t N, size_t M, typename Typ>
ostream & operator<<(ostream &out, Matrix<N, M, Typ> MM) {
    MM.print();
    return out;
}

/*template<size_t N, typename Typ>
class Matrix<N, N, Typ> {
      Matrix(){cout << "Jestem macierza kwadratowa";}
    
};
*/
#endif// __MATRIX

