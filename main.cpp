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
void mostrarMenu();
Cancion dameCancion();
Cancion *crearNodo(Cancion *&pila, Cancion tema);
void pushCancion(Cancion *&pila, Cancion tema);
Cancion popCancion(Cancion *&pila);
void revertirPlaylist(Cancion *&pila);
Registro *crearNodoRegistro(Cancion cancionGuardar, short estrellas);
Registro *calificar_listar(Cancion cancionAgregar, Registro *historial);
void imprimirListaSimple(Registro *inicio);

int main()
{
    int menu = 0;
    Cancion *playlist = nullptr;
    Registro *historial = nullptr;
    Cancion nuevaCancion;
    Cancion cancionActual;
    cancionActual.nombre = "Primer recorrido";
    cout << "Bienvenido a Spotify " << endl;
    while (menu != 6)
    {
        mostrarMenu();
        cin >> menu;
        switch (menu)
        {
        case 1:
            pushCancion(playlist, nuevaCancion);
            nuevaCancion = dameCancion();
            break;

        case 2:
            if (cancionActual.nombre != "Primer recorrido")
            {
                historial = calificar_listar(cancionActual, historial);
            }
            cancionActual = popCancion(playlist);
            if (cancionActual.nombre != "_")
            {
                cout << "Ahora se reproduce: " << cancionActual.nombre << " > " << endl;
            }
            break;
        case 3:
            if (playlist != NULL)
            {
                cout << "La siguiente cancion a reproducir es: " << playlist->sgte->nombre << ">" << endl;
            }
            else
            {
                cout << "No hay mas canciones en la playlist." << endl;
            }
            break;
        case 4:
            revertirPlaylist(playlist);
            break;
        case 5:
            imprimirListaSimple(historial);
            break;
        case 6:
            cout << "Saliendo de Spotify..." << endl;
            break;
        default:
            break;
        }
    }

    return 0;
}

void mostrarMenu()
{
    cout << "1. Agregar nueva cancion a la playlist." << endl;
    cout << "2. Reproducir siguiente cancion." << endl;
    cout << "3. Siguiente cancion en la playlist." << endl;
    cout << "4.Revertir la playlist." << endl;
    cout << "5. Mostrar historial." << endl;
    cout << "6. Salir." << endl;
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
        pushCancion(pilaaux, auxiliar);
    }
    pila = pilaaux;
    cout << "Se revirtio con exito la playlist.";
}

Registro *crearNodoRegistro(Cancion cancionGuardar, short estrellas)
{
    Registro *nodoRegistro = new Registro;
    nodoRegistro->estrellas = estrellas;
    nodoRegistro->song = cancionGuardar;
    nodoRegistro->siguiente = nullptr;
    return nodoRegistro;
}

Registro *calificar_listar(Cancion cancionAgregar, Registro *historial)
{
    short estrellas;
    cout << "Puntue de 1 a 5 estrellas la ultima cancion: ";
    cin >> estrellas;
    cin.ignore();

    Registro *nuevoNodoRegistro = crearNodoRegistro(cancionAgregar, estrellas);
    if (historial == nullptr || cancionAgregar.artista < historial->song.artista)
    {
        nuevoNodoRegistro->siguiente = historial;
        historial = nuevoNodoRegistro;
        return historial;
    }
    Registro *actual = historial;
    while (actual->siguiente != nullptr && actual->siguiente->song.artista < cancionAgregar.artista)
    {
        actual = actual->siguiente;
    }
    nuevoNodoRegistro->siguiente = actual->siguiente;
    actual->siguiente = nuevoNodoRegistro;
    return historial;
}

void imprimirListaSimple(Registro *inicio)
{
    Registro *actual = inicio;
    while (actual != nullptr)
    {
        cout << "Titulo: " << actual->song.nombre << ", Artista: " << actual->song.artista << " ,estrellas: " << actual->estrellas << endl;
        actual = actual->siguiente;
    }
}