// Lab2_S03_john.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Temperatura.h"

int main()
{
    int cantiadDias = 0;

    double* registroTeam = crearRegistro(cantiadDias);

    ingresarTemperatura(registroTeam, cantiadDias);

    mostrarResultado(registroTeam, cantiadDias);

    mostrarResultado(registroTeam, cantiadDias);

    delete[] registroTeam;
    registroTeam = nullptr;

    return 0;
}

