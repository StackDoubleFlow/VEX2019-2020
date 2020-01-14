
#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

const pros::Motor LEFT(1, pros::motor_gearset_e::E_MOTOR_GEARSET_18, false);
const pros::Motor RIGHT(2, pros::motor_gearset_e::E_MOTOR_GEARSET_18, true);
const pros::Motor WALL(4);
const pros::Motor THE_WINCH(5);


float clamp(float value, float min, float max) {
	value = value > max ? max : value;
	value = value < min ? min : value;
	return value;
}

/**
 * Runs initialization code. This occcurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

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
void competition_initialize() {}

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
void autonomous() {}

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
		int analogLeft = controller.get_analog(ANALOG_LEFT_Y);
		int analogRight = controller.get_analog(ANALOG_RIGHT_Y);

		if(controller.get_digital_new_press(DIGITAL_X)) {
			isReversed = !isReversed;
		}

		if(controller.get_digital_new_press(DIGITAL_A)) {
			WALL.move_relative(16, 200);
			WALL.move_relative(-16, 200);
		}

		if(isReversed) {
			LEFT = -analogRight;
			RIGHT = -analogLeft;
		} else {
			LEFT = analogLeft;
			RIGHT = analogRight;
		}

		pros::delay(20);
	}
}
