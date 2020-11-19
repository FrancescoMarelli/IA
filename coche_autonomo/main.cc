#include "Entorno.cc"
#include <chrono> 


void ShowHelp(){
	std::cout << "--Ayuda--\n\tLa malla es el entorno para un vehículo"
						<< " autonomo, este programa la prueba individualmente y acepta"
						<< " diferentes modos de trabajo\n\n\tVease:\n";
	std::cout << "\t./PruebaMalla\tEste modo le solicitará los datos durante "
						<< "su ejecución\n";
	std::cout << "\t./PruebaMalla N M\tEste modo toma los valores enteros N y "
						<< "M como tamaño de la malla\n";
	std::cout << "\t./PruebaMalla N M Obstaculos\tEste modo se diferencia del anterior "
						<< "Por contar con el número de obstaculos en la malla\n";
	std::cout << "\t./PruebaMalla fichero\tEste modo lee un fichero de entrada "
	          << "con el siguiente formato:\n\t\tN\n\t\tM\n\t\tObstaculos\n"
			  << "\t\tCoordenada x posición inicial\n\t\tCoordenada y posición inicial \n"
			            << "\t\tCoordenada x posición final \n\t\tCoordenada y posición final\n"
						<< "\t\tCoordenada x Obstaculo\n\t\tCoordenada y Obstaculo\n";
	std::cout << "\t./PruebaMalla N M Obstaculos aleatorio: \tEste modo recibe las "
						<< "dimensiones de la malla, el número de obstaculos y los posiciona de "
						<< "manera aleatoria\n";
	std::cout << "\t./PruebaMalla N M aleatorio:\tEste modo recibe las dimensiones de "
						<< "la malla y la rellena aleatoriamente con un numero aleatorio de obstaculos\n\n";

}

//Reconoce si es un .txt
bool ReconocerFichero(std::string fichero_nombre){
	//Nombre minimo a.txt > 4
	if(fichero_nombre.size()>4){
		if((fichero_nombre[fichero_nombre.size()-1] == 't') && (fichero_nombre[fichero_nombre.size()-2] == 'x') && 
		   (fichero_nombre[fichero_nombre.size()-3] == 't') && (fichero_nombre[fichero_nombre.size()-4] == '.'))
		return true;
	}
	else {return false;}
	
	return true;
}
Entorno ManualMode_Filas(){
    int N, M;
	int X;
	int posx,posy;
	int posxf, posyf;

    std::cout << "Introducir el numero de filas  de la Malla: ";
    std::cin >> N;
    std::cout << "Introducir el numero de columnas  de la Malla: ";
    std::cin >> M;
	std::cout << "Introducir el numero de obstaculos: ";
    std::cin >> X;

    Entorno a(N,M,X);
	std::cout << "Introducir la posición inicial del coche (x y) : ";
	std::cin >> posx >> posy;
	a.set_car(posx,posy);
	std::cout << "Introducir la posición final del coche (x y) : ";
	std::cin >> posxf >> posyf;
	a.set_end(posxf,posyf);

	
	return a;
}

Entorno ManualMode(int N, int M) {
	int posx, posy, posxf, posyf;
	Entorno a(N,M);
	std::cout << "Introducir la posición inicial del coche (x y) : ";
	std::cin >> posx >> posy;
	a.set_car(posx,posy);
	std::cout << "Introducir la posición final del coche (x y) : ";
	std::cin >> posxf >> posyf;
	a.set_end(posxf,posyf);

	return a;
}
Entorno ManualModeObs(int N, int M, int X) {
	int posx, posy, posxf, posyf;
	Entorno a(N,M,X);
	std::cout << "Introducir la posición inicial del coche (x y) : ";
	std::cin >> posx >> posy;
	a.set_car(posx,posy);
	std::cout << "Introducir la posición final del coche (x y) : ";
	std::cin >> posxf >> posyf;
	a.set_end(posxf,posyf);

	return a;
}

