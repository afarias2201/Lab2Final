#include "Cliente.h"
#include <cstring>

Cliente::Cliente(){
    _estado = true;
}

int Cliente::getID() const{
    return _id;
}

std::string Cliente::getDNI() const{
    return _dni;
}
std::string Cliente::getNombres() const{
    return _nombres;
}
std::string Cliente::getApellidos() const{
    return _apellidos;
}
std::string Cliente::getDomicilio() const{
    return _domicilio;
}
std::string Cliente::getTelefono() const{
    return _telefono;
}
std::string Cliente::getEmail() const{
    return _email;
}
bool Cliente::getEstado() const{
    return _estado;
}

void Cliente::setID(int id){
    _id = id;
}

void Cliente::setDNI(std::string dni){
    strcpy(_dni, dni.c_str());
}
void Cliente::setNombres(std::string nombres){
    strcpy(_nombres, nombres.c_str());
}
void Cliente::setApellidos(std::string apellidos){
    strcpy(_apellidos, apellidos.c_str());
}
void Cliente::setDomicilio(std::string domicilio){
    strcpy(_domicilio, domicilio.c_str());
}
void Cliente::setTelefono(std::string telefono){
    strcpy(_telefono, telefono.c_str());
}
void Cliente::setEmail(std::string email){
   strcpy(_email, email.c_str());
}
void Cliente::setEstado(bool estado){
    _estado = estado;
}
