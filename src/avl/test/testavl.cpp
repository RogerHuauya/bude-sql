#include "../avl.hpp"
#include <cstdlib>
#include <iostream>
#include "persona.hpp"

using namespace std;

greater<int> cmp;

function<int(Persona &)> index_dni = [](Persona& p) -> int {return p.dni;};
function<int(Persona &)> index_edad = [](Persona& p) -> int {return p.edad;};

void test_dni(){
    AVLFile<int, Persona, decltype(index_dni), decltype(cmp)> avl("personas.dat","dni",index_dni, cmp);
    if (!avl){
        avl.create_index();
        cout << "INDICE CREADO" << endl;
    }

    Persona p(77866655, "Alvamau", "Garcia", "CS", 19, 123, 1.80, 70);
    cout << "INSERTANDO UN NUEVO REGISTRO CON DNI: " << p.dni << endl;
    avl.insert(p);
    avl.print();

    vector<Persona> res;
    cout << "BUSQUEDA POR DNI A LA PERSONA CON DNI 12345678" << endl;
    res = std::move(avl.search(12345678));
    for (auto &p : res){
        cout << p << endl;
    }

    cout << "BUSQUEDA POR RANGO DE DNIs ENTRE 10000000 Y 20000000" << endl;
    res = std::move(avl.range_search(10000000, 20000000));
    for (auto &p : res){
        cout << p << endl;
    }

    vector<Persona> ordenado = std::move(avl.inorder());
    cout << "\nIN ORDER TRAVERSAL USANDO DNI COMO LLAVE DE ORDENACION" << endl;
    for (auto &p : ordenado){
        cout << p << endl;
    }

    cout << "ELIMINANDO 12345678 y 77766655" << endl;
    avl.remove(12345678);
    avl.remove(77766655);

    ordenado = std::move(avl.inorder());
    cout << "\nIN ORDER DESPUES DE LA ELIMINACION" << endl;
    for (auto &p : ordenado){
        cout << p << endl;
    }
    avl.print();
}

void test_age(){
    AVLFile<int, Persona, decltype(index_edad), decltype(cmp)> avl("personas.dat","edad",index_edad, cmp);
    vector<Persona> res;
    if (!avl){
        avl.create_index();
        cout << "index created" << endl;
    }

    Persona p(77866655, "Alvamau", "Garcia", "CS", 19, 123, 1.80, 70);
    cout << "INSERTANDO UN NUEVO REGISTRO CON EDAD: " << p.edad << endl;
    avl.insert(p);
    avl.print();

    cout << "BUSQUEDA POR EDAD A LA PERSONA CON EDAD 19" << endl;
    res = std::move(avl.search(19));
    for (auto &p : res){
        cout << p << endl;
    }

    cout << "BUSQUEDA POR RANGO DE EDAD ENTRE 20 Y 30" << endl;
    res = std::move(avl.range_search(20, 30));
    for (auto &p : res){
        cout << p << endl;
    }

    vector<Persona> ordenado = std::move(avl.inorder());
    cout << "\nIN ORDER TRAVERSAL USANDO EDAD COMO LLAVE DE ORDENACION" << endl;
    for (auto &p : ordenado){
        cout << p << endl;
    }

    cout << "ELIMINANDO 19, 22, 23, 24, 25 y 27" << endl;
    avl.remove(19);
    avl.remove(22);
    avl.remove(23);
    avl.remove(24);
    avl.remove(25);
    avl.remove(27);

    ordenado = std::move(avl.inorder());
    cout << "\nIN ORDER DESPUES DE LA ELIMINACION" << endl;
    for (auto &p : ordenado){
        cout << p << endl;
    }
    avl.print();

}

void test_name(){
    function<bool(char[100], char[100])> cmp_string = [](char a[100], char b[100]) -> bool { return strcmp(a,b) > 0; };
    function<char*(Persona &)> index_name = [=](Persona& p){return p.nombre;};
    AVLFile<char[100], Persona, decltype(index_name), decltype(cmp_string)> avl("personas.dat","nombre",index_name, cmp_string);
    vector<Persona> res;
    if (!avl){
        avl.create_index();
        cout << "index created" << endl;
    }

    Persona p(77866655, "Alvamau", "Garcia", "CS", 19, 123, 1.80, 70);
    cout << "INSERTANDO UN NUEVO REGISTRO CON NOMBRE: " << p.nombre << endl;
    avl.insert(p);
    avl.print();

    cout << "BUSQUEDA POR NOMBRE A LA PERSONA CON NOMBRE Alvamau" << endl;
    res = std::move(avl.search("Alvamau"));
    for (auto &p : res){
        cout << p << endl;
    }

    cout << "BUSQUEDA POR RANGO DE NOMBRES ENTRE A Y B" << endl;
    res = std::move(avl.range_search("A", "B"));
    for (auto &p : res){
        cout << p << endl;
    }

    vector<Persona> ordenado = std::move(avl.inorder());
    cout << "\nIN ORDER TRAVERSAL USANDO NOMBRE COMO LLAVE DE ORDENACION" << endl;
    for (auto &p : ordenado){
        cout << p << endl;
    }

    cout << "ELIMINANDO Alvamau" << endl;
    avl.remove("Alvamau");

    ordenado = std::move(avl.inorder());
    cout << "\nIN ORDER DESPUES DE LA ELIMINACION" << endl;
    for (auto &p : ordenado){
        cout << p << endl;
    }
    avl.print();
}

int main(){
    function<void ()> f[] = {test_dni, test_age, test_name};

    cout << "DNIs" << endl;
    cout << string(50, '-') << endl;
    f[0]();
    cout << endl <<string(50, '-') << endl;
    cout << "Edades" << endl;
    f[1]();

    cout << endl <<string(50, '-') << endl;
    cout << "Nombres" << endl;
    f[2]();

    return EXIT_SUCCESS;
}
