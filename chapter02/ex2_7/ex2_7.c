#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"
#include "fft.h"

int main(void)
{
  MONO_PCM pcm0;
  int n, k, N;
  double *x_real, *x_imag;
  
  mono_wave_read(&pcm0, "ex2_1.wav"); /* WAVE�t�@�C�����烂�m�����̉��f�[�^����͂��� */
  
  N = 64;
  x_real = calloc(N, sizeof(double)); /* �������̊m�� */
  x_imag = calloc(N, sizeof(double)); /* �������̊m�� */
  
  for (n = 0; n < N; n++)
  {
    x_real[n] = pcm0.s[n]; /* x(n)�̎����� */
    x_imag[n] = 0.0; /* x(n)�̋����� */
  }
  
  FFT(x_real, x_imag, N); /* FFT�̌v�Z���ʂ�x_real��x_imag�ɏ㏑������� */
  
  /* ���g������ */
  for (k = 0; k < N; k++)
  {
    printf("%d %f+j%f\n", k, x_real[k], x_imag[k]);
  }
  
  free(pcm0.s); /* �������̉�� */
  free(x_real); /* �������̉�� */
  free(x_imag); /* �������̉�� */
  
  return 0;
}
