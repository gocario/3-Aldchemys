#ifndef IMAGES_HPP
#define IMAGES_HPP

struct elementTilesImageGIMP
{
	unsigned int width;
	unsigned int height;
	unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
	unsigned char pixel_data[800 * 800 * 4 + 1];
};

struct workspaceBackgroundImageGIMP
{
	unsigned int width;
	unsigned int height;
	unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
	unsigned char pixel_data[256 * 240 * 4 + 1];
};

struct libraryBackgroundImageGIMP
{
	unsigned int width;
	unsigned int height;
	unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
	unsigned char pixel_data[64 * 240 * 4 + 1];
};

namespace ImageManager
{
	extern const elementTilesImageGIMP elemTiles_img;
	extern const workspaceBackgroundImageGIMP workspaceBackground_img;
	extern const libraryBackgroundImageGIMP libraryBackground_img;
}

#endif // IMAGES_HPP
