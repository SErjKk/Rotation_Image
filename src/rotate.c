#include <stdio.h>
#include <malloc.h>
#include "../descriptions/rotate.h"

const char* rotation[] = {
        [ROTATE_OK] = "Successful rotating\n",
        [ROTATE_ERROR] = "Rotating error\n",
};

// Cоздаёт копию изображения, повёрнутую на 90 градусов против часовой стрелки
struct image rotate(struct image const old_image) {
    enum rotate_status status = ROTATE_OK;
    struct image new_image;
    set_image_size(&new_image, old_image.width, old_image.height);

    // Выделение памяти под двумерный массив пикселей повернутой картинки
    struct pixel **rotate_array = malloc(old_image.width * 8);
    for (int q = 0; q < old_image.width; q++)
        rotate_array[q] = malloc(old_image.height * sizeof(struct pixel));

    // Выделение памяти под двумерный массив пикселей исходной картинки
    struct pixel **array = malloc(old_image.height * 8);
    for (int p = 0; p < old_image.height; p++)
        array[p] = malloc(old_image.width * sizeof(struct pixel));

    uint8_t padding = (4 - (old_image.width*3 % 4)) % 4;

    // Запись пикселей одномерного массива в двумерный
    int k = 0;
    for(int i =  old_image.height - 1; i > -1; i--) {
        for (int j = 0; j < old_image.width; j++) {
            array[i][j].b = *(&old_image.data->b + k);
            array[i][j].r = *(&old_image.data->r + k);
            array[i][j].g = *(&old_image.data->g + k);
            k += sizeof(struct pixel);
        }
        k += padding;
    }

    // Поворот двумерного массива
    for(int i = 0; i < old_image.width; i++) {
        for (int j = 0; j < old_image.height; j++) {
            rotate_array[i][j] = array[j][old_image.width - i - 1];
        }
    }

    // Запись пикселей двумерного массива в одномерный
    int h = 0;
    for (int a = old_image.width - 1; a > -1; a--) {
        for (int b = 0; b < old_image.height; b++) {
            new_image.data[h].b = rotate_array[a][b].b;
            new_image.data[h].r = rotate_array[a][b].r;
            new_image.data[h].g = rotate_array[a][b].g;
            h++;
        }
    }

    // Очистка памяти, выделенной под двумерные массивы
    for (int i = 0; i < old_image.height; i++) {
        free(array[i]);
    }
    free(array);

    for (int i = 0; i < old_image.width; i++) {
        free(rotate_array[i]);
    }
    free(rotate_array);

    printf("%s", rotation[status]);
    return new_image;
}

