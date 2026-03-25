#ifndef FLOTA_H
#define FLOTA_H

#include "Vehiculo.h"
#include <string>

namespace UNA {

    class Flota {
    private:

        int cantidad;
        int capacidad;
        Vehiculo** vehiculos;
        static const int CAPACIDAD_INICIAL = 3;

        void redimensionar();  
    public:
        Flota();
        ~Flota();

        void      agregar(Vehiculo* nuevo);
        Vehiculo* buscarPorPlaca(std::string placa);
        void      mostrarPorMarca(std::string marca) const;
        bool      eliminar(std::string placa);
        int       contarActivos() const;
        void      mostrarTodos()  const;
    };

} 

#endif 

