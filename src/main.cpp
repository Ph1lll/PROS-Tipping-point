// 2976G Tipping Point Code

#include "main.h"

// Stating Components
	// V5 Parts
		// Controller
			// Name of the controller is master since it's the main controller incase we use 2 controllers
			Controller master (E_CONTROLLER_MASTER);
			// This is if we use a 2nd controller
			Controller partner (E_CONTROLLER_PARTNER);
		// Motors
			/*
				The initialization of motors requires 4 things
				Name of the motor
				Declareing what port the motor is
				What gearset the motor uses
					Blue  6:1  E_MOTOR_GEARSET_06
Default:	Green 18:1 E_MOTOR_GEARSET_18
					Red   36:1 E_MOTOR_GEARSET_36
				And if it's reversed
			*/
			Motor LBM(13, E_MOTOR_GEARSET_18 , false);
			Motor LFM(2, E_MOTOR_GEARSET_18, false);
			Motor RFM(1, E_MOTOR_GEARSET_18, true);
			Motor RBM(12, E_MOTOR_GEARSET_18, true);
			Motor DR4BL(19, E_MOTOR_GEARSET_36, false);
			Motor DR4BR(20, E_MOTOR_GEARSET_36, true);
	// Piston
		/*
			ADI is for the tri port
			CLAMPY is the piston for the front clamp
		*/
		ADIDigitalOut CLAMPY(7);
	// Sensors
		// Encoders
			ADIEncoder LYEN(1, 2, false);
			ADIEncoder RYEN(3, 4, false);
		// Limit Switch
			ADIDigitalIn LIFTO(8);
// Global Variables
	bool usercontrol = false;
	/*
		Declareing the clampState variable to specify what state we want the clamp's piston to be in
		We can also read this to determine what state the piston is currently in
	*/
	int clampState = 0;

	// PID desired
		double desired = 0;
		double tesired = 0;

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

/*
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

// Control for the lift
void liftCtrl() {
	while(1) {
		// Lifting
			/*
				This is to check if the robot's lift is at the bottom
				If it is, then the robot's wont go any lower
			*/
			int liftBtm;
			if (LIFTO.get_value() == 1) {
				liftBtm = 0;
			} else if (LIFTO.get_value() == 0) {
				liftBtm = 1;
			}
			/*
				Declared variable for lifting the DR4B
				127 is because the (motor).move function uses volts
				times the boolean value of Button R1 minus R2 being 1,0, or -1
				R1 meaning going up and R2 going down
			*/
			double liftPwr = 127 * (master.get_digital(DIGITAL_R1) - (master.get_digital(DIGITAL_R2)* liftBtm));
			/*
			Move the motors for the DR4B proportional to the variable liftPwr
			The value can be 127 (up) 0 (Stop) or -127 (Reverse)
			*/
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
		if (master.get_digital(DIGITAL_L2) && clampState == 0) {
			clampState = 1;
		} else if (master.get_digital(DIGITAL_L1) && clampState == 1){
			clampState = 0;
		}

		// Setting the state to either high or low for the piston to fire or retract
		CLAMPY.set_value(clampState);
	delay(20);
	}
}


void initialize() {
	lcd::initialize();
	lcd::set_text(1, "Hello PROS User!");

	lcd::register_btn1_cb(on_center_button);

	Task liftControl(liftCtrl);
	Task clampControl(clampCtrl);

}



/*
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/*
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
	return 1;
}

// Autonomous code
void autonomous() {

	LFM.move(60);
	LBM.move(60);
	RFM.move(60);
	RBM.move(60);
	delay(1150);
	LFM.set_brake_mode(E_MOTOR_BRAKE_COAST);
	LBM.set_brake_mode(E_MOTOR_BRAKE_COAST);
	RFM.set_brake_mode(E_MOTOR_BRAKE_COAST);
	RBM.set_brake_mode(E_MOTOR_BRAKE_COAST);

	CLAMPY.set_value(1);
	delay(200);
	LFM.move(-50);
	LBM.move(-50);
	RFM.move(-50);
	RBM.move(-50);
	delay(500);
	LFM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	LBM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	RFM.set_brake_mode(E_MOTOR_BRAKE_COAST);
	RBM.set_brake_mode(E_MOTOR_BRAKE_COAST);

}

/*
	This is the driver control code
*/
void opcontrol() {
	usercontrol = true;
	while (usercontrol) {
	// Driving
		// CONTROLLER
			/*
				Our team uses the Arcade Control system instad of tank due to its simplicity
				mPwr is a variable to move the bot forward or backwards based on value from the verticle axis of the left joystick
				turn is a variable to turning the robot round the center of it, the value of turn is from the horizontial axis of the right joystick
			*/
			double mPwr = master.get_analog(ANALOG_LEFT_Y);
			double turn = master.get_analog(ANALOG_RIGHT_X);
		// Motors
			/*
				(motor).move function moves the motors
				mPwr moves the bot back and forward
				turn rotates the robot
				E.G. if I move the right joystick to the right the
				left set of the wheels would speed up and the right set would slow down
			*/
			LBM.move(mPwr + turn);
			LFM.move(mPwr + turn);
			RBM.move(mPwr - turn);
			RFM.move(mPwr - turn);
		delay(20);
	}
}
