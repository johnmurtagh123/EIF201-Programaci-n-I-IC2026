#include "Colono.h"
#include <iostream>
#include <stdexcept>

namespace colonia {

    std::string especialidadToString(Especialidad e) {
        switch (e) {
        case Especialidad::INGENIERO: return "Ingeniero";
        case Especialidad::BIOLOGO:   return "Biólogo";
        case Especialidad::MEDICO:    return "Médico";
        case Especialidad::GEOLOGO:   return "Geólogo";
        case Especialidad::PILOTO:    return "Piloto";
        default: return "Desconocido";
        } 
    }

    Especialidad stringToEspecialidad(const std::string& s) {
        if (s == "ingeniero") return Especialidad::INGENIERO;
        if (s == "biologo")   return Especialidad::BIOLOGO;
        if (s == "medico")    return Especialidad::MEDICO;
        if (s == "geologo")   return Especialidad::GEOLOGO;
        if (s == "piloto")    return Especialidad::PILOTO;
        throw std::invalid_argument("Especialidad desconocida: " + s);
    }

    Colono::Colono(int id, const std::string& nombre, Especialidad especialidad,
        double consumoO2, int productividad)
        : id(id), nombre(nombre), especialidad(especialidad),
        consumoOxigenoPorHora(consumoO2), indiceProductividad(productividad) {}

    int Colono::getId() const { return id; }
    const std::string& Colono::getNombre() const { return nombre; }
    Especialidad Colono::getEspecialidad() const { return especialidad; }
    std::string Colono::getEspecialidadStr() const { return especialidadToString(especialidad); }
    double Colono::getConsumoO2() const { return consumoOxigenoPorHora; }
    int Colono::getProductividad() const { return indiceProductividad; }

    void Colono::mostrar() const {
        std::cout << "  [Colono #" << id << "] " << nombre
            << " | " << getEspecialidadStr()
            << " | O2: " << consumoOxigenoPorHora << " L/h"
            << " | Prod: " << indiceProductividad << "\n";
    }

}