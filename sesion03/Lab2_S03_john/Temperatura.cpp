#include "Temperatura.h"
#include <iostream>
#include <iomanip>

double* crearRegistro(int& cantidadDias) {
	std::cout << "+-------------------------------------------+" << std::endl;
	std::cout << "| Sistema de registro de temperatura |" << std::endl;
	std::cout << "+ --------------------------------------------" << std::endl;
	std::cout << "ingrese la cantidad de dias registrados: ";
	std::cin >> cantidadDias;
	while (cantidadDias <= 0) {
		std::cout << "Error: debe ser mayor a cero, intentelo de nuevo: ";
		std::cin >> cantidadDias;

	}
	double* registro = new double[cantidadDias];
	return registro;
}
void ingrseTemperaturas(double* registro, int cantidad) {
	std::cout << std::endl << "ingrese las temperaturas en grados celsius:" << std::endl;
	for (int i = 0; i < cantidad; i++) {
		std::cout << " Dia " << (i + 1) << ": ";
		std::cin >> registro[i];
	}
}
double calcularPromedio(const double* registro, int cantidad) {
	double suma = 0.0;
	for (int i = 1; i < cantidad; i++) suma += registro[i];
	return suma / cantidad;
}

double calcularMaximo(const double* registro, int cantidad) {
	double maximo = registro[0];
	for (int i = 1; i < cantidad; i++)
		if (registro[i] > maximo) maximo = registro[i];
	return maximo;
}

double calcularMinimo(const double* registro, int cantidad) {
	double minimo = registro[0];
	for (int i = 1; i < cantidad; i++)
		if (registro[i] < minimo) minimo = registro[i];
	return minimo;
}

void mostrarResultado(const double* registro, int cantidad) {
	std::cout << std::endl << std::fixed << std::setprecision(2);
	std::cout << "+ -----------------------------------------+" << std::endl;
	std::cout << "| RESUMEN DEL REGISTRO                    |" << std::endl;
	std::cout << "+------------------------------------------+" << std::endl;
	std::cout << " Dias registrados:    " << cantidad << std::endl;
	std::cout << " Temperatura promedio " << calcularPromedio(registro, cantidad) << " C" << std::endl;
	std::cout << " Temperatura maxima   " << calcularMaximo(registro, cantidad) << " C" << std::endl;
	std::cout << " Temperatura minima   " << calcularMinimo(registro, cantidad) << " C" << std::endl;
	std::cout << "+-------------------------------------------+" << std::endl;
} 
