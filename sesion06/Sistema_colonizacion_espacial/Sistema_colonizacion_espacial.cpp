#include <iostream>
#include "Colonia.h"
#include "Colono.h"
#include "Domo.h"

using namespace colonia;

void separador(const std::string& titulo) {
    std::cout << "\n\n############################################\n";
    std::cout << "  " << titulo << "\n";
    std::cout << "############################################\n";
}

int main() {

 
    separador("1. Creando colonos");

    Colono* colonos[8];
    colonos[0] = new Colono(1, "Ana Torres", Especialidad::BIOLOGO, 4.5, 85);
    colonos[1] = new Colono(2, "Bruno Meza", Especialidad::INGENIERO, 5.0, 90);
    colonos[2] = new Colono(3, "Carla Vega", Especialidad::MEDICO, 3.8, 78);
    colonos[3] = new Colono(4, "Diego Solis", Especialidad::GEOLOGO, 4.2, 72);
    colonos[4] = new Colono(5, "Elena Rojas", Especialidad::PILOTO, 5.5, 88);
    colonos[5] = new Colono(6, "Fabio Nunez", Especialidad::INGENIERO, 6.0, 91);
    colonos[6] = new Colono(7, "Gabriela Perez", Especialidad::BIOLOGO, 3.5, 80);
    colonos[7] = new Colono(8, "Hugo Vargas", Especialidad::MEDICO, 4.0, 76);

    for (int i = 0; i < 8; i++) colonos[i]->mostrar();

  
    separador("2. Creando colonia y domos");

    std::vector<ConfigDomo> config = {
        {"LAB-01",  TipoDomo::LABORATORIO, 15.0, 3},  // lab: biólogos, médicos, geólogos
        {"ING-01",  TipoDomo::INGENIERIA,  18.0, 3},  // ing: ingenieros, pilotos
        {"HAB-01",  TipoDomo::HABITAT,     25.0, 4},  // hábitat: todos
    };

    Colonia marte("Nueva Esperanza", "Marte", config);
    std::cout << "Colonia '" << marte.getNombre()
        << "' en " << marte.getPlaneta() << " creada con "
        << marte.getDomos().size() << " domos.\n";

   
    separador("3. Asignación inteligente de colonos");

    for (int i = 0; i < 8; i++) marte.asignarColono(colonos[i]);

    marte.mostrarTableroControl();

   
    separador("4. Alertas de oxígeno (umbral 1.5)");
    marte.alertaOxigeno(1.5);

  
    separador("5. Transferencias");

    // Intentar transferir un biólogo (Ana Torres #1) a domo Ingeniería → debe fallar
    std::cout << "Intentando transferir biologo al domo de Ingenieria (debe fallar):\n";
    marte.transferirColono(1, "ING-01");

    // Intentar transferir el ingeniero Bruno (#2) al hábitat → puede funcionar
    std::cout << "\nIntentando transferir ingeniero al Habitat:\n";
    marte.transferirColono(2, "HAB-01");

    marte.mostrarTableroControl();

 
    separador("6. Evacuacion de emergencia del domo LAB-01");

    auto resEvac = marte.evacuarDomo("LAB-01");
    std::cout << "\nResultado evacuacion:\n"
        << "  Evacuados: " << resEvac.totalEvacuados << "\n"
        << "  No reubicados: " << resEvac.noReubicados << "\n";
    if (!resEvac.colonosSinDomo.empty()) {
        std::cout << "  Colonos sin domo:\n";
        for (Colono* c : resEvac.colonosSinDomo) c->mostrar();
    }

    marte.mostrarTableroControl();

 
    separador("7. Rebalanceo de colonia");

    auto resRebal = marte.rebalancear();
    std::cout << "\nColonos rebalanceados: " << resRebal.colonosMovidos << "\n";

    marte.mostrarTableroControl();

  
    separador("8. Reporte final");

    marte.reporteProductividadPorEspecialidad();
    marte.estadisticasGlobales();

    // Buscar un colono
    std::cout << "\nBuscando colono #3 (Carla Vega):\n";
    auto ubicacion = marte.buscarColono(3);
    if (ubicacion.colono) {
        std::cout << "  Encontrado en domo [" << ubicacion.domo->getCodigo() << "]\n";
        ubicacion.colono->mostrar();
    }
    else {
        std::cout << "  No esta asignado a ninguSn domo.\n";
    }


    separador("9. Liberando memoria");

    // Primero liberar colonos (independientes de la colonia)
    for (int i = 0; i < 8; i++) {
        delete colonos[i];
        colonos[i] = nullptr;
    }

  
    std::cout << "Memoria liberada correctamente. Sin fugas.\n";

    return 0;
}