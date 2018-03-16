#include "modules/CR7/square.h"
#include "generated/flight_plan.h"
#include "generated/airframe.h"
#include "firmwares/rotorcraft/navigation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int x_array[4] = { 1, 2, 2, 1 };
int y_array[4] = { 1, 1, 2, 2 };
int i = 0;

void running_square()
{
	// Let the drone fly in a square
	if(GetPosX()==waypoint_get_x(WP_GOAL) && GetPosy()==waypoint_get_y(WP_GOAL))
	{
		waypoint_set_xy_i(WP_GOAL, x_array[i], y_array[i])
		i += 1
	}
	

	
}



// /*
//  * Sets waypoint 'waypoint' to the coordinates of 'new_coor'
//  */
// uint8_t moveWaypoint(uint8_t waypoint, struct EnuCoor_i *new_coor)
// {
//   VERBOSE_PRINT("Moving waypoint %d to x:%f y:%f\n", waypoint, POS_FLOAT_OF_BFP(new_coor->x),
//                 POS_FLOAT_OF_BFP(new_coor->y));
//   waypoint_set_xy_i(waypoint, new_coor->x, new_coor->y);
//   return false;
// }

// /*
//  * Calculates coordinates of distance forward and sets waypoint 'waypoint' to those coordinates
//  */
// uint8_t moveWaypointForward(uint8_t waypoint, float distanceMeters)
// {
//   struct EnuCoor_i new_coor;
//   calculateForwards(&new_coor, distanceMeters);
//   moveWaypoint(waypoint, &new_coor);
//   return false;
// }