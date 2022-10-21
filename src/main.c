#include <stdio.h>
#include <malloc.h>
#include "../descriptions/image.h"
#include "../descriptions/files.h"
#include "../descriptions/rotate.h"

int main() {
    int argc = 3;

    const char *input = "../pictures/INPUT_1.bmp";
    const char *output = "../pictures/OUTPUT.bmp";

    FILE* input_file;
    FILE* output_file;

    struct image old_image;
    struct image new_image;

    // Проверка на кол-во аргументов
    if (argc != 3) {
        printf("Arguments error");
        return -1;
    }

    // Открыть файл
    enum open_status openStatus = open_file(input, &input_file, "rb");
    if (openStatus != OPEN_OK)
        return -2;

    // Считать заголовок + картинку
    enum read_status readStatus = from_bmp(input_file, &old_image);
    if (readStatus != READ_OK)
        return -3;

    // Закрыть файл
    enum close_status closeStatus = close_file(&input_file);
    if (closeStatus != CLOSE_OK)
        return -4;

    // Повернуть картинку
    new_image = rotate(old_image);

    // Открыть новый файл
    enum open_status openStatus_1 = open_file(output, &output_file, "wb");
    if (openStatus_1 != OPEN_OK)
        return -5;

    // Записать повернутую картинку в новый файл
    enum write_status writeStatus = to_bmp(output_file, &new_image);
    if (writeStatus != WRITE_OK)
        return -6;

    // Закрыть новый файл
    enum close_status closeStatus_1 = close_file(&output_file);
    if (closeStatus_1 != CLOSE_OK)
        return -7;

    // Очистить память, выделенную под старое и новое изображение
    _freea(old_image.data);
    _freea(new_image.data);

    return 0;
}