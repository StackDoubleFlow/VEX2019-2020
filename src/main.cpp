
#include "main.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

const pros::Motor LEFT(8, pros::motor_gearset_e::E_MOTOR_GEARSET_18, false);
const pros::Motor RIGHT(2, pros::motor_gearset_e::E_MOTOR_GEARSET_18, true);
const pros::Motor WALL_PUSHER(4, pros::motor_gearset_e::E_MOTOR_GEARSET_36);
const pros::Motor WALL_LATCH(5);
const pros::Motor THE_WINCH(6);

#define MAX_VELOCITY_18 200


// float clamp(float value, float min, float max) {
// 	value = value > max ? max : value;
// 	value = value < min ? min : value;
// 	return value;
// }

/**
 * Runs initialization code. This occcurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//WALL.set_encoder_units(MOTOR_ENCODER_DEGREES);
	WALL_LATCH.set_encoder_units(MOTOR_ENCODER_DEGREES);
	WALL_LATCH.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
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
	// When the timer is -1, the sequence is not running				
	int wall_timer = -1;
	bool isReversed = false;																																																																																																																																																																																																																																																																																																																																																																																																																						
	for(;;) {
		// Winch
		bool R1 = controller.get_digital(DIGITAL_R1);
		bool L1 = controller.get_digital(DIGITAL_L1);

		if(R1) {
			THE_WINCH = 64;
		}else if(L1) {
			THE_WINCH = -64;
		} else {
			THE_WINCH = 0;
		}

		// Reversing
		if(controller.get_digital_new_press(DIGITAL_X)) {
			isReversed = !isReversed;
		}

		// Wall sequence
		if(wall_timer != -1) wall_timer--;

		if(wall_timer == 0) {
			WALL_PUSHER.move_relative(100, 100/2);
			WALL_LATCH.move_relative(-120, MAX_VELOCITY_18);
		} else if(wall_timer == 70) {
			WALL_PUSHER.move_relative(-100, 100);
		}

		if(controller.get_digital_new_press(DIGITAL_A) && wall_timer == -1) {
			WALL_LATCH.move_relative(120, MAX_VELOCITY_18);
			
			wall_timer = 100;
		}

		// Driving
		int analogLeft = controller.get_analog(ANALOG_LEFT_Y);
		int analogRight = controller.get_analog(ANALOG_RIGHT_Y);

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
