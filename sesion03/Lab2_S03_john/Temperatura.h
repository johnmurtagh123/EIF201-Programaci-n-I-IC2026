#pragma once

#ifndef TEMPERATURA_H
#define TEMPERATURA_H

double* crearRegistro(int& cantidadDias);
void ingresarTemperatura(double* registro, int cantidad);
double calcularPromedio(const double* registro, int cantidad);
double calcularMaximo(const double* registro, int cantidad);
double calcularMinimo(const double* registro, int cantidad);
void mostrarResultado(const double* registro, int cantidad);

#endif 