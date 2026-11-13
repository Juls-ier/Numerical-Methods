#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cstdlib> // rand, srand
#include <ctime>   // time



struct Point {

    double x;
    double y;

    Point(int x, int y) : x(x), y(y) {};

};

struct EQ {

    int x, y, z, r;

    EQ(int x, int y, int z, int r) : x(x), y(y), z(z), r(r) {};

};





struct Mesh {

    std::vector<Point*> baza;
    int liczba_pkt = 0;

    void wczytaj_punkty(std::string plik) {


        std::ifstream wczyt;
        wczyt.open(plik);

        if (!wczyt.is_open()) {
            std::cout << "nie otwiera siee";

        }

        int count;
        int x = 0;
        int y = 0;


        wczyt >> count;
        for (int i = 0; i < count; i++) {

            wczyt >> x;
            wczyt >> y;
            Point* nowy = new Point(x, y);
            baza.push_back(nowy);
            liczba_pkt++;

        }


        wczyt.close();
        return;
    }

    void wypisz() {
        std::cout << "x  y" << std::endl;

        for (int i = 0; i < liczba_pkt; i++) {

            std::cout << baza[i]->x << " " << baza[i]->y << std::endl;
        }


    }


    std::vector<EQ*> baza_eq;
    int liczba_eq = 0;


    void wczytaj_eq(std::string plik) {


        std::ifstream wczyt;
        wczyt.open(plik);

        if (!wczyt.is_open()) {
            std::cout << "nie otwiera siee";

        }

        int count;
        int x = 0;
        int y = 0;
        int z = 0;
        int r = 0;


        wczyt >> count;
        for (int i = 0; i < count; i++) {

            wczyt >> x;
            wczyt >> y;
            wczyt >> z;
            wczyt >> r;
            EQ* nowy = new EQ(x, y, z, r);
            baza_eq.push_back(nowy);
            liczba_eq++;

        }


        wczyt.close();
        return;

    }

    void wypisz_eq() {
        std::cout << "a b c d" << std::endl;

        for (int i = 0; i < liczba_eq; i++) {

            std::cout << baza_eq[i]->x << " " << baza_eq[i]->y << " " << baza_eq[i]->z << " " << baza_eq[i]->r << std::endl;
        }


    }

    std::vector<std::vector<double>> uklad;
    int count;

    void wczytaj_uklad(std::string plik) {


        std::ifstream wczyt;
        wczyt.open(plik);

        if (!wczyt.is_open()) {
            std::cout << "nie otwiera siee";

        }
     

        wczyt >> count;
        uklad.resize(count, std::vector<double>(count + 1));
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count + 1; j++) {


                wczyt >> uklad[i][j];

            }

        }

    }

        void wypisz_uklad() {


            for (int i = 0; i < count; i++) {
                for (int j = 0; j < count + 1; j++) {


                    std::cout<< uklad[i][j] << " ";

                }
                std::cout << std::endl;

            }


        }




};


double interpol_lagrange(std::vector<Point*> baza,  int size) {


    std::cout << " liczba wezlow: " << size << std::endl;

    std::cout << "w jakim punkcie znalezc wartosc?";
    double s;

    std::cin >> s;
    double sum_l = 0;
    double licz_l;

    for (int i = 0; i < size; i++) {

        licz_l = 1;
        for (int j = 0; j < size; j++) {
        
            if (i != j) {

                licz_l *= (s - baza[j]->x) / (baza[i]->x - baza[j]->x);

            }

        }

        licz_l *= baza[i]->y;
        sum_l += licz_l;

    }




    return sum_l;
}

double interpol_newton(std::vector<Point*> baza, int size) {

    std::cout << " liczba wezlow: " << size << std::endl;

    double s;

    std::cout << "w jakim punkcie znalezc wartosc?\n";
    std::cin >> s;

    
    double b[100];

    for (int i = 0; i < size; i++) {

        b[i] = baza[i]->y;

    }

    std::cout << std::endl;

    for (int j = 1; j < size/2; j++) {

        for (int i = size/2 - 1; i >= j; i--) {

            b[i] = (b[i] - b[i - 1]) / (baza[i]->x - baza[i - j]->x);

        }

    }
    
    for (int i = 0; i < size/2; i++) {
        
        std::cout << b[i]<< std::endl;

    }



    double wynik = b[0];

    double ilocz = 1;




    for (int i = 1; i < size; i++) {
        
        ilocz *= (s - baza[i - 1]->x);
        wynik += b[i] *ilocz;

    }

    return wynik;

}





double interpol_newton(std::vector<Point*> baza, int size, double s) { // przeciazenie dla pkt z input

    std::cout << " liczba wezlow: " << size << std::endl;



    double b[100];

    for (int i = 0; i < size; i++) {

        b[i] = baza[i]->y;

    }

    std::cout << std::endl;

    for (int j = size/2; j < size; j++) {

        for (int i = size - 1; i >= j; i--) {

            if (baza[i]->x - baza[i - j]->x <= 0) {

               b[i] = 0;
                
           }
           else {
                b[i] = (b[i] - b[i - 1]) / (baza[i]->x - baza[i - j]->x);
            }
        }

    }

    for (int i = 0; i < size; i++) {

        std::cout << b[i] << std::endl;

    }



    double wynik = b[0];

    double ilocz = 1;




    for (int i = 1; i < size; i++) {

        ilocz *= (s - baza[i - 1]->x);
        wynik += b[i] * ilocz;

    }

    return wynik;

}





double val_fun(double x) {

    return 1.0 + (1.0 / (25.0 * x * x));

}

