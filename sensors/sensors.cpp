
#include "sensors.h"

double TemperatureSensor::GetData() const {
	double temperature = ((100 - 1) * ((float)rand() / RAND_MAX)) + 1;
	return temperature;
}

double HumiditySensor::GetData() const {
	double temperature = ((100 - 1) * ((float)rand() / RAND_MAX)) + 1;
	return temperature;
}

uintptr_t Sensor::GetBaseAddress() const {
	return reinterpret_cast<uintptr_t>(this);
}
/*

*/