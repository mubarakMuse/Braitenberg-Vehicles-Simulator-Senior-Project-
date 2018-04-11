
#include <math.h> 

#include "src/food_sensor.h"
#include "src/food.h"
#include "src/params.h"



NAMESPACE_BEGIN(csci3081);
int count1 = 0;

int FoodSensor::CalculateReading( Food *ent){
  int reading = 0;
	Pose mypose= get_pose();
	double deltaX = mypose.x - ent->get_pose().x;
  double deltaY = mypose.y - ent->get_pose().y; 
  count1++;
  // std::cout << count1;
  //std::cout << ent->get_pose().x;
  double distance = (pow( deltaX*deltaX + deltaY*deltaY, 0.5) - 16);
  reading = 1200/(pow(1.00,distance));
  //std::cout <<  reading << "    ";
  return reading;
}
  

void FoodSensor::update( std::vector<class ArenaEntity *> stimili){
  int reading = get_reading();
  
  for (auto &food : stimili){
    
    //std::cout << count;
  	reading += CalculateReading(dynamic_cast<Food *>(food));
  }	

  if (reading > 1000) {
  	reading = 1000;
  } 
  //std::cout <<  reading << "    ";    
  set_reading(reading);
count1 =0;
};

void FoodSensor::Reset() {
  	set_reading(0);
  }




NAMESPACE_END(csci3081);
