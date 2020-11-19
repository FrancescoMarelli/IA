#include <iostream>
#include <vector>
#include <utility> //Para los pairs


class Entorno;

class Car{
  private:
    std::pair<int,int> pos_;
		int pos_y_;
    int pos_x_;
		
  
	public:
    std::vector<int> Sensor_;
    
    int GetPosX();
    int GetPosY();
		std::pair<int,int> GetPos();
    
    void SetPosX(int pos_x);
    void SetPosY(int pos_y);
    void SetPos(int x, int y);
    void SetPos(std::pair<int,int> pos);


		void ActualizarSensor(Entorno*);

    Car();
    Car(int posx, int posy);
		Car(std::pair<int,int>);
    ~Car();
};

