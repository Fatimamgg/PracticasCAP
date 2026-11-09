#include <tmmintrin.h>
#include <emmintrin.h>
#include "stencil.h"

/*
void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) {
  
	short val;
	unsigned char val_out;

	for (int i = 1; i < height-1; i++)
		for (int j = 1; j < width-1; j++) {
			val = img_in[(i  )*width + j];
			val +=	-img_in[(i-1)*width + j-1] -   img_in[(i-1)*width + j] - img_in[(i-1)*width + j+1] 
					-img_in[(i  )*width + j-1] + 7*img_in[(i  )*width + j] - img_in[(i  )*width + j+1] 
					-img_in[(i+1)*width + j-1] -   img_in[(i+1)*width + j] - img_in[(i+1)*width + j+1];
			if (val<0){
				val=0;
			}else val_out = (unsigned char)val;
			if (val>255){
				val_out=255;
			}else val_out = (unsigned char)val;

			img_out[i*width + j] = (unsigned char)(val_out);
		}
}
*/
void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) {
	const __m128i zero = _mm_setzero_si128();
	const __m128i max255 = _mm_set1_epi16(255);

	for (int i = 1; i < height-1; i++) {
		int j = 1;
		for (; j <= width-9 ; j += 8) {
			__m128i p00 = _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)&img_in[(i-1)*width + j-1]));
			__m128i p01 = _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)&img_in[(i-1)*width + j]));
			__m128i p02 = _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)&img_in[(i-1)*width + j+1]));
			__m128i p10 = _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)&img_in[(i  )*width + j-1]));
			__m128i p11 = _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)&img_in[(i  )*width + j]));
			__m128i p12 = _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)&img_in[(i  )*width + j+1]));
			__m128i p20 = _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)&img_in[(i+1)*width + j-1]));
			__m128i p21 = _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)&img_in[(i+1)*width + j]));
			__m128i p22 = _mm_cvtepu8_epi16(_mm_loadl_epi64((__m128i*)&img_in[(i+1)*width + j+1]));
			__m128i val = _mm_slli_epi16(p11, 3);
			val = _mm_sub_epi16(val, p00);
			val = _mm_sub_epi16(val, p01);
			val = _mm_sub_epi16(val, p02);
			val = _mm_sub_epi16(val, p10);
			val = _mm_sub_epi16(val, p12);
			val = _mm_sub_epi16(val, p20);
			val = _mm_sub_epi16(val, p21);
			val = _mm_sub_epi16(val, p22);
			val = _mm_max_epi16(val, zero);
			val = _mm_min_epi16(val, max255);
			__m128i val_out = _mm_packus_epi16(val, val);
			_mm_storel_epi64((__m128i*)&img_out[i*width + j], val_out);
		}
			
			for (; j < width-1 ; j++) {
				short val = img_in[(i  )*width + j];
				val +=	-img_in[(i-1)*width + j-1] -   img_in[(i-1)*width + j] - img_in[(i-1)*width + j+1] 
						-img_in[(i  )*width + j-1] + 7*img_in[(i  )*width + j] - img_in[(i  )*width + j+1] 
						-img_in[(i+1)*width + j-1] -   img_in[(i+1)*width + j] - img_in[(i+1)*width + j+1];
				if (val<0){
					val=0;
				}
				else if (val>255){
					val =255;
				}

				img_out[i*width + j] = (unsigned char)(val);
			}
	}


void CopyImage(unsigned char *img_in, unsigned char *img_out, int width, int height) {

	for (int i = 0; i < height; i++) {
		#pragma ivdep
		for (int j = 0; j < width; j++){
			img_in[i*width + j] = img_out[i*width + j];
	}
}
}
