#include "EO556.h"
#include <Arduino.h>


EO556::EO556(int motorPwmPin, int motorDirPin, int motorEnPin, int pwmChannel) {
  MOTOR_PWM_PIN = motorPwmPin;
  MOTOR_DIR_PIN = motorDirPin;
  MOTOR_EN_PIN = motorEnPin;
  MOTOR_PWM_CHANNEL = pwmChannel;
}

void EO556::changeDutyCycle(int dutyCycle) {
  MOTOR_DUTY_CYCLE = dutyCycle;
  if (DEBUG == 1) {
    MESSAGE = MOTOR_ID + " : DUTY CYCLE CHANGED";
    Serial.println(MESSAGE);
  }
}

void EO556::changeResolution(int resolution) {
  MOTOR_PWM_RESOLUTION = resolution;
  if (DEBUG == 1) {
    MESSAGE = MOTOR_ID + " : RESOLUTION CHANGED";
    Serial.println(MESSAGE);
  }
}

void EO556::changeMaxFrequency(int frequency) {
  MAX_FREQUENCY = frequency;
  if (DEBUG == 1) {
    MESSAGE = MOTOR_ID + " : MAX FREQUENCY CHANGED";
    Serial.println(MESSAGE);
  }
}

void EO556::changeMinFrequency(int frequency) {
  MIN_FREQUENCY = frequency;
  if (DEBUG == 1) {
    MESSAGE = MOTOR_ID + " : MIN FREQUENCY CHANGED";
    Serial.println(MESSAGE);
  }
}

void EO556::begin() {
  pinMode(MOTOR_DIR_PIN, OUTPUT);
  pinMode(MOTOR_EN_PIN, OUTPUT);
  digitalWrite(MOTOR_EN_PIN, HIGH);
  digitalWrite(MOTOR_DIR_PIN, LOW);
  delay(MOTOR_START_DELAY_MS);
  ledcAttachChannel(MOTOR_PWM_PIN, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION, MOTOR_PWM_CHANNEL);
  ledcWrite(MOTOR_PWM_PIN, MOTOR_DUTY_CYCLE);
  if (DEBUG == 1) {
    MESSAGE = MOTOR_ID + " : MOTOR INSTALLATION COMPLETED";
    Serial.println(MESSAGE);
  }
}

void EO556::moveClockwise(int frequency) {
  MOTOR_PWM_FREQUENCY = frequency;
  if (!digitalRead(MOTOR_EN_PIN) == LOW) {
    digitalWrite(MOTOR_EN_PIN, LOW);
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : ENABLE PIN LOW";
      Serial.println(MESSAGE);
    }
  } else {
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : ENABLE PIN IS ALREADY LOW";
      Serial.println(MESSAGE);
    }
  }
  if (!digitalRead(MOTOR_DIR_PIN) == LOW) {
    digitalWrite(MOTOR_DIR_PIN, LOW);
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : DIR PIN LOW";
      Serial.println(MESSAGE);
    }
  } else {
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : DIR PIN IS ALREADY LOW";
      Serial.println(MESSAGE);
    }
  }
  if (MOTOR_PWM_FREQUENCY != MOTOR_LAST_PWM_FREQUENCY && MOTOR_PWM_FREQUENCY >= 10) {
    if (MOTOR_PWM_FREQUENCY >= MIN_FREQUENCY && MOTOR_PWM_FREQUENCY <= MAX_FREQUENCY) {
      ledcWriteTone(MOTOR_PWM_PIN, MOTOR_PWM_FREQUENCY);
      MOTOR_LAST_PWM_FREQUENCY = MOTOR_PWM_FREQUENCY;
      if (DEBUG == 1) {
        MESSAGE = MOTOR_ID + " : MOTOR IS (CLOCK WISE) SPINNING AT " + MOTOR_PWM_FREQUENCY + " FREQUENCY";
        Serial.println(MESSAGE);
      }
    } else {
      if (MOTOR_PWM_FREQUENCY <= MIN_FREQUENCY) {
        ledcWriteTone(MOTOR_PWM_PIN, MIN_FREQUENCY);
        MOTOR_LAST_PWM_FREQUENCY = MIN_FREQUENCY;
        if (DEBUG == 1) {
          MESSAGE = MOTOR_ID + " : A VALUE BELOW THE MINIMUM FREQUENCY HAS BEEN RECEIVED";
          Serial.println(MESSAGE);
          MESSAGE = MOTOR_ID + " : MOTOR IS (CLOCK WISE) SPINNING AT " + MIN_FREQUENCY + " FREQUENCY";
          Serial.println(MESSAGE);
        }
      } else if (MOTOR_PWM_FREQUENCY >= MAX_FREQUENCY) {
        ledcWriteTone(MOTOR_PWM_PIN, MAX_FREQUENCY);
        MOTOR_LAST_PWM_FREQUENCY = MAX_FREQUENCY;
        if (DEBUG == 1) {
          MESSAGE = MOTOR_ID + " : A VALUE BELOW THE MAXIMUM FREQUENCY HAS BEEN RECEIVED";
          Serial.println(MESSAGE);
          MESSAGE = MOTOR_ID + " : MOTOR IS (CLOCK WISE) SPINNING AT " + MAX_FREQUENCY + " FREQUENCY";
          Serial.println(MESSAGE);
        }
      }
    }
  }
}

