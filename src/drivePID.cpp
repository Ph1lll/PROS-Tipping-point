#include "main.h"

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
    	// Going forward
      		double kP = 0;
      		double kI = 0;
      		double kD = 0;
    	// Turning
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