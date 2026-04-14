#ifndef COLONO_H
#define COLONO_H

#include <string>

namespace colonia {

    enum class Especialidad {
        INGENIERO,
        BIOLOGO,
        MEDICO,
        GEOLOGO,
        PILOTO
    };

    std::string especialidadToString(Especialidad e);
    Especialidad stringToEspecialidad(const std::string& s);

    class Colono {
    private:
        int id;
        std::string nombre;
        Especialidad especialidad;
        double consumoOxigenoPorHora;
        int indiceProductividad;

    public:
        Colono(int id, const std::string& nombre, Especialidad especialidad,
            double consumoO2, int productividad);

        int getId() const;
        const std::string& getNombre() const;
        Especialidad getEspecialidad() const;
        std::string getEspecialidadStr() const;
        double getConsumoO2() const;
        int getProductividad() const;

        void mostrar() const;
    };

} 

#endif