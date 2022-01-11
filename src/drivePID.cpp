#include "main.h"

// V5 Parts
	// Controller
	Controller master (E_CONTROLLER_MASTER);
	Controller partner (E_CONTROLLER_PARTNER);
	// Motors
	Motor LBM(3, E_MOTOR_GEARSET_18 , false);
	Motor LFM(2, E_MOTOR_GEARSET_18, false);
	Motor RFM(10, E_MOTOR_GEARSET_18, true);
	Motor RBM(1, E_MOTOR_GEARSET_18, true);
	Motor DR4BL(18, E_MOTOR_GEARSET_36, false);
	Motor DR4BR(19, E_MOTOR_GEARSET_36, true);
	// Distance
	Distance LIFTO(20);

/// Tri port
	// Piston
	ADIDigitalOut CLAMPY(7);
	// Encoders
	ADIEncoder LYEN(1, 2, false);
	ADIEncoder RYEN(3, 4, false);

// Global Variables
bool usercontrol = false;
bool autonGo = false;
bool sideAuto = false;
int liftdir = 0;
int clampState = 0;

// PID desired
double desired = 0;
double tesired = 0;

// PID system for autonomous that hopefully gets implemented
void drivePID() {

	// Encoders
	double yPos = LYEN.get_value() + RYEN.get_value();
	double tspoon  = LYEN.get_value() - RYEN.get_value();
	// PID system
    // Position
  	double error = 0;
  	double prevError = 0;
  	double deriv = 0;
    // Turning
  	float terror = 0;
  	float tPrevError = 0;
  	float teriv = 0;

	// Konstants
    	// Transform
  		double kP = 0;
  		double kI = 0;
  		double kD = 0;
    	// Rotate
  		double tkP = 0;
  		double tkI = 0;
  		double tkD = 0;

	while (!usercontrol) {
		// PID yPos
  		error = yPos - desired;
  		prevError += error;
  		deriv = error - prevError;
    	// PID Turning
  		terror = tspoon - tesired;
  		tPrevError += terror;
		teriv = terror - tPrevError;

		// Lateral movement
		double proton = (error * kP) + (prevError * kI) + (deriv * kD);
		double electron = (terror * tkP) + (tPrevError * tkI) + (teriv * tkD);

    	// Motor Asignment
	  	LBM.move_velocity(proton + electron);
      	LFM.move_velocity(proton + electron);
      	RBM.move_velocity(proton - electron);
      	RFM.move_velocity(proton - electron);

		delay(20);
	}
}