
#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

const pros::Motor FRONT_LEFT(1, pros::motor_gearset_e::E_MOTOR_GEARSET_18, false);
const pros::Motor FRONT_RIGHT(2, pros::motor_gearset_e::E_MOTOR_GEARSET_18, true);
const pros::Motor BACK_LEFT(3, pros::motor_gearset_e::E_MOTOR_GEARSET_18, true);
const pros::Motor BACK_RIGHT(4, pros::motor_gearset_e::E_MOTOR_GEARSET_18, false);


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
	while (true) {
		int analogY = controller.get_analog(ANALOG_RIGHT_Y);
		int analogX = controller.get_analog(ANALOG_RIGHT_X);

		FRONT_LEFT = (clamp(analogX, -100, 0) + clamp(analogY, 0, 100)) / 2;
		FRONT_RIGHT = (clamp(analogX, 0, 100) + clamp(analogY, 0, 100)) / 2;
		BACK_LEFT = (clamp(analogX, -100, 0) + clamp(analogY, -100, 0)) / 2;
		BACK_RIGHT = (clamp(analogX, 0, 100) + clamp(analogY, -100, 0)) / 2;

		pros::delay(20);
	}
}
