#include "ListaAccesoPartidas.h"

//PRACTICA 5
void ordenarTurno(tListaAccesoPartidas &accesos, string & usuario){

	tParIdEn elemento;
	int j;
	bool jota;
	for (int i = 1; i< accesos.contador; ++i)
	{
		elemento = accesos.PartidasEnCurso[i];
		j = i;
		jota = esSuTurno(*(accesos.PartidasEnCurso[i].enlace),usuario);
		//jotamenos = esSuTurno(*(accesos.PartidasEnCurso[j - 1].enlace),usuario);
		while ((j > 0) && jota && !esSuTurno(*(accesos.PartidasEnCurso[j - 1].enlace), usuario))
		{
			accesos.PartidasEnCurso[j] = accesos.PartidasEnCurso[j - 1];
			j--;
			//jotamenos = esSuTurno(*(accesos.PartidasEnCurso[j - 1].enlace),usuario);
		}
		accesos.PartidasEnCurso[j] = elemento;
	}

}

void ordenarFecha(tListaAccesoPartidas &accesos){

	tParIdEn elemento;
	int j;

	for (int i = 1; i< accesos.contador; ++i)
	{
		elemento = accesos.PartidasEnCurso[i];
		j = i;
		while ((j > 0) && accesos.PartidasEnCurso[j].enlace->actualizacion
			< accesos.PartidasEnCurso[j - 1].enlace->actualizacion)
		{
			accesos.PartidasEnCurso[j] = accesos.PartidasEnCurso[j - 1];
			j--;
		}
		accesos.PartidasEnCurso[j] = elemento;
	}

}
//PRACTICA 5
void iniciar(tListaAccesoPartidas & lista){
	
	lista.contador = 0;
	
}

bool llena(tListaAccesoPartidas const& lista){
	
	return lista.contador == (MAX_PAR_US);
	
}

bool insertar(tListaAccesoPartidas & lista, tParIdEn par)
{

	if (!llena(lista))
	{ 
		lista.PartidasEnCurso[lista.contador] = par;
		lista.contador += 1;
		return true;
	}
	else return false;
	
}

bool buscar(tListaAccesoPartidas  const& lista, string const& ID, int &pos){
	
	if (pos == lista.contador + 1) return false;
	else if (lista.PartidasEnCurso[pos].ID == ID) return true;
	else
	{
		pos += 1;
		return buscar(lista, ID, pos);
	}

}


bool eliminarLista(tListaAccesoPartidas & lista, int pos){
	if ((pos < 0) || (pos >= lista.contador)) return false;
	else {
			suprimirIzq(lista, pos);
			lista.contador--;
			return true;
	}
}

bool eliminar(tListaAccesoPartidas &lista, string const& ID) {
	int pos = 0;
	if (buscar(lista,ID,pos))
		return eliminarLista(lista,pos);
	else return false;
}

void suprimirIzq(tListaAccesoPartidas &lista, int pos){

	for (int i = pos + 1; i < lista.contador; i++)
	lista.PartidasEnCurso[i - 1] = lista.PartidasEnCurso[i];
	
}