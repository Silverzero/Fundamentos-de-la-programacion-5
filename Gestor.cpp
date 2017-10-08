#include "Gestor.h"


void eliminarInactivas(tGestor &gestor){

	int pos;
	int pos2;

	tFecha Hoy = fechaActual();
	for (int i = 0; i < gestor.listapartidas.contador; i++)
	{
		if ((Hoy - gestor.listapartidas.partida[i]->actualizacion) >= TREINTADIAS)
		{
			abandonar(*(gestor.listapartidas.partida[i]));
			buscar(gestor.listausuarios, gestor.listapartidas.partida[i]->jugador1, pos);
			buscar(gestor.listausuarios, gestor.listapartidas.partida[i]->jugador2, pos2);

			if (esSuTurno(*(gestor.listapartidas.partida[i]),gestor.listapartidas.partida[i]->jugador1))
			{
				
				aplicarFinPartida(gestor.listausuarios.usuarios[pos], Pierde);
				aplicarFinPartida(gestor.listausuarios.usuarios[pos2], Gana);
				actualizarAvisos(gestor.listausuarios.usuarios[pos2], "Ha ganado por abandono una partida contra " + gestor.listausuarios.usuarios[pos].nombre + ".");

			}
			else
			{
				aplicarFinPartida(gestor.listausuarios.usuarios[pos], Gana);
				aplicarFinPartida(gestor.listausuarios.usuarios[pos2], Pierde);
				actualizarAvisos(gestor.listausuarios.usuarios[pos], "Ha ganado por abandono una partida contra " + gestor.listausuarios.usuarios[pos2].nombre + ".");
			}
		}
	}
}
	

bool arrancar(tGestor & gestor){

	ifstream Usuarios;
	ifstream Partidas;
	bool cargar1, cargar2;
	
	Partidas.open("partidas.txt");
	iniciar(gestor.listapartidas);
	cargar1 = cargar(gestor.listapartidas, Partidas);

	Usuarios.open("usuarios.txt");
		
	cargar2 = cargar(gestor.listausuarios, Usuarios);
	
	Usuarios.close();
	Partidas.close();

	return cargar1 && cargar2;
}

void apagar(tGestor & gestor){

	ofstream Usuarios;
	ofstream Partidas;
	ofstream Historico;

	eliminarInactivas(gestor);

	Partidas.open("partidas.txt");
	Historico.open("historico.txt",ios::app);
	guardar(gestor.listapartidas, Partidas, Historico);

	Usuarios.open("usuarios.txt");
	guardar(gestor.listausuarios, Usuarios);
	

	Historico.close();
	Usuarios.close();
	Partidas.close();
	eliminar(gestor.listapartidas);
	apagar(gestor.listausuarios);

}

bool crearCuenta(tGestor &gestor, string const &idUsu, string const &clave){

	bool creado = false;
	tUsuario usuario;
					
			iniciar(usuario, idUsu, clave);
			creado = insertar(gestor.listausuarios,usuario,gestor.usuarioindice);
				

	return creado;
}

bool iniciarSesion(tGestor & gestor, string const &idUsu, string const &clave){
	

	if (buscar(gestor.listausuarios, idUsu,gestor.usuarioindice)){
		
		if (iniciarSesion(gestor.listausuarios.usuarios[gestor.usuarioindice], clave))
		{
			return true;
		}
		else return false;
	
	}
	else return false;
}

void limpiarAvisos(tGestor &gestor){
	
	limpiarAvisos(gestor.listausuarios.usuarios[gestor.usuarioindice]);

}

bool tieneAvisos(tGestor const &gestor, string &aviso){

	bool HayAvisos;


	HayAvisos = tieneAvisos(gestor.listausuarios.usuarios[gestor.usuarioindice], aviso);

	return HayAvisos;
}

string resumenActividad(tGestor const &gestor){
	
	string resumen;
	resumen = resumenActividad(gestor.listausuarios.usuarios[gestor.usuarioindice]);
	return resumen;

}

