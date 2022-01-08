#include "main.h"


void autonmo() {
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