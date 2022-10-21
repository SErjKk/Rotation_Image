#include "../descriptions/image.h"
#include <malloc.h>

// Установить размеры картинки
void set_image_size(struct image* image, uint64_t height, uint64_t width) {
    image->height = height;
    image->width = width;
    image->data = malloc(get_size(height, width));
}

// Размер картинки с учетом паддингов
uint64_t get_size(uint64_t height, uint64_t width) {
    uint32_t padding = (4 - (width*3 % 4)) % 4;
    return height * (width * sizeof(struct pixel) + padding);
}