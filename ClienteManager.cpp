#include "ClienteManager.h"
#include <iostream>
using namespace std;
#include "MenuEditarCliente.h"

void ClienteManager::Cargar(){
    int dni;
    string nombres, apellidos, domicilio, telefono, email;

    cout << "Ingrese informacion del nuevo cliente." << endl;
    cout << "Nro. de DNI: ";
    cin >> dni;
    if(Buscar(dni)!= -1){
        cout << "El nro. de DNI indicado ya existe." << endl;
        cout << "No se ha grabado el nuevo registro." << endl;
        return;
    }
    cout << "Nombres: ";
    cin.ignore();
    getline(cin, nombres);
    cout << "Apellidos: ";
    getline(cin, apellidos);
    cout << "Domicilio: ";
    getline(cin, domicilio);
    cout << "Telefono: ";
    getline(cin, telefono);
    cout << "E-mail: ";
    getline(cin, email);

    Cliente reg;
    reg.setDNI(dni);
    reg.setNombres(nombres);
    reg.setApellidos(apellidos);
    reg.setDomicilio(domicilio);
    reg.setTelefono(telefono);
    reg.setEmail(email);
    reg.setEstado(true);

    Mostrar(reg);
    char confirmacion;
    cout << endl << "Desea guardar el siguiente registro (S/N)?: " << endl;
    cin >> confirmacion;

    if(toupper(confirmacion) == 'S'){
        bool guardado = _archivo.Guardar(reg);
        if(guardado){
            cout << "Registro guardado satisfactoriamente.";
        }
        else{
            cout << "Oops, Error. No se ha podido guardar el registro.";
        }
        cout << endl;
    }
    else {
        cout << "Carga de registro cancelada." << endl;
    }
}

void ClienteManager::Editar(){
    int dni, posicion;
    cout << "Ingrese DNI del cliente a editar: ";
    cin >> dni;

    posicion = _archivo.Buscar(dni);
    if(posicion >= 0){
        Cliente reg = _archivo.Leer(posicion);
        cout << "Registro a modificar: " << endl;
        Mostrar(reg);
        MenuEditarCliente menuEditarCliente;
        menuEditarCliente.Mostrar(reg);
        _archivo.Guardar(reg, posicion);
    }
    else{
        cout << "Registro no encontrado." << endl;
    }
}

void ClienteManager::Eliminar(){
    int dni;
    int posicion;

    cout << "Ingrese nro. DNI a eliminar: ";
    cin >> dni;
    posicion = Buscar(dni);
    if(posicion >= 0){
        Cliente reg = _archivo.Leer(posicion);
        cout << "Registro a eliminar: " << endl;
        Mostrar(reg);

        char confirmacion;
        cout << endl << "¿Desea continuar. El registro sera eliminado (S/N): ";
        cin >> confirmacion;

        if(toupper(confirmacion)== 'S'){
            reg.setEstado(false);
            _archivo.Guardar(reg, posicion);
            cout << endl << "Cliente eliminado correctamente.";
        }
        else{
            cout << "No se han realizado cambios." << endl;
        }
    }
    else{
        cout << "Registro no encontrado. No se han realizado cambios." << endl;
    }
}
void ClienteManager::Mostrar(Cliente reg){
    cout << "---------------------------" << endl;
    cout << "DNI: " << reg.getDNI() << endl;
    cout << "NOMBRES: " << reg.getNombres() << endl;
    cout << "APELLIDOS: " << reg.getApellidos() << endl;
    cout << "DOMICILIO: " << reg.getDomicilio() << endl;
    cout << "TELEFONO: " << reg.getTelefono() << endl;
    cout << "E-MAIL: " << reg.getEmail() << endl;
}
void ClienteManager::ListarTodos(){
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++){
        Mostrar(_archivo.Leer(i));
    }
    cout << endl;
}
int ClienteManager::Buscar(int dni){
    int cantidadRegistros = _archivo.contarRegistros();
    for (int i=0; i<cantidadRegistros; i++){
        Cliente reg = _archivo.Leer(i);
        if(dni == reg.getDNI()){
            return i;
        }
    }
    return -1;
}
void ClienteManager::ListarxDNI(){
    int dni;
    int posicion;

    cout << "Ingrese DNI a buscar: ";
    cin >> dni;
    posicion = _archivo.Buscar(dni);
    if(posicion >= 0){
        Cliente reg = _archivo.Leer(posicion);
        Mostrar(reg);
    }
    else{
        cout << "No se pudo encontrar el DNI indicado.";
        cout << endl;
    }
}
