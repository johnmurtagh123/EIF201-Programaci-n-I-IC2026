#include "Vehiculo.h"
#include <iostream>
#include <iomanip>

namespace UNA {

   
    Vehiculo::Vehiculo(std::string placa, std::string marca, int anio, double kilometraje)
        : placa(placa), marca(marca), anios(anio), kilometraje(kilometraje), activo(true) {}

    // Getters 
    std::string Vehiculo::getPlaca()       const { return placa; }
    std::string Vehiculo::getMarca()       const { return marca; }
    int         Vehiculo::getAnio()        const { return anios; }
    double      Vehiculo::getKilometraje() const { return kilometraje; }
    bool        Vehiculo::isActivo()       const { return activo; }

    //registrarKilometros
    void Vehiculo::registrarKilometros(double km) {
        if (!activo) {
            std::cout << "[ERROR] El vehiculo " << placa
                << " esta FUERA DE SERVICIO. No se puede registrar kilometros.\n";
            return;
        }
        if (km <= 0) {
            std::cout << "[ERROR] La cantidad de kilometros debe ser positiva.\n";
            return;
        }
        kilometraje += km;
        std::cout << "[OK] Se registraron " << km << " km al vehiculo " << placa
            << ". Kilometraje total: " << kilometraje << " km.\n";
    }

    // desactivar
    void Vehiculo::desactivar() {
        if (!activo) {
            std::cout << "[AVISO] El vehiculo " << placa << " ya esta FUERA DE SERVICIO.\n";
            return;
        }
        activo = false;
        std::cout << "[OK] Vehiculo " << placa << " marcado como FUERA DE SERVICIO.\n";
    }

    //  reactivar 
    void Vehiculo::reactivar() {
        if (activo) {
            std::cout << "[AVISO] El vehiculo " << placa << " ya esta ACTIVO.\n";
            return;
        }
        activo = true;
        std::cout << "[OK] Vehiculo " << placa << " reactivado como ACTIVO.\n";
    }

    //mostrar 
    void Vehiculo::mostrar() const {
        std::cout << "???????????????????????????????????????\n";
        std::cout << "  Placa       : " << placa << "\n";
        std::cout << "  Marca       : " << marca << "\n";
        std::cout << "  Año         : " << anios << "\n";
        std::cout << "  Kilometraje : " << std::fixed << std::setprecision(2)
            << kilometraje << " km\n";
        std::cout << "  Estado      : " << (activo ? "ACTIVO" : "FUERA DE SERVICIO") << "\n";
        std::cout << "???????????????????????????????????????\n";
    }

} 