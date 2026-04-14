#ifndef DOMO_H
#define DOMO_H

#include <string>
#include <vector>
#include "Colono.h"

namespace colonia {

    enum class TipoDomo {
        LABORATORIO,
        INGENIERIA,
        HABITAT
    };

    std::string tipoDomToString(TipoDomo t);

    class Domo {
    private:
        std::string codigo;
        TipoDomo tipo;
        double capacidadO2PorHora;
        int maxOcupantes;
        bool sellado;
        std::vector<Colono*> colonos;

        bool especialidadCompatible(Especialidad e) const;

    public:
        Domo(const std::string& codigo, TipoDomo tipo,
            double capacidadO2, int maxOcupantes);
        ~Domo(); // No destruye colonos, solo limpia el vector

        const std::string& getCodigo() const;
        TipoDomo getTipo() const;
        std::string getTipoStr() const;
        double getCapacidadO2() const;
        int getMaxOcupantes() const;
        bool isSellado() const;
        int getNumColonos() const;
        double getConsumoTotalO2() const;
        double getRatioO2() const;
        std::string getEstadoRatio() const;
        const std::vector<Colono*>& getColonos() const;

        // Retorna true si admitió al colono
        bool admitirColono(Colono* c);

        // Retorna true si lo encontró y removió
        bool retirarColono(int colonoId);

        // Sellado / evacuación
        void sellar();
        void dessellar();

        // Evacuación forzosa: retorna todos los colonos y vacía el domo
        std::vector<Colono*> evacuar();

        bool puedeAdmitir(Colono* c) const;
        bool estaLleno() const;

        void mostrar() const;
    };

} 
#endif