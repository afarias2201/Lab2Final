#include "MenuCliente.h"
#include <iostream>
using namespace std;

void MenuCliente::Mostrar(){
    int opc;
    while(true)
    {
        system("cls");
        cout << "------------------------------------------" << endl;
        cout << "--------------MENU DE CLIENTES------------" << endl;
        cout << "------------------------------------------" << endl;
        cout << "1 - CARGAR" << endl;
        cout << "2 - EDITAR" << endl;
        cout << "3 - ELIMINAR" << endl;
        cout << "4 - LISTADO DE CLIENTES" << endl;
        cout << "5 - BUSCAR POR DNI" << endl;
        cout << "6 - LISTAR ALFABÉTICAMENTE" << endl;
        cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
        cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _manager.Cargar();
            break;
        case 2:
            _manager.Editar();
            break;
        case 3:
            _manager.Eliminar();
            break;
        case 4:
            _manager.ListarTodos();
            break;
        case 5:
            _manager.ListarxDNI();
            break;
        case 6:
            _manager.ClientesOrdenadoAlfabeticamente();
            break;
        case 0:
            return ;
            break;
        default:
            cout << "Opcion ingresada es incorrecta." << endl << "Intente nuevamente." << endl;
            break;
        }
        system("pause");
    }
}
