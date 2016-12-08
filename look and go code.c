
const int eyes = motorA;
const int leftWheel = motorB;
const int rightWheel = motorC;

const int THRESHOLD = 30;

const float DISTANCE_BETWEEN_WHEELS = 10;

int look() {
	nMotorEncoder[eyes] = 0;
	motor[eyes] = 20;
	while(nMotorEncoder[eyes] < 360) {
		if(SensorValue(ultrasound) < THRESHOLD) {
			return nMotorEncoder[eyes];
		}
		wait1Msec(10);
	}
}

void turnTo(float degree) {
	float encoder_ticks = (degree/360) * (PI*DISTANCE_BETWEEN_WHEELS);
	nSyncedMotors = synchBC;
	nSyncedTurnRatio = -100;
	motor[leftWheel] = 50;
	nMotorEncoder[leftWheel] = 0;
	while(nMotorEncoder[leftWheel] < encoder_ticks) {
		wait1Msec(10);
	}
	nMotorEncoder[eyes] = 0;
	motor[eyes] = 40;
	while(nMotorEncoder[eyes] < degree) {
		wait1Msec(10);
	}
	nSyncedTurnRatio = 100;
}

void go() {
	nSyncedMotors = synchBC;
	nSyncedTurnRatio = 100;
	motor[leftWheel] = 60;
	wait1Msec(50);
}

task main()
{
	turnTo((float) look());
	while(SensorValue(ultrasound) > CLOSE_THRESHOLD) {
			go();
	}
}