void generarAccesos(tGestor & gestor){
	
	tParIdEn PartidaJugador;
	iniciar(gestor.accesos);

	for (int i = 0; i < gestor.listapartidas.contador; i++)
	{
		int pos;
		if (gestor.listapartidas.partida[i]->estadoPartida == EnCurso)
		{
			buscar(gestor.listausuarios, gestor.listapartidas.partida[i]->jugador1, pos);
			buscar(gestor.listausuarios, gestor.listapartidas.partida[i]->jugador2, pos);
			if (gestor.listapartidas.partida[i]->jugador1 == gestor.listausuarios.usuarios[gestor.usuarioindice].nombre)
			{
				PartidaJugador.ID = gestor.listapartidas.partida[i]->ID;
				PartidaJugador.enlace = gestor.listapartidas.partida[i];
				insertar(gestor.accesos, PartidaJugador);
			}
			else if (gestor.listapartidas.partida[i]->jugador2 == gestor.listausuarios.usuarios[gestor.usuarioindice].nombre)
			{
				PartidaJugador.ID = gestor.listapartidas.partida[i]->ID;
				PartidaJugador.enlace = gestor.listapartidas.partida[i];
				insertar(gestor.accesos, PartidaJugador);
			}
		}
	}

}

int partidasUsuario(tGestor const& gestor){

	return gestor.accesos.contador;

}

bool nuevaPartida(tGestor & gestor){

	bool encontrado = false;
	int pos;
	gestor.listausuarios.usuarios[gestor.usuarioindice].espera = false;
	if (!llena(gestor.accesos) && buscarUsuarioEsperando(gestor.listausuarios, gestor.listausuarios.usuarios[gestor.usuarioindice].nivel, pos) && gestor.listapartidas.contador < MAX)
	{
		encontrado = true;
		gestor.listausuarios.usuarios[gestor.usuarioindice].espera = false;
		tParIdEn partidanew;
		tPartida partida;
		nueva(partida, gestor.listausuarios.usuarios[gestor.usuarioindice].nombre, gestor.listausuarios.usuarios[pos].nombre);
		insertar(gestor.listapartidas, partida);
		partidanew.ID = partida.ID;
		//partidanew.enlace = gestor.partidaindice;
		partidanew.enlace = gestor.listapartidas.partida[gestor.listapartidas.contador-1];
		if (insertar(gestor.accesos, partidanew))
		{
			nuevaPartida(gestor.listausuarios.usuarios[gestor.usuarioindice]);
			nuevaPartida(gestor.listausuarios.usuarios[pos]);
		}
	}
	else if (!llena(gestor.accesos) && gestor.listapartidas.contador < MAX)
	{
		gestor.listausuarios.usuarios[gestor.usuarioindice].espera = true;
		cout << "En espera\n";
		system("pause");
	}
	else if (llena(gestor.accesos)|| gestor.listapartidas.contador == MAX){
		cout << "Maximo de partidas alcanzado\n";
		system("pause");
	}
	return encontrado;
}

string cabecera(tGestor const& gestor, int posEnCurso){
	
	string resultado;
	if (gestor.accesos.PartidasEnCurso[posEnCurso].enlace->juego.turno == Jugador1 && gestor.listausuarios.usuarios[gestor.usuarioindice].nombre == gestor.accesos.PartidasEnCurso[posEnCurso].enlace->jugador1
	|| gestor.accesos.PartidasEnCurso[posEnCurso].enlace->juego.turno == Jugador2 && gestor.listausuarios.usuarios[gestor.usuarioindice].nombre == gestor.accesos.PartidasEnCurso[posEnCurso].enlace->jugador2)
				resultado = resultado + " *" + cabecera(*(gestor.accesos.PartidasEnCurso[posEnCurso].enlace)) + "\n";
	else resultado = resultado + "  " + cabecera(*(gestor.accesos.PartidasEnCurso[posEnCurso].enlace)) + "\n";

	return resultado;

}

void apuntaPartida(tGestor &gestor, int posParEnCurso)
{
	
	gestor.partidaindice = gestor.accesos.PartidasEnCurso[posParEnCurso].enlace;
}

void mostrarPartida(tGestor const& gestor){

	cout << EstadoPartida[gestor.partidaindice->estadoPartida];

}

bool esSuTurno(tGestor &gestor, string &usuario){
	
	return esSuTurno(*(gestor.partidaindice), usuario);

}

