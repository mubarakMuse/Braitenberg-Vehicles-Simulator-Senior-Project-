
#include "src/light_sensor.h"
#include "src/params.h"
#include <math.h> 


NAMESPACE_BEGIN(csci3081);

int LightSensor::CalculateReading(Light *ent){
  int reading = 0;
	Pose mypose= get_pose();
	double deltaX = mypose.x - ent->get_pose().x;
  double deltaY = mypose.y - ent->get_pose().y;  
  double distance = (pow( deltaX*deltaX + deltaY*deltaY, 0.5) - 30);
  reading = 1200/(pow(1.08,distance));
  return reading;
}
  

void LightSensor::update( std::vector<class Light *> stimili){
  	//set_reading(0);
  int reading = get_reading();
  for (auto light : stimili){
  	reading += CalculateReading(dynamic_cast<Light *>(light));
  }	
  if (reading > 1000) {
  	reading = 1000;
  }         
  set_reading(reading);
};

void LightSensor::Reset() {
  	set_reading(0);
  }




NAMESPACE_END(csci3081);


