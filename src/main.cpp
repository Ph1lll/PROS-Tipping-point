// 2976G Tipping Point Code

#include "main.h"

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

// Autonomous code
void autonomous() {
autonGo = true;
void autonmo();

	/* if (sideAuto) {

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
	} */

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
