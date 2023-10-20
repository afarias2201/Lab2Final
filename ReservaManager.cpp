#include "ReservaManager.h"
#include <iostream>
#include <algorithm>
using namespace std;

void ReservaManager::Cargar(){
    int id;
    string patenteVehiculo;
    float importeAlquiler;
    int diaInicio, mesInicio, anioInicio, diaFin, mesFin, anioFin;

    cout << "Por favor, ingrese los datos de la reserva." << endl;
    cout << "-------------------------------------------" << endl;

    id = generarReservaId();
    cout << "ID a generar: " << id << endl;
    cout << "Patente del vehiculo a alquilar: ";
    cin >> patenteVehiculo;
    transform(patenteVehiculo.begin(), patenteVehiculo.end(), patenteVehiculo.begin(), ::toupper);

    if(_vehiculoManager.Buscar(patenteVehiculo) == -1){
        cout << "El vehiculo no existe." << endl;
        cout << "Carga de reserva cancelada." << endl;
        return;
    }

    cout << "Importe total de la reserva: $";
    cin >> importeAlquiler;
    cout << "Fecha de Inicio: ";
    cin >> diaInicio;
    cin >> mesInicio;
    cin >> anioInicio;
    cout << "Fecha de Fin: ";
    cin >> diaFin;
    cin >> mesFin;
    cin >> anioFin;

    Reserva reg;
    reg.setIdReserva(id);
    reg.setPatenteVehiculo(patenteVehiculo);
    reg.setImporteAlquiler(importeAlquiler);
    reg.setFechaInicio(Fecha(diaInicio, mesInicio, anioInicio));
    reg.setFechaFin(Fecha(diaFin, mesFin, anioFin));
    reg.setEstado(true);

    int cantidadReservasConMismaPatente = contarReservasxPatentes(patenteVehiculo);
    if(cantidadReservasConMismaPatente != 0){
        Reserva* reservasConMismaPatente;
        reservasConMismaPatente = new Reserva[cantidadReservasConMismaPatente];
        if(reservasConMismaPatente == nullptr){
            cout << endl << "Error en memoria dinamica. Carga cancelada." << endl;
            return;
        }
        CargarVectorPorNroPatente(patenteVehiculo, cantidadReservasConMismaPatente, reservasConMismaPatente);
        for(int i=0; i<cantidadReservasConMismaPatente; i++){
            if(reg.getFechaInicio() > reservasConMismaPatente[i].getFechaInicio() && reg.getFechaInicio() < reservasConMismaPatente[i].getFechaFin()){
                cout << "El vehiculo no se encuentra disponible para las fechas indicadas. Carga canceladad." << endl;
                return;
            }
        }
        delete []reservasConMismaPatente;
    }

    Mostrar(reg);
    char confirmacion;
    cout << endl << "Desea guardar el siguiente registro (S/N)?: " << endl;
    cin >> confirmacion;

    if(toupper(confirmacion) == 'S'){
        bool guardado = _archivo.Guardar(reg);
        if(guardado){
            cout << "Registro guardado con satisfactoriamente";
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

void ReservaManager::Eliminar(){
    int id, posicion;

    cout << "Ingrese ID de reserva a eliminar: #";
    cin >> id;
    posicion = Buscar(id);
    if(posicion >= 0){
        Reserva reg = _archivo.Leer(posicion);
        cout << "Registro a eliminar: " << endl;
        Mostrar(reg);

        char confirmacion;
        cout << endl << "¿Desea continuar. El registro sera elimiando (S/N): ";
        cin >> confirmacion;

        if(toupper(confirmacion) == 'S'){
            reg.setEstado(false);
            _archivo.Guardar(reg, posicion);
            cout << endl << "Reserva eliminada correctamente.";
        }
        else{
            cout << "No se han regitrado cambios." << endl;
        }
    }
    else{
        cout << "Registro no encontrado. No se han realizado cambios." << endl;
    }
}

void ReservaManager::Mostrar(Reserva reg){
    cout << "---------------------------" << endl;
    cout << "ID Reserva: " << reg.getIdReserva() << endl;
    cout << "Vehiculo alquilado: " << reg.getPatenteVehiculo() << endl;
    cout << "Importe del contrato: " << reg.getImporteAlquiler() << endl;
    cout << "Fecha de Inicio: " << reg.getFechaInicio().toString() << endl;
    cout << "Fecha de Fin: " << reg.getFechaFin().toString() << endl;
}

void ReservaManager::ListarTodos(){
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++){
        Mostrar(_archivo.Leer(i));
    }
    cout << endl;
}

int ReservaManager::Buscar(int idReserva){
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++){
        Reserva reg = _archivo.Leer(i);
        if(idReserva == reg.getIdReserva()){
            return i;
        }
    }
    return -1;
}

void ReservaManager::ListarxID(){
    int id, posicion;
    cout << "Ingrese ID de Reserva a buscar: ";
    cin >> id;
    posicion = _archivo.Buscar(id);
    if (posicion >= 0){
        Reserva reg = _archivo.Leer(posicion);
        Mostrar(reg);
    }
    else{
        cout << "ID de Reserva no encontrado.";
    }
    cout << endl;
}

int ReservaManager::generarReservaId(){
    return _archivo.contarRegistros() + 1;
}

//Se cuentan las cantidad de reservas con la misma patente para validar existencias.
//Si existen reservar, se validará las fechas de inicio y fin para corroborar que el vehiculo esté disponible
int ReservaManager::contarReservasxPatentes(std::string patente){
    int cantidadRegistrso = _archivo.contarRegistros();
    int cantidad = 0;
    for(int i=0; i<cantidadRegistrso; i++){
        Reserva reg = _archivo.Leer(i);
        if(patente == reg.getPatenteVehiculo() && reg.getEstado()){
            cantidad++;
        }
    }
    return cantidad;
}

void ReservaManager::CargarVectorPorNroPatente(std::string patente, int cantidadElementos, Reserva* vec){
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadElementos; i++){
        for(int x=0; x<cantidadRegistros; x++){
            Reserva reg = _archivo.Leer(x);
            if(patente == reg.getPatenteVehiculo() && reg.getEstado()){
                vec[i] = reg;
            }
        }
    }
}
