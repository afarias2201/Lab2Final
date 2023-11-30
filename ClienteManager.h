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
        void RecuperarRegistroEliminado();

        void HacerCopiaSeguridad();
        void RestaurarCopiaSeguridad();

        //Listado
        void ClientesOrdenadoAlfabeticamente();

    private:
        ClienteArchivo _archivo = ClienteArchivo("clientes.dat");
        ClienteArchivo _archivoBkp = ClienteArchivo("clientes.bkp");
        void cargarVectorClientes(Cliente* clientes, int cantidadRegistros);
        void OrdenarVectorClientesAlfabeticamente(Cliente* clientes, int cantidadRegistros);
        int generarIdCliente();
        bool validarEmail(std::string email);
        void mostrarTituloClientes();
};

#endif // CLIENTEMANAGER_H
