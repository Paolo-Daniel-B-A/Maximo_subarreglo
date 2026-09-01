#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using Valor = long long;

Valor cubica(const vector<int>& a){
    int n = a.size();
    Valor mejor = a[0];
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            Valor suma = 0;
            for (int k = i; k <= j; k++){
                suma += a[k];
            }
            if (suma > mejor){
                mejor = suma;
            }
        }
    }
    return mejor;
}

Valor cuadratica(const vector<int>& a){
    int n = a.size();
    Valor mejor = a[0];
    for (int i = 0; i < n; i++){
        Valor suma = 0;
        for (int j = i; j < n; j++){
            suma += a[j];

            if (suma > mejor){
                mejor = suma;
            }
        }
    }
    return mejor;
}

Valor kadane(const vector<int>& a){
    Valor sumaActual = a[0];
    Valor mejor = a[0];

    for (int i = 1; i < a.size(); i++){
        if (a[i] > sumaActual + a[i]){
            sumaActual = a[i];
        } 
        else{
            sumaActual = sumaActual + a[i];
        }
        if (sumaActual > mejor){
            mejor = sumaActual;
        }
    }
    return mejor;
}

vector<int> generarArreglo(int n){
    vector<int> a(n);
    random_device rd;
    mt19937 generador(rd());

    uniform_int_distribution<int> distribucion(-100, 100);
    for (int i = 0; i < n; i++){
        a[i] = distribucion(generador);
    }
    return a;
}

template <typename Funcion>
double medirTiempo(Funcion funcion) {
    auto inicio = chrono::high_resolution_clock::now();
    volatile Valor resultado = funcion();

    auto fin = chrono::high_resolution_clock::now();
    double tiempo = chrono::duration<double, milli>(fin - inicio).count();

    return tiempo;
}

void pruebasCorrectitud() {
    random_device rd;
    mt19937 generador(rd());

    uniform_int_distribution<int> longitud(1, 50);
    uniform_int_distribution<int> valores(-50, 50);

    for (int prueba = 1; prueba <= 100; prueba++) {
        int n = longitud(generador);

        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = valores(generador);
        }

        Valor resultado1 = cubica(a);
        Valor resultado2 = cuadratica(a);
        Valor resultado3 = kadane(a);

        if (resultado1 != resultado2 || resultado1 != resultado3) {
            cout << "ERROR en la prueba " << prueba << endl;
            return;
        }
    }
    cout << "CORRECCION: OK (100/100 pruebas)" << endl;
}

void mostrarTabla(
    const vector<int>& tamanos,
    const vector<double>& tiempos,
    const char* nombre){

    cout << "\n";
    cout << "MEDICIONES: " << nombre << endl;

    cout << left << setw(12) << "n" << setw(15) << "Tiempo(ms)" << setw(12) << "Razon" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < tamanos.size(); i++){
        cout << left << setw(12) << tamanos[i] << setw(15) << tiempos[i];
        if (i == 0){
            cout << setw(12) << "-";
        } 
        else if (tiempos[i - 1] > 0){
            double razon = tiempos[i] / tiempos[i - 1];
            cout << setw(12) << razon;
        } 
        else{
            cout << setw(12) << "-";
        }
        cout << endl;
    }
    cout << "----------------------------------------" << endl;
}

int main() {
    cout << fixed << setprecision(3);
    pruebasCorrectitud();

    vector<int> tamanos = { 1000, 2000, 4000, 8000 };
    vector<vector<int>> arreglos;

    for (int i = 0; i < tamanos.size(); i++){
        arreglos.push_back(generarArreglo(tamanos[i]));
    }

    vector<double> tiemposKadane;
    cout << "\nEjecutando KADANE..." << endl;
    for (int i = 0; i < tamanos.size(); i++){
        double tiempo = medirTiempo([&](){
                    return kadane(arreglos[i]);
                }
            );
        tiemposKadane.push_back(tiempo);
    }
    mostrarTabla(tamanos, tiemposKadane, "KADANE O(n)");

    vector<double> tiemposCuadratica;
    cout << "\nEjecutando CUADRATICA..." << endl;
    for (int i = 0; i < tamanos.size(); i++){
        double tiempo = medirTiempo( [&]() {
                    return cuadratica(arreglos[i]);
                }
            );
        tiemposCuadratica.push_back(tiempo);
    }
    mostrarTabla(tamanos, tiemposCuadratica, "CUADRATICA O(n^2)");

    vector<double> tiemposCubica;
    cout << "\nEjecutando CUBICA..." << endl;
    for (int i = 0; i < tamanos.size(); i++){
        if (tamanos[i] == 8000) {
            tiemposCubica.push_back(-1);
            cout << "n = 8000 omitido." << endl;
        } else {
            double tiempo = medirTiempo( [&]() {
                        return cubica(arreglos[i]);
                    }
                );
            tiemposCubica.push_back(tiempo);
        }
    }
    mostrarTabla( tamanos, tiemposCubica, "CUBICA O(n^3)");

    cout << "\n========================================" << endl;
    cout << "EJECUCION PARA n = 10^8" << endl;

    vector<int> grande = generarArreglo(100000000);
    cout << "Ejecutando Kadane..." << endl;

    double tiempoGrande = medirTiempo( [&](){
                return kadane(grande);
            }
        );

    cout << "Tiempo: " << tiempoGrande / 1000 << " segundos" << endl;
    return 0;
}