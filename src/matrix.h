#ifndef MATRIX_H
#define MATRIX_H

#include "common.h"

void mat_mult(double out[], double m_l[], size_t lh, double m_r[], size_t rw, size_t s);
void mat_sum(double out[], double m_l[], double m_r[], size_t w, size_t h);
void mat_print(const char *name, double mat[], size_t size);

#endif
