#include <stdio.h>
#include <string.h>
#include "img.h"

/*
	written by Gabriele Simoni (14/04/2022)
*/

void cleanUp();

int main(int argc, char *argv[]){


	if(argc == 1){

		printf("\tFor usage and info refer to the \"README.md\"\n");
		return 0;
	}

	Set *sets;
	sets = (Set *)malloc(sizeof(Set));

	sets[0].imgs = (Image *)malloc(sizeof(Image));
	sets[0].size = 0;

	int setsNum = 1;
	int firstImg = 0;

	for(int i = 1;i < argc; i++){

		if(strcmp(argv[i],"-") == 0){

			if(strcmp(argv[i - 1],"-") == 0 || i == 1)
				continue;

			setsNum++;
			sets = realloc(sets,sizeof(Set) * setsNum);
			sets[setsNum - 1].size = 0;
			sets[setsNum - 1].count = 0;
			sets[setsNum - 1].imgs = (Image *)malloc(sizeof(Image));
		}else{

			if(!firstImg)
				firstImg = i;

			FILE *fp = fopen(argv[i],"rb");
			if(fp == 0){
				printf("\e[0;91mFile \"%s\" not found.\n\e[0;37m",argv[i]);
				cleanUp(sets,setsNum);
				exit(1);
			}

			fclose(fp);

			sets[setsNum - 1].size++;
			sets[setsNum - 1].imgs = (Image *)realloc(sets[setsNum - 1].imgs,sizeof(Image) * sets[setsNum - 1].size + 1);

			initImage( (sets[setsNum - 1].imgs + (sets[setsNum - 1].size - 1)));

			if(loadImage( (sets[setsNum - 1].imgs + (sets[setsNum - 1].size - 1)) ,argv[i]) == -1){
				cleanUp(sets,setsNum);
				exit(1);
			}

		}

	}

	//if last set is empty remove it
	if(sets[setsNum - 1].size == 0)
		setsNum--;


	int filesNum = 1; //number of files to generate
	char imgName[25];

	for(int i = 0; i < setsNum; i++)
		filesNum *= sets[i].size; 
	

	Image merged;
	initImage(&merged);

	loadImage(&merged,argv[firstImg]);

	clearImage(&merged);

	system("mkdir out"); //create output dir

	printf(" Generating images...\n");

	for(int i = 0; i < filesNum; i++){

		clearImage(&merged);
		for(int j = 0; j < setsNum; j++){
			if((sets[j].count + 1) >= sets[j].size){
				sets[j].count = 0;

			}else{
				sets[j].count++;
				break;
			}
		}

		for(int j = 0; j < setsNum; j++)
			mergeImage(&merged,&sets[j].imgs[sets[j].count]);

		sprintf(imgName,"img%02d.bmp",i + 1);
		printf("[%d/%d] out/%s\n",i + 1,filesNum,imgName);
		saveImage(&merged,imgName);
	}

	printf("\n All images generated successfully.\n");
	cleanUp(sets,setsNum);
}


void cleanUp(Set *sets,int setsNum){

	for(int i = 0; i < setsNum; i++){
		for(int j = 0; j < sets[i].size; j++){
			free(sets[i].imgs[j].bytes);
		}
		free(sets[i].imgs);
	}

	free(sets);

	free(header);

}




