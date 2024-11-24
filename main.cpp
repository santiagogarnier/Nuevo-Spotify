#include <iostream>
#include <fstream>

using namespace std;

struct Cancion
{
    string nombre;
    string artista;
    Cancion *sgte;
};

struct Registro
{
    Cancion song;
    short estrellas;
    Registro *siguiente;
};

// Prototipos de funciones
Cancion dameCancion();
Cancion *crearNodo(Cancion *&pila, Cancion tema);
void pushCancion(Cancion *&pila, Cancion tema);
Cancion popCancion(Cancion *&pila, Cancion tema);
void revertirPlaylist(Cancion *&pila);

int main()
{

    return 0;
}

Cancion dameCancion()
{
    Cancion tema;
    cout << "Ingrese un tema que desea escuchar:";
    cin >> tema.nombre;
    cout << "Artista de la cancion: ";
    cin >> tema.artista;
    return tema;
}

Cancion *crearNodo(Cancion tema)
{
    Cancion *nodoCancion = new Cancion;
    nodoCancion->nombre = tema.nombre;
    nodoCancion->sgte = nullptr;
    return nodoCancion;
}

// Agrega canciones a la pila de reproduccion, quedando primera.
void pushCancion(Cancion *&pila, Cancion tema)
{
    Cancion *nodoCancion = crearNodo(tema);
    nodoCancion->sgte = nullptr;
    pila = nodoCancion;
}

// Toma la proxima cancion de la pila (removiendola)
Cancion popCancion(Cancion *&pila)
{
    if (pila == nullptr)
    {
        cout << "La playlist esta vacia." << endl;
        Cancion cancionNula;
        cancionNula.nombre = "_";
        return cancionNula;
    }
    Cancion cancionActual = *pila;
    Cancion *temp = pila;
    pila = pila->sgte;
    delete temp;
    return cancionActual;
}

void revertirPlaylist(Cancion *&pila)
{
    Cancion *pilaaux = nullptr;
    Cancion auxiliar;
    while (pila != nullptr)
    {
        auxiliar = popCancion(pila);
        pushCancion(pilaaux,auxiliar);

    }
    pila = pilaaux;
    cout << "Se revirtio con exito la playlist.";

}

Registro *crearNodoRegistro(Cancion cancionGuardar, short estrellas)
{
   Registro* nodoRegistro = new Registro;
   nodoRegistro->estrellas = estrellas;
   nodoRegistro->song = cancionGuardar;
   nodoRegistro->siguiente = nullptr;
   return nodoRegistro;
}