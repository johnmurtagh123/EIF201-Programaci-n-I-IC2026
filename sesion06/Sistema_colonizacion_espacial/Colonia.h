#ifndef COLONIA_H
#define COLONIA_H

#include <string>
#include <vector>
#include "Domo.h"
#include "Colono.h"

namespace colonia {

    struct ConfigDomo {
        std::string codigo;
        TipoDomo tipo;
        double capacidadO2;
        int maxOcupantes;
    };

    struct ResultadoEvacuacion {
        int totalEvacuados;
        int noReubicados;
        std::vector<Colono*> colonosSinDomo;
    };

    struct ResultadoRebalanceo {
        int colonosMovidos;
    };

    struct UbicacionColono {
        Colono* colono;
        Domo* domo; // nullptr si no está en ningún domo
    };

    class Colonia {
    private:
        std::string nombre;
        std::string planeta;
        std::vector<Domo*> domos;

        Domo* encontrarDomóOptimo(Colono* c) const;

    public:
        Colonia(const std::string& nombre, const std::string& planeta,
            const std::vector<ConfigDomo>& configDomos);
        ~Colonia();

        const std::string& getNombre() const;
        const std::string& getPlaneta() const;
        const std::vector<Domo*>& getDomos() const;

        // Asignación inteligente
        bool asignarColono(Colono* c);

        // Evacuación de emergencia
        ResultadoEvacuacion evacuarDomo(const std::string& codigoDomo);

        // Transferencia individual (segura: no retira hasta confirmar destino)
        bool transferirColono(int colonoId, const std::string& codigoDestino);

        // Rebalanceo
        ResultadoRebalanceo rebalancear();

        // Consultas
        UbicacionColono buscarColono(int colonoId) const;
        void mostrarTableroControl() const;
        void alertaOxigeno(double umbral) const;
        void reporteProductividadPorEspecialidad() const;
        void estadisticasGlobales() const;

        Domo* getDomo(const std::string& codigo) const;
    };

} 

#endif