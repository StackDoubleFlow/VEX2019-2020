#include "main.h"

// Define controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain motors
const pros::Motor LEFT_FRONT(11);
const pros::Motor LEFT_BACK(12);
const pros::Motor RIGHT_FRONT(17);
const pros::Motor RIGHT_BACK(18);

// Intake motors
const pros::Motor INTAKE_LEFT(1);
const pros::Motor INTAKE_RIGHT(10);
const pros::Motor INTAKE_LIFT(2, pros::E_MOTOR_GEARSET_36);


// These macros help so we don't have to memorize the max volocities for
// each motor
#define MAX_VELOCITY_18 200

/**
 * Runs initialization code. This occcurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	RIGHT_FRONT.set_reversed(true);
	RIGHT_BACK.set_reversed(true);
	INTAKE_RIGHT.set_reversed(true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
}


void set_drive_train(float left, float right) {
	LEFT_FRONT.move_velocity(left);
	LEFT_BACK.move_velocity(left);
	RIGHT_FRONT.move_velocity(right);
	RIGHT_BACK.move_velocity(right);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	set_drive_train(60, 60);
	pros::delay(3000);
	set_drive_train(-60, -60);
	pros::delay(3000);
	set_drive_train(0, 0);
}

/**
 * Turns a motor in the response of two buttons.
 * 
 * \param velocity  
 *        The maximum allowable velocity for the movement in RPM 
 * \param button1  
 *        The button which, if pressed, moves the motor in the direction of the velocity
 * \param button2  
 *        The button which, if pressed, moves the motor in the opposite direction of the velocity
 * \param motor
 *        The motor that the buttons control
 */
void two_button_motor(int32_t velocity, pros::controller_digital_e_t button1, pros::controller_digital_e_t button2, pros::Motor motor) {
	/** 
	 * This is a neat trick, basically what it does is stop moving if either both the buttons are pressed
	 * or none of them are pressed.
	 * 
	 * To go into detail, the truth table of xor is:
	 * a b | out
	 * 0 0 | 0
	 * 0 1 | 1
	 * 1 0 | 1
	 * 0 0 | 0
	 * So only one button can be pressed to for the xor output 1. We then invert it so if no buttons are pressed,
	 * or both are pressed, the motor gets set to the velocity of 0
	 */  
	if(!(controller.get_digital(button1) ^ controller.get_digital(button2))) {
		motor.move_velocity(0);
	} else if(controller.get_digital(button1)) {
		motor.move_velocity(velocity); // If button1 was pressed, move motor forward
	} else if (controller.get_digital(button2)) {
		motor.move_velocity(-velocity); // If button2 was pressed, move motor backwards
	}

}

void inline boolean_button_toggle(pros::controller_digital_e_t btn, bool& b) {
	if(controller.get_digital_new_press(btn)) b=!b;
}

void tank_drive_reversable(pros::controller_analog_e_t analog_left, pros::controller_analog_e_t analog_right, bool reversed) {
	int analogLeft = controller.get_analog(analog_left);
	int analogRight = controller.get_analog(analog_right);

	if (reversed) {
		LEFT_FRONT = -analogRight;
		LEFT_BACK = -analogRight;
		RIGHT_FRONT = -analogLeft;
		RIGHT_BACK = -analogLeft;
	} else {
		LEFT_FRONT = analogLeft;
		LEFT_BACK = analogLeft;
		RIGHT_FRONT = analogRight;
		RIGHT_BACK = analogRight;
	}
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {		
	bool isReversed = false;																																																																																																																																																																																																																																																																																																																																																																																																																						
	for (;;) {
		// Reversing
		boolean_button_toggle(DIGITAL_X, isReversed);

		// Driving
		tank_drive_reversable(ANALOG_LEFT_Y, ANALOG_RIGHT_Y, isReversed);

		two_button_motor(120, DIGITAL_L1, DIGITAL_R1, INTAKE_LEFT);
		two_button_motor(120, DIGITAL_L1, DIGITAL_R1, INTAKE_RIGHT);

		two_button_motor(15, DIGITAL_L2, DIGITAL_R2, INTAKE_LIFT);

		if (controller.get_digital(DIGITAL_B)) {
			INTAKE_LEFT.move_velocity(-20);
			INTAKE_LEFT.move_velocity(-20);
			set_drive_train(20, 20);
		}

		pros::delay(20);
	}
}
