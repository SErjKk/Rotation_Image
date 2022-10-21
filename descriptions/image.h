#ifndef ROTATION_IMAGE_H
#define ROTATION_IMAGE_H

#include <stdint.h>
#include <inttypes.h>

// Заголовок BMP файла
#pragma pack(push, 1)
struct bmp_header {
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};
#pragma pack(pop)

// Mассив, в котором последовательно хранятся пиксели по строчкам (1 pxl = 3 байта)
struct pixel {
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

// Описание представления картинки
struct image {
    uint64_t width;
    uint64_t height;
    struct pixel* data;
};

void set_image_size(struct image* image, uint64_t height, uint64_t width);

uint64_t get_size(uint64_t height, uint64_t width);

#endif