#ifndef CLIENTEMANAGER_H
#define CLIENTEMANAGER_H
#include "Cliente.h"
#include "ClienteArchivo.h"
#include "string"

class ClienteManager
{
    public:
        void Cargar();
        void Editar();
        void Eliminar();
        void Mostrar(Cliente reg);
        void ListarTodos();
        int Buscar(std::string dni);
        void ListarxDNI();

    private:
        ClienteArchivo _archivo = ClienteArchivo("clientes.dat");
        int generarIdCliente();
};

#endif // CLIENTEMANAGER_H
