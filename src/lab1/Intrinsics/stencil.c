#include <mmintrin.h>
#include <tmmintrin.h>
#include <emmintrin.h>
#include <immintrin.h>
#include "stencil.h"

/*
void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) {

	short val;
	unsigned char val_out;

	for (int i = 1; i < height-1; i++) {
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
}
*/
/*
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

*/


void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) {


    for (int i = 1; i < height-1; i++) {
        int j = 1;

        for (; j < width - 17; j+=16) {
            __m256i p00 = _mm256_cvtepu8_epi16(_mm_loadu_si128((__m128i*)&img_in[(i-1)*width + j-1]));
            __m256i p01 = _mm256_cvtepu8_epi16(_mm_loadu_si128((__m128i*)&img_in[(i-1)*width + j]));
            __m256i p02 = _mm256_cvtepu8_epi16(_mm_loadu_si128((__m128i*)&img_in[(i-1)*width + j+1]));

            __m256i p10 = _mm256_cvtepu8_epi16(_mm_loadu_si128((__m128i*)&img_in[(i)*width + j-1]));
            __m256i p11 = _mm256_cvtepu8_epi16(_mm_loadu_si128((__m128i*)&img_in[(i)*width + j]));
            __m256i p12 = _mm256_cvtepu8_epi16(_mm_loadu_si128((__m128i*)&img_in[(i)*width + j+1]));

            __m256i p20 = _mm256_cvtepu8_epi16(_mm_loadu_si128((__m128i*)&img_in[(i+1)*width + j-1]));
            __m256i p21 = _mm256_cvtepu8_epi16(_mm_loadu_si128((__m128i*)&img_in[(i+1)*width + j]));
            __m256i p22 = _mm256_cvtepu8_epi16(_mm_loadu_si128((__m128i*)&img_in[(i+1)*width + j+1]));


            __m256i suma = _mm256_add_epi16(p00, p01);
            suma = _mm256_add_epi16(suma, p02);
            suma = _mm256_add_epi16(suma, p10);
            suma = _mm256_add_epi16(suma, p12);
            suma = _mm256_add_epi16(suma, p20);
            suma = _mm256_add_epi16(suma, p21);
            suma = _mm256_add_epi16(suma, p22);

            __m256i centroX8 = _mm256_slli_epi16(p11, 3);

            __m256i val = _mm256_sub_epi16(centroX8, suma);

            __m128i linea0 = _mm256_castsi256_si128(val);
            __m128i linea1 = _mm256_extracti128_si256(val, 1);

            __m128i val_o = _mm_packus_epi16(linea0, linea1);

            _mm_storeu_epi16((__m128i*)&img_out[i*width + j], val_o);
        }

        for (; j < width - 1; j++) {
            short val = img_in[(i)*width + j];
            val +=  -img_in[(i-1)*width + j-1] -   img_in[(i-1)*width + j] - img_in[(i-1)*width + j+1]
                    -img_in[(i  )*width + j-1] + 7*img_in[(i  )*width + j] - img_in[(i  )*width + j+1]
                    -img_in[(i+1)*width + j-1] -   img_in[(i+1)*width + j] - img_in[(i+1)*width + j+1];

            if (val < 0) val = 0;
            else if (val > 255) val = 255;

            img_out[i*width + j] = (unsigned char)val;
        }
    }
}


/*
void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) {
    for (int i = 1; i < height - 1; i++) {
        int j = 1;

        for (; j <= width - 33; j += 32) {
            __m512i p00 = _mm512_cvtepu8_epi16(_mm256_loadu_si256((__m256i*)&img_in[(i-1)*width + j-1]));
            __m512i p01 = _mm512_cvtepu8_epi16(_mm256_loadu_si256((__m256i*)&img_in[(i-1)*width + j]));
            __m512i p02 = _mm512_cvtepu8_epi16(_mm256_loadu_si256((__m256i*)&img_in[(i-1)*width + j+1]));

            __m512i p10 = _mm512_cvtepu8_epi16(_mm256_loadu_si256((__m256i*)&img_in[(i  )*width + j-1]));
            __m512i p11 = _mm512_cvtepu8_epi16(_mm256_loadu_si256((__m256i*)&img_in[(i  )*width + j]));
            __m512i p12 = _mm512_cvtepu8_epi16(_mm256_loadu_si256((__m256i*)&img_in[(i  )*width + j+1]));

            __m512i p20 = _mm512_cvtepu8_epi16(_mm256_loadu_si256((__m256i*)&img_in[(i+1)*width + j-1]));
            __m512i p21 = _mm512_cvtepu8_epi16(_mm256_loadu_si256((__m256i*)&img_in[(i+1)*width + j]));
            __m512i p22 = _mm512_cvtepu8_epi16(_mm256_loadu_si256((__m256i*)&img_in[(i+1)*width + j+1]));

            __m512i suma = _mm512_add_epi16(p00, p01);
            suma = _mm512_add_epi16(suma, p02);
            suma = _mm512_add_epi16(suma, p10);
            suma = _mm512_add_epi16(suma, p12);
            suma = _mm512_add_epi16(suma, p20);
            suma = _mm512_add_epi16(suma, p21);
            suma = _mm512_add_epi16(suma, p22);

            __m512i centroX8 = _mm512_slli_epi16(p11, 3);

            __m512i val = _mm512_sub_epi16(centroX8, suma);

            __m256i val_o = _mm512_cvtusepi16_epi8(val);

            _mm256_storeu_si256((__m256i*)&img_out[i*width + j], val_o);
        }

        for (; j < width - 1; j++) {
            short val = img_in[(i)*width + j];
            val +=  -img_in[(i-1)*width + j-1] -   img_in[(i-1)*width + j] - img_in[(i-1)*width + j+1]
                    -img_in[(i  )*width + j-1] + 7*img_in[(i  )*width + j] - img_in[(i  )*width + j+1]
                    -img_in[(i+1)*width + j-1] -   img_in[(i+1)*width + j] - img_in[(i+1)*width + j+1];

            if (val < 0) val = 0;
            else if (val > 255) val = 255;

            img_out[i*width + j] = (unsigned char)val;
        }
    }
}
*/

void CopyImage(unsigned char *img_in, unsigned char *img_out, int width, int height) {

	for (int i = 0; i < height; i++) {
		#pragma ivdep
		for (int j = 0; j < width; j++){
			img_in[i*width + j] = img_out[i*width + j];
    	}
    }
}
