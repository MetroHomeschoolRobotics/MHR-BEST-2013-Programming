#pragma config(Motor,  port2,           turret,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           shoulder,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           extend,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           wrist,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           lmag,          tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           rmag,          tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int rightX;
int leftX;
int leftY;



task armMovement() {
	while(on) {
	}
	// Turret Movement

	if(vexRT[Btn6D]) {
		motor[turret] = -rightX;
		} else {
		motor[arm] = 0;

	}

}
// Arm Movement

if(vexRT[Btn6U]) {
	motor[arm] = leftY;
	} else {
	motor[arm] = 0;
}

// Telescope Movement
if(vexRT[Btn5D]) {
	motor[extend] = 90;
	} else if(vexRT[Btn5U]) {
	motor[extend] = -64;
}
}




task main()
{StartTask(shoulder); // Starts "arm" Task
// Turret
// Extend Arm
// Wrist
// Shoulder
// Claw


}
StartTask(claw); // Starts "claw" Task
while(on) { // Keep Me Alive!!!!!!!!!!
rightX = vexRT[Ch1]; // Refresh rightX variable with JoyStick input
leftX = vexRT[Ch4]; // Refresh LeftX variable with Joy Stick's input
leftY = vexRT[Ch3]; // Refresh leftY variable with JoyStick input
}