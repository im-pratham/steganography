#define RGB_COMPONENT_COLOR 255

typedef struct PPMPixel{
	unsigned char red,green,blue;
}PPMPixel;

typedef struct PPMImage{
	int x, y;
	PPMPixel *data;
} PPMImage;

PPMImage *readPPM(const char *filename);
void writePPM(const char *filename, PPMImage *img);
void changeColorPPM(PPMImage *img, char *inputd);
void readData(const char *filename, char *dataout);

