#include "MenuCopiaYRestauracionDatos.h"
#include "rlutil.h"
#include "MenuCliente.h"
#include <iostream>
using namespace std;

void MenuCopiaYRestauracionDatos::Mostrar(){
    int opc;
    while(true)
    {
        system("cls");
        cout << "------------------------------------------------------" << endl;
        cout << "----------COPIAS DE SEGURIDAD Y RESTAURACIÓN----------" << endl;
        cout << "------------------------------------------------------" << endl;
        rlutil::locate(4, 5);cout << "1 - COPIA DE SEGURIDAD CLIENTES" << endl;
        rlutil::locate(4, 6);cout << "2 - RESTAURAR COPIA DE SEGURIDAD CLIENTES" << endl << endl;
        rlutil::locate(4, 8);cout << "3 - COPIA DE SEGURIDAD RESERVAS" << endl;
        rlutil::locate(4, 9);cout << "4 - RESTAURAR COPIA DE SEGURIDAD RESERVAS" << endl << endl;
        rlutil::locate(4, 11);cout << "5 - COPIA DE SEGURIDAD VEHÍCULOS" << endl;
        rlutil::locate(4, 12);cout << "6 - RESTAURAR COPIA DE SEGURIDAD VEHÍCULOS" << endl << endl;
        rlutil::locate(4, 14);cout << "7 - COPIA DE SEGURIDAD MARCAS" << endl;
        rlutil::locate(4, 15);cout << "8 - RESTAURAR COPIA DE SEGURIDAD MARCAS" << endl << endl;
        rlutil::locate(4, 17);cout << "9 - COPIA DE SEGURIDAD TODOS LOS ARCHIVOS" << endl;
        rlutil::locate(4, 18);cout << "10 - RESTAURAR COPIA DE SEGURIDAD TODOS LOS ARCHIVOS" << endl << endl;
        rlutil::locate(4, 20);cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
        cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _clienteManager.HacerCopiaSeguridad();
            break;
        case 2:
            _clienteManager.RestaurarCopiaSeguridad();
            break;
        case 3:
            _reservaManager.HacerCopiaSeguridad();
            break;
        case 4:
            _reservaManager.RestaurarCopiaSeguridad();
            break;
        case 5:
            _vehiculoManager.HacerCopiaSeguridad();
            break;
        case 6:
            _vehiculoManager.RestaurarCopiaDeSeguridad();
            break;
        case 7:
            _marcaManager.HacerCopiaSeguridad();
            break;
        case 8:
            _marcaManager.RestaurarCopiaSeguridad();
            break;
        case 9:
            _clienteManager.HacerCopiaSeguridad();
            _reservaManager.HacerCopiaSeguridad();
            _vehiculoManager.HacerCopiaSeguridad();
            _marcaManager.HacerCopiaSeguridad();
            break;
        case 10:
            _clienteManager.RestaurarCopiaSeguridad();
            _reservaManager.RestaurarCopiaSeguridad();
            _vehiculoManager.RestaurarCopiaDeSeguridad();
            _marcaManager.RestaurarCopiaSeguridad();
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
