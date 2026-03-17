#define BN_IMPLEMENTATION
#include "bn.h"

int main(void) {
    i32 image_width = 256;
    i32 image_height = 256;

    FILE* fptr;

    fptr = fopen("image.ppm", "w");

    fprintf(fptr, "P3\n");
    fprintf(fptr, "%d", image_width);
    fprintf(fptr, " ");
    fprintf(fptr, "%d", image_height);
    fprintf(fptr, "\n255\n");

    for (int j = 0; j < image_height; j++) {
        logInfof("Scanlines remaining: %d", (image_height - j));
        for (int i = 0; i < image_width; i++) {
            f32 r = (f32)i / (image_width - 1);
            f32 g = (f32)j / (image_height - 1);
            f32 b = 0.0;

            i32 ir = (i32)255.999 * r;
            i32 ig = (i32)255.999 * g;
            i32 ib = (i32)255.999 * b;

            fprintf(fptr, "%d", ir);
            fprintf(fptr, " ");
            fprintf(fptr, "%d", ig);
            fprintf(fptr, " ");
            fprintf(fptr, "%d", ib);
            fprintf(fptr, "\n");
        }
    }

    logInfo("Done");

    fclose(fptr);

    return 0;
}
