#ifndef __NEW_APPLICATION_IMAGES_H__
#define __NEW_APPLICATION_IMAGES_H__

#include <stdint.h>

#define hello_world_release_xip_size (24596U)
#define hello_world_release_size (7652U)

// array size is 24596
extern uint8_t hello_world_release_xip[];

// array size is 7652
extern uint8_t hello_world_release[];

#endif