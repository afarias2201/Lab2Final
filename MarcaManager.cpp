#include "MarcaManager.h"
#include <iomanip>
#include <iostream>
using namespace std;

void MarcaManager::Cargar(){
    int id;
    string nombre;

    cout << "Ingrese los datos de la nueva marca." << endl;
    id = generarIdMarca();
    cout << endl << "ID: " << id << endl;
    cout << "Nombre: ";
    cin >> nombre;

    if(_archivo.Buscar(nombre) != -1){
        cout << "Marca ya registrada." << endl;
        return;
    }

    Marca reg;
    reg.setID(id);
    reg.setNombre(nombre);
    reg.setActivo(true);

    char confirmacion;
    cout << endl;
    Mostrar(reg);
    cout << endl << "Desea guardar el siguiente registro (S/N): " << endl;
    cin >> confirmacion;

    if(toupper(confirmacion) == 'S'){
        if(_archivo.Guardar(reg)){
            cout << "Registro guardado correctamente." << endl;
        }
        else{
            cout << "Error al guardar el registro. Operación cancelada." << endl;
        }
    }
    else{
        cout << "Operación cancelada." << endl;
    }
}
void MarcaManager::Eliminar(){
    int id, posicion;
    cout << "Ingrese ID de marca a eliminar: ";
    cin >> id;
    posicion = _archivo.Buscar(id);
    if(posicion >= 0){
        Marca marca = _archivo.Leer(posicion);
        cout << "Marca a eliminar: " << endl;
        Mostrar(marca);
        cout << endl << "¿Desea continuar? (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if(toupper(confirmacion) == 'S'){
            marca.setActivo(false);
            bool eliminado = _archivo.Guardar(marca, posicion);
            if(eliminado){
                cout << "Registro eliminado correctamente." << endl;
            }
            else{
                cout << "Error al eliminar registro." << endl;
                return;
            }
        }
        else{
            cout << "Operación canceladad." << endl;
        }
    }
    else{
        cout << "ID inexistente." << endl;
    }
}
void MarcaManager::Editar(){
    int id, posicion;
    string nombre;
    cout << "Ingrese ID de marca a editar: ";
    cin >> id;
    posicion = _archivo.Buscar(id);
    if(posicion >= 0){
        Marca marca = _archivo.Leer(posicion);
        cout << "Marca a editar: " << endl;
        Mostrar(marca);

        cout << endl << "Ingrese el nuevo nombre: ";
        cin >> nombre;
        marca.setNombre(nombre);

        cout << endl << "¿Desea continuar? (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if(toupper(confirmacion) == 'S'){
            bool eliminado = _archivo.Guardar(marca, posicion);
            if(eliminado){
                cout << "Registro eliminado correctamente." << endl;
                Mostrar(marca);
            }
            else{
                cout << "Error al eliminar registro." << endl;
                return;
            }
        }
        else{
            cout << "Operación canceladad." << endl;
        }
    }
    else{
        cout << "ID inexistente." << endl;
    }
}
void MarcaManager::ListarTodos(){
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++){
        Marca marca = _archivo.Leer(i);
        if(marca.getActivo()){
            Mostrar(marca);
            cout << endl;
        }
    }
    cout << endl;
}

void MarcaManager::Mostrar(Marca reg){
    cout << left << setw(5) << reg.getID();
    cout << left << setw(5) << reg.getNombre();
}

void MarcaManager::HacerCopiaSeguridad(){
    int cantidadRegistros = _archivo.contarRegistros();
    Marca* marcas = new Marca[cantidadRegistros];
    if(marcas == nullptr){
        cout << "Error de memoria al realizar backup." << endl;
        return;
    }

    _archivo.Leer(marcas, cantidadRegistros);
    _archivobkp.Vaciar();

    if(_archivobkp.Guardar(marcas, cantidadRegistros)){
        cout << "BKP realizado correctamente." << endl;
    }
    else{
        cout << "Error al realizar BKP." << endl;
    }
    delete[] marcas;
}
void MarcaManager::RestaurarCopiaSeguridad(){
    int cantidadRegistros = _archivobkp.contarRegistros();
    Marca* marcas = new Marca[cantidadRegistros];
    if(marcas == nullptr){
        cout << "Error de memoria al restaurar backup" << endl;
        return;
    }

    _archivobkp.Leer(marcas, cantidadRegistros);
    _archivo.Vaciar();

    if(_archivo.Guardar(marcas, cantidadRegistros)){
        cout << "BKP restaurado correctamente." << endl;
    }
    else{
        cout << "Error al restaurar BKP." << endl;
    }
    delete[] marcas;
}

int MarcaManager::generarIdMarca(){
    return _archivo.contarRegistros() + 1;
}

void MarcaManager::RecuperarRegistroElimiando(){
    int cantidadRegistros = _archivo.contarRegistros();
    int id;
    cout << "Registros eliminados: " << endl;
    for(int i=0; i<cantidadRegistros; i++){
        Marca marca = _archivo.Leer(i);
        if(!marca.getActivo()){
            Mostrar(marca);
        }
    }
    cout << endl << "Ingrese ID de marca a recuperar: ";
    cin >> id;
    int posicion = _archivo.Buscar(id);
    if(posicion == -1){
        cout << "Registro no encontrado.";
    }
    Marca reg = _archivo.Leer(posicion);
    if(!reg.getActivo()){
        cout << "Registro a recuperar: " << endl;
        Mostrar(reg);
        cout << endl << "¿Desea continuar? (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if(toupper(confirmacion) == 'S'){
            reg.setActivo(true);
            if(_archivo.Guardar(reg, posicion)){
                cout << "Registro recuperado correctamente." << endl;
                return;
            }
            else{
                cout << "Error al recuperar registro." << endl;
            }
        }
        else{
            cout << "Operacion cancelada." << endl;
        }
    }
    else{
        cout << "El registro no se encuentra eliminado." << endl;
    }
}
