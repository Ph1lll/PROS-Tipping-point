#include "main.h"

// Controllers
Controller oleana(CONTROLLER_MASTER);
Controller archie(CONTROLLER_PARTNER);

// Motors
Motor LBM(2, MOTOR_GEARSET_18, false);
Motor LFM(10, MOTOR_GEARSET_18, false);
Motor RFM(9, MOTOR_GEARSET_18, true);
Motor RBM(20, MOTOR_GEARSET_18, true);
Motor DR4BL(11, MOTOR_GEARSET_36, false);
Motor DR4BR(12, MOTOR_GEARSET_36, true);

// Distance
Distance LIFTO(19);

// Pistons
ADIDigitalOut liftClampy(2);
ADIDigitalOut lowerClampy(1);

// Global Variables
bool usercontrol = false;
bool autonGo = false;
bool sideAuto = false;
int liftdir = 0;
int clampLiftState = 0;
int clampLowerState = 0;
int mPwr = 0;
int turn = 0;

