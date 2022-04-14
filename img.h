#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Color used for transparency
#define alphaR 255
#define alphaG 0
#define alphaB 255

#define BMPstart 10 //in the BMP format the byte number 10 contains the memory offset where the pixel data starts

//struct for images (contains pixel data)
typedef struct Image{

    int size;
    char* bytes;

}Image;

//struct for sets of images
typedef struct Set{

	int count;
	Image *imgs;
	int size;

}Set;

//The file size of the previous file that has been loaded
int prevSize;

//Size in bytes of the BMP header found
int headerSize;
//BMP header
char *header;

void initImage(Image *img); //initializes an image
void freeImage(Image *img); //clears the image memory

void clearImage(Image *img); //turns an image black

int loadImage(Image *img,char *name); //loads image from file path
void saveImage(Image *img,char *name); //save image

void mergeImage(Image *src,Image *merge); //places the second image on top of the first one

