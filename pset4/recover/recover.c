#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#define BLOCK_SIZE 512


int main (int argc, char*argv[]){

    //get file name from command line input
    char*file_name = argv[1];

    //Open memory card with file name given above
    FILE* card = fopen(file_name, "r");

    //Error check in case file can't be found
    if(!card){
        printf("Error, file cant be opened !\n");
        return 1;
    }

    unsigned char buffer[BLOCK_SIZE];
    char jpeg_title[8];
    int found = 1;

    // do the below while there are still blocks to read

    // Read the very first block of data
    fread(&buffer, BLOCK_SIZE, 1, card);

    // while there are block to read
    while (fread(&buffer, BLOCK_SIZE, 1, card) == 1){

        //check for jpeg
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){

            //stores jpeg name in jpeg title and open new jpeg with that name
            sprintf(jpeg_title, "%03d.jpg", found);
            FILE* img = fopen(jpeg_title, "a");
            found++;

            //write jpeg when haven't encounter new jpeg
            do{

                fwrite(&buffer, BLOCK_SIZE, 1, img);
                fread(&buffer, BLOCK_SIZE, 1, card);

            //while not new jpeg and not end of file
            }while(!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) && feof(card)==0);

            fclose(img);
            //move file to next block
            fseek(card, -1 * BLOCK_SIZE, SEEK_CUR);

        }

    }

    fclose(card);

}