void Roundy() {

    std::vector<Point*> pkt;


    for (int i = 0; i <= 10; i++) {
        double x = -1.0 + 2.0 * i /10;
        Point* point = new Point(x, 1 + (1 / (25 * x * x)));
        pkt.push_back(point);

    }



    for (double x = -1.0; x <= 1.0; x += 0.01) {
        std::cout << "Interpolacja: " << interpol_newton(pkt, pkt.size(), x);
        std::cout << "  Funkcja: " << val_fun(x) << std::endl;
    }
}

double * gauss(std::vector<std::vector<double>> uklad, int count) {



    for (int i = 0; i < count; i++) {

        if (uklad[i][i] == 0) {
            std::cout << "zero na przekatnej";
            return nullptr;
        }

    }



    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            double by = uklad[j][i] / uklad[i][i];

            for (int k = i; k <= count; k++)
            {
                uklad[j][k] -= by * uklad[i][k];
            }
        }


        for (int i = 0; i < count; i++) {

            if (uklad[i][i] == 0) {
                std::cout << "zero na przekatnej";
                return nullptr;
            }

        }


    }


    //wypisanie
    std::cout << std::endl;


    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count + 1; j++) {


            std::cout << uklad[i][j];

        }
        std::cout << std::endl;

    }
    std::cout << std::endl;

    /////



    double * x = new double[20];

    for (int i = count - 1; i >= 0; i--)
    {
        x[i] = uklad[i][count];

        for (int j = i + 1; j < count; j++)
        {
            x[i] -= uklad[i][j] * x[j];
        }

        x[i] /= uklad[i][i];
    }

    for (int i = 0; i < count; i++) {
        std::cout << x[i] << " ";
    }

    return x;
 
}





double * gauss_pivot(std::vector<std::vector<double>> uklad, int count) {

    for (int i = 0; i < count; i++) {

        int max_id = i;     
        double max_val = fabs(uklad[i][i]);


        for (int j = 1 + i; j < count; j++) {   //pivot

            if(fabs(uklad[j][i])>max_val){
            
                max_val = fabs(uklad[j][i]);
                max_id = j;   

            }

        }



        std::swap(uklad[i],uklad[max_id]);  //zmiana

        if (uklad[i][i] == 0) {
            std::cout << "zero na przekatnej po swap" << std::endl;
            return nullptr;
        }

        for (int j = i + 1; j < count; j++) {


            double by = uklad[j][i] / uklad[i][i];

            for (int k = i; k <= count; k++)
            {
                uklad[j][k] -= by * uklad[i][k];
            }

        }

    }

    std::cout << std::endl;

    //wypis

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count + 1; j++) {
            std::cout << uklad[i][j] << " ";
        }
        std::cout << std::endl;
    }


    ////


    double* x = new double[20];
    


    for (int i = count - 1; i >= 0; i--)
    {
        x[i] = uklad[i][count];

        for (int j = i + 1; j < count; j++)
        {
            x[i] -= uklad[i][j] * x[j];
        }

        x[i] /= uklad[i][i];
    }

    std::cout << std::endl;

    for (int i = 0; i < count; i++) {
        std::cout << x[i] << " ";
    }

    return x;

}

void gauss_crout(std::vector<std::vector<double>> uklad, int count) {

    std::vector<int> w(count);

    for (int i = 0; i < count; i++) {
        w[i] = i;
    }


    for (int i = 0; i < count; i++) {

        int max_id = i;
        double max_val = fabs(uklad[i][w[i]]);


        for (int j = i + 1; j < count; j++) {


            if (fabs(uklad[i][w[j]]) > max_val) {

                max_id = j;
                max_val = fabs(uklad[i][w[j]]);

            }


        }

        

        std::swap(w[i], w[max_id]);



        if (uklad[i][w[i]] == 0) {
            std::cout << "zero na przekatnej\n";
            return;
        }


        for (int j = i + 1; j < count; j++)
        {
            double by = uklad[j][w[i]] / uklad[i][w[i]];

            for (int k = i; k < count; k++)
            {
                uklad[j][w[k]] -= by * uklad[i][w[k]];
            }

            uklad[j][count] -= by * uklad[i][count];
        }

    }

        //////
        std::cout << std::endl;

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                std::cout << uklad[i][w[j]] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;

        for (int i = 0; i < count; i++) {
            std::cout << w[i] << " ";
        }

        std::cout << std::endl;

        //

        double xt[20];

        for (int i = count - 1; i >= 0; i--)
        {
            xt[i] = uklad[i][count];

            for (int j = i + 1; j < count; j++)
            {
                xt[i] -= uklad[i][w[j]] * xt[j];
            }

            xt[i] /= uklad[i][w[i]];
        }

        // powrot do kolejnosci

        double x[20];

        for (int i = 0; i < count; i++) {
            x[w[i]] = xt[i];
        }

        std::cout << "\n\n";
        for (int i = 0; i < count; i++) {
            std::cout << x[i] << " ";
        }



}




