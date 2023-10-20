#include "Reserva.h"
#include <algorithm>
#include <cstring>

Reserva::Reserva(){
    _estado = true;
}
Reserva::Reserva(std::string patenteVehiculo, float importeAlquiler, Fecha fechaInicio, Fecha fechaFin, bool estado){
    strcpy(_patenteVehiculo, patenteVehiculo.c_str());
    _importeAlquiler = importeAlquiler;
    _fechaInicio = fechaInicio;
    _fechaFin = fechaFin;
    _estado = estado;
}

int Reserva::getIdReserva() const{
    return _idReserva;
}
std::string Reserva::getPatenteVehiculo() const{
    return _patenteVehiculo;
}
float Reserva::getImporteAlquiler() const{
    return _importeAlquiler;
}
Fecha Reserva::getFechaInicio() const{
    return _fechaInicio;
}
Fecha Reserva::getFechaFin() const{
    return _fechaFin;
}
bool Reserva::getEstado() const{
    return _estado;
}

void Reserva::setIdReserva(int idReserva){
    _idReserva = idReserva;
}

void Reserva::setPatenteVehiculo(std::string patenteVehiculo){
    transform(patenteVehiculo.begin(), patenteVehiculo.end(), patenteVehiculo.begin(), ::toupper);
    strcpy(_patenteVehiculo, patenteVehiculo.c_str());
}
void Reserva::setImporteAlquiler(float importeAlquiler){
    _importeAlquiler = importeAlquiler;
}
void Reserva::setFechaInicio(Fecha fechaInicio){
    _fechaInicio = fechaInicio;
}
void Reserva::setFechaFin(Fecha fechafin){
    _fechaFin = fechafin;
}
void Reserva::setEstado(bool estado){
    _estado = estado;
}
