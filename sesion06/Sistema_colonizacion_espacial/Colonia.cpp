#include "Colonia.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

namespace colonia {

    Colonia::Colonia(const std::string& nombre, const std::string& planeta,
        const std::vector<ConfigDomo>& configDomos)
        : nombre(nombre), planeta(planeta) {
        for (const auto& cfg : configDomos) {
            domos.push_back(new Domo(cfg.codigo, cfg.tipo, cfg.capacidadO2, cfg.maxOcupantes));
        }
    } 

    Colonia::~Colonia() {
        for (Domo* d : domos) delete d;
        domos.clear();
    }

    const std::string& Colonia::getNombre() const { return nombre; }
    const std::string& Colonia::getPlaneta() const { return planeta; }
    const std::vector<Domo*>& Colonia::getDomos() const { return domos; }

    Domo* Colonia::getDomo(const std::string& codigo) const {
        for (Domo* d : domos) {
            if (d->getCodigo() == codigo) return d;
        }
        return nullptr;
    }

    Domo* Colonia::encontrarDomóOptimo(Colono* c) const {
        Domo* mejor = nullptr;
        double mejorRatio = -1.0;

        for (Domo* d : domos) {
            if (!d->puedeAdmitir(c)) continue;
            // Ratio hipotético después de admitir
            double nuevoConsumo = d->getConsumoTotalO2() + c->getConsumoO2();
            double ratio = d->getCapacidadO2() / nuevoConsumo;
            if (ratio > mejorRatio) {
                mejorRatio = ratio;
                mejor = d;
            }
        }
        return mejor;
    }

    bool Colonia::asignarColono(Colono* c) {
        Domo* optimo = encontrarDomóOptimo(c);
        if (!optimo) {
            std::cout << "  [!] No hay domo disponible para " << c->getNombre()
                << " (" << c->getEspecialidadStr() << ")\n";
            return false;
        }
        optimo->admitirColono(c);
        std::cout << "  [+] " << c->getNombre() << " asignado a domo ["
            << optimo->getCodigo() << "]\n";
        return true;
    }

    ResultadoEvacuacion Colonia::evacuarDomo(const std::string& codigoDomo) {
        ResultadoEvacuacion resultado = { 0, 0, {} };
        Domo* domo = getDomo(codigoDomo);
        if (!domo) {
            std::cout << "  [!] Domo " << codigoDomo << " no encontrado.\n";
            return resultado;
        }

        domo->sellar();
        std::vector<Colono*> evacuados = domo->evacuar();
        resultado.totalEvacuados = static_cast<int>(evacuados.size());

        for (Colono* c : evacuados) {
            Domo* destino = encontrarDomóOptimo(c);
            if (destino) {
                destino->admitirColono(c);
                std::cout << "  [~] " << c->getNombre() << " reubicado en ["
                    << destino->getCodigo() << "]\n";
            }
            else {
                resultado.noReubicados++;
                resultado.colonosSinDomo.push_back(c);
                std::cout << "  [!] " << c->getNombre() << " NO pudo ser reubicado.\n";
            }
        }
        return resultado;
    }

    bool Colonia::transferirColono(int colonoId, const std::string& codigoDestino) {
        // Primero encontrar colono y su domo origen
        Domo* origen = nullptr;
        Colono* colono = nullptr;

        for (Domo* d : domos) {
            for (Colono* c : d->getColonos()) {
                if (c->getId() == colonoId) {
                    colono = c;
                    origen = d;
                    break;
                }
            }
            if (colono) break;
        }

        if (!colono) {
            std::cout << "  [!] Colono #" << colonoId << " no encontrado en ningún domo.\n";
            return false;
        }

        Domo* destino = getDomo(codigoDestino);
        if (!destino) {
            std::cout << "  [!] Domo destino [" << codigoDestino << "] no existe.\n";
            return false;
        }

        // Validar antes de mover (seguro: no retiramos hasta confirmar)
        if (!destino->puedeAdmitir(colono)) {
            std::cout << "  [!] Domo [" << codigoDestino << "] rechaza a "
                << colono->getNombre() << " (sellado, lleno, incompatible o sin O2).\n";
            return false;
        }

        // Ahora sí: retirar del origen y agregar al destino
        origen->retirarColono(colonoId);
        destino->admitirColono(colono);
        std::cout << "  [->] " << colono->getNombre() << " transferido de ["
            << origen->getCodigo() << "] a [" << destino->getCodigo() << "]\n";
        return true;
    }

