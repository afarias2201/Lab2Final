#include "Vehiculo.h"
#include <cstring>

Vehiculo::Vehiculo(std::string patente, std::string modelo, std::string marca, int tipo, int anio, bool enTaller, bool estado){
    strcpy(_patente, patente.c_str());
    strcpy(_modelo, modelo.c_str());
    strcpy(_marca, marca.c_str());
    _tipo = tipo;
    _anioDeProduccion = anio;
    _enTaller = enTaller;
    _activo = estado;
}

Vehiculo::Vehiculo(){
    _activo = true;
}

std::string Vehiculo::getPatente()const{
    return _patente;
}

std::string Vehiculo::getModelo()const{
    return _modelo;
}

std::string Vehiculo::getMarca() const{
    return _marca;
}
int Vehiculo::getTipo() const{
    return _tipo;
}

std::string Vehiculo::getTipoString() const{
    if(_tipo == 1){
        return "Gama Baja";
    }
    if(_tipo == 2){
        return "Gama Media";
    }
    if(_tipo == 3){
        return "Gama Alta";
    }
}

int Vehiculo::getAnioDeProduccion() const{
    return _anioDeProduccion;
}

bool Vehiculo::getEnTaller() const{
    return _enTaller;
}
bool Vehiculo::getEstado() const{
    return _activo;
}

void Vehiculo::setPatente(std::string patente){
    strcpy(_patente, patente.c_str());
}
void Vehiculo::setModelo(std::string modelo){
    strcpy(_modelo, modelo.c_str());
}
void Vehiculo::setMarca(std::string marca){
    strcpy(_marca, marca.c_str());
}
void Vehiculo::setTipo(int tipo){
    _tipo = tipo;
}
void Vehiculo::setAnioProduccion(int anio){
    _anioDeProduccion = anio;
}
void Vehiculo::setEnTaller(bool enTaller){
    _enTaller = enTaller;
}
void Vehiculo::setEstado(bool activo){
    _activo = activo;
}
