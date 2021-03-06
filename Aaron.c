#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in8,    powerExpander,  sensorAnalog)
#pragma config(Sensor, dgtl1,  claw,           sensorDigitalOut)
#pragma config(Sensor, dgtl12, liftStop,       sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  liftEnc,        sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           leftLift1,     tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port2,           leftWheel1,    tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port3,           rightLift1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftLift2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftWheel2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightWheel1,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightLift2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftLift3,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightWheel2,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightLift3,    tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

int autonomousChoice;

#include "JonLib/Math.h"
#include "JonLib/Drivebase.h"
#include "JonLib/PID.h"
#include "JonLib/Autonomous.h"
#include "JonLib/LCD.h"

void setLeftWheelSpeed (int speed) {
	motor[leftWheel1] = speed;
	motor[leftWheel2] = speed;
}

void setRightWheelSpeed (int speed) {
	motor[rightWheel1] = speed;
	motor[rightWheel2] = speed;
}

void lift (int speed) {
	motor[leftLift1] = speed;
	motor[leftLift2] = speed;
	motor[leftLift3] = speed;
	motor[rightLift1] = speed;
	motor[rightLift2] = speed;
	motor[rightLift3] = speed;
}

void init() {
	startTask(LCD);
}

void pre_auton () {
	init();
}

void resetEncoders() {
	nMotorEncoder(leftWheel1) = 0;
	nMotorEncoder(rightWheel1) = 0;
}

void autonomousInit() {
	//clear the encoders before start of autonomous
	resetEncoders();


	//clear drivebase PID targets to prevent robot from running off anywhere
	l.target = 0;
	r.target = 0;

	startTask(drivebasePID);
}

task clawControl () {
	while(true) {
		if(vexRT[Btn5U]) {
			SensorValue[claw] = !SensorValue[claw];
			while(vexRT[Btn5U]) { delay(5); }
		}
		delay(25);
	}
}

task autonomous() {

}

task usercontrol() {
	startTask(clawControl);
	while(true) {

		tankDrive(vexRT[Ch3], vexRT[Ch2], 15);

		if(vexRT[Btn6U]) {
			lift(127);
		} else if (vexRT[Btn6D] && !SensorValue[liftStop]) {
			lift(-127);
		} else if(SensorValue[liftStop]) {
			lift(-10);
		} else {
			lift(0);
		}

		if(SensorValue[liftStop])
			SensorValue[liftEnc] = 0;

		delay(25);
	}
}