void LU(std::vector<std::vector<double>> uklad, int count) {

    std::vector<std::vector<double>> l(count, std::vector<double>(count, 0.0));
  
   


    for (int i = 0; i < count; i++) {

        if (uklad[i][i] == 0) {
            std::cout << "zero na przekatnej";
            return;
        }

    }



    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            double by = uklad[j][i] / uklad[i][i];
            l[j][i] = by;
           

            for (int k = i; k <= count; k++)
            {
                uklad[j][k] -= by * uklad[i][k];
            }
        }


        for (int i = 0; i < count; i++) {

            if (uklad[i][i] == 0) {
                std::cout << "zero na przekatnej";
                return;
            }

        }


    }

    for (int i = 0; i < count; i++) {

        l[i][i] = 1;

    }


    //wypisanie
    std::cout << std::endl;


    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {


            std::cout << uklad[i][j]<< " ";

        }
        std::cout << std::endl;

    }
    std::cout << std::endl;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count ; j++) {


            std::cout << l[i][j]<<" ";

        }
        std::cout << std::endl;

    }
    std::cout << std::endl;

    /////
    for (int i = 0; i < count; i++) {
        std::cout << uklad[i][count]<<std::endl;
    }

    /////

    double x[20] = { 1,1,1,1,1,1,1,1,1,1,1 };
    
    for (int i = count-1; i >= 0; i--) {
        double sum = 0;

        x[i] = 1 / uklad[i][i];
        for (int j = i + 1; j < count; j++) {

            sum += uklad[i][j] * x[j];
   
        }

        x[i] *= (uklad[i][count] - sum);

    }
    
    std::cout << std::endl;
   
    for (int i = 0; i < count; i++) {
        std::cout << x[i] << std::endl;
    }



}


double eps = 0.001;

void jacob(std::vector<std::vector<double>> uklad, int count) {

    //// czy dominujaca
    bool dom = true;
    bool sharp = false;

    for (int i = 0; i < count; i++) {

        double s = 0;

        for (int j = 0; j < count ; j++) {
            if (i != j) {
                s += abs(uklad[i][j]);
            }
        }

        if (abs(uklad[i][i]) < s) {
            dom = false;

        } else if (abs(uklad[i][i]) > s) {
            sharp = true;
        }
        
    }
    if (dom==false) {
        std::cout << "macierz nie jest diagonalnie dominujaca" << std::endl;

    }
    else if (sharp == true) {
        std::cout << "macierz jest diagonalnie dominujaca (ostra)" << std::endl;
    }
    else {
        std::cout << "macierz jest diagonalnie dominujaca (slabo)" << std::endl;
    }






    ////


    int max_iter;
    int iter = 0;
    std::cout << "podaj liczbe iteracji " << std::endl;
    std::cin >> max_iter;
    bool check= false;
    std::vector<double> x(count, 0.0);
    std::vector<double> x_new(count, 0.0);

    while (iter < max_iter && !check) {

        check = true;
        for (int i = 0; i < count; i++) {
           

            double sum = uklad[i][count];  // b

            for (int j = 0; j < count; j++) {

                if (j != i) {
                    sum -= uklad[i][j]*x[j];    // - SUMA
                }


            }

            x_new[i] = sum / uklad[i][i];

            

            if (abs(x_new[i] - x[i]) > eps) {
                
                check = false;
            }

           
        }
        std::cout << "blad po iteracji " << iter+1 << std::endl;
        for (int i = 0; i < count; i++) {
            std::cout << abs(x_new[i] - x[i])<< std::endl;
        }
        x = x_new;
        iter++;


    }


    std::cout << std::endl;
    std::cout << "rozwiazanie po " << iter << " iteracji dla epsilon = " << eps<<  std::endl;

    for (int i = 0; i < count; i++) {
        std::cout << "x[" << i << "] = " << x[i] << std::endl;
    }


}

std::vector<std::vector<double>> uklad(int count) {

    std::vector<std::vector<double>> u(count, std::vector<double>(count + 1, 0.0));

    double density = 0.05; 

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {

            double p = (double)rand() / RAND_MAX;

            if (p < density) {
                u[i][j] = rand() % 100 + 1; 
            }
        }

       
        u[i][count] = rand() % 100 + 1;
    }

   
    for (int i = 0; i < count; i++) {
        double sum = 0.0;

        for (int j = 0; j < count; j++) {
            if (i != j) {
                sum += std::abs(u[i][j]);
            }
        }

        u[i][i] = sum + 1.0; 
    }

    return u;
}



double f1(double x) {

    return sin(x);

}

double f2(double x) {

    return x * x + (2 * x) + 5;
}

double f3(double x) {

    return exp(x);

}

double f4(double x) {   //  3
    return x * x * x - 2 * x * x + x - 1;
}

double f5(double x) {   //  5
    return x * x * x * x * x + 3 * x * x * x - x + 2;
}

double f6(double x) {   // 7
    return x * x * x * x * x * x * x - x * x * x * x + 2 * x * x - 5;
}


double prostokat( double(*f)(double), double a, double b, int n ) {

    double s = (b - a) / n;
    double sum=0;
    for (int i = 0; i < n; i++) {

        sum += f(a + s * i + s / 2);

    }

    return s * sum;

}

double trapez(double(*f)(double), double a, double b, int n) {

    double s = (b - a) / n;
    double sum = 0;

    for (int i = 0; i < n; i++) {

        sum += f(a + s * i);
        sum += f(a + s * (i+1));

    }

    return sum * s/2;

}

double parabola(double(*f)(double), double a, double b, int n) {
    if ( (n % 2) != 0){
        double s = (b - a) / n;
        double sum = 0;
        double c, d;

        for (int i = 0; i < n; i++) {

            c = a + s * i;
            d = a + s * (i + 1);

            sum += ((d - c) / 6) * (f(c) + 4 * f((c + d) / 2) + f(d));


        }

        return sum;
    }
    else {
        double s = (b - a) / (n / 2);
        double sum = 0;
        double c, d;

        for (int i = 0; i < n/2; i++) {


          
            c = a + s * i;
            d = a + s * (i + 1);

            sum += ((d - c) / 6) * (f(c) + 4 * f((c + d) / 2) + f(d));


        }

        return sum;

    }

}


