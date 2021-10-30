#include "main.h"


// Stating Components
	Controller master (E_CONTROLLER_MASTER);
	Motor LBM(4 , E_MOTOR_GEARSET_18 , true);
	Motor LFM(8, E_MOTOR_GEARSET_18, true);
	Motor RFM(7, E_MOTOR_GEARSET_18, false);
	Motor RBM(5, E_MOTOR_GEARSET_18, false);
	Motor DR4BL(6, E_MOTOR_GEARSET_36, true);
	Motor DR4BR(11, E_MOTOR_GEARSET_36, false);

// Global Variables




/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
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

	return 1;
}


void autonomous() {

}

void opcontrol() {
	while (true) {

	// Driving
		// CONTROLLER
			float pwr = master.get_analog(ANALOG_LEFT_Y);
			float side = master.get_analog(ANALOG_LEFT_X);
			float turn = master.get_analog(ANALOG_RIGHT_X);
		// Motors
			LBM.move(pwr - side + turn);
			LFM.move(pwr + side + turn);
			RBM.move(pwr + side - turn);
			RFM.move(pwr - side - turn);

	// Special Stuff
		// Lifting
			double liftpwr = 127 * (master.get_digital(DIGITAL_R2) - master.get_digital(DIGITAL_R1));
			DR4BL.move(liftpwr);
			DR4BR.move(liftpwr);
		// Ringles
			

		delay(20);
	}
}
