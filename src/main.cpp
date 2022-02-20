// 2976G Tipping Point Code
#include "asignment.hpp"

// LLEMU's center button
void on_center_button()
{
	static bool pressed = !pressed;
	if (pressed)
	{
		lcd::set_text(2, "Made by Phillip, Janzen, Ethn, Blake, and Frank");
	}
	else
	{
		lcd::clear_line(2);
	}
}

// Function for controlling the drivetrain
void driveTrain()
{
	while (1)
	{
		LBM.move(mPwr + turn);
		LFM.move(mPwr + turn);
		RBM.move(mPwr - turn);
		RFM.move(mPwr - turn);
		delay(20);
	}
}

// Automatically do some preperations before the match starts
void compReady()
{
	bool readyClamp = false;
	bool readyLift = false;
	while (!autonGo && !usercontrol)
	{

		// Controlling what side we want auton to go
		if (oleana.get_digital(DIGITAL_X))
		{
			sideAuto == !sideAuto;
		}

		// Telling the user what side of auton we're using
		if (sideAuto)
		{
			oleana.clear_line(0);
			oleana.print(1, 0, "Auton on the Right");
		}
		else if (!sideAuto)
		{
			oleana.clear_line(0);
			oleana.print(1, 0, "Auton on the Left");
		}

		// Check if we have pumped up the canisters for the clamp
		while (!readyClamp)
		{
			oleana.clear_line(1);
			oleana.print(2, 0, "Have you pumped the canisters?");
			if (oleana.get_digital(DIGITAL_Y))
				readyClamp = true;
		}

		// Ensuring that the robot's lift is lowered
		while (!readyLift)
		{
			if (LIFTO.get() >= 60)
			{
				DR4BL.move(-80);
				DR4BR.move(-80);
			}
			else if (LIFTO.get() <= 50)
			{
				DR4BL.move(0);
				DR4BR.move(0);
				readyLift = true;
			}
		}

		if (usercontrol) break;
		delay(30);
	}
}

// Control function for the clamps
void clampCtrl()
{
	while (1)
	{
		// User control
		if (usercontrol)
		{
			// Lift Clamp
			if (oleana.get_digital_new_press(DIGITAL_L1))
			{
				clampLiftState = (clampLiftState == 1) ? 0 : 1;
			}

			// Lower Clamp
			if (oleana.get_digital_new_press(DIGITAL_L2))
			{
				clampLowerState = (clampLowerState == 1) ? 0 : 1;
			}
		}

		liftClampy.set_value(clampLiftState);
		lowerClampy.set_value(clampLowerState);
		delay(20);
	}
}

// Control function for the lift
void liftCtrl()
{
	DR4BL.set_brake_mode(MOTOR_BRAKE_HOLD);
	DR4BR.set_brake_mode(MOTOR_BRAKE_HOLD);

	double liftPwr;
	while (1)
	{
		// Check if the lift bottomed out
		int liftBtm;
		if (LIFTO.get() <= 30)
		{
			liftBtm = 0;
		}
		else if (LIFTO.get() >= 55)
		{
			liftBtm = 1;
		}

		// Controlling the motors
		if (usercontrol)
		{
			liftPwr = 127 * (oleana.get_digital(DIGITAL_R1) - (oleana.get_digital(DIGITAL_R2) * liftBtm));
		}
		else if (autonGo)
		{
			liftPwr = 80 * liftdir * liftBtm;
		}


		// Lift Motors
		DR4BL.move(liftPwr);
		DR4BR.move(liftPwr);
		delay(20);
	}
}

// Pre-game housekeeping functions
void initialize()
{

	// LCD Welcome
	lcd::initialize();
	lcd::set_text(1, "Hello VEX World!");
	lcd::register_btn1_cb(on_center_button);

	// Switching on tasks
	Task clampControl(clampCtrl);
	Task liftControl(liftCtrl);
	Task driving(driveTrain);
}

// Auton Variables
bool autonStop = false;
bool autonFighting = false;
void autonTop()
{
	while (autonGo)
	{
		// Checking what the current is (measured by mA)
		std::cout << "LBM Current Draw: " << LBM.get_current_draw();
		std::cout << "LFM Current Draw: " << LFM.get_current_draw();
		std::cout << "RBM Current Draw: " << RBM.get_current_draw();
		std::cout << "RFM Current Draw: " << RFM.get_current_draw();

		// Stop the Robot
		if (autonStop && !autonFighting)
		{
			mPwr = 0;
			turn = 0;
			autonStop = false;
		}

		if (usercontrol)
		{
			break;
		}
		delay(20);
	}
}

// Autonomous code
void autonomous()
{
	double liftTime = 500;
	autonGo = true;
	Task autonStopBool(autonTop);

	if (sideAuto)
	{
		mPwr = 127;
		delay(2400);
		autonStop = true;
		clampLiftState = 1;
		delay(100);
		liftdir = 1;
		mPwr = -90;
		delay(liftTime);
		liftdir = 0;
		delay(2500);
		mPwr = 0;
		liftdir = -1;
		delay(liftTime);
		liftdir = 0;
		clampLiftState = 0;
		turn = 70;
		delay(1600);
		turn = 0;
		mPwr = 70;
		delay(750);
		mPwr = -70;
		delay(350);
		mPwr = 0;
	}
	else if (!sideAuto)
	{
		mPwr = 127;
		delay(1800);
		autonStop = true;
		clampLiftState = 1;
		delay(100);
		mPwr = -90;
		liftdir = 1;
		delay(liftTime);
		liftdir = 0;
		delay(2000);
		mPwr = 0;
		liftdir = -1;
		delay(liftTime);
		liftdir = 0;
		clampLiftState = 0;
		delay(100);
		turn = 70;
		delay(1600);
		turn = 0;
		mPwr = 70;
		delay(660);
		autonStop = true;
		clampLiftState = 1;
		delay(50);
		liftdir = 1;
		mPwr = -70;
		delay(liftTime);
		liftdir = 0;
		delay(250);
		autonStop = true;
		liftdir = -1;
		delay(liftTime);
		liftdir = 0;
		clampLiftState = 0;
	}
}

// Driver control
void opcontrol()
{
	autonGo = false;
	usercontrol = true;
	int rev = 1;
	while (usercontrol)
	{
		oleana.print(1, 0, "Driver Control");

		if (usercontrol)
		{
			// Controller
			mPwr = (oleana.get_analog(ANALOG_LEFT_Y) * rev);
			turn = oleana.get_analog(ANALOG_RIGHT_X);

			if (oleana.get_digital_new_press(DIGITAL_DOWN))
			{
				rev = (rev == 1) ? -1 : 1;
				if (rev == -1) {
				oleana.print(0,0, "Reversed");
				} else {
				oleana.print(0,0, "0");	
				}
			}
		}
		delay(20);
	}
}