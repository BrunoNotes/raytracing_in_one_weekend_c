#include <math.h>
#define BN_IMPLEMENTATION
#include "bn.h"

void writeColor(FILE* fptr, Vec3f32 pixel_color) {
    i32 ir = (i32)255.999 * pixel_color.r;
    i32 ig = (i32)255.999 * pixel_color.g;
    i32 ib = (i32)255.999 * pixel_color.b;

    fprintf(fptr, "%d", ir);
    fprintf(fptr, " ");
    fprintf(fptr, "%d", ig);
    fprintf(fptr, " ");
    fprintf(fptr, "%d", ib);
    fprintf(fptr, "\n");
}

Vec3f32 vec3f32Add(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){{u.x + v.x, u.y + v.y, u.z + v.z}};
}

Vec3f32 vec3f32AddScalar(Vec3f32 u, f32 s) {
    return (Vec3f32){{u.x + s, u.y + s, u.z + s}};
}

Vec3f32 vec3f32Sub(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){{u.x - v.x, u.y - v.y, u.z - v.z}};
}

Vec3f32 vec3f32Mult(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){{u.x * v.x, u.y * v.y, u.z * v.z}};
}

Vec3f32 vec3f32MultScalar(Vec3f32 u, f32 s) {
    return (Vec3f32){{u.x * s, u.y * s, u.z * s}};
}

Vec3f32 vec3f32DivScalar(Vec3f32 u, f32 s) {
    return (Vec3f32)vec3f32MultScalar(u, (1 / s));
}

f32 vec3f32LengthSquared(Vec3f32 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

f32 vec3f32Length(Vec3f32 v) {
    return sqrt(vec3f32LengthSquared(v));
}

Vec3f32 vec3f32UnitVector(Vec3f32 v) {
    return vec3f32DivScalar(v, vec3f32Length(v));
}

f32 vec3f32Dot(Vec3f32 u, Vec3f32 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vec3f32 vec3f32Cross(Vec3f32 u, Vec3f32 v) {
    return (Vec3f32){
        {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x}
    };
}

typedef struct {
    Vec3f32 orig;
    Vec3f32 dir;
} Ray;

Vec3f32 rayAt(Ray* r, f32 t) {
    return vec3f32Add(r->orig, vec3f32MultScalar(r->dir, t));
}

bool hitSphere(Vec3f32 center, f32 radius, Ray* r) {
    Vec3f32 oc = vec3f32Sub(center, r->orig);
    f32 a = vec3f32Dot(r->dir, r->dir);
    f32 b = -2.0 * vec3f32Dot(r->dir, oc);
    f32 c = vec3f32Dot(oc, oc) - radius * radius;
    f32 discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

Vec3f32 rayColor(Ray* r) {
    if (hitSphere((Vec3f32){{0, 0, -1}}, 0.5, r)) {
        logWarn("sphere");
        return (Vec3f32){{1, 0, 0}};
    }

    Vec3f32 unit_direction = vec3f32UnitVector(r->dir);
    f32 a = 0.5 * (unit_direction.y + 1.0);
    return vec3f32Add(
        vec3f32MultScalar((Vec3f32){{1.0, 1.0, 1.0}}, (1.0 - a)),
        vec3f32MultScalar((Vec3f32){{0.5, 0.7, 1.0}}, a)
    );
}

int main(void) {
    // image
    f32 aspect_ratio = 16.0 / 9.0;
    i32 image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    i32 image_height = (i32)((f32)image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    f32 focal_length = 1.0;
    f32 viewport_height = 2.0;
    f32 viewport_width = viewport_height * ((f32)image_width / image_height);
    Vec3f32 camera_center = {{0, 0, 0}};

    // Calculate the vectors across the horizontal and down the vertical
    // viewport edges.
    Vec3f32 viewport_u = {{viewport_width, 0, 0}};
    Vec3f32 viewport_v = {{0, -viewport_height, 0}};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vec3f32 pixel_delta_u = vec3f32DivScalar(viewport_u, (f32)image_width);
    Vec3f32 pixel_delta_v = vec3f32DivScalar(viewport_v, (f32)image_height);

    // Calculate the location of the upper left pixel.
    // Vec3f32 viewport_upper_left = vec3f32Sub(
    //     vec3f32Sub(camera_center, (Vec3f32){{0, 0, focal_length}}),
    //     vec3f32Sub(
    //         vec3f32DivScalar(viewport_u, 2), vec3f32DivScalar(viewport_v, 2)
    //     )
    // );
    Vec3f32 viewport_upper_left = vec3f32Sub(
        vec3f32Sub(
            vec3f32Sub(camera_center, (Vec3f32){{0, 0, focal_length}}),
            vec3f32DivScalar(viewport_u, 2)
        ),
        vec3f32DivScalar(viewport_v, 2)
    );

    // Vec3f32 pixel00_loc = vec3f32Mult(
    //     vec3f32AddScalar(viewport_upper_left, 0.5),
    //     vec3f32Add(pixel_delta_u, pixel_delta_v)
    // );
    Vec3f32 pixel00_loc = vec3f32Add(
        viewport_upper_left,
        vec3f32MultScalar(vec3f32Add(pixel_delta_u, pixel_delta_v), 0.5)
    );

    // render

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

            Vec3f32 pixel_center = vec3f32Add(
                vec3f32Add(pixel00_loc, vec3f32MultScalar(pixel_delta_u, i)),
                vec3f32MultScalar(pixel_delta_v, j)
            );
            Vec3f32 ray_direction = vec3f32Sub(pixel_center, camera_center);
            Ray r = {camera_center, ray_direction};

            Vec3f32 pixel_color = rayColor(&r);

            writeColor(fptr, pixel_color);
        }
    }

    logInfo("Done");

    fclose(fptr);

    return 0;
}
