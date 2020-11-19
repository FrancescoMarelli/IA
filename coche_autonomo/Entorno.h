#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>
#include <string>
#include <utility>
#include <stdlib.h>
#include "Car.cc"

#define PASS_ID  0
#define WALL_ID  1
#define PATH_ID  2
#define START_ID 8
#define END_ID   9
#define UPPER_ID 3
#define LIMIT_ID 4

#define WALL_CHR  "█"
#define PASS_CHR  " "
#define PATH_CHR  "*"
#define START_CHR "A"
#define END_CHR   "B"
#define LIMIT     "|"
#define UPPERLIMIT "-"
#define GREEN "\033[1m\033[32m"
#define RESET "\033[0m"

const int NORTH = 0;
const int SOUTH = 1;
const int WEST= 2;
const int EAST= 3;


const int aleatorio = 1;
const int manual = 0;



class Entorno
{
private:
  int M_, N_, X_;                                 
  std::vector< std::vector <int> > Malla_;
  Car car_;
  std::pair<int,int> end_;
  
  //std::vector<std::vector<bool>> visited_;
  void ColocarObstaculosAleatorio();
  

  void CaminoManhattan(std::vector<int>& caminos, std::pair<int,int> actual_pos);
  void CaminoEuclidean(std::vector<int>& caminos, std::pair<int,int> actual_pos);
  int Direccion(std::vector<int>caminos);
  int ComparadorCaminos(std::vector<int>& caminos, std::vector<int>& camino);

public:
int exp_nod_=0;
void ColocarObstaculosManual();
  Entorno();
  Entorno(std::string& nombre);
  Entorno(int n, int m);
  Entorno(int n, int m, int x);
  //Modo aleatorio es 1 y manual es 0 luego se puede
  // sustituir por la funcion de arriba y poner un if == 0 
  // y que haga las 2 funciones;
  Entorno(int n, int m, int x, int modo);
  ~Entorno();

   void ZeroFill();
   void LimitFill();


  inline int GetWidth(){ return M_;}
  inline int GetHeight(){ return N_;}
  inline int get_size() { return N_* M_; }
  inline int get_num_obst() { return X_; }
  inline int get_state(int x, int y) { return Malla_.at(x).at(y); }
  inline int get_state(std::pair<int,int> A) { return Malla_.at(A.first).at(A.second); }
  
  inline void clean_position(int x, int y) { Malla_[x][y] = 0; }
  inline void set_obstaculo(int& x, int& y) { Malla_.at(x).at(y) = 1; }
  // Inicializa el punto de partida del coche
  void set_car(int& x, int& y);
  // punto de llegada
  void set_end(int& x, int& y);

  int Manhattan(int x1, int y1, int x2, int y2);
  int Manhattan(int x1, int y1);
  double Euclidean(double x1, double y1, double x2, double y2);
  double Euclidean (double x1, double y1);
  //inline int get_car(int x, int y) { return ;Malla_.at(x).at(y); }

  //std::vector<int> Solve();
  bool IsThereAnObstacle(int i, int j);
  void show_malla();
 void Solve();
};


void Car::ActualizarSensor(Entorno* Malla){
  std::pair<int,int> aux_pos = pos_;

// Comprueba para cada dirección si hay una pared o no
//WEST
 if(aux_pos.first != 0){
  if (Malla->get_state(aux_pos.first, aux_pos.second - 1) == WALL_ID ) {
    Sensor_[WEST] = WALL_ID;
  }
  else{
    Sensor_[WEST] = 0; 
    Malla->exp_nod_++;
    
  }
}
else {Sensor_[WEST] = WALL_ID;  Malla->exp_nod_++;}
// EAST
if(aux_pos.first != Malla ->GetWidth()){
  if (Malla->get_state(aux_pos.first, aux_pos.second + 1) == WALL_ID) {
    Sensor_[EAST] = WALL_ID;
  }
  else{
    Sensor_[EAST] = 0; 
     Malla->exp_nod_++;
  }
}
else{ Sensor_[EAST] = WALL_ID;
 Malla->exp_nod_++; }

// NORTH
if(aux_pos.second != Malla ->GetHeight()){
  if (Malla->get_state(aux_pos.first - 1, aux_pos.second) == WALL_ID) {
    Sensor_[NORTH] = WALL_ID;
  }
  else{
     Sensor_[NORTH] = 0; 
      Malla->exp_nod_++;
     }
}
else{ Sensor_[NORTH] = WALL_ID; 
 Malla->exp_nod_++;}

// SOUTH
if(aux_pos.second != 0){
  if (Malla->get_state(aux_pos.first + 1, aux_pos.second) == WALL_ID) {
    Sensor_[SOUTH] = WALL_ID;
  }
  else{
     Sensor_[SOUTH] = 0; 
      Malla->exp_nod_++;
     }    
}
else{ Sensor_[SOUTH] = WALL_ID; 
 Malla->exp_nod_++;}



}