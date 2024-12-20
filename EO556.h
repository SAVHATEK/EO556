#ifndef EO556_H
#define EO556_H
#include <Arduino.h>

class EO556 {
public:
  EO556(int motorPwmPin, int motorDirPin, int motorEnPin, int pwmChannel);
  void begin();
  void changeDutyCycle(int dutyCycle);
  void changeResolution(int resolution);
  void moveClockwise(int frequency);
  void stop();
  void moveCounterClockwise(int frequency);
  void changeMinFrequency(int frequency);
  void changeMaxFrequency(int frequency);
  void openDebug(String motorID);
  void disableDebug();


private:
  int MOTOR_PWM_PIN;
  int MOTOR_DIR_PIN;
  int MOTOR_EN_PIN;
  int MOTOR_PWM_CHANNEL;
  int MOTOR_PWM_FREQUENCY = 10;
  int MOTOR_LAST_PWM_FREQUENCY = 10;
  int MOTOR_DUTY_CYCLE = 128;
  int MOTOR_PWM_RESOLUTION = 8;
  int MOTOR_START_DELAY_MS = 100;
  int MAX_FREQUENCY = 10000;
  int MIN_FREQUENCY = 10;
  int DEBUG = 0;
  String MOTOR_ID;
  String MESSAGE;
};

#endif