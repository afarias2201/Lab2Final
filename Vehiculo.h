#ifndef VEHICULO_H
#define VEHICULO_H
#include <string>


class Vehiculo
{
    public:
        Vehiculo(std::string patente, std::string modelo, int marca, int tipo, int anio, bool enTaller, bool activo);
        Vehiculo();
        ///Getters de las propiedades.
        std::string getPatente() const;
        std::string getModelo() const;
        int getIDMarca() const;
        int getTipo() const;
        int getAnioDeProduccion() const;
        float getTarifaDiaria() const;
        bool getEnTaller() const;
        bool getEstado() const;
        std::string getTipoString() const;

        void setPatente(std::string patente);
        void setModelo(std::string modelo);
        void setIdMarca(int marca);
        void setTipo(int tipo);
        void setAnioProduccion(int anio);
        void setTarifaDiaria(float tarifa);
        void setEnTaller(bool enTaller);
        void setEstado(bool activo);


    private:
        char _patente[10];
        char _modelo[10];
        int _idMarca;
        int _tipo; ///1- Gama baja, 2- Gama media, 3-Gama alta
        int _anioDeProduccion;
        float _tarifaDiaria;
        bool _enTaller;
        bool _activo;
};

#endif // VEHICULO_H
