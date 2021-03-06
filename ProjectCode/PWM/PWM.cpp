// Author: Augustus Ellis
#include <project/PWM.h>

PWM::PWM(int chipNumberr, int PWMNumberr, int Periodd, int DutyCyclee) {
  // check that inputs are valid - for now we assume they are valid
  // Set internal port parameters
  PWMNumber = PWMNumberr;
  DutyCycle = DutyCyclee;
  Period = Periodd;
  std::cout << "PWM Constructor Start\n.";
  if (!(chipNumberr == 0 || chipNumberr == 2)) {
    std::cout << "Cannot Access pwmchipx." << std::endl;
  }
  if (!(PWMNumberr == 0 || PWMNumberr == 1)) {
    std::cout << "Cannot Access pwmx." << std::endl;
  }
  // Set filename strings
  std::stringstream ss;
  ss << "/sys/class/pwm/pwmchip" << chipNumberr << "/pwm" << PWMNumber
     << "/";                      // PWMFile
  PWMFile = ss.str();             //
  ss.clear();                     //
  ss.str(std::string());          //
  ss << PWMFile << "period";      // PeriodFile
  PWMPeriodFile = ss.str();       //
  ss.clear();                     //
  ss.str(std::string());          //
  ss << PWMFile << "duty_cycle";  // DutyCycleFile
  PWMDutyCycleFile = ss.str();    //
  ss.clear();                     //
  ss.str(std::string());          //
  ss << PWMFile << "polarity";    // PolarityFile
  PWMPolarityFile = ss.str();     //
  ss.clear();                     //
  ss.str(std::string());          //
  ss << PWMFile << "enable";      // EnableFile
  PWMEnableFile = ss.str();       //
  ss.clear();                     //
  ss.str(std::string());          //

  // Check if the PWM device is in slots

  std::string PWMSlots = "/sys/devices/platform/bone_capemgr/slots";
  std::ofstream ofs;
  /*  ofs.open(PWMSlots.c_str(),
             std::ios::app);
    if (!(ofs.is_open())) {
      std::cout << "Cannot export the PWM Device to Slots\n";
      // throw exception;
    } else {
      ofs << "BB-PWM2";  // write pin number to export file
      std::cout << "Wrote to Slots" << std::endl;
      //usleep(100000);
      ofs.close(); // and close the file
    }
  */
  // Export the PWM  Number (this will make the pwm directory we can then use)
  ss << "/sys/class/pwm/pwmchip" << chipNumberr << "/export";  // PWMFile
  PWMExportFile = ss.str();
  ss.clear();                                                    //
  ss.str(std::string());                                         //
  ss << "/sys/class/pwm/pwmchip" << chipNumberr << "/unexport";  // PWMFile
  PWMUnexportFile = ss.str();
  ss.clear();             //
  ss.str(std::string());  //

  ofs.open(PWMExportFile.c_str(), std::ios::app);
  if (!(ofs.is_open())) {
    std::cout << "Cannot export the PWM Pin\n";
    // throw exception;
  } else {
    ofs << PWMNumber;  // write pin number to export file
    ofs.close();       // and close the file
    int dummy;
    std::cout << "Exported PWM pin." << std::endl;
  }
  // Disable pin Control
  enable(0);
  // Set Period and Duty Cycle
  std::cout << "Setting Period and Duty Cycle." << std::endl;
  setPeriod(Periodd);
  setDutyCycle(DutyCyclee);
  std::cout << "Period and Duty Cycle set." << std::endl;
  std::cout << "PWM Constructor End." << std::endl;
}

PWM::~PWM() {
  // Unexport the PWM
  setDutyCycle(0);
  std::ofstream ofs;
  ofs.open(PWMUnexportFile.c_str(), std::ios::app);
  if (!(ofs.is_open())) {
    std::cout << "Cannot unexport the PWM Pin\n";
    // throw exception;
  } else {
    ofs << PWMNumber;  // write pin number to unexport file
  }
  ofs.close();  // and close the file
}

void PWM::setPeriod(int Periodd) {
  std::ofstream ofs;
  ofs.open(PWMPeriodFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot set the PWM Period.";
    // throw exception;
  } else {
    Period = Periodd;
    ofs << Period;
    ofs.close();
    std::cout << "Period Set." << std::endl;
  }
}

void PWM::setDutyCycle(int DutyCyclee) {
  std::ofstream ofs;
  ofs.open(PWMDutyCycleFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot set the PWM Duty Cycle.";
    // throw exception;
  } else {
    DutyCycle = DutyCyclee;
    ofs << DutyCyclee;
    ofs.close();
  }
}

void PWM::setPolarity(std::string Polarityy) {
  std::ofstream ofs;
  ofs.open(PWMPolarityFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot set the PWM Polarity.";
    // throw exception;
  } else {
    Polarity = Polarityy;
    ofs << Polarityy;
    ofs.close();
  }
}
void PWM::enable(int enablee) {
  // First we truly disable the PWM if we unenable by setting duty cycle to
  // zero.
  std::ofstream ofs;
  ofs.open(PWMEnableFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot enable the PWM.";
    // throw exception;
  } else {
    Enabled = enablee;
    ofs << enablee;
    ofs.close();
  }
  if (enablee == 0) {
    int temp = DutyCycle;
    setDutyCycle(0);
    DutyCycle = temp;
  } else if (enablee == 1)  // otherwise reactivate PWM before enabling
  {
    setDutyCycle(DutyCycle);
  }
}

int PWM::getPeriod() {
  //  std::ifstream ifs;
  //  int PeriodValue = 0;
  //  ifs.open(PWMPeriodFile.c_str());
  //  if (!(ifs.is_open())) {
  //    std::cout << "Cannot get the PWM Period.\n";
  //    // throw exception;
  //  } else {
  //    ifs >> PeriodValue;
  //  }
  //  ifs.close();
  return Period;
}

int PWM::getDutyCycle() {
  //  std::ifstream ifs;
  //  int DutyCycleValue = 0;
  //  ifs.open(PWMDutyCycleFile.c_str());
  //  if (!(ifs.is_open())) {
  //    std::cout << "Cannot get the PWM Duty Cycle.\n";
  //    // throw exception;
  //  } else {
  //    ifs >> DutyCycleValue;
  //  }
  //  ifs.close();
  return DutyCycle;
}

std::string PWM::getPolarity() {
  //  std::ifstream ifs;
  //  std::string PolarityValue;
  //  ifs.open(PWMPolarityFile.c_str());
  //  if (!(ifs.is_open())) {
  //    std::cout << "Cannot get the PWM Polarity.\n";
  //    // throw exception;
  //  } else {
  //    ifs >> PolarityValue;
  //  }
  // ifs.close();
  return Polarity;
}
