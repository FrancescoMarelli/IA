#include "Entorno.h"
#include <bits/stdc++.h> 

// CONSTRUCTORES-------------------------
Entorno::Entorno(){
  N_ = 0;
  M_ = 0;
  X_ = 0;
  //visited_.resize(N_*M_);
}

//Constructor que recibe el tamaño de la malla
Entorno::Entorno(int n, int m){
  N_ = n;
  M_ = m;
  X_ = 0;
 // visited_.resize(N_*M_);
  for (int i = 0; i < N_; i++) {
    std::vector <int> aux;
    for (int j = 0; j < M_; j++) {
      aux.push_back(0);
    }
    Malla_.push_back(aux);
  }
}

//Constructor que recibe el tamaño de la malla y el numero de obstaculos
Entorno::Entorno(int n, int m, int x){
  N_ = n;
  M_ = m;
  X_ = x;
  assert (X_ <= (N_*M_));
  //visited_.resize(N_*M_);
  if(X_ > (N_*M_)) std::cout << "Has introducido mas obstaculos de lo posible." << std::endl;
  for (int i = 0; i < N_; i++) {
    std::vector <int> aux;
    for (int j = 0; j < M_; j++) {
      aux.push_back(0);
    }
    Malla_.push_back(aux);
  }
  if( x != 0) ColocarObstaculosAleatorio();
}


//Constructor que recibe el tamaño de la malla, 
// el numero de obstaculos y la libertad de situarlos aleatoriamente
Entorno::Entorno(int n, int m, int x, int modo){
  N_ = n;
  M_ = m;
  X_ = x;
 // visited_.resize(N_*M_);
  assert (X_ <= (N_*M_));
  for (int i = 0; i < N_; i++) {
    std::vector <int> aux;
    for (int j = 0; j < M_; j++) {
      aux.push_back(0);
    }
    Malla_.push_back(aux);
  }

  if(modo == aleatorio) {
    std::cout << "Se situarán aleatoriamente...\n";
    ColocarObstaculosAleatorio();
  }
  if(modo == manual){
    std::cout << "Modo manual\n";
    ColocarObstaculosManual();
  }     


}

Entorno::Entorno(std::string& nombre){
  std::fstream fichero;
  int pos_X, pos_Y;
  std::string aux;
  
  fichero.open(nombre);
  assert(fichero);
  
// Leo la dimensión del entorno y el numero de obstaculos
    std::getline(fichero,aux);
    N_ = std::stoi(aux);
    std::getline(fichero,aux);
    M_ = std::stoi(aux);
    std::getline(fichero,aux);
    X_ = std::stoi(aux);
    assert(M_ != 0 && N_ != 0);
   // visited_.resize(N_*M_);
  
//Poner la matriz a 0
    ZeroFill();
    

// Set posición Inicial del coche
    std::getline(fichero,aux);    std::getline(fichero, aux);
    pos_X = std::stoi(aux);
    std::getline(fichero, aux);
    pos_Y = std::stoi(aux);
    set_car(pos_X,pos_Y);

// Set posición Final del coche
    std::getline(fichero,aux);  std::getline(fichero, aux);
    pos_X = std::stoi(aux);
    std::getline(fichero, aux);
    pos_Y = std::stoi(aux);
    set_end(pos_X,pos_Y);


    do {      
      for (int i = 0; i < X_; i++) {
       std::getline(fichero,aux); std::getline(fichero,aux);
       pos_X = std::stoi(aux);
       std::getline(fichero,aux);
       pos_Y = std::stoi(aux);
       //compruebo que no se solapen obstaculos con el punto A  y B
       if(get_state(pos_X,pos_Y) == (START_ID || END_ID )) {
        std::cout << " EASTas suprimendo el punto de partida del coche, cambiar la posición del obstaculo.";
       }
       set_obstaculo(pos_X,pos_Y);
      }
    }while(get_state(pos_X,pos_Y) != WALL_ID);

    fichero.close();

    std::cout << " Posición inicial " << car_.GetPos().first << " - " << car_.GetPos().second << "\n";
    std::cout << " Posición Final " << end_.first << " - " << end_.second << "\n";
    
}

//Destructor por defecto
Entorno::~Entorno(){}

// --------------------------------------

