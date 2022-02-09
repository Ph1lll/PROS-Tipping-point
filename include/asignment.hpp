#include "main.h"

// Controllers
Controller oleana(CONTROLLER_MASTER);
Controller archie(CONTROLLER_PARTNER);
// Motors
Motor LBM(3, MOTOR_GEARSET_18, false);
Motor LFM(2, MOTOR_GEARSET_18, false);
Motor RFM(10, MOTOR_GEARSET_18, true);
Motor RBM(1, MOTOR_GEARSET_18, true);
Motor DR4BL(18, MOTOR_GEARSET_36, false);
Motor DR4BR(19, MOTOR_GEARSET_36, true);
// Distance
Distance LIFTO(20);
// Pistons
ADIDigitalOut liftClampy(7);
ADIDigitalOut lowerClampy(6);

// Global Variables
bool usercontrol = false;
bool autonGo = false;
bool sideAuto = false;
int liftdir = 0;
int clampLiftState = 0;
int clampLowerState = 0;
double mPwr = 0;
double turn = 0;

