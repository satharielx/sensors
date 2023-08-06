/*
   Description: 
   - This simple application serves as a sophisticated simulation platform designed to replicate the intricate operations of embedded software systems.
   Author: Sathariel
*/

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "sensors.h"
#include <thread>
#include <chrono>
#include <iomanip>

void UpdateData(const Sensor& sensor) {
	while (true) {
		std::string name = sensor.GetName();
		double value = sensor.GetData();
		std::cout << "Sensor: " << name << ", Value: " << value << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

int main() {

	HMODULE baseAddress = GetModuleHandle(NULL);
	uintptr_t baseAddressv = reinterpret_cast<uintptr_t>(baseAddress);

	TemperatureSensor tempSensor("Temperature Sensor");
	HumiditySensor humiditySensor("Humidity Sensor");

	//Printing out our sensors app's base address so our control panel can access its memory space.
	std::cout << "Current base address is: " << std::hex << baseAddressv << std::endl;

	//Getting our sensors' values addresses, so our control panel can access their memory space and get their value.
	uintptr_t temperatureAddress = Sensor::GetMemberFunctionAddress(&TemperatureSensor::GetData);
	uintptr_t humidityAddress = Sensor::GetMemberFunctionAddress(&HumiditySensor::GetData);
	
	//Getting offset from the base address to our function that serves the sensors' metrics.
	std::cout << "Offset of TemperatureSensor::GetData(): " << std::hex << temperatureAddress << std::endl;
	std::cout << "Offset of HumiditySensor::GetData(): " << std::hex << humidityAddress << std::endl;

	//Threads reading the updated metrics value recorded by the sensors.
	std::thread tempThread([&tempSensor]() { UpdateData(tempSensor); });
	std::thread humidityThread([&humiditySensor]() { UpdateData(humiditySensor); });


	tempThread.join();
	humidityThread.join();

	return 0;
}