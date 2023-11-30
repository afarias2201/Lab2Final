#include "MenuMarcas.h"
#include <iostream>
using namespace std;
#include "rlutil.h"

void MenuMarcas::Mostrar(){
    int opc;
    while(true)
    {
        system("cls");
        cout << "------------------------------------------" << endl;
        cout << "--------------MENU DE CLIENTES------------" << endl;
        cout << "------------------------------------------" << endl;
        rlutil::locate(4, 5);cout << "1 - CARGAR" << endl;
        rlutil::locate(4, 6);cout << "2 - EDITAR" << endl;
        rlutil::locate(4, 7);cout << "3 - ELIMINAR" << endl;
        rlutil::locate(4, 8);cout << "4 - LISTADO DE MARCAS" << endl;
        rlutil::locate(4, 9);cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
        cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _marcaManager.Cargar();
            break;
        case 2:
            _marcaManager.Editar();
            break;
        case 3:
            _marcaManager.Eliminar();
            break;
        case 4:
            _marcaManager.ListarTodos();
            break;
        case 0:
            return;
            break;
        default:
            cout << "Opcion ingresada es incorrecta." << endl << "Intente nuevamente." << endl;
            break;
        }
        system("pause");
    }
}