double Kwadratury(double(*f)(double), double a, double b, int n) {

    std::vector<double> x(n);
    std::vector<double> A(n);

    if (n == 2) {
        x[0] = -sqrt(3.0) / 3.0;
        x[1] = sqrt(3.0) / 3.0;
        A[0] = 1.0;
        A[1] = 1.0;
    }
    else if (n == 3) {
        x[0] = -sqrt(3.0 / 5.0);
        x[1] = 0.0;
        x[2] = sqrt(3.0 / 5.0);
        A[0] = 5.0 / 9.0;
        A[1] = 8.0 / 9.0;
        A[2] = 5.0 / 9.0;
    }
    else if (n == 4) {
        x[0] = -sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));
        x[1] = -sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
        x[2] = sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0));
        x[3] = sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0));

        A[0] = (18.0 - sqrt(30.0)) / 36.0;
        A[1] = (18.0 + sqrt(30.0)) / 36.0;
        A[2] = (18.0 + sqrt(30.0)) / 36.0;
        A[3] = (18.0 - sqrt(30.0)) / 36.0;
    }
    else { return -1;}


    double sum = 0;

    for (int i = 0; i < n; i++) {

        double t = x[i] * ((b - a) / 2) + (a + b) / 2;
        sum += A[i] * f(t);

    }

    sum *= ((b - a) / 2);

    return sum;

}


double r1(double x, double y) {
    return x*x + y ;
}

double r2(double x, double y) {
    return x + y;
}


double euler(double(*f)(double, double), double x0, double y0, double xs, int n) {

    double h = (xs - x0) / n;

    double ys = y0;

    for (int i = 0; i < n; i++) {

        ys = ys + h * (f(x0 + i * h, ys));

    }

    return ys;

}

double RK2(double(*f)(double, double), double x0, double y0, double xs, int n) {
    double h = (xs - x0) / n;

    double ys = y0;
    double k1, k2;


    for (int i = 0; i < n; i++) {

        k1 = f(x0 + i * h, ys);
        k2 = f(x0 + i * h + h, ys + h * k1);
        ys = ys + h * (k1 + k2) / 2;


    }

    return ys;


}


double RK4(double(*f)(double, double), double x0, double y0, double xs, int n) {
    double h = (xs - x0) / n;

    double ys = y0;
    double k1, k2, k3, k4;


    for (int i = 0; i < n; i++) {

        k1 = f(x0 + i * h, ys);
        k2 = f(x0 + i * h + h / 2, ys + h * k1 / 2);
        k3 = f(x0 + i * h + h / 2, ys + h * k2 / 2);
        k4 = f(x0 + i * h + h, ys + h * k3);


        ys = ys + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;


    }

    return ys;


}

double b(double x, double pow) {

    return std::pow(x, pow);
}

double fa(double x) {

    return 1;

}




double* aproks(std::vector<Point> nodes, int count, int n, double(*w)(double)) {

    std::cout << "liczba wezlow : " << count << std::endl;

    int size = n + 1; /// liczba wspolczynnikow, rozmiar macierzy

    std::vector<std::vector<double>> G(size, std::vector<double>(size +1, 0.0));


    /////////           macierz G konstrukcja

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {


            for (int k = 0; k < count; k++) { // suma po punktach

                G[i][j] += b(nodes[k].x, i) * b(nodes[k].x, j) * w(nodes[k].x);

            }
        }

        /// F

        for (int k = 0; k < count; k++) {

            G[i][size] += b(nodes[k].x, i) * nodes[k].y * w(nodes[k].x);
        }
    }

    double * x  = gauss_pivot(G, size);
    if (x == nullptr) {
        std::cout << "blad z gaussem";
        return nullptr;
    }
    
    std::cout<<std::endl;



    double E=0.0;

    for (int k = 0; k < count; k++) {

        std::cout << "wezel: ( " << nodes[k].x << " , " << nodes[k].y << " ) ";

        double y = 0;
        

        for (int i = 0; i < size; i++) {

            y += x[i] * pow(nodes[k].x, i);
           

        }
        
        E += w(k) * pow(nodes[k].y - y, 2);

        std::cout << "aproksymacja : " << y << std::endl;

       


    }
    std::cout << "Wartosc funkcjonalu bledu E: " << E << std::endl;

    return x;

}


double w(double x)
{
    return 1.0;
}



///  wielomian ortagonalny
double phi_x(double x,int j,std::vector<double>& alpha,std::vector<double>& beta)
{
    if (j == 0)
        return 1.0;

    double phi_prev = 0.0; 
    double phi_curr = 1.0; 


    ///kazdy nastepny z dwoch poprzednich, (24) 

    for (int k = 0; k < j; k++)
    {
        double phi_next =(x - alpha[k]) * phi_curr  - beta[k] * phi_prev;

        phi_prev = phi_curr;
        phi_curr = phi_next;
    }

    return phi_curr;
}

/// aproksymacja trojczlownowa


