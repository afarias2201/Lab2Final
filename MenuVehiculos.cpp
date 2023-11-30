#include "MenuVehiculos.h"
#include <iostream>
using namespace std;
#include "rlutil.h"

void MenuVehiculos::Mostrar(){
    int opc;
    while(true)
    {
        system("cls");
        cout << "-------------------------------------------" << endl;
        cout << "--------------MENU DE VEHICULOS------------" << endl;
        cout << "-------------------------------------------" << endl;
        rlutil::locate(4, 5);cout << "1 - CARGAR" << endl;
        rlutil::locate(4, 6);cout << "2 - EDITAR" << endl;
        rlutil::locate(4, 7);cout << "3 - ELIMINAR" << endl;
        rlutil::locate(4, 8);cout << "4 - LISTADO DE VEHICULOS" << endl;
        rlutil::locate(4, 9);cout << "5 - BUSCAR POR PATENTE" << endl;
        rlutil::locate(4, 10);cout << "6 - INGRESO A TALLER" << endl;
        rlutil::locate(4, 11);cout << "7 - RETIRO DE TALLER" << endl;
        rlutil::locate(4, 12);cout << "8 - ACCEDER A LISTADOS DE VEHICULOS" << endl;
        rlutil::locate(4, 13);cout << "9 - ABM MARCAS" << endl;
        rlutil::locate(4, 14);cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
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
            _manager.ListarxPatente();
            break;
        case 6:
            _manager.VehiculoIngresaTaller();
            break;
        case 7:
            _manager.VehiculoRetiroDeTaller();
            break;
        case 8:
            _menuListados.Mostrar();
            break;
        case 9:
            _menuMarcas.Mostrar();
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
