#include <iostream>
#include <string>
#include <limits>
#include "Flota.h"
#include "Vehiculo.h"

using namespace UNA;


void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void mostrarMenu() {
    std::cout << "\n+==========================================+\n";
    std::cout << "|   SISTEMA DE CONTROL DE FLOTA VEHICULAR  |\n";
    std::cout << "+==========================================+\n";
    std::cout << "|  1. Registrar vehiculo                   |\n";
    std::cout << "|  2. Buscar vehiculo por placa            |\n";
    std::cout << "|  3. Mostrar vehiculos por marca          |\n";
    std::cout << "|  4. Registrar kilometros                 |\n";
    std::cout << "|  5. Desactivar vehiculo                  |\n";
    std::cout << "|  6. Reactivar vehiculo                   |\n";
    std::cout << "|  7. Eliminar vehiculo (dar de baja)      |\n";
    std::cout << "|  8. Mostrar flota completa               |\n";
    std::cout << "|  9. Cantidad de vehiculos activos        |\n";
    std::cout << "| 10. Salir                                |\n";
    std::cout << "+==========================================+\n";
    std::cout << "  Seleccione una opcion: ";
}

// Opciones del menú 
void opcionRegistrar(Flota& flota) {
    std::string placa, marca;
    int anio;
    double km;

    std::cout << "\n--- REGISTRAR VEHICULO ---\n";
    std::cout << "Placa       : "; std::getline(std::cin, placa);
    std::cout << "Marca       : "; std::getline(std::cin, marca);
    std::cout << "Año         : "; std::cin >> anio;  limpiarBuffer();
    std::cout << "Kilometraje : "; std::cin >> km;    limpiarBuffer();

    Vehiculo* v = new Vehiculo(placa, marca, anio, km);
    flota.agregar(v);
}

void opcionBuscarPlaca(Flota& flota) {
    std::string placa;
    std::cout << "\n--- BUSCAR POR PLACA ---\n";
    std::cout << "Ingrese la placa: "; std::getline(std::cin, placa);

    Vehiculo* v = flota.buscarPorPlaca(placa);
    if (v) {
        v->mostrar();
    }
    else {
        std::cout << "[INFO] No se encontro el vehiculo con placa \"" << placa << "\".\n";
    }
}

void opcionMostrarPorMarca(Flota& flota) {
    std::string marca;
    std::cout << "\n--- MOSTRAR POR MARCA ---\n";
    std::cout << "Ingrese la marca: "; std::getline(std::cin, marca);
    flota.mostrarPorMarca(marca);
}

void opcionRegistrarKm(Flota& flota) {
    std::string placa;
    double km;
    std::cout << "\n--- REGISTRAR KILOMETROS ---\n";
    std::cout << "Placa del vehiculo : "; std::getline(std::cin, placa);

    Vehiculo* v = flota.buscarPorPlaca(placa);
    if (!v) {
        std::cout << "[ERROR] Vehiculo no encontrado.\n";
        return;
    }
    std::cout << "Kilometros a agregar: "; std::cin >> km; limpiarBuffer();
    v->registrarKilometros(km);
}

void opcionDesactivar(Flota& flota) {
    std::string placa;
    std::cout << "\n--- DESACTIVAR VEHICULO ---\n";
    std::cout << "Placa del vehiculo: "; std::getline(std::cin, placa);

    Vehiculo* v = flota.buscarPorPlaca(placa);
    if (!v) { std::cout << "[ERROR] Vehiculo no encontrado.\n"; return; }
    v->desactivar();
}

void opcionReactivar(Flota& flota) {
    std::string placa;
    std::cout << "\n--- REACTIVAR VEHICULO ---\n";
    std::cout << "Placa del vehiculo: "; std::getline(std::cin, placa);

    Vehiculo* v = flota.buscarPorPlaca(placa);
    if (!v) { std::cout << "[ERROR] Vehiculo no encontrado.\n"; return; }
    v->reactivar();
}

void opcionEliminar(Flota& flota) {
    std::string placa;
    std::cout << "\n--- ELIMINAR VEHICULO ---\n";
    std::cout << "Placa del vehiculo a dar de baja: "; std::getline(std::cin, placa);
    flota.eliminar(placa);
}


int main() {
    Flota flota;
    int opcion = 0;

    do {
        mostrarMenu();
        std::cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
        case 1:  opcionRegistrar(flota);       break;
        case 2:  opcionBuscarPlaca(flota);     break;
        case 3:  opcionMostrarPorMarca(flota); break;
        case 4:  opcionRegistrarKm(flota);     break;
        case 5:  opcionDesactivar(flota);      break;
        case 6:  opcionReactivar(flota);       break;
        case 7:  opcionEliminar(flota);        break;
        case 8:  flota.mostrarTodos();         break;
        case 9:
            std::cout << "\n[INFO] Vehiculos activos: "
                << flota.contarActivos() << "\n";
            break;
        case 10:
            std::cout << "\nSaliendo del sistema. Hasta luego.\n";
            break;
        default:
            std::cout << "[ERROR] Opcion invalida. Intente de nuevo.\n";
        }

    } while (opcion != 10);

    return 0;
}