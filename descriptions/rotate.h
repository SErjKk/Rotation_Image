#ifndef ROTATION_ROTATE_H
#define ROTATION_ROTATE_H

#include "image.h"

enum rotate_status  {
    ROTATE_OK = 0,
    ROTATE_ERROR
};

struct image rotate(struct image const old_image);

#endif

