#pragma config(Motor,  port2,           front,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           left,          tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           right,         tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

float degrees; // holds the position of the joystick in degrees.
float power; // holds the power multiplier of the wheels
float wheel1direction = 90; // constant, holds the direction of the first wheel
float wheel2direction = 210; // constant, holds the direction of the second wheel
float wheel3direction = 330;
float wheel1distance; //  holds the distance from the wheel to the joystick
float wheel2distance; //  holds the distance from the wheel to the joystick
float wheel3distance; //  holds the distance from the wheel to the joystick
float rawwheel1speed;
// okay i'm going to stop defining variables, you need quite a few
float maxRightX = 127;
float maxRightY = 127;

float wheel1speed;
float wheel2speed;
float wheel3speed;

float R = 0;

float maxpower;

float rightX;
float rightY;

bool spinleftbutton;
bool spinrightbutton;

task main() {
	while(true) {

		rightX = vexRT[Ch1];
		rightY = vexRT[Ch2];

		// finds the degree of the joystick
		if (abs(rightY) > abs(rightX) && rightY >= 0) // in the top fourth of the circle
		{
			degrees = (1/(rightY/rightX))*45;
		} // end if
		if (abs(rightX) > abs(rightY) && rightX >= 0) // in the right fourth of the circle
		{
			degrees = ((-1/(rightX/rightY))*45)+90;
		} // end if
		if (abs(rightY) > abs(rightX) && rightY < 0) // in the bottom fourth of the circle
		{
			degrees = ((1/(rightY/rightX))*45)+180;
		} // end if
		if (abs(rightX) > abs(rightY) && rightX < 0) // in the left fourth of the circle
		{
			degrees = ((-1/(rightX/rightY))*45)+270;
		} // end if

//		degrees = (((atan2(rightX, rightY))/PI)*180);//+180;

		if (degrees < 0) // catches negative degrees
		{
			degrees = degrees+360;
		} // end if

		// finds the power multipler for the wheels
		power = sqrt((rightX*rightX)+(rightY*rightY));
		maxpower =sqrt((127*127)+(127*127));



		// finds the distance from each wheel to the joystick's position; repeat for each wheel
		wheel1distance = (degrees-wheel1direction);
		if (wheel1distance > 180) // catches diffrences that go the wrong direction
		{
			wheel1distance = abs(360-wheel1distance);
		}
		if (wheel1distance > 90) // converts numbers higher than 90 floato numbers lower than 90 and negative ie. 95 becomes -85, 180 becomes 0
		{
			wheel1distance = ((wheel1distance-90)*-1)+90;
		}
		rawwheel1speed = 100-(wheel1distance*(100/90)); // speed if you are full sticking
		wheel1speed = (100-(rawwheel1speed)*power)/maxpower; // takes into account not full sticking

		// spinning code, I'm leaving the spin speed pretty slow so you can drive fast while spinning
		if (spinrightbutton == true)
		{
			wheel1speed = (wheel1speed*0.8)+20;
			wheel2speed = (wheel2speed*0.8)+20;
			wheel3speed = (wheel3speed*0.8)+20;
		}
		else if (spinleftbutton == true)
		{
			wheel1speed = (wheel1speed*0.8)-20;
			wheel2speed = (wheel2speed*0.8)-20;
			wheel3speed = (wheel3speed*0.8)-20;
		}

		//wheel1speed = (-0.5 * rightX) - ((sqrt(3)/2) * rightY) + R;
		//wheel2speed = (-0.5 * rightX) + ((sqrt(3)/2) * rightY) + R;
		//wheel3speed = rightX + R;

		// there's no way I got all of that right
		/*motor[left] = 0.5*(wheel1speed);
		motor[right] = 0.5*(wheel2speed);
		motor[front] = wheel3speed;*/

		motor[front] = wheel1speed;
		motor[left] = 0.5*(wheel2speed);
		motor[right] = 0.5*(wheel3speed);
	}
}
