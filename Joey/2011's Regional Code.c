#pragma config(Sensor, dgtl1,  fArmStop,            sensorDigitalIn)
#pragma config(Sensor, dgtl2,  rArmStop,            sensorDigitalIn)
#pragma config(Sensor, dgtl3,  uDoorStop,           sensorDigitalIn)
#pragma config(Sensor, dgtl4,  dDoorStop,           sensorDigitalIn)
#pragma config(Motor,  port2,           ldrive,        tmotorNormal, openLoop)
#pragma config(Motor,  port3,           smotor1,       tmotorNormal, openLoop)
#pragma config(Motor,  port4,           serv1,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           serv3,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           serv4,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           serv2,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port8,           smotor2,       tmotorNormal, openLoop)
#pragma config(Motor,  port9,           rdrive,        tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/***********************************************************\
| Code written for Metro Homeschool Robotics, Inc's robot,  |
| for the 2011 BEST Regional competition at the Frontier    |
| Trails BEST Regional in Fort Smith, Arkansas.             |
|                                                           |
| This is the 41st revision of the code since the start of  |
| the season.                                               |
|                                                           |
| Programming Leader:  Joseph Keller                        |
|                                                           |
| Others involved:     Joey McGee                           |
|                      Bryant Young                         |
|                      Michael Ward                         |
|                      Ian Johnson                          |
|                      Noah Huff                            |
|                      Tanner Robinson                      |
|                      Michael Bell                         |
\***********************************************************/


task Drive() {
  // Initialing variables for the Drive system
  int RightX;
  int RightY;
  int RightXcu;
  int RightYcu;
  int threshold = 15;
  int drivesystem = 2;
  int slow = 1;
  int ldmotor;
  int rdmotor;
  int backwards = 1;

  while (true){
    //  This section does calculations for Standard and Cubed input for
    //  the right joystick, so we can control the robot with better precision.
    RightX = vexRT[Ch1];
    RightY = vexRT[Ch2];
    RightXcu = (((vexRT[Ch1] * vexRT[Ch1]) / 127) * vexRT[Ch1]) / 127; // 'Cubed' input calculation.
    RightYcu = (((vexRT[Ch2] * vexRT[Ch2]) / 127) * vexRT[Ch2]) / 127;

  	if(drivesystem == 2) { // Arcade Drive calculations using the 'cubed' joystick input.
      if(RightY > threshold) { // Forwards
        ldmotor = (RightYcu + RightXcu)^2/127;
        rdmotor = (RightYcu - RightXcu)^2/127;
      }  else if(RightY < -threshold) { // Backwards
        ldmotor = (RightYcu + RightXcu)^2/127;
        rdmotor = (RightYcu - RightXcu)^2/127;
      }  else if((abs(RightX) > threshold) && (abs(RightY) < threshold)) { // Turning in Place
        ldmotor = RightXcu;
        rdmotor = (-1 * RightXcu);
      }  else { // If no controls held, disable motors
        ldmotor = 0;
        rdmotor = 0;
      }
    }
    // We have a 'Slow Mode' that allows us to control the robot even more precisely, the button '7D' disables
	// 'Slow Mode' and goes to full power while held.
    if(vexRT[Btn7D])
      slow = 0;
    else
      slow = 1;

    // This allows us to control which direction is the 'front' of the robot so that we can control it more smoothly.
    if(vexRT[Btn8U])
      backwards = 0;
    else if(vexRT[Btn8D])
      backwards = 1;

    // This 'slows' down the motors when the robot is in slow mode and makes sure it is going in the correct direction
	// according to the directional flip above.
    if(slow) {
      if(backwards) {
        motor[ldrive] = -(0.62 * rdmotor);
        motor[rdrive] = -(0.62 * ldmotor);
      } else {
        motor[ldrive] = 0.62 * ldmotor;
        motor[rdrive] = 0.62 * rdmotor;
      }
    } else {
      if(backwards) {
        motor[ldrive] = -rdmotor;
        motor[rdrive] = -ldmotor;
      } else {
        motor[ldrive] = ldmotor;
        motor[rdrive] = rdmotor;
      }
    }
  }
}

task Motors() { // Arm, Claw, and Door control.
  // Initializing variables
  int LeftY;
  int LeftYsq;
  int canauto = 1;
  while(true) {
    LeftY = vexRT[Ch3];
    if(vexRT[Btn8L] && canauto) {
	  // This is for our one-button 'unfolding' to save time at the beginning of the round
	  // getting our arm into the correct position to collect red flies.
      motor(smotor2) = -127;  // Start opening door
      wait10Msec(50);         // Wait half a second
      motor(smotor1) =  127;  // Start raising arm
      wait10Msec(50);         // Wait half a second
      motor(smotor2) =  0;    // Stop opening door
      wait10Msec(50);         // Wait half a second
      motor(serv1) =  38;     // Open claw slightly
      motor(serv2) = -38;     // Open other half of claw slightly
      wait10Msec(70);         // Wait 7/10ths of a second
      motor(smotor1) = 0;     // Stop moving arm
	    canauto = 0;            // Disable this function until next restart of the cortex
    }

    // Squaring the arm input:
    if(vexRT[Ch3] >= 0)
      LeftYsq = (vexRT[Ch3] * vexRT[Ch3]) / 127;
    if(vexRT[Ch3] < 0)
      LeftYsq = -((vexRT[Ch3] * vexRT[Ch3]) / 127);


    if(vexRT[Btn7R]) { // Claw Control
      motor(serv1) = -127;
      motor(serv2) =  127;
    } else  if(vexRT[Btn7L]) {
      motor(serv1) =  85;
      motor(serv2) = -85;
    }  else if(vexRT[Btn8R]) { // Fly-grabbing position
      if(motor(serv1) == 55 && motor(serv2) == -55) {
        motor(serv1) =  38;
        motor(serv2) = -38;
        while(vexRT[Btn8R]) {}
      } else {
        motor(serv1) =  55;
        motor(serv2) = -55;
        while(vexRT[Btn8R]) {}
      }
    }  else  if(vexRT[Btn5U]) {
      if(LeftY <= 85) {
        motor(serv1) =  LeftY;
        motor(serv2) = -LeftY;
      } else {
        motor(serv1) =  85;
        motor(serv2) = -85;
      }
    }


    if(vexRT[Btn6U]) { // Arm Movement Code
      if( ( LeftYsq > 5 )  && ( SensorValue(fArmStop) )  ) {
        motor[smotor1] = LeftYsq;
      } else if( ( LeftYsq < -5 )  && ( SensorValue(rArmStop) )  ) {
        motor[smotor1] = LeftYsq;
      } else {
        motor[smotor1] = 0;
      }
    } else {
      motor[smotor1] = 0;
    }

    if(vexRT[Btn6D] && SensorValue(uDoorStop)) // Door Control
    	motor(smotor2) =  127;
    else if(vexRT[Btn5D] && SensorValue(dDoorStop))
    	motor(smotor2) = -128;
    else
	    motor(smotor2) = 0;
  }
}

task main() {
  motor(serv1) = -127;
  motor(serv2) =  127;
  StartTask(Drive);
  StartTask(Motors);
  int on = true;
  while(on){} // Keeps the code running.
}