#include "ListaPartidas.h"
#include <iomanip>


//PRACTICA 5
void iniciar(tListaPartidas & partidas){

	partidas.contador = 0;
	for (int i = 0; i < MAX; i++)
	{
		partidas.partida[i] = new tPartida;
	}
	
}

void eliminar(tListaPartidas &partidas){

	for (int i = 0; i < MAX; i++)
	{
		delete partidas.partida[i];
	}
	partidas.contador = 0;

}



//PRACTICA 5

bool cargar(tListaPartidas & partidas, ifstream & archivo){

	archivo >> partidas.contador;

	for (int i = 0; i < partidas.contador;i++)
	{
		cargar(*(partidas.partida[i]), archivo);	
	}
	
	return !archivo.fail();
}

void guardar(tListaPartidas const& partidas, ofstream & archivo, ofstream & historico){

	int Hermecontador = 0; //Si, pone Herme
	archivo << setw(11) << partidas.contador << endl;
	
	for (int i = 0; i < partidas.contador; i++)
	{
		if (partidas.partida[i]->estadoPartida == Terminada)
		{
			guardar(*(partidas.partida[i]), historico);
			Hermecontador++;
		}
		else guardar(*(partidas.partida[i]), archivo);
	}
	archivo.seekp(0, ios::beg);
	archivo << setw(11) << partidas.contador-Hermecontador;
}

bool insertar(tListaPartidas & partidas, tPartida const& partida){


	if (partidas.contador < MAX){
		*(partidas.partida[partidas.contador]) = partida;
		partidas.contador++;
		return true;
	}
	else return false;


}