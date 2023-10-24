#include "DisponibilidadFlota.h"
#include <cstring>
#include "Vehiculo.h"
#include "ReservaManager.h"
#include <iostream>

void DisponibilidadFlota::generarDisponibilidad()
{
    int cantidadVehiculos = _archivoVehiculo.contarRegistros();

    DisponibilidadFlota* vecDispo;
    vecDispo = new DisponibilidadFlota[cantidadVehiculos];
    if(vecDispo == nullptr)
    {
        std::cout << "Error de memoria." << std::endl;
        return;
    }

    for (int i=0; i<cantidadVehiculos; i++)
    {
        Vehiculo vehiculo = _archivoVehiculo.Leer(i);
        vecDispo[i].setPatenteDispo(vehiculo.getPatente());
        vecDispo[i].setMarcaDispo(vehiculo.getMarca());
        vecDispo[i].setModeloDispo(vehiculo.getModelo());
        vecDispo[i].setAnioProduccionDispo(vehiculo.getAnioDeProduccion());
        vecDispo[i].setTipoDispo(vehiculo.getTipo());

        ReservaManager reservaManager;
        int cantidadReservasPorPatente = reservaManager.contarReservasxPatentes(vehiculo.getPatente());
        if(cantidadReservasPorPatente != 0)
        {
            Reserva* reservasConMismaPatente;
            reservasConMismaPatente = new Reserva[cantidadReservasPorPatente];
            if(reservasConMismaPatente == nullptr)
            {
                std::cout << std::endl << "Error en memoria dinamica." << std::endl;
                return;
            }

            reservaManager.CargarVectorPorNroPatente(vehiculo.getPatente(), cantidadReservasPorPatente, reservasConMismaPatente);
            if(!validarSiEstaDisponibleHoy(fechaDeConsulta, reservasConMismaPatente, cantidadReservasPorPatente))
            {
                vecDispo[i].setEstadoVehiculoDispo(1);
            }
            else if(validarSiEstaDisponibleHoy(fechaDeConsulta, reservasConMismaPatente, cantidadReservasPorPatente) || cantidadReservasPorPatente == 0)
            {
                vecDispo[i].setEstadoVehiculoDispo(0);
            }
            delete[] reservasConMismaPatente;

        }
        else if(vehiculo.getEnTaller())
        {
            vecDispo[i].setEstadoVehiculoDispo(2);
        }
    }
    Mostrar(vecDispo, cantidadVehiculos);
    delete[] vecDispo;
}

void DisponibilidadFlota::setPatenteDispo(std::string patente)
{
    strcpy(_patenteDispo, patente.c_str());
}
void DisponibilidadFlota::setModeloDispo(std::string modelo)
{
    strcpy(_modeloDispo, modelo.c_str());
}
void DisponibilidadFlota::setMarcaDispo(std::string marca)
{
    strcpy(_marcaDispo, marca.c_str());
}
void DisponibilidadFlota::setAnioProduccionDispo(int anio)
{
    _anioDeProduccionDispo = anio;
}
void DisponibilidadFlota::setTipoDispo(int tipo)
{
    _tipoDispo = tipo;
}
void DisponibilidadFlota::setEstadoVehiculoDispo(int estadoVehiculo)
{
    if(estadoVehiculo == 0){
        _estadoVehiculo = 0;
    }
    if(estadoVehiculo == 1){
        _estadoVehiculo = 1;
    }
    if(estadoVehiculo == 2){
        _estadoVehiculo = 2;
    }
}

std::string DisponibilidadFlota::getPatenteDispo() const
{
    return _patenteDispo;
}
std::string DisponibilidadFlota::getModeloDispo() const
{
    return _modeloDispo;
}
std::string DisponibilidadFlota::getMarcaDispo() const
{
    return _marcaDispo;
}
int DisponibilidadFlota::getAnioProduccionDispo() const
{
    return _anioDeProduccionDispo;
}
std::string DisponibilidadFlota::getTipoDispo() const
{
    if(_tipoDispo == 1)
    {
        return "Gama baja";
    }
    else if(_tipoDispo == 2)
    {
        return "Gama media";
    }
    else
    {
        return "Gama Alta";
    }
}
std::string DisponibilidadFlota::getEstadoVehiculoDispo() const
{
    if(_estadoVehiculo == 0)
    {
        return "Disponible";
    }
    if(_estadoVehiculo == 1)
    {
        return "Alquilado";
    }
    if(_estadoVehiculo == 2)
    {
        return "En taller";
    }
}
bool DisponibilidadFlota::validarSiEstaDisponibleHoy(Fecha fechaHoy, Reserva* reserva, int cantidadElementos)
{
    for(int i=0; i<cantidadElementos; i++)
    {
        if(fechaHoy > reserva[i].getFechaInicio() && fechaHoy < reserva[i].getFechaFin())
        {
            return false;
        }
    }
    return true;
}

void DisponibilidadFlota::Mostrar(DisponibilidadFlota* vDispo, int cantidadElementos)
{
    std::cout << "Fecha de Ejecucion: " << fechaDeConsulta.toString() << std::endl << std::endl;
    for(int i=0; i<cantidadElementos; i++)
    {
        std::cout << vDispo[i].getPatenteDispo() << "   -   " << vDispo[i].getMarcaDispo() << "   -   " << vDispo[i].getModeloDispo() << "   -   " << vDispo[i].getAnioProduccionDispo() << "   -   " << vDispo[i].getEstadoVehiculoDispo() << "   -   " << vDispo[i].getTipoDispo() << std::endl << std::endl;
    }
}
