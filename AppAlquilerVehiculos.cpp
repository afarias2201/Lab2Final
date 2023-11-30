#include "AppAlquilerVehiculos.h"
#include "VehiculoManager.h"
#include <iostream>
#include "rlutil.h"
using namespace std;

void AppAlquilerVehiculos::Ejecutar(){
    int opc;
    VehiculoManager _manager;
    while(true)
    {
        system("cls");
        cout << "-------------------------------------------------------------" << endl;
        cout << "---------SISTEMA DE GESTION DE ALQUILER DE VEHÍCULOS---------" << endl;
        cout << "-------------------------------------------------------------" << endl;
        rlutil::locate(4, 5); cout << "1 - RESERVAS" << endl;
        rlutil::locate(4, 6); cout << "2 - VEHÍCULOS" << endl;
        rlutil::locate(4, 7); cout << "3 - CLIENTES" << endl;
        rlutil::locate(4, 8); cout << "4 - REPORTES" << endl;
        rlutil::locate(4, 9); cout << "5 - DISPONIBILIDAD DE VEHÍCULOS" << endl;
        rlutil::locate(4, 10); cout << "6 - COPIAS DE SEGURIDAD Y RESTAURACIÓN DE DATOS" << endl;
        rlutil::locate(4, 11); cout << "7 - RESTAURAR REGISTROS ELIMINADOS" << endl;
        rlutil::locate(4, 12); cout << "0 - CERRAR PROGRAMA" <<endl;
        rlutil::locate(4, 13); cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _menuReserva.Mostrar();
            break;
        case 2:
            _menuVehiculos.Mostrar();
            break;
        case 3:
            _menuCliente.Mostrar();
            break;
        case 4:
            _menuReportes.Mostrar();
            break;
        case 5:
            _manager.generarDisponibilidad();
            break;
        case 6:
            _menuCopiaRestauracion.Mostrar();
            break;
        case 7:
            _menuRecuperarRegistros.Mostrar();
            break;
        case 0:
            return ;
            break;
        default:
            cout << "Opcion ingresada es incorrecta." << endl << "Intente nuevamente." << endl;
            break;
        }
        // system("pause");
    }
}
