#include "MenuReserva.h"
#include <iostream>
using namespace std;
#include "rlutil.h"

void MenuReserva::Mostrar(){
 int opc;
    while(true)
    {
        system("cls");
        cout << "-------------------------------------------------" << endl;
        cout << "-------------------MENU DE RESERVAS--------------" << endl;
        cout << "-------------------------------------------------" << endl;

        rlutil::locate(4, 5); cout << "1 - CARGAR";
        rlutil::locate(4, 6); cout << "2 - ELIMINAR";
        rlutil::locate(4, 7); cout << "3 - LISTADO DE RESERVA";
        rlutil::locate(4, 8); cout << "4 - BUSCAR POR ID DE RESERVA";
        rlutil::locate(4, 9); cout << "5 - EXTENSIÓN DE RESERVA";
        rlutil::locate(4, 10); cout << "6 - BUSCAR POR RANGOS DE IMPORTE DE RESERVA";
        rlutil::locate(4, 11); cout << "7 - BUSCAR RESERVAS POR FECHA DE INICIO";
        rlutil::locate(4, 12); cout << "8 - LISTAR RESERVAS POR FECHA DE INICIO";
        rlutil::locate(4, 13); cout << "9 - LISTAR RESERVAS POR IMPORTE";
        rlutil::locate(4, 14); cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
        cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _manager.Cargar();
            break;
        case 2:
            _manager.Eliminar();
            break;
        case 3:
            _manager.ListarTodos();
            break;
        case 4:
            _manager.ListarxID();
            break;
        case 5:
            _manager.extenderReserva();
            break;
        case 6:
            _manager.ListarxRangoDeImporte();
            break;
        case 7:
            _manager.ListarxFechaDeInicioReserva();
            break;
        case 8:
            _manager.ReservasOrdenadasxFechaInicio();
            break;
        case 9:
            _manager.ReservasOrdenadasxImporte();
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