void abandonarPartida(tGestor &gestor){

	int pos, pos2;
	//Deja la partida en lista de partidas finalizada.
	abandonar(*(gestor.partidaindice));
	eliminar(gestor.accesos,gestor.partidaindice->ID);

	buscar(gestor.listausuarios, gestor.partidaindice->jugador1, pos);
	buscar(gestor.listausuarios, gestor.partidaindice->jugador2, pos2);
	//Elimina acceso Jugador1.
	if (gestor.listausuarios.usuarios[pos].nombre == gestor.listausuarios.usuarios[gestor.usuarioindice].nombre){

		aplicarFinPartida(gestor.listausuarios.usuarios[pos], Pierde);
		aplicarFinPartida(gestor.listausuarios.usuarios[pos2], Gana);
		actualizarAvisos(gestor.listausuarios.usuarios[pos2], "Ha ganado por abandono una partida contra " + gestor.listausuarios.usuarios[pos].nombre + ".");

	}
	else
	{
		aplicarFinPartida(gestor.listausuarios.usuarios[pos],Gana);
		aplicarFinPartida(gestor.listausuarios.usuarios[pos2],Pierde);
		actualizarAvisos(gestor.listausuarios.usuarios[pos], "Ha ganado por abandono una partida contra " + gestor.listausuarios.usuarios[pos2].nombre + ".");
	}
}
/*
void ordenarTurno(tGestor &gestor){

	tParIdEn elemento;
	int j;
	bool jota;
	bool jotamenos;
	for (int i = 1; i< gestor.accesos.contador; ++i)
	{
		elemento = gestor.accesos.PartidasEnCurso[i];
		j = i;
		gestor.partidaindice = gestor.accesos.PartidasEnCurso[j].enlace;
		jota = esSuTurno(gestor);
		gestor.partidaindice = gestor.accesos.PartidasEnCurso[j-1].enlace;
		jotamenos = esSuTurno(gestor);
		while ((j > 0) && jota && !jotamenos)
		{
			gestor.accesos.PartidasEnCurso[j] = gestor.accesos.PartidasEnCurso[j - 1];
			j--;
			gestor.partidaindice = gestor.accesos.PartidasEnCurso[j - 1].enlace;
			jotamenos = esSuTurno(gestor);
		}
	gestor.accesos.PartidasEnCurso[j] = elemento;
	}

}
*/

/*
void ordenarFecha(tGestor &gestor){

	tParIdEn elemento;
	int j;
		
	for (int i = 1; i< gestor.accesos.contador; ++i)
	{
		elemento = gestor.accesos.PartidasEnCurso[i];
		j = i;
		while ((j > 0) && gestor.accesos.PartidasEnCurso[j].enlace->actualizacion
			< gestor.accesos.PartidasEnCurso[j-1].enlace->actualizacion)
		{
			gestor.accesos.PartidasEnCurso[j] = gestor.accesos.PartidasEnCurso[j - 1];
			j--;
		}
		gestor.accesos.PartidasEnCurso[j] = elemento;
	}

}
*/

void jugarPartida(tGestor &gestor, int col){
	
	string aviso;
	int pos;
	gestor.partidaindice->actualizacion = fechaActual();
	aplicarJugada(gestor.partidaindice->juego,col);
	if (gestor.partidaindice->juego.estado == Ganador)
	{
		eliminar(gestor.accesos,gestor.partidaindice->ID);
		gestor.partidaindice->estadoPartida = Terminada;
		aplicarFinPartida(gestor.listausuarios.usuarios[gestor.usuarioindice], Gana);
		buscar(gestor.listausuarios,gestor.partidaindice->jugador2, pos);
		if (pos != gestor.usuarioindice)
			aplicarFinPartida(gestor.listausuarios.usuarios[pos], Pierde);
		else
		{
			buscar(gestor.listausuarios, gestor.partidaindice->jugador1, pos);
			aplicarFinPartida(gestor.listausuarios.usuarios[pos], Pierde);
			actualizarAvisos(gestor.listausuarios.usuarios[pos], "Ha perdido una partida contra " + gestor.partidaindice->jugador2 + "el dia " + stringFecha(fechaActual(), true));
		}
	}
	else if (gestor.partidaindice->juego.estado == Bloqueo)
	{
		eliminar(gestor.accesos, gestor.partidaindice->ID);
		gestor.partidaindice->estadoPartida = Terminada;
		buscar(gestor.listausuarios, gestor.partidaindice->jugador1, pos);
		aplicarFinPartida(gestor.listausuarios.usuarios[pos], Empate);
		actualizarAvisos(gestor.listausuarios.usuarios[pos], "Ha empatado una partida contra " + gestor.partidaindice->jugador2 + "el dia " + stringFecha(fechaActual(), true));
		buscar(gestor.listausuarios, gestor.partidaindice->jugador2, pos);
		aplicarFinPartida(gestor.listausuarios.usuarios[pos], Empate);
		actualizarAvisos(gestor.listausuarios.usuarios[pos], "Ha empatado una partida contra " + gestor.partidaindice->jugador1 + "el dia " + stringFecha(fechaActual(), true));
	}
	
}