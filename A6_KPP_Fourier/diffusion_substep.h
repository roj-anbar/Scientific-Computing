/// @file diffusion_substep.h
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to solve for the diffusion part of the 1D KPP-Fisher equation.

#ifndef DIFFUSION_SUBSTEP_H
#define DIFFUSION_SUBSTEP_H

#include <cmath>
#include <complex>
#include <rarray>
#include <fftw3.h>

// Define complex number type for convenience
using complex = std::complex<double>;

/// @brief Solves the diffusion equation in Fourier space.
/// @param dt Time step size.
/// @param u_old Real-valued rarray vector of solution at the previous timestep.
/// @param u_current Real-valued rarray vector of solution at the next timestep.
void solve_diffusion(const double &L, const double &dt, rvector<double> &u_old, rvector<double> &u_current);

/// @brief Computes the Fast Fourier Transform (FFT) or Inverse FFT.
/// @param f Real-valued rarray vector (input of forward transform / output of inverse transform).
/// @param fhat Complex-valued rarray vector in Fourier space (output of forward transform / input of inverse transform).
/// @param inverse Boolean paraneter that if true, performs an inverse FFT; otherwise, performs a forward FFT.
void fft_fast(rvector<double> &f, rvector<complex> &fhat, bool inverse);

#endif
