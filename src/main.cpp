// 2976G Tipping Point Code
#include "asignment.hpp"

// LLEMU's center button
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		lcd::set_text(2, "Made by Phillip, Janzen, Ethn, Blake");
	} else {
		lcd::clear_line(2);
	}
}

// Automatically do some preperations before the match starts
void compReady() {
	bool readyClamp = false;
	while (!autonGo && !usercontrol) {

		// Controlling what side we want auton to go 
		if (oleana.get_digital(DIGITAL_X) && !sideAuto) {
			sideAuto == !sideAuto;
		} else if (oleana.get_digital(DIGITAL_A) && sideAuto) {
			sideAuto == !sideAuto;
		}

		// Telling the user what side of auton we're using
		if (sideAuto) {
			oleana.clear_line(0);
			oleana.print(0, 0, "Auton on the Right");
		} else if (!sideAuto) {
			oleana.clear_line(0);
			oleana.print(0, 0, "Auton on the Left");
		} 

		// Check if we have pumped up the canisters for the clamp
		while (!readyClamp) {
			oleana.clear_line(1);
			oleana.print(1, 0, "Have you pumped the canisters?");
			if (oleana.get_digital(DIGITAL_Y)) readyClamp = true;
		}

	delay(30);
	}

	bool readyLift = false;
	while (!readyLift) {
		if (LIFTO.get() >= 60) {
			DR4BL.move(-80);
			DR4BR.move(-80);
		} else if (LIFTO.get() <= 50) {
			DR4BL.move(0);
			DR4BR.move(0);
			readyLift = true;
		}
	delay(30);
	}
}

// Control function for the clamp
void clampCtrl() {
	while (1) {
		// User control
		if (usercontrol) {

			bool psshhh;
			// Preventing the piston to basically waste the air
			if (!(oleana.get_digital(DIGITAL_L2) && oleana.get_digital(DIGITAL_L1))) {
				// User control
				if (oleana.get_digital(DIGITAL_L2) && clampState == 0) {
					clampState = 1;
				} else if (oleana.get_digital(DIGITAL_L1) && clampState == 1){
					clampState = 0;
				}
			}
		}

		CLAMPY.set_value(clampState);
	delay(20);
	}
}

// Control function for the lift
void liftCtrl() {
	double liftPwr;
	while(1) {
		// Check if the lift bottomed out
		int liftBtm;
		if (LIFTO.get() <= 30 ) {
			liftBtm = 0;
		} else if (LIFTO.get() >= 55) {
			liftBtm = 1;
		}

		// Controlling the motors
		if (usercontrol) {
		liftPwr = 127 * (oleana.get_digital(DIGITAL_R1) - (oleana.get_digital(DIGITAL_R2)* liftBtm));
		} else if (autonGo) {
		liftPwr = 70 * liftdir;	
		}
		
		// Lift Motors
		DR4BL.move(liftPwr);
		DR4BR.move(liftPwr);
		delay(20);
	}
}

// Pre-game housekeeping functions
void initialize() {

	// LCD Welcome
	lcd::initialize();
	lcd::set_text(1, "Hello VEX World!");
	lcd::register_btn1_cb(on_center_button);

	// Switching on tasks
	Task clampControl(clampCtrl);
	Task liftControl(liftCtrl);
	compReady();

}

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

// Autonomous code
void autonomous() {
autonGo = true;
	// Task myTask(drivePID);
    if (sideAuto) {
		LBM.move(127);
		LFM.move(127);
		RFM.move(127);
		RBM.move(127);
		delay(2400);
		LFM.move(0);
		LBM.move(0);
		RFM.move(0);
		RBM.move(0);
		clampState = 1;
		delay(100);
		LFM.move(-90);
		LBM.move(-90);
		RFM.move(-90);
		RBM.move(-90);
		delay(3000);
		clampState = 0;
		LFM.move(70);
		LBM.move(70);
		RFM.move(-70);
		RBM.move(-70);
		delay(1600);
		LFM.move(70);
		LBM.move(70);
		RFM.move(70);
		RBM.move(70);
		delay(750);
		LFM.move(-70);
		LBM.move(-70);
		RFM.move(-70);
		RBM.move(-70);
		delay(350);
		LFM.move(0);
		LBM.move(0);
		RFM.move(0);
		RBM.move(0);
	
	} else if (!sideAuto) {
	
		LFM.move(127);
		LBM.move(127);
		RFM.move(127);
		RBM.move(127);
		delay(1800);
		LFM.move(0);
		LBM.move(0);
		RFM.move(0);
		RBM.move(0);
		clampState = 1;
		delay(100);
		LFM.move(-90);
		LBM.move(-90);
		RFM.move(-90);
		RBM.move(-90);
		delay(2500);
		clampState = 0;
		LFM.move(70);
		LBM.move(70);
		RFM.move(-70);
		RBM.move(-70);
		delay(1600);
		LFM.move(70);
		LBM.move(70);
		RFM.move(70);
		RBM.move(70);
		delay(660);
		LFM.move(0);
		LBM.move(0);
		RFM.move(0);
		RBM.move(0);
		clampState = 1;
		delay(50);
		LFM.move(-70);
		LBM.move(-70);
		RFM.move(-70);
		RBM.move(-70);
		delay(750);
		LFM.move(0);
		LBM.move(0);
		RFM.move(0);
		RBM.move(0);
		clampState = 0;
	}
} 

// Driver control 
void opcontrol() {
	autonGo = false;
	usercontrol = true;
	while (usercontrol) {
	// Driving
		// Controller
		/* Control the robot with the Left Y Axis for forward 
	   	   and the Right X Axis for turning (Arcade Drive) */
		double mPwr = oleana.get_analog(ANALOG_LEFT_Y);
		double turn = oleana.get_analog(ANALOG_RIGHT_X);
		// Motors
		LBM.move(mPwr + turn);
		LFM.move(mPwr + turn);
		RBM.move(mPwr - turn);
		RFM.move(mPwr - turn);
	delay(20);
	}
}
