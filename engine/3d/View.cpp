#include "View.h"

View::View() {
	eye = { 0, 0, -50.0f };
	target = { 0, 0, 0 };
	up = { 0, 1, 0 };
	focalLengs = 90.0f;
	camSensor = 35.0f;
}
View::~View(){}

float View::FieldOfViewY(float focalLengs, float sensor) {

	return 2 * atan(sensor / (2 * focalLengs));

}