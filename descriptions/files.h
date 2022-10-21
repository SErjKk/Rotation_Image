#ifndef ROTATION_IO_FORMATS_H
#define ROTATION_IO_FORMATS_H

#include <stdio.h>
#include "image.h"

enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_FILE_NOT_FOUND,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
};
enum write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
};
enum open_status  {
    OPEN_OK = 0,
    OPEN_ERROR
};
enum close_status  {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

enum open_status open_file(const char *input, FILE** filename, const char *mode);

enum close_status close_file(FILE** filename);

enum read_status from_bmp(FILE* in, struct image* img);

enum write_status to_bmp(FILE* out, struct image const* img);

#endif