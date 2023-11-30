#ifndef MARCA_H
#define MARCA_H
#include <string>


class Marca
{
    public:
        Marca();
        int getID() const;
        std::string getNombre() const;
        bool getActivo() const;
        void setID(int id);
        void setNombre(std::string nombre);
        void setActivo(bool activo);


    private:
        int _id;
        char _nombre[20];
        bool _activo;
};

#endif // MARCA_H
