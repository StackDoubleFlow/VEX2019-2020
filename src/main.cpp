
#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

const pros::Motor LEFT_FRONT(1);
const pros::Motor LEFT_BACK(2);
const pros::Motor RIGHT_FRONT(3);
const pros::Motor RIGHT_BACK(4);

#define MAX_VELOCITY_18 200

/**
 * Runs initialization code. This occcurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	LEFT_FRONT.set_reversed(true);
	LEFT_BACK.set_reversed(true);
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
	for(;;) {
		// Reversing
		if(controller.get_digital_new_press(DIGITAL_X)) {
			isReversed = !isReversed;
		}

		// Driving
		int analogLeft = controller.get_analog(ANALOG_LEFT_Y);
		int analogRight = controller.get_analog(ANALOG_RIGHT_Y);

		if(isReversed) {
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

		pros::delay(20);
	}
}
