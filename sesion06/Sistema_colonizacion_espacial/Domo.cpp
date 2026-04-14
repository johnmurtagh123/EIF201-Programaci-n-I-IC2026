
#include "Domo.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace colonia {

    std::string tipoDomToString(TipoDomo t) {
        switch (t) {
        case TipoDomo::LABORATORIO: return "Laboratorio";
        case TipoDomo::INGENIERIA:  return "Ingeniería";
        case TipoDomo::HABITAT:     return "Hábitat";
        default: return "Desconocido";
        }
    }

    Domo::Domo(const std::string& codigo, TipoDomo tipo,
        double capacidadO2, int maxOcupantes)
        : codigo(codigo), tipo(tipo), capacidadO2PorHora(capacidadO2),
        maxOcupantes(maxOcupantes), sellado(false) {}

    Domo::~Domo() {
        // No destruye los colonos, solo limpia las referencias
        colonos.clear();
    }

    bool Domo::especialidadCompatible(Especialidad e) const {
        switch (tipo) {
        case TipoDomo::LABORATORIO:
            return e == Especialidad::BIOLOGO ||
                e == Especialidad::MEDICO ||
                e == Especialidad::GEOLOGO;
        case TipoDomo::INGENIERIA:
            return e == Especialidad::INGENIERO ||
                e == Especialidad::PILOTO;
        case TipoDomo::HABITAT:
            return true;
        default: return false;
        }
    }

    const std::string& Domo::getCodigo() const { return codigo; }
    TipoDomo Domo::getTipo() const { return tipo; }
    std::string Domo::getTipoStr() const { return tipoDomToString(tipo); }
    double Domo::getCapacidadO2() const { return capacidadO2PorHora; }
    int Domo::getMaxOcupantes() const { return maxOcupantes; }
    bool Domo::isSellado() const { return sellado; }
    int Domo::getNumColonos() const { return static_cast<int>(colonos.size()); }

    double Domo::getConsumoTotalO2() const {
        double total = 0.0;
        for (const Colono* c : colonos) total += c->getConsumoO2();
        return total;
    }

    double Domo::getRatioO2() const {
        double consumo = getConsumoTotalO2();
        if (consumo == 0.0) return 9999.0; // Sin colonos: ratio "infinito"
        return capacidadO2PorHora / consumo;
    }

    std::string Domo::getEstadoRatio() const {
        double ratio = getRatioO2();
        if (ratio > 1.5)  return "SEGURO";
        if (ratio >= 1.2) return "PRECAUCION";
        return "CRITICO";
    }

    const std::vector<Colono*>& Domo::getColonos() const { return colonos; }

    bool Domo::estaLleno() const {
        return static_cast<int>(colonos.size()) >= maxOcupantes;
    }

    bool Domo::puedeAdmitir(Colono* c) const {
        if (sellado) return false;
        if (estaLleno()) return false;
        if (!especialidadCompatible(c->getEspecialidad())) return false;
        double nuevoConsumo = getConsumoTotalO2() + c->getConsumoO2();
        return nuevoConsumo <= capacidadO2PorHora;
    } 

    bool Domo::admitirColono(Colono* c) {
        if (!puedeAdmitir(c)) return false;
        colonos.push_back(c);
        return true;
    }

    bool Domo::retirarColono(int colonoId) {
        if (sellado) return false;
        auto it = std::find_if(colonos.begin(), colonos.end(),
            [colonoId](const Colono* c) { return c->getId() == colonoId; });
        if (it == colonos.end()) return false;
        colonos.erase(it);
        return true;
    }

    void Domo::sellar() { sellado = true; }
    void Domo::dessellar() { sellado = false; }

    std::vector<Colono*> Domo::evacuar() {
        std::vector<Colono*> evacuados = colonos;
        colonos.clear();
        return evacuados;
    }

    void Domo::mostrar() const {
        double ratio = getRatioO2();
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  Domo [" << codigo << "] Tipo: " << getTipoStr()
            << " | O2 cap: " << capacidadO2PorHora << " L/h"
            << " | Colonos: " << colonos.size() << "/" << maxOcupantes
            << " | Ratio O2: ";
        if (colonos.empty()) std::cout << "N/A";
        else std::cout << ratio;
        std::cout << " [" << getEstadoRatio() << "]"
            << (sellado ? " [SELLADO]" : "") << "\n";
        for (const Colono* c : colonos) c->mostrar();
    }

}