int main (int argc, char* argv[]){
    // Leer disposición de fichero
    //--help
    //leer por comandos la disposición de la malla 
    //Leer por comandos la cantidad de obstaculos
    //Poner el modo aleatorio desde comandos 

	int modo; 			//Mode de rellenar la malla
						// 0 = manual, 1 = aleatorio
    Entorno a;
    std::ifstream fichero;
	std::chrono::time_point<std::chrono::system_clock> start, end;
  
	//Pulir switch de acuerdo al --help
	switch (argc)
	{
	case 1:{
		modo = manual;
		std::cout << "Modo manual\n";
		Entorno B;
		B = ManualMode_Filas();
		B.show_malla();
			start = std::chrono::system_clock::now();
			B.Solve();
			end = std::chrono::system_clock::now();
		std::chrono::duration<double> tiempo =  end -start;
		std::cout <<"Tiempo de ejcución: " << tiempo.count() << "segundos";
		break;
		}

	case 2:{
		// Por Fichero
		std::string argumento;
		argumento = argv[1];
		if(argumento == "--help"){
			ShowHelp();
			return 0;
		}
		else{
			if(ReconocerFichero(argumento))
				std::cout << "El fichero indicado es " << argumento << "\n";

			else{
				std::cout << "Indique un fichero con formato .txt\nMás información con --help\n";
				return 0;
			}
			
			fichero.open(argumento);
			if(!fichero) {
				std::cout << "No existe el fichero\n";
				return 0;
			}
			fichero.close();
			Entorno B(argumento);
			B.show_malla();
			start = std::chrono::system_clock::now();
			B.Solve();
			end = std::chrono::system_clock::now();
			B.show_malla();
			std::chrono::duration<double> tiempo =  end -start;
		std::cout <<"Tiempo de ejcución: " << tiempo.count() << "segundos";

		}
		break;
		}

	case 3:{
		// se le introducen las dimensiones de la malla y los obstaculos 
		std::cout << "Los valores de malla indicados son: N = "<< argv[1] << " y M = " << argv[2] << "\n";
		int n = atoi(argv[1]);
		int m = atoi(argv[2]);
		Entorno b(n, m);
		a = b;
		std::cout << "El tamaño de la malla es " << a.get_size() << "\n";
		a = ManualMode(n,m);
		a.show_malla();
		start = std::chrono::system_clock::now();
		a.Solve();
		end = std::chrono::system_clock::now();
		a.show_malla();
		std::chrono::duration<double> tiempo =  end -start;
		std::cout <<"Tiempo de ejcución: " << tiempo.count()<< "segundos";
		break;
		}

	case 4:{
		// Aleatorio por defecto
		int n = atoi(argv[1]);
		int m = atoi(argv[2]);
		int x = atoi(argv[3]);
		std::cout << "Los valores de malla indicados son: N = "<< n << " y M = " << m << "\n";
		std::cout << "El numero de obstaculos indicados es " << x << "\n";
		Entorno env;
		env = ManualModeObs(n,m,x);
		env.show_malla();
		start = std::chrono::system_clock::now();
		env.Solve();
		end = std::chrono::system_clock::now();
		env.show_malla();
		std::chrono::duration<double> tiempo =  end - start;
		std::cout <<"Tiempo de ejcución: " << tiempo.count()<< "segundos";
		break;
		}

	case 5:{
		std::string argumento;
		argumento = argv[4];
		if((argumento == "aleatorio") || (argumento == "manual")){
		int n = atoi(argv[1]);
		int m = atoi(argv[2]);
		int x = atoi(argv[3]);
		if(argumento == "aleatorio"){
		modo = aleatorio;
		}else {
			modo = manual;
		}
		std::cout << "Los valores de malla indicados son: N = "<< n << " y M = " << m << "\n";
		std::cout << "El numero de obstaculos indicados es " << x << "\n";
		//std::cout << "Se situarán aleatoriamente...\n";
		Entorno b(n, m, x, modo);
		b = ManualModeObs(n,m,x);
		b.show_malla();
		start = std::chrono::system_clock::now();
		b.Solve();
		end = std::chrono::system_clock::now();
		b.show_malla();
		std::chrono::duration<double> tiempo =  end -start;
		std::cout <<"Tiempo de ejcución: " << tiempo.count()<< "segundos";
		}else{
			std::cout << "Las unicas opciones validad como cuarto argumento son [aleatoria] o [manual]" << std::endl;
		}

		break;
		}	
	
	default:{
		std:: cout << "Introduzca una opción válida. Más información mediante --help\n";
		break;
		}
	}
	
	return 0;
}


