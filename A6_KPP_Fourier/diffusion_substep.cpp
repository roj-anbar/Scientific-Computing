/// @file diffusion_substep.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to solve for the diffusion part of the 1D KPP-Fisher equation.

#include "diffusion_substep.h"

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
void solve_diffusion(const double &L, const double &dt, rvector<double> &u_old, rvector<double> &u_current)
{
    // Size of solution vector
    int N = u_old.size();

    // Number of stored Fourier coefficients
    int complex_size = N / 2 + 1;

    // Initialize the fourier vectors (there will be total N/2+1 points in the fourier vectors)
    rvector<complex> u_hat_old(complex_size), u_hat_current(complex_size);

    // 1. Calculate u_hat_old:
    // Take fourier transform of u_old
    fft_fast(u_old, u_hat_old, 0);

    // 2. Solve diffusion equation in fourier space
    // Loop over each wavenumber
    for (int q = 0; q < N/2+1; q++)
    {
        double k = 2 * M_PI * q / L;
        u_hat_current[q] = u_hat_old[q] * std::exp(-k * k * dt);
    }
        
    // 3. Calculate u_current:
    // Taking inverse FT of u_hat_current
    fft_fast(u_current, u_hat_current, 1);
}


/// @brief Computes the Fast Fourier Transform (FFT) or Inverse FFT.
/// @param f Real-valued rarray vector (input of forward transform / output of inverse transform).
/// @param fhat Complex-valued rarray vector in Fourier space (output of forward transform / input of inverse transform).
/// @param inverse Boolean paraneter that if true, performs an inverse FFT; otherwise, performs a forward FFT.
void fft_fast(rvector<double> &f, rvector<complex> &fhat, bool inverse)
{
    int N = f.size();

    // Forward FFT (real → complex)
    if (!inverse)
    {                              
        fftw_plan p = fftw_plan_dft_r2c_1d(N, f.data(), reinterpret_cast<fftw_complex*>(fhat.data()), FFTW_ESTIMATE);
        fftw_execute(p);
        fftw_destroy_plan(p);
    }

    // Inverse FFT (complex → real)
    else
    {                                                
        fftw_plan p = fftw_plan_dft_c2r_1d(N, reinterpret_cast<fftw_complex*>(fhat.data()), f.data(), FFTW_ESTIMATE);
        fftw_execute(p);
        fftw_destroy_plan(p);

        // Normalize the inverse FFT (since FFTW does not do it automatically)
        for (int i = 0; i < N; i++)
            f[i] = f[i] / static_cast<double>(N);
    }
}
