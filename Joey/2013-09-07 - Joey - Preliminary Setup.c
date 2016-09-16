#pragma config(Motor,  port2,           ldrive,       tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           lclaw,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           arm,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           manip,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port8,           rclaw,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port9,           rdrive,           tmotorServoContinuousRotation, openLoop)

int inputCurve(float in, float power) {
	float out;
	if((power/2) == (float)((int)(power/2))) {
		out = (int)in^((int)power);
		if(in < 0) {
			return -(out);
		} else {
			return out;
		}
	} else {
		out = (int)in^(int)power;
		return out;
	}
}

void arcadeDrive(int x, int y, int curve = 1, int threshold = 10, tMotor& ldMotor = port2, tMotor& rdMotor = port9) {
	int lMotor;
	int rMotor;
	x = inputCurve(x, curve);
	y = inputCurve(y, curve);
	lMotor = y + x;
	rMotor = y + -x;
	if(abs(y) > threshold) { // Forwards and Backwards
		if(abs(x) > threshold) {
			lMotor = (y + x);
			rMotor = (y - x);
		} else {
			lMotor = y;
			rMotor = y;
		}
	}  else if((abs(x) > threshold) && (abs(y) < threshold)) { // Turning in Place
		lMotor = x;
		rMotor = -x;
	}  else { // If no controls held, disable motors
		lMotor = 0;
		rMotor = 0;
	}
	motor[ldMotor] = lMotor;
	motor[rdMotor] = rMotor;
	return;
}

task drive() {
	arcadeDrive(vexRT[Ch1], vexRT[Ch2]);
}

task main() {
	//Yay!  BEST 2013 Gatekeeper!!!
	StartTask(drive);
	bool running = true;
	while(running) {
		leftX = vexRT[Ch4];
		leftY = vexRT[Ch3];
		rightX =
		} // "Don't die on me.  Don't you dare die on me..." -The Doctor
}