double* aproks_trojczlonowa(std::vector<Point> nodes, int count,int n,double(*w)(double)){


    std::cout << " liczba wezow: " << count << " stopien wielomianu :" << n << std:: endl;

    int size = n + 1;


    
    // tablice wspolczynnikow (25, 26) 
    

    std::vector<double> alpha(size, 0.0);
    std::vector<double> beta(size, 0.0);

    std::vector<double> d(size, 0.0);

    double* a = new double[size];

    

    /// Zainicjalizować 𝜑−1(𝑥𝑖) = 0, 𝜑0(𝑥𝑖) = 1 dla wszystkich i
  
    std::vector<std::vector<double>> phi(size,std::vector<double>(count, 0.0));

    for (int i = 0; i < count; i++)
    {
        phi[0][i] = 1.0;
    }

    
    // d0 = w(xi) 

    for (int i = 0; i < count; i++)
    {
        d[0] += w(nodes[i].x);
    }

    




    // generowanie wielomianow ortogonalnych
   
    for (int j = 0; j < n; j++)
    {
        
        // alpha_j
        
        double licznik_alpha = 0.0;

        for (int i = 0; i < count; i++)
        {
            licznik_alpha += w(nodes[i].x)* nodes[i].x * phi[j][i]* phi[j][i];
        }

        alpha[j] = licznik_alpha / d[j];

        
        // beta_j
        

        if (j == 0) {
            beta[j] = 0.0;
        }
        else {
            beta[j] = d[j] / d[j - 1];
        }
       
        // phi_(j+1)
       

        for (int i = 0; i < count; i++)
        {
            double phi_prev;

            if (j == 0)
                phi_prev = 0.0;
            else
                phi_prev = phi[j - 1][i];

            phi[j+1][i] = (nodes[i].x - alpha[j])* phi[j][i] - beta[j] * phi_prev;
        }

      
        // d_(j+1)
   
        for (int i = 0; i < count; i++)
        {
            d[j +1] +=  w(nodes[i].x) * phi[j + 1][i] * phi[j + 1][i];
        }
    }

    // wspolczynniki aproksymacji
    
    for (int j = 0; j < size; j++)
    {
        double licznik = 0.0;

        for (int i = 0; i < count; i++)
        {
            licznik += w(nodes[i].x)* nodes[i].y * phi[j][i];
        }

        a[j] = licznik / d[j];
    }

    // wypisywanie wspolczynnikow -----------------------------------------
    

    std::cout << "alpha_j :" << std::endl;

    for (int j = 0; j < n; j++)
    {
        std::cout << "alpha[" << j << "] = "<< alpha[j] << std::endl;
    }

    std::cout << std::endl;

    std::cout << "beta_j :" << std::endl;

    for (int j = 0; j < n; j++)
    {
        std::cout << "beta[" << j << "] = " << beta[j] << std::endl;
    }

    std::cout << std::endl;

    std::cout << "d_j :" << std::endl;

    for (int j = 0; j < size; j++)
    {
        std::cout  << "d[" << j << "] = " << d[j]  << std::endl;
    }

    std::cout << std::endl;

    std::cout << "wspolczynniki aproksymacji :" << std::endl;

    for (int j = 0; j < size; j++)
    {
        std::cout << "a[" << j << "] = " << a[j]   << std::endl;
    }

    /// -----------------------------------------------------------------


    // obliczanie bledu  E   (2) 
   
    double E = 0.0;

    std::cout << std::endl;

    for (int i = 0; i < count; i++)
    {
        double y = 0.0;

        for (int j = 0; j < size; j++)
        {
            y += a[j] * phi[j][i];
        }

        E +=w(nodes[i].x)* pow(nodes[i].y - y, 2);

        std::cout<< "wezel: ( " << nodes[i].x << " , "  << nodes[i].y  << " ) ";

        std::cout << "aproksymacja: " << y << std::endl;
    }

    std::cout << std::endl;

    std::cout
        << "funkcjonal bledu E = " << E  << std::endl;


    // wartosci poza wezłami
 

    std::cout << std::endl;
    std::cout << "punkty poza wezlami :" << std::endl;

    std::vector<double> test_x =
    {
        0.0,
        1.5,
        2.5,
        4.5,
        6.5,
        9.0
    };

    for (double x = 0 ; x< test_x.size(); x++)
    {
        double y = 0.0;

        for (int j = 0; j < size; j++)
        {
            y += a[j]* phi_x(x, j, alpha, beta);
        }

        std::cout
            << "x = "
            << x
            << "  F(x) = "
            << y
            << std::endl;
    }

    return a;
}

double f(double x) {

    return -pow(x, 3) + 10 * x + 5 ;
}

double fp(double x) {

    return -2* pow(x,2) + 10 ;
}


double q(double x) {   // x0 =  2

    return pow(x, 2) - 4;
}

double qp(double x) {

    return 2 * x;
}


double q1(double x) {  // x0 = 2.0945514815

    return pow(x, 3) - 2 * x - 5;
}

double qp1(double x) {

    return 3 * pow(x, 2) - 2;
}



double bisekcja(double(*f)(double), double(*fp)(double), double a, double b, double eps, int max_iter) {

    if (f(a) * f(b) > 0) {

        std::cout << "brak miejsca zerowego w przedziale";
        return -10000;
    }

    double x0;

    for (int i = 0; i < max_iter; i++) {
        x0 = (a + b) / 2.0;

        std::cout << "iteracja: " << i << " rozwiazanie " << x0 << " f(x) = "<< f(x0)<<std::endl;

        if (std::abs(f(x0)) < eps) {

            std::cout << "znaleziono rozwiazanie: " << x0<< std::endl;
            return x0;
        }


        if (f(a) * f(x0) < 0) {

            b = x0;
        }
        else {

            a = x0;
        }


    }

    return x0;

}


