/// @file model.h
/// @author Ramses van Zon (commented by Rojin Anbarafshan)
/// @date February 13, 2025
/// @brief Module for creating a timeseries spatial and velocity dataset of a falling object in a viscous liquid.

#ifndef MODELH
#define MODELH

#include <rarray>

/// @brief Structure to hold the parameters for the friction rate model.
///
/// This structure contains physical parameters required for creating a sample dataset: \n
/// - alpha = friction constant \n
/// - g     = gravitational acceleration \n
/// - v0    = initial velocity \n
/// - z0    = initial location \n
struct ModelParameters
{
    double alpha;  // friction constant
    double g;      // gravitation acceleration
    double v0;     // initial (vertical) velocity
    double z0;     // initial height
};

/// @brief Function to compute the spatial position at each time using the given model parameters.
/// Returns the computed location z at time t.
/// @param t time step at which position is calculated
/// @param p model parameters including initial velocity, gravity, and friction rate
double z(double t, const ModelParameters& p);

/// @brief Function to compute the velocity at each time using the given model parameters.
/// Returns the computed velocity v at time t.
/// @param t time step at which velocity is calculated
/// @param p model parameters including initial velocity, gravity, and friction rate
double v(double t, const ModelParameters& p);


/// @brief Function to calculate the vector of velocities over a time range using the model.
/// Returns the vector of timeseries velocities.
/// @param t1 start time
/// @param t2 end time
/// @param dt time step size (between two data point)
/// @param p model parameters including initial velocity, gravity, and friction rate
rvector<double> compute_model_v(double t1, double t2, double dt,
                               const ModelParameters& p);


/// @brief Function to calculate the vector of positions over a time range using the model.
/// Returns the vector of timeseries positions.
/// @param t1 start time
/// @param t2 end time
/// @param dt time step size (between two data point)
/// @param p model parameters including initial velocity, gravity, and friction rate
rvector<double> compute_model_z(double t1, double t2, double dt,
                               const ModelParameters& p);

#endif
