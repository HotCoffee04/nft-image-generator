#include "img.h"

void initImage(Image *img){
    img->bytes = 0;
    img->size = 0;
}

void freeImage(Image *img){
    free(img->bytes);
    img->bytes = 0;
    img->size = 0;
}

void clearImage(Image *img){

	if(img->bytes == 0)
		return;

	char *ip = img->bytes;
	for(int i = 0; i < img->size;i++){
		*ip = 0;
		ip++;
	}

}

int loadImage(Image *img,char *name){

    //deletes already existing image
    if(img->size != 0)
        freeImage(img);

    //loads from file
    unsigned int bmpStart = 0; //this is where the BMP data starts
    unsigned int size; //file size (header excluded)

    FILE *fp;
    fp = fopen(name,"rb");
    
    if(fp == 0){
        return -1;
    }

    //find image start
    fseek(fp,10,0);
    fread(&bmpStart,1,1,fp);

	//saves the first header it finds
	//needs it to save the image later
	if(!headerSize){
		fseek(fp,0,0);
		headerSize = bmpStart;
		header = (char *)malloc(bmpStart);
		fread(header,1,bmpStart,fp);
	
		if(header[0] != 'B' || header[1] != 'M'){
			printf("\e[0;91mWrong file format.\n\e[0;37m");
			return -1;
		}

	}

    //finds size
    fseek(fp,0,2); //goto end
    size = ftell(fp) - bmpStart; //get size
    fseek(fp,bmpStart,0); //goto start

	if(!prevSize){
		prevSize = size;	
	}else{
		if(prevSize != size){
			printf("\e[0;91mImage dimensions don\'t match.\n\e[0;37m");
			return -1;
		}			
	}

    img->bytes = (char *)malloc(size);
    
    fread(img->bytes,1,size,fp);

    img->size = size;

    fclose(fp);

    return 0;
}
void saveImage(Image *img,char *name){

	if(img->bytes == 0){
		return;
	}	

	char path[30];
	sprintf(path,"out/%s",name);

	FILE *fp;
	fp = fopen(path,"wb");

	fwrite(header,1,headerSize,fp);
	fwrite(img->bytes,1,img->size,fp);

	fclose(fp);
}

void mergeImage(Image *src,Image *merge){

    if(src->bytes == 0 || merge->bytes == 0){
        return;
	}

	unsigned char *pm = merge->bytes;
	unsigned char *ps = src->bytes;

	for(int i = 0; i < src->size;i+=3){

		//if 3 bytes don't match the transparency color the pixel gets copied.
		if(*pm != alphaB || *(pm+1) != alphaG || *(pm+2) != alphaR){

			*ps = *pm;
			ps++; pm++;
			*ps = *pm;
			ps++; pm++;
			*ps = *pm;
			ps++; pm++;

		}else{
			ps+=3;
			pm+=3;
		}

	}

}















































