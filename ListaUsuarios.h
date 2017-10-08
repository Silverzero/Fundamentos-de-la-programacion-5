#ifndef LISTAUSUARIO_H
#define LISTAUSUARIO_H

#include "Usuario.h"

//40 pre prueba --> 5
//const int MAX_Usuarios = 10; //5ToTest;
typedef struct{

	tUsuario* usuarios;
	int contador;
	int DIM;

}tListaUsuarios;
//PRACTICA 5
void iniciar(tListaUsuarios &ListaUsuarios, int inicializar);
void redimensionar(tListaUsuarios &ListaUsuarios);
void apagar(tListaUsuarios &ListaUsuarios);
//PRACTICA 5

bool cargar(tListaUsuarios & usuarios, ifstream & archivo);
//Carga la lista de usuarios desde el flujo(ya abierto) archivo(ver detalles y ejemplo en la secci�n 2.2).

void guardar(tListaUsuarios const& usuarios, ofstream & archivo);
//Guarda la lista de usuarios en el flujo(ya abierto) archivo.

bool buscar(tListaUsuarios const& usuarios, string const& idUser, int &pos); 
//Dado un identificador de usuario y la lista, devuelve, si dicho identificador existe en la lista, su posici�n y el valor true, y si no existe en la lista, la posici�n que le corresponder�a
//y el valor false.

bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int &pos);
//A�ade un usuario en la posici�n de la lista que le corresponde, si hay sitio para ello y no hay otro usuario con el mismo identificador.Adem�s devuelve un booleano indicando
//si la operaci�n tuvo �xito o no, y la posici�n donde se ha insertado.

bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos);
//Devuelve true y la posici�n del primer usuario del nivel dado que est� esperando para iniciar una partida.Si no existe devuelve false.

//EXTRAS
void desplazarDerecha(tListaUsuarios & usuarios, int pos);

#endif //LISTAUSUARIO_H