#ifndef LISTAACCESOPARTIDAS_H
#define LISTAACCESOPARTIDAS_H
#include <string>
#include "ListaPartidas.h"
using namespace std;
const int MAX_PAR_US = 3;//10; //3ToTest;



typedef struct{

	string ID;
	tPartida* enlace;
	
}tParIdEn;

typedef struct{

	int contador;
	tParIdEn PartidasEnCurso[MAX_PAR_US];

}tListaAccesoPartidas;
//PRACTICA 5
void ordenarTurno(tListaAccesoPartidas &accesos, string & usuario);
void ordenarFecha(tListaAccesoPartidas &accesos);
//PRACTICA 5

//Inicia la lista vac�a.
void iniciar(tListaAccesoPartidas & lista);

//Comprueba si la lista est� llena.
bool llena(tListaAccesoPartidas const& lista);

//Dado un elemento, si la lista no est� llena lo inserta al final de la lista y devuelve true.En otro caso devuelve false.
bool insertar(tListaAccesoPartidas & lista, tParIdEn par);

//Dado un identificador de partida, lo busca en la lista y si lo encuentra lo elimina de la lista(�sin dejar huecos!).Si no lo encuentra, devuelve false, en otro caso devuelve true.Ojo: esta
//operaci�n s�lo supone que el elemento se elimina de la lista de partidas en curso del jugador pero la partida sigue existiendo en la lista de partidas del gestor.
bool eliminar(tListaAccesoPartidas & lista, string const& id);
//Da la posicion que queremos eliminar
bool buscar(tListaAccesoPartidas  const& lista, string const& ID, int &pos);
// sabiendo la posicion, elimina de la lista;
bool eliminarLista(tListaAccesoPartidas & lista, int pos);
//sabiendo la posicion y sabiendo que no es una posicion nula, elimina desplazando el array a la izquierda;
void suprimirIzq(tListaAccesoPartidas &lista, int pos);

#endif //LISTAACCESOPARTIDAS_H