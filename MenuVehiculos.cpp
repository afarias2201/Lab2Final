#include "MenuVehiculos.h"
#include <iostream>
using namespace std;

void MenuVehiculos::Mostrar(){
    int opc;
    while(true)
    {
        system("cls");
        cout << "-------------------------------------------" << endl;
        cout << "--------------MENU DE VEHICULOS------------" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "1 - CARGAR" << endl;
        cout << "2 - EDITAR" << endl;
        cout << "3 - ELIMINAR" << endl;
        cout << "4 - LISTADO DE VEHICULOS" << endl;
        cout << "5 - BUSCAR POR PATENTE" << endl;
        cout << "6 - INGRESO A TALLER" << endl;
        cout << "7 - RETIRO DE TALLER" << endl;
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
            _manager.ListarxPatente();
            break;
        case 6:
            _manager.VehiculoIngresaTaller();
            break;
        case 7:
            _manager.VehiculoRetiroDeTaller();
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
