// Ryan Root
// Write A Random PPM of Specified size with random RGB values
// 11/26/24

#include <stdio.h>
#include <stdlib.h>

#define RANDOM_MAX 255
#define RANDOM_MIN 0 

// change these variables accordingly
#define PPM_WIDTH 30000
#define PPM_HEIGHT 30000
#define FILENAME "random.ppm"

typedef struct {
      unsigned char r, g, b;
} PPMPixel;


PPMPixel* create_ppm(unsigned long int width, unsigned long int height) {
    unsigned long int area = width * height;
    int red, green, blue;
    PPMPixel *ppm_array = malloc(area * sizeof(PPMPixel));

    if (ppm_array == NULL) {
        fprintf(stderr, "Memory allocation has failed\n");
        return NULL;
    }

    for (int i = 0; i < area; i++) {
        red = rand() % (RANDOM_MAX - RANDOM_MIN + 1) + RANDOM_MIN;
        green = rand() % (RANDOM_MAX - RANDOM_MIN + 1) + RANDOM_MIN;
        blue = rand() % (RANDOM_MAX - RANDOM_MIN + 1) + RANDOM_MIN;

        ppm_array[i].r = red;
        ppm_array[i].g = green;
        ppm_array[i].b = blue;
    }

    return ppm_array;
}




void write_image(PPMPixel *image, char *filename, unsigned long int width, unsigned long int height) {
    // open/create new ppm file using filename arg with fopen
    // this WILL NOT copy any comments from the PPM original file
    FILE *ppm = fopen(filename, "wb");
    if (ppm == NULL) {
        fprintf(stderr, "Error creating or opening file\n");
        free(image);
        return;
    }

    // write the header information
    fprintf(ppm, "P6\n");
    fprintf(ppm, "%lu %lu\n", width, height);
    fprintf(ppm, "255\n");

    // write the data from the struct array
    unsigned long int array_size = width * height;
    if (fwrite(image, sizeof(PPMPixel), array_size, ppm) != array_size) {
        fprintf(stderr, "Error writing to new ppm file\n");
    }

    free(image);
    fclose(ppm); 
}


int main() {
    char* filename = "random.ppm";
    PPMPixel *ppm_array = create_ppm(PPM_WIDTH, PPM_HEIGHT);

    if (ppm_array == NULL) {
        printf("create_ppm failed\n");
        return -1;
    }

    write_image(ppm_array, FILENAME, PPM_WIDTH, PPM_HEIGHT);
    return 0;
}