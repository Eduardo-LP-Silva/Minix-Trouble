#include "Bitmap.h"
#include "stdio.h"
#include "video_gr.h"
#include <minix/drivers.h>

/* The following code, including the one in Bitmap.h, was made available by a former MIEIC student,
 * Henrique Ferrolho. It allows us to use images in a bmp format instead of xmps. Some changes were made
 * by us though, such as the creation of a near identical function of drawBitmap but instead of painting
 * line by line, it goes throught each pixel, allowing us to select specific colors we don't wish to
 * actually paint. We also modified both functions to write to an auxiliary buffer instead.
 */

Bitmap* loadBitmap(const char* filename) {
    // allocating necessary size
    Bitmap* bmp = (Bitmap*) malloc(sizeof(Bitmap));

    // open filename in read binary mode
    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
        return NULL;

    // read the bitmap file header
    BitmapFileHeader bitmapFileHeader;
    fread(&bitmapFileHeader, 2, 1, filePtr);

    // verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.type != 0x4D42) {
        fclose(filePtr);
        return NULL;
    }

    int rd;
    do {
        if ((rd = fread(&bitmapFileHeader.size, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.reserved, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.offset, 4, 1, filePtr)) != 1)
            break;
    } while (0);

    if ((rd =! 1)) {
        fprintf(stderr, "Error reading file\n");
        return NULL;
    }

    // read the bitmap info header
    BitmapInfoHeader bitmapInfoHeader;
    fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);

    // move file pointer to the begining of bitmap data
    fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

    // allocate enough memory for the bitmap image data
    unsigned char* bitmapImage = (unsigned char*) malloc(
            bitmapInfoHeader.imageSize);

    // verify memory allocation
    if (!bitmapImage) {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    // read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader.imageSize, 1, filePtr);

    // make sure bitmap image data was read
    if (bitmapImage == NULL) {
        fclose(filePtr);
        return NULL;
    }

    // close file and return bitmap image data
    fclose(filePtr);

    bmp->bitmapData = bitmapImage;
    bmp->bitmapInfoHeader = bitmapInfoHeader;

    return bmp;
}

void drawBitmap(Bitmap* bmp, int x, int y, Alignment alignment) {
    if (bmp == NULL)
        return;

    int width = bmp->bitmapInfoHeader.width;
    int drawWidth = width;
    int height = bmp->bitmapInfoHeader.height;

    if (alignment == ALIGN_CENTER)
        x -= width / 2;
    else if (alignment == ALIGN_RIGHT)
        x -= width;

    if (x + width < 0 || x > get_hres() || y + height < 0
            || y > get_vres())
        return;

    int xCorrection = 0;
    if (x < 0) {
        xCorrection = -x;
        drawWidth -= xCorrection;
        x = 0;

        if (drawWidth > get_hres())
            drawWidth = get_hres();
    } else if (x + drawWidth >= get_hres()) {
        drawWidth = get_hres() - x;
    }

    char* bufferStartPos;
    unsigned char* imgStartPos;

    int i;

    for (i = 0; i < height; i++) {
        int pos = y + height - 1 - i;

        if (pos < 0 || pos >= get_vres())
            continue;

        bufferStartPos = get_aux_mem();
        bufferStartPos += x * 2 + pos * get_hres() * 2;

        imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;

        memcpy(bufferStartPos, imgStartPos, drawWidth * 2);
    }
}

void drawBitmap_pixels(Bitmap* bmp, int x, int y, Alignment alignment) {
    if (bmp == NULL)
        return;

    int width = bmp->bitmapInfoHeader.width;
    int drawWidth = width;
    int height = bmp->bitmapInfoHeader.height;

    if (alignment == ALIGN_CENTER)
        x -= width / 2;
    else if (alignment == ALIGN_RIGHT)
        x -= width;

    if (x + width < 0 || x > get_hres() || y + height < 0
            || y > get_vres())
        return;

    int xCorrection = 0;
    if (x < 0) {
        xCorrection = -x;
        drawWidth -= xCorrection;
        x = 0;

        if (drawWidth > get_hres())
            drawWidth = get_hres();
    } else if (x + drawWidth >= get_hres()) {
        drawWidth = get_hres() - x;
    }

    char* bufferStartPos;
    unsigned char* imgStartPos;
    short value;

    int i, j;

    for (i = 0; i < height; i++) {
        int pos = y + height - 1 - i;

        if (pos < 0 || pos >= get_vres())
            continue;

        bufferStartPos = get_aux_mem();
        bufferStartPos += x * 2 + pos * get_hres() * 2;

        imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;

        for(j = 0; j < width; j++, bufferStartPos += 2, imgStartPos += 2)
        {
        	value = (((short) *imgStartPos) << 8) | *(imgStartPos + 1);

        	if(value == TRANSPARENCY_COLOR)
        		continue;

        	memcpy(bufferStartPos, imgStartPos, 2);
        }
    }
}

void deleteBitmap(Bitmap* bmp) {
    if (bmp == NULL)
        return;

    free(bmp->bitmapData);
    free(bmp);
}

void eraseBitmap(Bitmap *bmp, short x, short y)
{
	unsigned int i, j;
	unsigned h_res = get_hres();
	short *video_mem = (short *) get_video_mem(), *ptr;

	if(bmp == NULL)
		return;

	ptr = video_mem + h_res*y + x;

	for(i = 0; i < bmp->bitmapInfoHeader.height; i++, ptr = ptr + h_res * i)
		{
			for(j = 0; j < bmp->bitmapInfoHeader.width / 2; j++, ptr++)
			{
				*ptr = 0;
				ptr++;
				*ptr = 0;
			}

			ptr = video_mem + h_res*y + x;
		}

}
