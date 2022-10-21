#include <stdio.h>
#include <io.h>
#include <inttypes.h>
#include "../descriptions/image.h"
#include "../descriptions/files.h"

struct bmp_header header;

const char* reading[] = {
        [READ_OK] = "Successful reading\n",
        [READ_INVALID_SIGNATURE] = "Invalid signature error\n",
        [READ_FILE_NOT_FOUND] = "File not found error\n",
        [READ_INVALID_BITS] = "Invalid bits error\n",
        [READ_INVALID_HEADER] = "Invalid header error\n",
};

const char* writing[] = {
        [WRITE_OK] = "Successful writing\n",
        [WRITE_ERROR] = "Writing error\n",
};

const char* opening[] = {
        [OPEN_OK] = "Successful opening\n",
        [OPEN_ERROR] = "Opening error\n",
};

const char* closing[] = {
        [CLOSE_OK] = "Successful closing\n",
        [CLOSE_ERROR] = "Closing error\n",
};

// Открытие файла на чтение или запись
enum open_status open_file(const char *input, FILE** filename, const char *mode) {
    enum open_status status;
    if (strcmp(mode, "wb") == 0 || access(input, F_OK) == 0) {
        *filename = fopen(input, mode);
        status = OPEN_OK;
    } else {
        status = OPEN_ERROR;
    }
    printf("%s", opening[status]);
    return status;
}

// Закрытие файла
enum close_status close_file(FILE** filename) {
    enum close_status status;
    if (!filename)
        status = CLOSE_ERROR;
    else {
        fclose(*filename);
        status = CLOSE_OK;
    }
    printf("%s", closing[status]);
    return status;
}

// Прочитать заголовок + картинку из файла
enum read_status from_bmp(FILE* filename, struct image* img) {
    enum read_status status;
    if (!filename)
        status = READ_FILE_NOT_FOUND;
    else {
        size_t header_size = fread(&header, sizeof(struct bmp_header), 1, filename);
        if (header_size == 0)
            status = READ_INVALID_HEADER;
        else {
            set_image_size(img, header.biHeight, header.biWidth);
            if (img->data == NULL)
                status = READ_INVALID_SIGNATURE;
            else {
                int offset = fseek(filename, header.bOffBits, SEEK_SET);
                if (offset != 0)
                    status = READ_INVALID_SIGNATURE;
                else {
                    fread(img->data, header.biSizeImage, 1, filename);
                    status =  READ_OK;
                }
            }
        }
    }
    printf("%s", reading[status]);
    return status;
}

// Записать картинку в файл
enum write_status to_bmp(FILE* filename, struct image const* img) {
    enum write_status status;
    if (!filename)
        status = WRITE_ERROR;
    else {
        struct bmp_header new_header = header;
        new_header.biWidth = img->width;
        new_header.biHeight = img->height;
        new_header.biSizeImage = get_size(img->height, img->width);

        uint32_t padding = (4 - (img->width*3 % 4)) % 4;
        char a[] = {0, 0, 0};
        fwrite(&new_header, sizeof(struct bmp_header), 1, filename);
        for (uint32_t i = 0; i < img->height; i++) {
            fwrite(img->data + i*img->width, sizeof(struct pixel), img->width, filename);
            fwrite(a, 1, padding, filename);
        }
        status = WRITE_OK;
    }
    printf("%s", writing[status]);
    return status;
}