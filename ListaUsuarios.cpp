#include "ListaUsuarios.h"
#include <fstream>

//PRACTICA 5
void iniciar(tListaUsuarios &ListaUsuarios,int inicializar){

	ListaUsuarios.DIM = inicializar;
	ListaUsuarios.usuarios = new tUsuario[ListaUsuarios.DIM];
	ListaUsuarios.contador = inicializar;	

}

void redimensionar(tListaUsuarios &ListaUsuarios){

	int nuevaDIM;
	//nuevaDIM = ( ListaUsuarios.DIM * 3) / 2 + 1;
	nuevaDIM = ListaUsuarios.DIM + 1;
	tUsuario* aux = new tUsuario[nuevaDIM];
	for (int i = 0; i < ListaUsuarios.DIM; i++){
		aux[i] = ListaUsuarios.usuarios[i];
	}
	delete[] ListaUsuarios.usuarios;
	ListaUsuarios.usuarios = aux;
	ListaUsuarios.DIM = nuevaDIM;
}

void apagar(tListaUsuarios &ListaUsuarios){
	delete[] ListaUsuarios.usuarios;
	ListaUsuarios.usuarios = nullptr;
	ListaUsuarios.contador = 0;
	ListaUsuarios.DIM = 0;
}
//PRACTICA 5


bool cargar(tListaUsuarios & usuarios, ifstream & archivo){

	int aux;
	archivo >> aux;
	iniciar(usuarios,aux);

	//Redimensiono tantas veces como el array.

	while (usuarios.contador > usuarios.DIM)
		redimensionar(usuarios);

	for (int i = 0; i < usuarios.contador; i++)
	{
		cargar(usuarios.usuarios[i], archivo);
	}

	return !archivo.fail();

}


void guardar(tListaUsuarios const& usuarios, ofstream & archivo){

	archivo << usuarios.contador << endl;

	for (int i = 0; i < usuarios.contador; i++)
	{
		guardar(usuarios.usuarios[i], archivo);
	}

}

bool buscar(tListaUsuarios const& usuarios, string const& idUser, int &pos){

	int ini = 0, fin = usuarios.contador - 1, mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (idUser < usuarios.usuarios[mitad].nombre) fin = mitad - 1;
		else if (usuarios.usuarios[mitad].nombre < idUser) ini = mitad + 1;
		else encontrado = true;
	}
	
	if (encontrado) pos = mitad;
	else pos = ini;

	return encontrado;

}


bool insertar(tListaUsuarios & usuarios, tUsuario const& usuario, int &pos){

	
	if (usuarios.contador == usuarios.DIM)
	{
		redimensionar(usuarios);
	}
	pos = 0;
		if (!buscar(usuarios,usuario.nombre,pos)) {
				desplazarDerecha(usuarios, pos);
				usuarios.usuarios[pos] = usuario;
				usuarios.contador++;
				return true;
		}else return false;
		
}

void desplazarDerecha(tListaUsuarios & usuarios, int pos){
	
	for (int i = usuarios.contador; i > pos; i--)
		usuarios.usuarios[i] = usuarios.usuarios[i - 1];
}

bool buscarUsuarioEsperando(tListaUsuarios const& usuarios, tNivel nivel, int & pos){

	bool encontrado = false;

	for (int i = 0; i < usuarios.contador && !encontrado ; i++){
	
		if (usuarios.usuarios[i].nivel == nivel && usuarios.usuarios[i].espera)
		{
			pos = i;
			encontrado = true;
		}
	
	}
	return encontrado;
}