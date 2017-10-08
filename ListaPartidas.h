#ifndef LISTAPARTIDAS_H
#define LISTAPARTIDAS_H
#include "Partida.h"
#include <iostream>
using namespace std;
const tFecha TREINTADIAS = 30 * 24 * 60 * 60;

const int MAX = 5;//30//5ToTest
typedef struct{

	int contador;
	tPartida* partida[MAX];

}tListaPartidas;
//PRACTICA 5
void iniciar(tListaPartidas & partidas);
void eliminar(tListaPartidas & partidas);

//PRACTICA 5

//Carga la lista de partidas desde el flujo archivo.Devuelve false si la lista no se ha podido cargar correctamente.
bool cargar(tListaPartidas & partidas, ifstream & archivo);

//Dada una partida, si hay espacio en la lista, la añade al final de la lista y devuelve true.Si no se ha podido insertar devuelve false.
bool insertar(tListaPartidas & partidas, tPartida const& partida);

//Guarda la lista de partidas en el flujo archivo.
void guardar(tListaPartidas const& partidas, ofstream & archivo, ofstream & historico);


#endif //LISTAPARTIDAS_H