#include "main.h"

// Stating Components
	// V5 Parts
		// Controller
			// Name of the controller is master since it's the main controller incase we use 2 controllers
			Controller master (E_CONTROLLER_MASTER);
			// This is if we use a 2nd controller
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
	// Tri port
		// Piston
			ADIDigitalOut CLAMPY(7);
		// Encoders
			ADIEncoder LYEN(1, 2, false);
			ADIEncoder RYEN(3, 4, false);