#ifndef GPIO_H
#define GPIO_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

class GPIO {
private:
  // port parameters
  int gpioPinNumber;
  std::string direction;
  int value;
  // filename strings
  std::string GPIOFile;
  std::string GPIOValueFile;
  std::string GPIODirectionFile;

public:
  GPIO(int gpioPinNumberr, std::string directionn);
  ~GPIO();
  void setValue(int Valuee);
  int getValue();
};

#endif