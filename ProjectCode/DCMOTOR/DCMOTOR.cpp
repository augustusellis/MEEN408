#include "DCMOTOR.h"

DCMOTOR::DCMOTOR(int PWMNumberr, int EQEPNumberr)
    : motorPWM(PWMNumberr, 999999, 0), motorEQEP(EQEPNumberr) {
  // the commands above with : pwmconstructor, eqepconstructor are called an
  // initializer list. We used to initialize the member variables, especially
  // when they are a instances of our own classes
  setk_trq(0);
  setk_emf(0);
  // We now unenable the motor
  enable(0);
  // and are done with the constructor.
}
int DCMOTOR::getAngle() {
  return motorEQEP.readPosition(); // return the current EQEP position.
}
void DCMOTOR::setPWMPeriod(int Periodd) {
  motorPWM.setPeriod(Periodd); // set the pwm period in the pwm object
}
int DCMOTOR::getPWMPeriod() {
  return motorPWM.getPeriod(); // get the pwm period from the pwm object
}
void DCMOTOR::setPWMDutyCycle(int DutyCyclee) {
  int DutyCycleActual = int(DutyCyclee/100.0*getPWMPeriod());
  motorPWM.setDutyCycle(DutyCycleActual);
}
int DCMOTOR::getPWMDutyCycle() {
  return motorPWM.getDutyCycle(); // same as getPWMPeriod above
}
double DCMOTOR::setk_emf(double k_emff) { k_emf = k_emff; }
double DCMOTOR::getk_emf() { return k_emf; }
double DCMOTOR::setk_trq(double k_trqq) { k_trq = k_trqq; }
double DCMOTOR::getk_trq() { return k_trq; }
void DCMOTOR::enable(int enablee) {
  if (enablee != 0) { // so long as the input is not zero, we accept it as enable
    enablee = 1;
  }
  motorPWM.enable(enablee);
}


