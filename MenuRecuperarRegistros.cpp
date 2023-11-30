#include "MenuRecuperarRegistros.h"
#include <iostream>
using namespace std;
#include "rlutil.h"
void MenuRecuperarRegistros::Mostrar(){
        int opc;
    while(true)
    {
        system("cls");
        cout << "-------------------------------------------" << endl;
        cout << "---------------RECUPERAR DATOS-------------" << endl;
        cout << "-------------------------------------------" << endl;
        rlutil::locate(4, 5);cout << "1 - RESERVAS" << endl;
        rlutil::locate(4, 6);cout << "2 - VEHÍCULOS" << endl;
        rlutil::locate(4, 7);cout << "3 - CLIENTES" << endl;
        rlutil::locate(4, 8);cout << "4 - MARCAS" << endl;
        rlutil::locate(4, 9);cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
        cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _managerReserva.RecuperarRegistroEliminado();
            break;
        case 2:
            _managerVehiculo.RecuperarRegistroEliminado();
            break;
        case 3:
            _managerCliente.RecuperarRegistroEliminado();
            break;
        case 4:
            _managerMarca.RecuperarRegistroElimiando();
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
