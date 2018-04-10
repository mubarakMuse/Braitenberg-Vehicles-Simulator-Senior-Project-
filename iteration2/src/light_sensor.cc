
#include <math.h> 

#include "src/light_sensor.h"
#include "src/light.h"
#include "src/params.h"



NAMESPACE_BEGIN(csci3081);

int count = 0;

int LightSensor::CalculateReading(Light *ent){
  int reading = 0;
	Pose mypose= get_pose();
	double deltaX = mypose.x - ent->get_pose().x;
  double deltaY = mypose.y - ent->get_pose().y;  
  //std::cout << deltaX << "  x  " << deltaY << "  y \n ";
  double distance = (pow( deltaX*deltaX + deltaY*deltaY, 0.5)-11);
  reading = 1200/(pow(1.02,distance));

  
  count++;
  // std::cout << count << "   " << 1200/(pow(1.02,distance))<< "\n";
  
  return reading;
}
  

void LightSensor::update( std::vector<class ArenaEntity *> stimili){
  int reading = 0;
  for (auto &light : stimili){
  	reading += CalculateReading(dynamic_cast<Light *>(light));
  }	
  count = 0;
  if (reading > 1000) {
  	reading = 1000;
  } 
  //std::cout <<  count << "----" << reading << "  ";  
  set_reading(reading);
  // std::cout << get_reading() << " ";
};

void LightSensor::Reset() {
  	set_reading(0);
  }




NAMESPACE_END(csci3081);


