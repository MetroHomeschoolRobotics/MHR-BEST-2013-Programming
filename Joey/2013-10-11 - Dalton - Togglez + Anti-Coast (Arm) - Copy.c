#pragma config(Motor,  port2,           arm,           tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           extend,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           rClaw,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           lClaw,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port8,           wrist,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           turret,        tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// 8U = Enable Free Arm Movement
// 7U = Disable Free Arm Movement
// Left Y (Ch3) + 6U = Arm
// Right X (Ch2) + 6D = Turret
// 7L = LClaw Open
// 7R = LClaw Close
// 8R = RClaw Open
// 8L = RClaw Close
// 7D = Both Claws Open
// 8D = Both Claws Close
// 5U = Extend
// 5D = Retract

int rightX;  // Holds Right Stick's X Position
int rightY;
int leftX; // Holds Left Stick's X Position
int leftY; // Holds Left Stick's Y Position
const bool on = true; // ALIVE!!!!!!
bool free = false;



task armMovement() {
	while(on) {
		// Turret Movement
		if(vexRT[Btn6D]) {
			motor[turret] = -leftX;
			} else {
			motor[turret] = 0;
		}

		// Arm Movement
		if(vexRT[Btn6U]) {
			motor[arm] = leftY+15;
			} else {
			motor[arm] = +15;
		}

		// Arm Toggle
		if(vexRT[Btn8U]) {
			free = true;
		}
		if(vexRT[Btn7U]) {
			free = false;
		}
		if (free) {
			motor[turret] = -leftX;
			motor[arm] = leftY;
		}

		// Telescope Movement
		if(vexRT[Btn5D]) {
			motor[extend] = 90;
			} else if(vexRT[Btn5U]) {
			motor[extend] = -90;
			} else {
			motor[extend] = 0;
		}

		//Wrist Movement

				if(rightY > 10) {
			motor[wrist] = rightY;
		} else if(rightY < -10) {
			motor[wrist] = rightY;
		} else {
			motor[wrist] = 0;
		}
	}
}

task claw() {
	while(on) {
		// Claw Movement

		// Left Claw
		if(vexRT[Btn7R]) { // Close
			if(motor[lClaw] < 127) {
				motor[lClaw] = motor[lClaw] + 1;
			}
			} else if(vexRT[Btn7L]) { // Open
			if(motor[lClaw] > -127) {
				motor[lClaw] = motor[lClaw] - 1;
			}
		}

		// Right Claw
		if(vexRT[Btn8L]) { // Close
			if(motor[rClaw] > -127) {
				motor[rClaw] = motor[rClaw] - 1;
			}
			} else if(vexRT[Btn8R]) { // Open
			if(motor[rClaw] < 127) {
				motor[rClaw] = motor[rClaw] + 1;
			}
		}

		// Both Claws
		if(vexRT[Btn8D]) { // Close
			if(motor[lClaw] < 127) {
				motor[lClaw] = motor[lClaw] + 1;
			}
			if(motor[rClaw] > -127) {
				motor[rClaw] = motor[rClaw] - 1;
			}
			} else if(vexRT[Btn7D]) { // Open
			if(motor[lClaw] > -127) {
				motor[lClaw] = motor[lClaw] - 1;
			}
			if(motor[rClaw] < 127) {
				motor[rClaw] = motor[rClaw] + 1;
			}
		}
		wait1Msec(5);
	}
}

task main() {
	StartTask(armMovement); // Starts "armMovement" Task
	StartTask(claw); // Starts "claw" Task
	while(on) { // Keep me alive!!!!!!!!!!!
		rightX = vexRT[Ch1]; // Refresh rightX variable with Joystick input
		rightY = vexRT[Ch2]; //Wrist
		leftX = vexRT[Ch4]; // Refresh LeftX variable with Joystick input
		leftY = vexRT[Ch3]; // Refresh leftY variable with Joystick input
	}
}
