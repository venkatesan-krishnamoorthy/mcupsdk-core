#ifndef __NEW_APPLICATION_IMAGES_H__
#define __NEW_APPLICATION_IMAGES_H__

#include <stdint.h>

#define hello_world_release_xip_size (24252U)
#define hello_world_release_size (7812U)

// array size is 24252
extern uint8_t hello_world_release_xip[];

// array size is 7812
extern uint8_t hello_world_release[];

#endif