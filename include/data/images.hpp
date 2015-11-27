#ifndef IMAGES_HPP
#define IMAGES_HPP

struct ElementTilesImageGIMP
{
	unsigned int width;
	unsigned int height;
	unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
	unsigned char pixel_data[800 * 800 * 4 + 1];
};

namespace ImageManager
{
	extern const ElementTilesImageGIMP elemTiles_img;
}

#endif // IMAGES_HPP
