/* GRChombo
 * Copyright 2012 The GRChombo collaboration.
 * Please refer to LICENSE in GRChombo's root directory.
 */

#ifndef SIMULATIONPARAMETERS_HPP_
#define SIMULATIONPARAMETERS_HPP_

// General includes
#include "GRParmParse.hpp"
#include "SimulationParametersBase.hpp"

// Problem specific includes:
#include "CCZ4.hpp"
#include "KerrBH.hpp"

class SimulationParameters : public SimulationParametersBase
{
  public:
    SimulationParameters(GRParmParse &pp) : SimulationParametersBase(pp)
    {
        readParams(pp);
    }

    /// Read parameters from the parameter file
    void readParams(GRParmParse &pp)
    {
        // Initial Kerr data
        pp.load("kerr_mass", kerr_params.mass);
        pp.load("kerr_spin", kerr_params.spin);
        pp.load("kerr_center", kerr_params.center, center);

#ifdef USE_AHFINDER
        pp.load("AH_initial_guess", AH_initial_guess, 0.5 * kerr_params.mass);
#endif
    }

    KerrBH::params_t kerr_params;

#ifdef USE_AHFINDER
    double AH_initial_guess;
#endif
};

#endif /* SIMULATIONPARAMETERS_HPP_ */