// SETTERS----------------------------------
void Entorno::set_car(int& x, int& y) {
   Malla_.at(x).at(y) = START_ID;
   car_.SetPos(x,y);
  
}

void Entorno::set_end(int& x, int& y) {
   Malla_.at(x).at(y) = END_ID;
   end_.first = x;
   end_.second = y;
}
// --------------------------------------

// COLOCACION DE OBSTACULOS--------------
void Entorno::ColocarObstaculosAleatorio(){
  int posX, posY;
  for (int i = 0; i < X_; i++) {
    posX = rand() % N_;
    posY = rand() % M_; 
    if (get_state(posX, posY) != 0){
      i--;
      }
    else{
      set_obstaculo(posX, posY);
      }
  }
}

void Entorno::ColocarObstaculosManual(){
  std::cout << "Manual\n";
  int obsx, obsy;
	for(int i = 0; i < X_; i++) {
		std::cout << "Introducir la posición de cada obstaculo: ";
		std::cin >> obsx >> obsy;
		set_obstaculo(obsx, obsy);
		}

}
// --------------------------------------

// FUNCIONES HEURÍSTICAS-----------------
int Entorno::Manhattan(int x1, int y1, int x2, int y2) {

int distance = 0;
int dif_x = x1 - x2;
int dif_y = y1 - y2;

if(dif_x < 0) dif_x = -dif_x;
if(dif_y < 0) dif_y = -dif_y;

  distance= dif_x + dif_y;
  std::cout << distance ;
return distance;

}

int Entorno::Manhattan(int x, int y){
  int distance = 0;
  int dif_x = x - end_.first;
  int dif_y = y - end_.second;

  if(dif_x < 0) dif_x = -dif_x;
  if(dif_y < 0) dif_y = -dif_y;
  distance= dif_x + dif_y;
  return distance;
}

double Entorno::Euclidean(double x1, double y1, double x2, double y2) {
	double x = x1 - x2;          //calculating number to square in next step
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);                  
  std::cout << dist;
	return dist;
}

double Entorno::Euclidean(double x1, double y1) {
	double x = x1 - end_.first;          //calculating number to square in next step
	double y = y1 - end_.second;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);                  

	return dist;
}

//IMPRIMIR ENTORNO --------------------------------------

void Entorno::show_malla(){
  for (int i = 2; i < M_+2; i++) {
    std::cout << UPPERLIMIT;
  }
 std::cout << "\n";
  
  for (int i = 0; i < M_; i++) {
    std::cout << LIMIT << "";
    for (int j = 0; j < N_; j++) {
      switch (Malla_.at(i).at(j)) { 
        case START_ID:
              std::cout << START_CHR; break;
        case END_ID:
              std::cout << END_CHR;   break;
        case WALL_ID:
              std::cout << WALL_CHR;  break;
        case PASS_ID:
              std::cout << PASS_CHR;  break;
        case PATH_ID:
               std::cout<< GREEN<<PATH_CHR<<RESET ;  break;

         default: 
        std::cout << "Error in the matrix implementation";
      }
    }
    std::cout << LIMIT << "";
    std::cout << std::endl;
}
  for (int i = 2; i <M_+2; i++) {
    std::cout << UPPERLIMIT;
  }
   std::cout << std::endl;
}

//CHECK SI PUEDE O NO IR A UNA CELDA CERCANA
bool Entorno::IsThereAnObstacle(int x, int y){
 // bool result = false;
  if(x < 0 || x > N_) { return true; }
  if(y > M_ || y < 0) { return true; }
  if(Malla_.at(x).at(y) == WALL_ID)  {return true; }
 // if(visited_.at(x).at(y)) { return true;}
  return false;
}

void Entorno::CaminoManhattan(std::vector<int>& caminos, std::pair<int,int> actual_pos){

        if (!IsThereAnObstacle(actual_pos.first-1,actual_pos.second))
          caminos[NORTH] = Manhattan(actual_pos.first-1, actual_pos.second);
        else{caminos[NORTH] = 99999;}
        if (!IsThereAnObstacle(actual_pos.first+1,actual_pos.second))
          caminos[SOUTH] = Manhattan(actual_pos.first+1, actual_pos.second);
        else{caminos[SOUTH] = 99999;}  
        if (!IsThereAnObstacle(actual_pos.first , actual_pos.second-1)) 
          caminos[WEST] = Manhattan(actual_pos.first , actual_pos.second- 1);
        else{caminos[WEST] = 99999;}
        if (!IsThereAnObstacle(actual_pos.first, actual_pos.second + 1)) 
          caminos[EAST] = Manhattan(actual_pos.first , actual_pos.second+ 1);
        else{caminos[EAST] = 99999;}
  
}

