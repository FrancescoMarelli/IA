#include "Car.h"


Car::Car() {
  pos_x_ = 0;
  pos_y_ = 0;
  pos_.first = 0;
  pos_.second = 0;
  Sensor_.resize(4);
}

Car::Car(int posx,int posy){
  pos_x_ = posx;
  pos_y_ = posy;
  pos_.first = pos_x_;
  pos_.second = pos_y_;
  Sensor_.resize(4);
}

Car::Car(std::pair<int,int> pos){
  pos_x_ = pos.first;
  pos_y_ = pos.second;
  pos_ = pos;
  Sensor_.resize(4);
}  

Car::~Car(){}

void Car::SetPos(int x, int y){ 
    pos_y_ = y;
    pos_x_ = x;

    pos_.first = x;
    pos_.second = y;
}

void Car::SetPos(std::pair<int,int> pos){
    pos_x_ = pos.first;
    pos_y_ = pos.second;
    pos_ = pos;
}

void Car::SetPosX(int x){ 
    pos_x_ = x;
    pos_.first = x;
}

void Car::SetPosY(int y){ 
    pos_y_ = y;
    pos_.second = y;
}

int Car::GetPosY(){
    return pos_y_;
    // return pos_.second:
}

int Car::GetPosX(){
    return pos_x_;
    // return pos.first;
}

std::pair<int,int> Car::GetPos(){
    return pos_;
}






