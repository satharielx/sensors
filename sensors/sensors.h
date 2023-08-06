#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>

class Sensor {
public:
	/// <summary>
	/// Initializes a new generic sensor object.
	/// </summary>
	/// <param name="name">Sensor's name</param>
	Sensor(const std::string& name) : name(name) {}

	virtual ~Sensor() {}

	/// <summary>
	/// Gets sensor's metrics and data.
	/// </summary>
	/// <returns></returns>
	virtual double GetData() const = 0;
	/// <summary>
	/// Gets the sensor's name
	/// </summary>
	/// <returns>A string representing sensor's name.</returns>
	std::string GetName() const {
		return name;
	}
	/// <summary>
	/// The function takes a pointer to a member function (of any class) as its input and returns the memory address of that member function in the form of uintptr_t.
	/// </summary>
	/// <returns>Returns a unsigned int pointer of the address of a member</returns>
	template<typename T>
	static uintptr_t GetMemberFunctionAddress(T memberFunction) {
		union {
			T func;
			uintptr_t address;
		} u;
		u.func = memberFunction;
		return u.address;
	}
	/// <summary>
	/// The function gets the application's base address.
	/// </summary>
	/// <returns></returns>
	uintptr_t GetBaseAddress() const;

protected:
	std::string name;
};

class TemperatureSensor : public Sensor {
public:
	/// <summary>
	/// Initializes a new temperature sensor object.
	/// </summary>
	/// <param name="name">Sensor's name</param>
	TemperatureSensor(const std::string& name) : Sensor(name) {}
	/// <summary>
	/// Gets the temperature that the sensor recorded at that time.
	/// </summary>
	/// <returns>A double-precision floating point number representing the temperature in celsius.</returns>
	virtual double GetData() const override;
	
};

class HumiditySensor : public Sensor {
public: 
	/// <summary>
	/// Initializes a new humidity sensor object.
	/// </summary>
	/// <param name="name">Sensor's name</param>
	HumiditySensor(const std::string& name) : Sensor(name) {}
	/// <summary>
	/// Gets the humidity percentage in the air that the sensor recorded at that time.
	/// </summary>
	/// <returns>A double-precision floating point number representing the humidity percentage in the air.</returns>
	virtual double GetData() const override;
	
};