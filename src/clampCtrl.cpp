#include "main.h"

// Control for the clamp
void clampCtrl() {
	while (1) {
		// User control
		if (usercontrol) {

			bool psshhh;
			// Preventing the piston to basically waste the air
			if (master.get_digital(DIGITAL_L2) && master.get_digital(DIGITAL_L1)) {
				psshhh = true;
			} else {
				psshhh = false;
			}
			
			// User control
			if (master.get_digital(DIGITAL_L2) && clampState == 0 && !psshhh) {
				clampState = 1;
			} else if (master.get_digital(DIGITAL_L1) && clampState == 1 && !psshhh){
				clampState = 0;
			}
		}

		CLAMPY.set_value(clampState);
	delay(20);
	}
}