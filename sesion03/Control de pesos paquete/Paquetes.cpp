#include <iostream>
#include "paquetes.h"


double* crearRegistro(int& cantidad) {
    do {
        std::cout << "Ingrese la cantidad de paquetes (debe ser > 0): ";
        std::cin >> cantidad;
        if (cantidad <= 0) {
            std::cout << "Error: la cantidad debe ser mayor a 0. Intente de nuevo.\n";
        }
    } while (cantidad <= 0);

    double* pesos = new double[cantidad];
    return pesos;
}

void ingresarPesos(double* pesos, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        do {
            std::cout << "Ingrese el peso del paquete " << (i + 1) << " (kg, debe ser > 0): ";
            std::cin >> pesos[i];
            if (pesos[i] <= 0) {
                std::cout << "Error: el peso debe ser mayor a 0. Intente de nuevo.\n";
            }
        } while (pesos[i] <= 0);
    }
}

double calcularPesoTotal(const double* pesos, int cantidad) {
    double total = 0.0;
    for (int i = 0; i < cantidad; i++) {
        total += pesos[i];
    }
    return total;
}

int contarSobreLimite(const double* pesos, int cantidad, double limite) {
    int contador = 0;
    for (int i = 0; i < cantidad; i++) {
        if (pesos[i] > limite) {
            contador++;
        }
    }
    return contador;
}

const double* buscarMasPesado(const double* pesos, int cantidad) {
    const double* masPesado = &pesos[0];
    for (int i = 1; i < cantidad; i++) {
        if (pesos[i] > *masPesado) {
            masPesado = &pesos[i];
        }
    }
    return masPesado;
}