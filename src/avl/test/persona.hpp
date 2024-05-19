#include<fstream>
#include<iostream>
#include<cstring>
#include<vector>

struct Persona{
    int dni;
    char nombre[100];
    char apellido[100];
    char carrera[100];
    int edad;
    int numero;
    float estatura;
    float peso;
    bool removed = false;
    explicit Persona(int dni,const char* nombre, const char* apellido, const char* carrera, int edad, int numero, float estatura, float peso){
        strcpy(this->nombre, nombre);
        strcpy(this->apellido, apellido);
        strcpy(this->carrera, carrera);
        this->dni = dni;
        this->edad = edad;
        this->numero = numero;
        this->estatura = estatura;
        this->peso = peso;
    }
    explicit Persona(){}
};

std::ostream& operator<<(std::ostream& os, const Persona& persona);