void Entorno::CaminoEuclidean(std::vector<int>& caminos, std::pair<int,int> actual_pos){
  
        if (!IsThereAnObstacle(actual_pos.first-1,actual_pos.second))
          caminos[NORTH] = Euclidean(actual_pos.first-1, actual_pos.second);
        else{caminos[NORTH] = 99999;}
        if (!IsThereAnObstacle(actual_pos.first+1,actual_pos.second))
          caminos[SOUTH] = Euclidean(actual_pos.first + 1, actual_pos.second);
        else{caminos[SOUTH] = 99999;}  
        if (!IsThereAnObstacle(actual_pos.first , actual_pos.second-1 ))
          caminos[WEST] = Euclidean(actual_pos.first , actual_pos.second- 1);
        else{caminos[WEST] = 99999;}
        if (!IsThereAnObstacle(actual_pos.first , actual_pos.second+ 1))
          caminos[EAST] = Euclidean(actual_pos.first , actual_pos.second+ 1);
        else{caminos[EAST] = 99999;}
  
}


int Entorno::Direccion(std::vector<int>caminos){
    int camino_menor = 99999;
    int index_menor;

    for(int i = 0; i < 4; i++){
      if(caminos[i] < camino_menor){
        camino_menor = caminos[i];
        index_menor = i;
      }
    }
    return index_menor;
}

int Entorno::ComparadorCaminos(std::vector<int>& caminoM, std::vector<int>& caminoE ){
  int select = 0;
  int lower = 99999;
  for (int i = 0; i < 4; i++){
    if(caminoE[i] < lower){
      lower = caminoE[i];
      select = 2;
    }
    if(caminoM[i] < lower){
      lower = caminoM[i];
      select = 1;
    }
  }
  return select;
}

void Entorno::Solve() {
  // vectores que guardan el contenido de las cuatros direcciones 
  std::vector<int> caminosM;
  std::vector<int> caminosE;
  caminosM.resize(4);
  caminosE.resize(4);
  std::pair<int,int> actual_pos = car_.GetPos();
  int cost_min=0;
  

  do {
     // std::cout << actual_pos.first << actual_pos.second;
      // mira lo que hay en las cuatros casillas vecinas cada iteración
        car_.ActualizarSensor(this);
        CaminoManhattan(caminosM, actual_pos);
        CaminoEuclidean(caminosE, actual_pos);

    int index_menor;

    if(ComparadorCaminos(caminosM, caminosE) == 1){
      index_menor = Direccion(caminosM);
    }
    else{
      index_menor = Direccion(caminosE);
    }
    
    //Saca la direccion del menor coste
    switch (index_menor)
    {
        case 0:{ 
          // x-- north
          actual_pos.first = actual_pos.first - 1;
          cost_min++;
         
          break;
          }
        
        case 1:{
          //x++ sur
          actual_pos.first = actual_pos.first + 1;
         cost_min++;
          break;
          }

        case 2:{
            //y-- oeste
          actual_pos.second = actual_pos.second - 1;
          cost_min++;
          break;
          }

        case 3:{
          //y++ est
           actual_pos.second = actual_pos.second + 1;
           cost_min++;
          break;
          }
          
    }

    if(actual_pos != end_)
      Malla_[actual_pos.first][actual_pos.second] = 2;

  } while (actual_pos != end_);

  std::cout << "El coste del camino minimo es: "<< cost_min << std::endl;
  std::cout << "El numero de nodos expandidos es: "<< exp_nod_ << std::endl;

}

//RELLENA MATRIZ DE 0 = PASS_ID
void Entorno::ZeroFill(){
  // Relleno la matríz con ceros
  for (int i = 0; i < N_; i++) {
    std::vector <int> aux;
    for (int j = 0; j < M_; j++){
      aux.push_back(PASS_ID);
    }
    Malla_.push_back(aux);
  }
}




