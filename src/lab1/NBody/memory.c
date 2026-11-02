
#include <malloc.h>
#include <stdlib.h>
#include "nbody.h"

body* get_memory(int nBodies)
{
	body *p = (body*)malloc(nBodies*sizeof(body));
	p->m = (float*)malloc(nBodies*sizeof(float));
	p->x = (float*)malloc(nBodies*sizeof(float));
	p->y = (float*)malloc(nBodies*sizeof(float));
	p->z = (float*)malloc(nBodies*sizeof(float));
	p->vx = (float*)malloc(nBodies*sizeof(float));
	p->vy = (float*)malloc(nBodies*sizeof(float));
	p->vz = (float*)malloc(nBodies*sizeof(float));
	return p;
}

void free_memory(body *p)
{
	free(p);
}

void randomizeBodies(body *data, int n) {
	for (int i = 0; i < n; i++) {
		data->m[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;

		data->x[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data->y[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data->z[i]  = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;

		data->vx[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data->vy[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
		data->vz[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
	}
}

