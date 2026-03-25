#include "Flota.h"
#include <iostream>

namespace UNA {

    // Constructor 
    Flota::Flota() : cantidad(0), capacidad(CAPACIDAD_INICIAL) {
        vehiculos = new Vehiculo*[capacidad];
    }

    //Destructor (dos niveles) 
    Flota::~Flota() {
        // Nivel 1: liberar cada objeto Vehiculo
        for (int i = 0; i < cantidad; ++i) {
            delete vehiculos[i];
        }
        // Nivel 2: liberar el arreglo de punteros
        delete[] vehiculos;
    }

    //redimensionar
    void Flota::redimensionar() {
        int nuevaCapacidad = capacidad * 2;
        Vehiculo** nuevo = new Vehiculo * [nuevaCapacidad];

        for (int i = 0; i < cantidad; ++i) {
            nuevo[i] = vehiculos[i];
        }

        delete[] vehiculos;       // libera solo el arreglo viejo (no los objetos)
        vehiculos = nuevo;
        capacidad = nuevaCapacidad;

        std::cout << "[SISTEMA] Arreglo redimensionado: capacidad ahora es " << capacidad << ".\n";
    }

    //agregar
    void Flota::agregar(Vehiculo* nuevo) {
        if (cantidad == capacidad) {
            redimensionar();
        }
        vehiculos[cantidad++] = nuevo;
        std::cout << "[OK] Vehiculo " << nuevo->getPlaca() << " registrado en la flota.\n";
    }

    //buscarPorPlaca
    Vehiculo* Flota::buscarPorPlaca(std::string placa) {
        for (int i = 0; i < cantidad; ++i) {
            if (vehiculos[i]->getPlaca() == placa) {
                return vehiculos[i];
            }
        }
        return nullptr;
    }

    // mostrarPorMarca 
    void Flota::mostrarPorMarca(std::string marca) const {
        int encontrados = 0;
        for (int i = 0; i < cantidad; ++i) {
            if (vehiculos[i]->getMarca() == marca) {
                vehiculos[i]->mostrar();
                ++encontrados;
            }
        }
        if (encontrados == 0) {
            std::cout << "[INFO] No hay vehiculos de la marca \"" << marca << "\" en la flota.\n";
        }
        else {
            std::cout << "[INFO] Total de vehiculos de marca \"" << marca
                << "\": " << encontrados << ".\n";
        }
    }

    // eliminar
    bool Flota::eliminar(std::string placa) {
        for (int i = 0; i < cantidad; ++i) {
            if (vehiculos[i]->getPlaca() == placa) {
                // Verificar que esté fuera de servicio
                if (vehiculos[i]->isActivo()) {
                    std::cout << "[ERROR] El vehiculo " << placa
                        << " esta ACTIVO. Debe desactivarse antes de darlo de baja.\n";
                    return false;
                }
                // Eliminar objeto
                delete vehiculos[i];

                // Compactación: mover elementos hacia la izquierda
                for (int j = i; j < cantidad - 1; ++j) {
                    vehiculos[j] = vehiculos[j + 1];
                }
                vehiculos[--cantidad] = nullptr;

                std::cout << "[OK] Vehiculo " << placa << " eliminado de la flota.\n";
                return true;
            }
        }
        std::cout << "[ERROR] No se encontro el vehiculo con placa \"" << placa << "\".\n";
        return false;
    }

    //contarActivos 
    int Flota::contarActivos() const {
        int activos = 0;
        for (int i = 0; i < cantidad; ++i) {
            if (vehiculos[i]->isActivo()) ++activos;
        }
        return activos;
    }

    //mostrarTodos
    void Flota::mostrarTodos() const {
        if (cantidad == 0) {
            std::cout << "[INFO] La flota esta vacia. No hay vehiculos registrados.\n";
            return;
        }
        std::cout << "=== FLOTA COMPLETA (" << cantidad << " vehiculos) ===\n";
        for (int i = 0; i < cantidad; ++i) {
            vehiculos[i]->mostrar();
        }
    }

} 
