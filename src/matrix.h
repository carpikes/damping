#ifndef MATRIX_H
#define MATRIX_H

#include "common.h"

void mat_mult(double out[], double m_l[], int lh, double m_r[], int rw, int s);
void mat_sum(double out[], double m_l[], double m_r[], int w, int h);
void mat_print(const char *name, double mat[], int size);

#endif
