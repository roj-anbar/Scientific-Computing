/// @file friction.h
/// @author Ramses van Zon (commented by Rojin Anbarafshan)
/// @date February 13, 2025
/// @brief Module for computing the friction rate based on a timeseries sample of spatial positions.

#ifndef FRICTIONH
#define FRICTIONH

#include <rarray>

/// @brief Function to calculate the friction rate given a sample of velocities collected at a time dt apart.
/// The output is the estimated value for friction rate.
/// @param dt time step size between two sample points
/// @param v vector of velocity samples acquired through time
double frictionrate(double dt, const rvector<double>& v);


/// @brief Function to estimate the velocities using finite differences of position samples.
/// The output is the vector of velocity samples.
/// @param dt time step size between two sample points
/// @param z vector of location samples acquired through time
rvector<double> numdiff(double dt, const rvector<double>& z);

#endif
