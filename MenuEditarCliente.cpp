#include "MenuEditarCliente.h"
#include <iostream>
using namespace std;
#include "rlutil.h"

Cliente MenuEditarCliente::Mostrar(Cliente& reg)
{
    system("cls");
    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "--------------EDITAR CLIENTE------------" << endl;
    cout << "----------------------------------------" << endl;
    rlutil::locate(4, 5);cout << "1 - NOMBRES" << endl;
    rlutil::locate(4, 6);cout << "2 - APELLIDOS" << endl;
    rlutil::locate(4, 7);cout << "3 - DOMICILIO" << endl;
    rlutil::locate(4, 8);cout << "4 - TELEFONO" << endl;
    rlutil::locate(4, 9);cout << "5 - EMAIL" << endl;
    rlutil::locate(4, 10);cout << "0 - CANCELAR" <<endl;
    cout << endl <<"INGRESE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    cin.ignore();
    switch(opcion)
    {
    case 1:
    {
        string nombres;
        cout << "Ingrese nuevos nombres: ";
        getline(cin, nombres);
        reg.setNombres(nombres);
        return reg;
    }
    break;
    case 2:
    {
        string apellidos;
        cout << "Ingrese nuevos apellidos: ";
        getline(cin, apellidos);
        reg.setApellidos(apellidos);
        return reg;
    }
    break;
    case 3:
    {
        string domicilio;
        cout << "Ingrese nuevo domicilio: ";
        getline(cin, domicilio);
        reg.setDomicilio(domicilio);
        return reg;
    }
    break;
    case 4:
    {
        string telefono;
        cout << "Ingrese nuevo telefono: ";
        getline(cin, telefono);
        reg.setTelefono(telefono);
        return reg;
    }
    break;
    case 5:
    {
        string email;
        cout << "Ingrese nuevo e-mail: ";
        getline(cin, email);
        reg.setEmail(email);
        return reg;
    }
    break;
    case 0:
        cout << "No se realizaron modificaciones." << endl;
        return reg;
    break;
    }
    system("cls");
}
