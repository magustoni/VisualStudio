#include "Coordinador.h"
#include "fstream"


void Coordinador::inicializa()
{
	ifstream fichero;
	fichero.open("datos.txt"); // se leen los datos de las ultimas partidas del fichero
	if (!fichero)
		cout << "error";

	fichero >> nivel_max_completado;
	fichero >> moneda;
	
	fichero >> comprado1;
	fichero >> comprado2;
	fichero >> comprado3;
	fichero >> comprado4;
	fichero >> comprado5;
	

	for (int i = 0; i < 10; i++) //Obtener la puntuacion por niveles del fichero y pasarla a menu
	{
		fichero >> puntuacion_niveles[i];
		me.puntuacion_nivel(i, puntuacion_niveles[i]);
	}

	fichero.close();

	game_stage = MenuPrincipal;
	mu.inicializa(nivel_max_completado); // inicializar el mundo y pasar el numero de niveles completados del fichero
	me.iniciar();
	me.set_monedasini(moneda); //Pasar las monedas del fichero al menu
	me.set_compras(comprado1, comprado2, comprado3, comprado4, comprado5); //Pasar las compras del fichero a menu
}

	void Coordinador::dibuja()
	{
		//Establecer estado de juego para dibujar pantallas
		set_gamestage();
		switch (game_stage)
		{
		case MenuPrincipal://Pintar menu principal y pasar compras y monedas

			guardar_partida(); //Siempre que se entra al menu se guarda la partida
			compras();//Obtener variables de pelotas compradas

			//Pasar monedas
			pass_monedas();
			//Pasar nivel maximo
			me.set_nivelmax(nivel_max_completado);
			i.set_nivelmax(nivel_max_completado);

			me.menuprincipal(); //Pintar pantalla
		
			break;
		case Opciones:
			me.menuopciones(); //Pintar pantalla
			if (i.get_guardar()) //Opcion de guardar y salir
			{ 
			guardar_partida();
			exit(0);
			}
			break;
		case Niveles: me.menuniveles(); break; //Pintar pantalla de niveles
		case Tienda: me.menutienda(); break; //Pintar pantalla de tienda
		case Juego:
			if (mu.get_estado()==2) //Estado para el menu de pausa
			{
				nivel_max_completado = mu.get_nivel_max(); //Saber a que nivel maximo has llegado
				game_stage = Pausa; //Pantalla a Pausa
				mu.set_estado(1); //Devolver el estado al estado de juego
				i.set_interfaz(7); //Establecer la interfaz en 7 para que no haya cambio de pantalla y se quede en menu Pausa
				break;
			}
			if (mu.get_estado()==0) //Estado de juego acabado
			{
				nivel_max_completado = mu.get_nivel_max(); //Saber a que nivel maximo has llegado
				game_stage = Creditos; //Pantalla a Creditos
				mu.set_estado(1); //Devolver el estado al estado de juego
				i.set_interfaz(6); //Establecer la interfaz en 7 para que no haya cambio de pantalla y se quede en menu
				break;
			}
			//Cambiar el color de la pelota del mundo
			change_color();
			mu.set_pelota_color(rojocoord, verdecoord, azulcoord);

			//Pintar mundo del juego
			mu.dibuja(); break;
		case Creditos: me.menucreditos(); break;
		case Pausa: 
			if (i.get_guardar()) //Opcion de guardar en pausa
				guardar_partida();
			me.menupausa(); break;
		}
	}

	void Coordinador::teclas(unsigned char key)
	{
		mu.tecla(key); //Llamar al metodo de teclas del juego
	}

	void Coordinador::teclasespeciales(unsigned char key)
	{
		mu.special_tecla(key);
	}

	void Coordinador::mueve()
	{
		//Movimiento por pantallas
		switch (game_stage)
		{
		case MenuPrincipal:
			me.mueveprincipal(); //Rebote de la pelota con el suelo del menu
			break;
		case Tienda:me.muevetienda();  break; //Giro de las pelotas en el estante
		case Juego:
		{
			mu.mueve();
			if (mu.win()) {
				int aux = mu.get_nivel(); mu.level_up();
				if (aux > 5) { int p = aux-5; puntuacion_niveles[p] = mu.get_puntuacion(); } //El tutorial no tiene puntuacion
				for (int i = 0; i < 10; i++)
				{
					me.puntuacion_nivel(i, puntuacion_niveles[i]); //Pasar puntuacion al menu por niveles
				}
			}
			if (mu.die()) mu.cargar_nivel(false);
			break;
		}
		case Creditos:me.muevecreditos();  break; //Movimiento de creditos en el eje y
		}
	}

	void Coordinador::mouse(int button, int x, int y, int state) //Llamadas a las interacciones con raton, ambas usan la de interfaz
	{
		//Accion de raton por pantallas
		switch (game_stage)
		{
			//Clicks de la pantalla de menu Play, Opciones, Tienda
		case MenuPrincipal: i.Raton_menuprincipal(button, state, x, y); break;
			//Clicks de la pantalla de opciones, obtener el sonido y pasar de menu a mundo y guardar
		case Opciones: i.Raton_menuopciones(button, state, x, y); sound = i.get_sonido(); pass_sound(); me.set_guardar(i.get_guardar()); break; 
			//Clicls de la pantalla de niveles, obtener el nivel en funcion de la puerta clickada y cargar
		case Niveles: i.Raton_menuniveles(button, state, x, y); mu.set_nivel(i.get_nivel()); mu.cargar_nivel(true); break;
			//Clicks de los carteles de la tienda, establecer el cartel de compra y activar la compra
		case Tienda: i.Raton_menutienda(button, state, x, y); me.set_Tienda(i.get_tienda()); me.activar_compra(i.get_activarcompra()); break; 
			//Movimiento del raton del mundo
		case Juego: mu.mouse(button, x, y, state); break;
			//Click del objeto de retroceso
		case Creditos: i.Raton_menucreditos(button, state, x, y); break;
			//Clicks de la pantalla de opciones, obtener el sonido y pasar de pausa a mundo y guardar
		case Pausa: i.Raton_menupausa(button, state, x, y); sound = i.get_sonido(); pass_sound(); me.set_guardar(i.get_guardar()); break;
		}
	}

	void Coordinador::motion(int x, int y)
	{
		mu.motion(x, y);
	}

	void Coordinador::set_gamestage()
	{
		//Obtener los estados de los clicks de la interfaz y etablecer el estado del juego
		int estado = i.get_interfaz();
	
		switch (estado)
		{
		case 1: game_stage = MenuPrincipal; break;
		case 2: game_stage = Opciones; break;
		case 3: game_stage = Niveles; break;
		case 4: game_stage = Tienda; break;
		case 5: game_stage = Juego; break;
		case 6: game_stage = Creditos; break;
		case 7: game_stage = Pausa; break;
		}
	}
	void Coordinador::change_color()//Establece color de la clase coordinador, util para cambiar el color de la pelota
	{
		rojocoord = me.get_color(1);
		verdecoord = me.get_color(2);
		azulcoord = me.get_color(3);
	}

	void Coordinador::pass_monedas() //Funcion para pasar monedas de mundo a menu y resetear monedas de menu
	{
		moneda = mu.get_monedas();
		me.set_monedas(moneda); //Incrementar las monedas de menu con las de mundo
		mu.set_monedas(0);//Resetear las monedas del mundo una vez pasadas
	}
	void Coordinador::compras() //Pasar la variable de compras segun la pelota comprada de la tienda
	{
		comprado1 = me.get_compras(1); //Comprada pelota 1
		comprado2 = me.get_compras(2); //Comprada pelota 2
		comprado3 = me.get_compras(3); //Comprada pelota 3
		comprado4 = me.get_compras(4); //Comprada pelota 4
		comprado5 = me.get_compras(5); //Comprada pelota 5
	}
	void Coordinador::pass_sound() //Pasar el sonido a menu y a mundo
	{
		me.set_sonido(sound);
		mu.set_sonido(sound);
	}
	int Coordinador::get_stage() //Obtener el estado del juego actual
	{
		return game_stage;
	}

	void Coordinador::guardar_partida() //Guardar las variables de monedas, puntuacion y compras en el fichero
	{
		moneda = me.get_monedas(); //Obtener las monedas del menu
		for (int i = 0; i < 10; i++) //Obtener la puntuacion de cada nivel del menu
		puntuacion_niveles[i] = me.get_puntuacion(i);

		//Abrir y guardar cada variable en el fichero

		ofstream fichero;
		fichero.open("datos.txt");
		if (!fichero)
			cout << "error";
		
		fichero << nivel_max_completado << endl; //Nivel maximo
		fichero << moneda << endl << endl; //Monedas

		//Variabel que dice si hay una pelota de la tienda comprada
		fichero << comprado1 << endl;
		fichero << comprado2 << endl;
		fichero << comprado3 << endl;
		fichero << comprado4 << endl;
		fichero << comprado5 << endl << endl;


		for (int i = 0; i < 10; i++) //Puntuacion de cada nivel
		{
			fichero << puntuacion_niveles[i] << endl;
		}

		fichero.close();
		i.set_guardar(false); //quitar la opcion de guardado del interfaz para que no guarde constantemente
	}