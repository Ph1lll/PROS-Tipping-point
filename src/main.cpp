// 2976G Tipping Point Code

#include "main.h"
// This is all the electronics
#include "asignment.h"

// Global Variables
	bool usercontrol = false;
	bool autonGo = false;
	bool sideAuto = false;
	/*
		Declareing the clampState variable to specify what state we want the clamp's piston to be in
		We can also read this to determine what state the piston is currently in
	*/
	int clampState = 0;
	int liftdir = 0;

	// PID desired
		double desired = 0;
		double tesired = 0;

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

// Control for the lift
void liftCtrl() {
	double liftPwr;
	while(1) {
		// Lifting
			// Check if the lift bottomed out
			int liftBtm;
			if (LIFTO.get() <= 30 ) {
				liftBtm = 0;
			} else if (LIFTO.get() >= 55) {
				liftBtm = 1;
			}

			// Controlling the motors
			if (usercontrol) {
			liftPwr = 127 * (master.get_digital(DIGITAL_R1) - (master.get_digital(DIGITAL_R2)* liftBtm));
			} else if (autonGo) {
			liftPwr = 70 * liftdir;	
			}
			
			// Lift Motors
			DR4BL.move(liftPwr);
			DR4BR.move(liftPwr);
		delay(20);
	}
}

// Control for the clamp
void clampCtrl() {
	while (1) {
		/*
			The Solinoid valve uses just a boolean 1 and 0 for opening and closing the valve
			if the controller button R2 is pressed the piston will fire down and clamp on the MOGO
			if button R1 is pressed the piston releases and the clamp opens
			the variable clampState is used the in "if" statement so it doesn't fire when it already is clamped
		*/
		if (usercontrol) {
			if (master.get_digital(DIGITAL_L2) && clampState == 0) {
				clampState = 1;
				delay(30);
			} else if (master.get_digital(DIGITAL_L1) && clampState == 1){
				clampState = 0;
				delay(30);
			}
		}

		// Setting the state to either high or low for the piston to fire or retract
		CLAMPY.set_value(clampState);
	delay(20);
	}
}


// Automatically do some preperations before the match starts
void compReady() {
	while (!autonGo && !usercontrol) {

		// Controlling what side we want auton to go 
		if (master.get_digital(DIGITAL_X) && !sideAuto) {
			sideAuto == !sideAuto;
			delay(20);
		} else if (master.get_digital(DIGITAL_A) && sideAuto) {
			sideAuto == !sideAuto;
			delay(20);
		}

		// Telling the user what side of auton we're using
		if (sideAuto) {
			master.clear_line(0);
			master.print(0, 0, "Auton on the Right");
		} else if (!sideAuto) {
			master.clear_line(0);
			master.print(0, 0, "Auton on the Left");
		} 

		bool readyClamp = false;
		// Check if we have pumped up the canisters for the clamp
		while (!readyClamp) {
			master.clear_line(0);
			master.print(0, 0, "Have you pumped the canisters?");
			if (master.get_digital(DIGITAL_A)) readyClamp = true;
		}
		

		delay(30);
	}

	bool readyLift = false;
	while (!readyLift) {
		if (LIFTO.get() >= 50) {
			DR4BL.move(-80);
			DR4BR.move(-80);
		} else if (LIFTO.get() <= 50) { 
			readyLift = true;
		}
		delay(30);
	}
}


void initialize() {

	// LCD Welcome
	lcd::initialize();
	lcd::set_text(1, "Hello VEX World!");
	lcd::register_btn1_cb(on_center_button);

	// Switching on tasks
	Task liftControl(liftCtrl);
	Task clampControl(clampCtrl);
	compReady();

}

void disabled() {

}

void competition_initialize() {
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

// Autonomous code
void autonomous() {
autonGo = true;

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

void opcontrol() {
	autonGo = false;
	usercontrol = true;
		while (usercontrol) {
		// Driving
			// Controller
				/* Control the robot with the Left Y Axis for forward 
			   	   and the Right X Axis for turning (Arcade Drive) */
				double mPwr = master.get_analog(ANALOG_LEFT_Y);
				double turn = master.get_analog(ANALOG_RIGHT_X);
			// Motors
				LBM.move(mPwr + turn);
				LFM.move(mPwr + turn);
				RBM.move(mPwr - turn);
				RFM.move(mPwr - turn);
		delay(20);
		}
}
