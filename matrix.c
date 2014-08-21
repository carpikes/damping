#include "matrix.h"

/** Computes matrix multiplication
 * @param out Output matrix (lh*rw)
 * @param m_l Left matrix (input)
 * @param lh Number of left matrix rows
 * @param m_r Right matrix (input)
 * @param rw Number of right matrix columns
 * @param s Number of left matrix columns (or right matrix rows)
 */
void mat_mult(double out[], double m_l[], int lh, double m_r[], int rw, int s) {
    int i,x,y;

    for(y=0;y<lh;y++)
        for(x=0;x<rw;x++) {
            out[y*rw+x] = 0;
            for(i=0;i<s;i++)
                out[y*rw+x] += m_l[i+y*s] * m_r[i*rw+x];
        }

}

/** Computes matrix sum
 * @param out Output matrix(w*h)
 * @param m_l Left matrix
 * @param m_r Right matrix
 * @param w width
 * @param h height
 */
void mat_sum(double out[], double m_l[], double m_r[], int w, int h) {
    int i, wh=w*h;

    for(i=0;i<wh;i++)
        out[i]=m_l[i]+m_r[i];
}

 /** Prints a matrix
  */
void mat_print(const char *name, double mat[], int size) {
    int i;
    printf("%s [", name);
    for(i=0;i<size;i++)
        printf("%2.5f ", mat[i]);
    printf("]\n");
}
