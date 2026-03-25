#ifndef VEHICULO_H
#define VEHICULO_H


#include <iostream>
#include <string>

namespace UNA {
	class Vehiculo
	{
	private:
		std::string placa;
		std::string marca;
		int anios;
		double kilometraje;
		bool activo;
		

	public:
		Vehiculo(std::string placa, std::string marca, int anio, double kilometraje);

		std::string getPlaca()      const;
		std::string getMarca()      const;
		int         getAnio()       const;
		double      getKilometraje()const;
		bool        isActivo()      const;

		void registrarKilometros(double km);
		void desactivar();
		void reactivar();
		void mostrar() const;

	};
}

#endif 