void EO556::stop() {
  if (!digitalRead(MOTOR_EN_PIN) == HIGH) {
    digitalWrite(MOTOR_EN_PIN, HIGH);
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : DIR PIN HIGH";
      Serial.println(MESSAGE);
    }
  } else {
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : DIR PIN IS ALREADY HIGH";
      Serial.println(MESSAGE);
    }
  }
  MOTOR_PWM_FREQUENCY = 10;
  MOTOR_LAST_PWM_FREQUENCY = 0;
  ledcWriteTone(MOTOR_PWM_PIN, MOTOR_PWM_FREQUENCY);
  if (DEBUG == 1) {
    MESSAGE = MOTOR_ID + " : MOTOR STOP";
    Serial.println(MESSAGE);
  }
}

void EO556::moveCounterClockwise(int frequency) {
  MOTOR_PWM_FREQUENCY = frequency;
  if (!digitalRead(MOTOR_EN_PIN) == LOW) {
    digitalWrite(MOTOR_EN_PIN, LOW);
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : ENABLE PIN LOW";
      Serial.println(MESSAGE);
    }
  } else {
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : ENABLE PIN IS ALREADY LOW";
      Serial.println(MESSAGE);
    }
  }
  if (!digitalRead(MOTOR_DIR_PIN) == HIGH) {
    digitalWrite(MOTOR_DIR_PIN, HIGH);
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : DIR PIN HIGH";
      Serial.println(MESSAGE);
    }
  } else {
    if (DEBUG == 1) {
      MESSAGE = MOTOR_ID + " : DIR PIN IS ALREADY HIGH";
      Serial.println(MESSAGE);
    }
  }
  if (MOTOR_PWM_FREQUENCY != MOTOR_LAST_PWM_FREQUENCY && MOTOR_PWM_FREQUENCY >= 10) {
    if (MOTOR_PWM_FREQUENCY >= MIN_FREQUENCY && MOTOR_PWM_FREQUENCY <= MAX_FREQUENCY) {
      ledcWriteTone(MOTOR_PWM_PIN, MOTOR_PWM_FREQUENCY);
      MOTOR_LAST_PWM_FREQUENCY = MOTOR_PWM_FREQUENCY;
      if (DEBUG == 1) {
        MESSAGE = MOTOR_ID + " : MOTOR IS (COUNTER CLOCK WISE) SPINNING AT " + MOTOR_PWM_FREQUENCY + " FREQUENCY";
        Serial.println(MESSAGE);
      }
    } else {
      if (MOTOR_PWM_FREQUENCY <= MIN_FREQUENCY) {
        ledcWriteTone(MOTOR_PWM_PIN, MIN_FREQUENCY);
        MOTOR_LAST_PWM_FREQUENCY = MIN_FREQUENCY;
        if (DEBUG == 1) {
          MESSAGE = MOTOR_ID + " : A VALUE BELOW THE MINIMUM FREQUENCY HAS BEEN RECEIVED";
          Serial.println(MESSAGE);
          MESSAGE = MOTOR_ID + " : MOTOR IS (COUNTER CLOCK WISE) SPINNING AT " + MIN_FREQUENCY + " FREQUENCY";
          Serial.println(MESSAGE);
        }
      } else if (MOTOR_PWM_FREQUENCY >= MAX_FREQUENCY) {
        ledcWriteTone(MOTOR_PWM_PIN, MAX_FREQUENCY);
        MOTOR_LAST_PWM_FREQUENCY = MAX_FREQUENCY;
        if (DEBUG == 1) {
          MESSAGE = MOTOR_ID + " : A VALUE BELOW THE MAXIMUM FREQUENCY HAS BEEN RECEIVED";
          Serial.println(MESSAGE);
          MESSAGE = MOTOR_ID + " : MOTOR IS (COUNTER CLOCK WISE) SPINNING AT " + MAX_FREQUENCY + " FREQUENCY";
          Serial.println(MESSAGE);
        }
      }
    }
  }
}

void EO556::openDebug(String motorID) {
  DEBUG = 1;
  MOTOR_ID = motorID;
  MESSAGE = MOTOR_ID + " : DEBUG MODE OPEN";
  Serial.println(MESSAGE);
}

void EO556::disableDebug() {
  DEBUG = 0;
  MESSAGE = MOTOR_ID + " : DEBUG MODE OFF";
  Serial.println(MESSAGE);
}