double falsi(double a, double b, double eps, int max_iter) {

    if (f(a) * f(b) > 0) {

        std::cout << "brak miejsca zerowego";
        return -10000;
    }

    double x1;

    for (int i = 0; i < max_iter; i++) {

        x1 = a - (f(a) * (b - a)) / (f(b) - f(a));



        if (std::abs(f(x1)) < eps) {

            std::cout << "znaleziono rozwiazanie" << x1 << std::endl;
            return x1;
        }

        if (f(a) * f(x1) < 0) {

            b = x1;
        }
        else {

            a = x1;
        }


    }

return x1;

}

double sieczne(double(*f)(double), double(*fp)(double),double x0, double x1, double eps, int max_iter) {

    double x2;

    for (int i = 0; i < max_iter; i++) {

        x2 = x1 - (f(x1) * (x1 - x0))  / (f(x1) - f(x0));


        double e = std::abs(f(x2));

        std::cout << " iteracja : " << i << " rozwiazanie " << x2 << std::endl<< " blad : (3) "<< e<< " (2) " << abs(x2 - x1) <<   std::endl;

        bool r1 = e < eps;
        bool r2 = abs(x2 - x1) < eps;
        
        if ( r1 || r2) {

            std::cout << "znaleziono rozwiazanie : " << x2 <<std::endl<<" f(x) = "<< f(x2) <<  std::endl;
            if (r1) {
                std::cout << " abs(f(x2)) < eps "<<std::endl;
            }
            if (r2) {
                std::cout << "abs(x2 - x1) < eps "<<std::endl;
            }

            return x2;
        }

       

        x0 = x1;
        x1 = x2;
    }

    std::cout << "koniec iteracji " << std::endl;
    return x2;
}


double styczne(double(*f)(double), double(*fp)(double), double x0, double eps, int max_iter) {

    double x1;

    for (int i = 0; i < max_iter; i++) {


        if (fp(x0) == 0) {

            std::cout << "pochodna = 0";
            return -1000;
        }

        x1 = x0 - f(x0) / fp(x0);
        double e = std::abs(f(x1));

        std::cout << " iteracja : " << i << " rozwiazanie " << x1 << std::endl<< " blad : (3) " << e << " (2) " << abs(x1 - x0) << std::endl;
      
      
        bool r1 = e < eps;
        bool r2 = abs(x1 - x0) < eps;
        if (r1 || r2) {

            std::cout << "znaleziono rozwiazanie : " << x1 << std::endl<< "f(x) = " << f(x1) << std::endl;
           
            if (r1) {
                std::cout << " abs(f(x2)) < eps "<<std::endl;
            }
            if (r2) {
                std::cout << "abs(x2 - x1) < eps "<<std::endl;
            }


            return x1;
        }

       

        x0 = x1;
    }

    return x1;
}



