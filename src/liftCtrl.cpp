#include "main.h"

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