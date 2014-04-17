#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"
#include "window_function.h"

int main(void)
{
  MONO_PCM pcm0;
  int n, k, N;
  double *x_real, *x_imag, *X_real, *X_imag, *w;
  double W_real, W_imag;
  
  mono_wave_read(&pcm0, "ex2_1.wav"); /* WAVE�t�@�C�����烂�m�����̉��f�[�^����͂��� */
  
  N = 64; /* DFT�̃T�C�Y */
  x_real = calloc(N, sizeof(double)); /* �������̊m�� */
  x_imag = calloc(N, sizeof(double)); /* �������̊m�� */
  X_real = calloc(N, sizeof(double)); /* �������̊m�� */
  X_imag = calloc(N, sizeof(double)); /* �������̊m�� */
  w = calloc(N, sizeof(double)); /* �������̊m�� */
  
  Hanning_window(w, N); /* �n�j���O�� */
  
  for (n = 0; n < N; n++)
  {
    x_real[n] = pcm0.s[n] * w[n]; /* x(n)�̎����� */
    x_imag[n] = 0.0; /* x(n)�̋����� */
  }
  
  /* DFT */
  for (k = 0; k < N; k++)
  {
    for (n = 0; n < N; n++)
    {
      W_real = cos(2.0 * M_PI * k * n / N);
      W_imag = -sin(2.0 * M_PI * k * n / N);
      X_real[k] += W_real * x_real[n] - W_imag * x_imag[n]; /* X(k)�̎����� */
      X_imag[k] += W_real * x_imag[n] + W_imag * x_real[n]; /* X(k)�̋����� */
    }
  }
  
  /* ���g������ */
  for (k = 0; k < N; k++)
  {
    printf("%d %f+j%f\n", k, X_real[k], X_imag[k]);
  }
  
  free(pcm0.s); /* �������̉�� */
  free(x_real); /* �������̉�� */
  free(x_imag); /* �������̉�� */
  free(X_real); /* �������̉�� */
  free(X_imag); /* �������̉�� */
  free(w); /* �������̉�� */
  
  return 0;
}
