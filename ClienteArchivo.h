#ifndef CLIENTEARCHIVO_
#define CLIENTEARCHIVO_
#include "Cliente.h"
#include <iostream>


class ClienteArchivo
{
    public:
        ClienteArchivo(std::string nombreArchivo);
        bool Guardar(Cliente reg);
        bool Guardar(Cliente reg, int nroRegistro);
        int contarRegistros();
        Cliente Leer(int nroRegistro);
        int Buscar(std::string dniCliente);

    private:
        std::string _nombreArchivo;
};

#endif // CLIENTEARCHIVO_