    ResultadoRebalanceo Colonia::rebalancear() {
        ResultadoRebalanceo resultado = { 0 };
        const double UMBRAL_SOBRECARGADO = 1.3;

        for (Domo* origen : domos) {
            if (origen->isSellado()) continue;
            if (origen->getRatioO2() >= UMBRAL_SOBRECARGADO) continue;

            // Domo sobrecargado: intentar mover colonos
            std::vector<Colono*> copiaColonos = origen->getColonos();
            for (Colono* c : copiaColonos) {
                // Buscar domo destino con ratio resultante >= 1.3
                Domo* mejor = nullptr;
                double mejorRatio = -1.0;

                for (Domo* destino : domos) {
                    if (destino == origen) continue;
                    if (!destino->puedeAdmitir(c)) continue;
                    double nuevoConsumo = destino->getConsumoTotalO2() + c->getConsumoO2();
                    double ratioResultante = destino->getCapacidadO2() / nuevoConsumo;
                    if (ratioResultante >= UMBRAL_SOBRECARGADO && ratioResultante > mejorRatio) {
                        mejorRatio = ratioResultante;
                        mejor = destino;
                    }
                }

                if (mejor) {
                    origen->retirarColono(c->getId());
                    mejor->admitirColono(c);
                    resultado.colonosMovidos++;
                    std::cout << "  [=] " << c->getNombre() << " rebalanceado de ["
                        << origen->getCodigo() << "] a [" << mejor->getCodigo() << "]\n";
                }
                // Si no hay destino, se queda en su domo original
            }
        }
        return resultado;
    }

    UbicacionColono Colonia::buscarColono(int colonoId) const {
        for (Domo* d : domos) {
            for (Colono* c : d->getColonos()) {
                if (c->getId() == colonoId) return { c, d };
            }
        }
        return { nullptr, nullptr };
    }

    void Colonia::mostrarTableroControl() const {
        std::cout << "\n====== TABLERO DE CONTROL: " << nombre
            << " (" << planeta << ") ======\n";
        for (const Domo* d : domos) d->mostrar();
        std::cout << "=============================================\n";
    }

    void Colonia::alertaOxigeno(double umbral) const {
        std::cout << "\n--- Alerta O2 (ratio < " << umbral << ") ---\n";
        bool hayAlertas = false;
        for (const Domo* d : domos) {
            if (d->getNumColonos() > 0 && d->getRatioO2() < umbral) {
                std::cout << "  [ALERTA] Domo [" << d->getCodigo()
                    << "] ratio=" << std::fixed << std::setprecision(2)
                    << d->getRatioO2() << " [" << d->getEstadoRatio() << "]\n";
                hayAlertas = true;
            }
        }
        if (!hayAlertas) std::cout << "  Sin alertas.\n";
    }

    void Colonia::reporteProductividadPorEspecialidad() const {
        std::map<int, int> prod;
        std::map<int, int> conteo;

        for (const Domo* d : domos) {
            for (const Colono* c : d->getColonos()) {
                int key = static_cast<int>(c->getEspecialidad());
                prod[key] += c->getProductividad();
                conteo[key]++;
            }
        }

        std::cout << "\n--- Reporte de Productividad por Especialidad ---\n";
        for (auto& par : prod) {
            int key = par.first;
            int total = par.second;

            Especialidad esp = static_cast<Especialidad>(key);
            std::cout << "  " << especialidadToString(esp)
                << ": total=" << total
                << " (" << conteo[key] << " colonos)\n";
        }
    }

    void Colonia::estadisticasGlobales() const {
        int totalColonos = 0;
        double consumoGlobal = 0.0, capacidadGlobal = 0.0;
        int prodTotal = 0;

        for (const Domo* d : domos) {
            totalColonos += d->getNumColonos();
            consumoGlobal += d->getConsumoTotalO2();
            capacidadGlobal += d->getCapacidadO2();
            for (const Colono* c : d->getColonos()) prodTotal += c->getProductividad();
        }

        std::cout << "\n--- Estadísticas Globales ---\n"
            << "  Total colonos:       " << totalColonos << "\n"
            << std::fixed << std::setprecision(2)
            << "  Consumo O2 global:   " << consumoGlobal << " L/h\n"
            << "  Capacidad O2 global: " << capacidadGlobal << " L/h\n"
            << "  Productividad total: " << prodTotal << "\n";
    }

}