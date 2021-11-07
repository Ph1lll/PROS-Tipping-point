// 2976G Tipping Point Code

#include "main.h"


// Stating Components
	// V5 Parts
		// Controller
			Controller master (E_CONTROLLER_MASTER);
		// Motors
			Motor	LBM(4 , E_MOTOR_GEARSET_18 , true);
			Motor 	LFM(8, E_MOTOR_GEARSET_18, true);
			Motor 	RFM(7, E_MOTOR_GEARSET_18, false);
			Motor 	RBM(5, E_MOTOR_GEARSET_18, false);
			Motor 	DR4BL(6, E_MOTOR_GEARSET_36, true);
			Motor	DR4BR(11, E_MOTOR_GEARSET_36, false);
			Motor	R_MTR(13, E_MOTOR_GEARSET_18, false);
	// Sensors
		// Distance
			Distance R_DIS(12);
		// Encoders
			ADIEncoder LYEN(1, 2, false);
			ADIEncoder RYEN(3, 4, false);
			ADIEncoder XEN(5, 6, false);

// Global Variables
	bool usercontrol = false;

	// PID desired
		double desired = 0;
		double sesired = 0;
		float tesired = 0;

// LLEMU's center button
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		lcd::set_text(2, "I was pressed!");
	} else {
		lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lcd::initialize();
	lcd::set_text(1, "Hello PROS User!");

	lcd::register_btn1_cb(on_center_button);

}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}



// PID system for autonomous that hopefully gets implemented
int drovePID() {

	// Encoders
		//
			double yPos = LYEN.get_value() + RYEN.get_value();
			double xPos = XEN.get_value();
			double tspoon  = LYEN.get_value() - RYEN.get_value();
	// PID system
    // y Position
      double error = 0;
      double prevError = 0;
      double deriv = 0;
    // x Pos
      double serror = 0;
      double sPrevError = 0;
      double seriv = 0;
    // Turning
      float terror = 0;
      float tPrevError = 0;
      float teriv = 0;

	// Konstants
    // Going forward
      double kP = 0;
      double kI = 0;
      double kD = 0;
    // Side
      double skP = 0;
      double skI = 0;
     	double skD = 0;
    // Turning
      double tkP = 0;
      double tkI = 0;
      double tkD = 0;

	while (!usercontrol) {
		// PID yPos
      error = yPos - desired;
      prevError += error;
      deriv = error - prevError;
    // PID xPos
      serror = xPos - sesired;
      sPrevError += serror;
      seriv = serror - sPrevError;
    // PID Turning
      terror = tspoon - tesired;
      tPrevError += terror;
      teriv = terror - tPrevError;

		// Lateral movement
      float proton = (error * kP) + (prevError * kI) + (deriv * kD);
      float neutron = (serror * skP) + (sPrevError * skI) + (seriv * skD);
      float electron = (terror * tkP) + (tPrevError * tkI) + (teriv * tkD);

    // Motor Asignment
			LBM.move_velocity(proton - neutron + electron);
      LFM.move_velocity(proton + neutron + electron);
      RBM.move_velocity(proton + neutron - electron);
      RFM.move_velocity(proton - neutron - electron);

			delay(20);
		}
	return 1;
}

// Autonomous code
void autonomous() {
Task drivePD(drovePID);


}

void opcontrol() {
	usercontrol = true;
	while (usercontrol) {
	// Driving
		// CONTROLLER
			float mpwr = master.get_analog(ANALOG_LEFT_Y);
			float side = master.get_analog(ANALOG_LEFT_X);
			float turn = master.get_analog(ANALOG_RIGHT_X);
		// Motors
			LBM.move(mpwr - side + turn);
			LFM.move(mpwr + side + turn);
			RBM.move(mpwr + side - turn);
			RFM.move(mpwr - side - turn);

	// Special Stuff
		// Lifting
			double liftpwr = 127 * (master.get_digital(DIGITAL_R2) - master.get_digital(DIGITAL_R1));
			DR4BL.move(liftpwr);
			DR4BR.move(liftpwr);
		// Ringles
			if(R_DIS.get() < 180 && !master.get_digital(DIGITAL_Y)) {
				R_MTR.move_velocity(100);
			} else if (master.get_digital(DIGITAL_Y)) {
				R_MTR.move_velocity(-100);
			} else {
				R_MTR.set_brake_mode(E_MOTOR_BRAKE_COAST);
			}

		delay(20);
	}
}