int main(){


 //   double a = 0;
 //   double b = 4;

//    double eps = 1e-5;

 //   int max_iter = 100;



  //  double x0;
   // std::cout << " podaj pkt x0 : ";
  //  std::cin >> x0;


 //   sieczne(f,fp,x0, x0-0.1, eps, max_iter);

 //   std::cout<<std::endl;

  //  styczne(f, fp,  x0, eps, max_iter);

  //  bisekcja(f,fp,  a, b, eps, max_iter);




    // a = 1;
    // b = 3;



    //sieczne(q, qp, x0, x0 - 0.1, eps, max_iter);

    //std::cout << std::endl;

    //styczne(q, qp, x0, eps, max_iter);

    //bisekcja(q, qp, a, b, eps, max_iter);






    //sieczne(q1, qp1, x0, x0 - 0.1, eps, max_iter);

    //std::cout << std::endl;

    //styczne(q1, qp1, x0, eps, max_iter);

    //bisekcja(q1, qp1, a, b, eps, max_iter);



/*
    std::vector<Point> nodes =
    {
        {1, 2},
        {2, 4},
        {3, 3},
        {4, 5},
        {5, 6},
        {6, 9},
        {7, 11},
        {8, 11}
    };

    int count = nodes.size();

    int n = 2;

    double* a =aproks_trojczlonowa( nodes,count,n, w);

    delete[] a;


    std::cout <<" \n \n \n";


    double* b= aproks(nodes, 8, 1, f*);

























    //double x0 = 0.0;
    //double xs = 1.0;

    //int n = 10;
    //int n_values[] = { 2, 4, 8, 16, 32, 64, 128, 256 };

    ////for (int i = 0; i < 8; i++) {

    ////    n = n_values[i];
    //    double h = (xs - x0) / n;




    //    double y0_1 = 0.1;


    //    std::cout << "y' =  x^2 +y\n";
    //    std::cout << "Warunek poczatkowy: y(" << x0 << ") = " << y0_1 << "\n";
    //    std::cout << "Punkt koncowy: x = " << xs << "\n";
    //    std::cout << "Krok h = " << h << "\n";

    //    std::cout << "Euler: " << euler(r1, x0, y0_1, xs, n) << "\n";
    //    std::cout << "RK2:   " << RK2(r1, x0, y0_1, xs, n) << "\n";
    //    std::cout << "RK4:   " << RK4(r1, x0, y0_1, xs, n) << "\n";
    //    std::cout << "Dokladne: " << 2.1 * exp(1) - 5 << "\n";
    //    std::cout << "\n";


    //    double y0_2 = 0.1;



    //    std::cout << "y' = x + y\n";
    //    std::cout << "Warunek poczatkowy: y(" << x0 << ") = " << y0_2 << "\n";
    //    std::cout << "Punkt koncowy: x = " << xs << "\n";
    //    std::cout << "Krok h = " << h << "\n";

    //    std::cout << "Euler: " << euler(r2, x0, y0_2, xs, n) << "\n";
    //    std::cout << "RK2:   " << RK2(r2, x0, y0_2, xs, n) << "\n";
    //    std::cout << "RK4:   " << RK4(r2, x0, y0_2, xs, n) << "\n";
    //    std::cout << "Dokladne: " << 1.1 * exp(1) - 2 << "\n";


    //







//{
//    int n = 20;
//    int n_values[] = { 2, 4, 8, 16, 32, 64, 128, 256 };
//    
//    //for (int i = 0; i < 8; i++) {
//
//        //n = n_values[i];
//
//        std::cout << "Funkcja: sin(x)" << std::endl;
//        std::cout << "Przedzial: [0.5, 2.5]" << std::endl;
//        std::cout << "Liczba podzialow: " << n << std::endl;
//        std::cout << "Prostokaty: " << prostokat(f1, 0.5, 2.5, n) << std::endl;
//        std::cout << "Trapezy:    " << trapez(f1, 0.5, 2.5, n) << std::endl;
//        std::cout << "Parabole:   " << parabola(f1, 0.5, 2.5, n) << std::endl;
//        std::cout << "rozzw.dokladne" << -cos(2.5) + cos(0.5) << std::endl;
//        std::cout << std::endl;
//
//
//
//
//        std::cout << "Gauss (n=2): " << Kwadratury(f1, 0.5, 2.5, 2) << std::endl;
//        std::cout << "Gauss (n=3): " << Kwadratury(f1, 0.5, 2.5, 3) << std::endl;
//        std::cout << "Gauss (n=4): " << Kwadratury(f1, 0.5, 2.5, 4) << std::endl;
//        std::cout << std::endl;
//
//
//
//
//        std::cout << "Funkcja: x^2 + 2x + 5" << std::endl;
//        std::cout << "Przedzial: [0.5, 5]" << std::endl;
//        std::cout << "Liczba podzialow: " << n << std::endl;
//        std::cout << "Prostokaty: " << prostokat(f2, 0.5, 5.0, n) << std::endl;
//        std::cout << "Trapezy:    " << trapez(f2, 0.5, 5.0, n) << std::endl;
//        std::cout << "Parabole:   " << parabola(f2, 0.5, 5.0, n) << std::endl;
//        std::cout << "rozzw.dokladne" << 2133.0/24.0 << std::endl;
//        std::cout << std::endl;
//
//
//
//
//        std::cout << "Gauss (n=2): " << Kwadratury(f2, 0.5, 5.0, 2) << std::endl;
//        std::cout << "Gauss (n=3): " << Kwadratury(f2, 0.5, 5.0, 3) << std::endl;
//        std::cout << "Gauss (n=4): " << Kwadratury(f2, 0.5, 5.0, 4) << std::endl;
//        std::cout << std::endl;
//
//
//
//
//        std::cout << "Funkcja: exp(x)" << std::endl;
//        std::cout << "Przedzial: [0.5, 5]" << std::endl;
//        std::cout << "Liczba podzialow: " << n << std::endl;
//        std::cout << "Prostokaty: " << prostokat(f3, 0.5, 5.0, n) << std::endl;
//        std::cout << "Trapezy:    " << trapez(f3, 0.5, 5.0, n) << std::endl;
//        std::cout << "Parabole:   " << parabola(f3, 0.5, 5.0, n) << std::endl;
//        std::cout << "rozzw.dokladne" << exp(5.0) - exp(0.5) << std::endl;
//        std::cout << std::endl;
//
//
//
//
//
//        std::cout << "Gauss (n=2): " << Kwadratury(f3, 0.5, 5.0, 2) << std::endl;
//        std::cout << "Gauss (n=3): " << Kwadratury(f3, 0.5, 5.0, 3) << std::endl;
//        std::cout << "Gauss (n=4): " << Kwadratury(f3, 0.5, 5.0, 4) << std::endl;
//        std::cout << std::endl;
//
//
//        std::cout << std::endl;
//
//
//
//        std::cout << "Funkcja: x^3 - 2x^2 + x - 1" << std::endl;
//        std::cout << "Przedzial: [0.5, 5]" << std::endl;
//        std::cout << "Liczba podzialow: " << n << std::endl;
//        std::cout << "Prostokaty: " << prostokat(f4, 0.5, 5.0, n) << std::endl;
//        std::cout << "Trapezy:    " << trapez(f4, 0.5, 5.0, n) << std::endl;
//        std::cout << "Parabole:   " << parabola(f4, 0.5, 5.0, n) << std::endl;
//        double dokl = ((pow(5, 4) / 4 - 2 * pow(5, 3) / 3 + pow(5, 2) / 2 - 5) - (pow(0.5, 4) / 4 - 2 * pow(0.5, 3) / 3 + pow(0.5, 2) / 2 - 0.5));
//        std::cout << "rozw. dokladne: " << dokl<< std::endl;
//
//        std::cout << "Gauss (n=2): " << Kwadratury(f4, 0.5, 5.0, 2) << std::endl;
//        std::cout << "Blad bezwzgledny: " << abs(dokl - Kwadratury(f4, 0.5, 5.0, 2)) << std::endl;
//        std::cout << "Gauss (n=3): " << Kwadratury(f4, 0.5, 5.0, 3) << std::endl;
//        std::cout << "Blad bezwzgledny: " << abs(dokl - Kwadratury(f4, 0.5, 5.0, 3)) << std::endl;
//        std::cout << "Gauss (n=4): " << Kwadratury(f4, 0.5, 5.0, 4) << std::endl;
//        std::cout << "Blad bezwzgledny: " << abs(dokl - Kwadratury(f4, 0.5, 5.0, 4)) << std::endl;
//        std::cout << std::endl;
//
//
//
//
//        std::cout << std::endl;
//
//
//        std::cout << "Funkcja: x^5 + 3x^3 - x + 2" << std::endl;
//        std::cout << "Przedzial: [0.5, 5]" << std::endl;
//        std::cout << "Liczba podzialow: " << n << std::endl;
//        std::cout << "Prostokaty: " << prostokat(f5, 0.5, 5.0, n) << std::endl;
//        std::cout << "Trapezy:    " << trapez(f5, 0.5, 5.0, n) << std::endl;
//        std::cout << "Parabole:   " << parabola(f5, 0.5, 5.0, n) << std::endl;
//
//        dokl = ((pow(5, 6) / 6 + 3 * pow(5, 4) / 4 - pow(5, 2) / 2 + 2 * 5) - (pow(0.5, 6) / 6 + 3 * pow(0.5, 4) / 4 - pow(0.5, 2) / 2 + 2 * 0.5));
//        std::cout << "rozw. dokladne: "  << dokl << std::endl;
//
//        std::cout << "Gauss (n=2): " << Kwadratury(f5, 0.5, 5.0, 2) << std::endl;
//        std::cout << "Blad bezwzgledny: " << abs(dokl - Kwadratury(f5, 0.5, 5.0, 2)) << std::endl;
//        std::cout << "Gauss (n=3): " << Kwadratury(f5, 0.5, 5.0, 3) << std::endl;
//        std::cout << "Blad bezwzgledny: " << abs(dokl - Kwadratury(f5, 0.5, 5.0, 3)) << std::endl;
//        std::cout << "Gauss (n=4): " << Kwadratury(f5, 0.5, 5.0, 4) << std::endl;
//        std::cout << "Blad bezwzgledny: " << abs(dokl - Kwadratury(f5, 0.5, 5.0, 4)) << std::endl;
//        std::cout << std::endl;
//
//
//        std::cout << std::endl;
//
//
//
//
//        std::cout << "Funkcja: x^7 - x^4 + 2x^2 - 5" << std::endl;
//        std::cout << "Przedzial: [0.5, 5]" << std::endl;
//        std::cout << "Liczba podzialow: " << n << std::endl;
//        std::cout << "Prostokaty: " << prostokat(f6, 0.5, 5.0, n) << std::endl;
//        std::cout << "Trapezy:    " << trapez(f6, 0.5, 5.0, n) << std::endl;
//        std::cout << "Parabole:   " << parabola(f6, 0.5, 5.0, n) << std::endl;
//
//        dokl = ((pow(5, 8) / 8 - pow(5, 5) / 5 + 2 * pow(5, 3) / 3 - 5 * 5) - (pow(0.5, 8) / 8 - pow(0.5, 5) / 5 + 2 * pow(0.5, 3) / 3 - 5 * 0.5));
//        std::cout << "rozw.dokladne: "<< dokl << std::endl;
//
//        std::cout << "Gauss (n=2): " << Kwadratury(f6, 0.5, 5.0, 2) << std::endl;
//        std::cout << "Blad bezwzgledny: " << abs(dokl - Kwadratury(f6, 0.5, 5.0, 2)) << std::endl;
//        std::cout << "Gauss (n=3): " << Kwadratury(f6, 0.5, 5.0, 3) << std::endl;
//        std::cout << "Blad bezwzgledny: " << abs(dokl - Kwadratury(f6, 0.5, 5.0, 3)) << std::endl;
//        std::cout << "Gauss (n=4): " << Kwadratury(f6, 0.5, 5.0, 4) << std::endl;
//        std::cout << "Blad bezwzgledny: " << abs(dokl - Kwadratury(f6, 0.5, 5.0, 4))<<std::endl;
//        std::cout << std::endl;
//
//
//


    //}






    /*Mesh mesh;*/
    /*
    mesh.wczytaj_punkty("dane1.txt");
    mesh.wypisz();
    mesh.wczytaj_eq("dane2.txt");
    mesh.wypisz_eq();
    */

    //mesh.wczytaj_punkty("inter.txt");
    //mesh.wypisz();

    //std::cout<<"wartosc wielomianu w zadanym pkt:" << interpol_lagrange(mesh.baza, mesh.liczba_pkt);
    //std::cout << "wartosc wielomianu w zadanym pkt:" << interpol_newton(mesh.baza, mesh.liczba_pkt);
    //Roundy();

 
   // mesh.wczytaj_uklad("RURL_dane1.txt");
   // mesh.wczytaj_uklad("zero.txt");
   /* mesh.wczytaj_uklad("Jac.txt");
    mesh.wypisz_uklad();*/
   // gauss(mesh.uklad, mesh.count);
   // gauss_pivot(mesh.uklad, mesh.count);
   // std::cout << std::endl;
   // gauss(mesh.uklad, mesh.count);

    //std::cout << std::endl;
    //jacob(mesh.uklad, mesh.count);


   /*auto start = std::chrono::high_resolution_clock::now();
    jacob(uklad(100), 100);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Czas jacobiego: " << elapsed.count() << " s\n";*/

   //auto st = std::chrono::high_resolution_clock::now();
   // gauss(uklad(100), 100);
   // auto en = std::chrono::high_resolution_clock::now();
   // std::chrono::duration<double> elapse = en - st;
   // std::cout << "Czas gaussa: " << elapse.count() << " s\n";





}
