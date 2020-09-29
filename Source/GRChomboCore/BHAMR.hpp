/* GRChombo
 * Copyright 2012 The GRChombo collaboration.
 * Please refer to LICENSE in GRChombo's root directory.
 */

#ifndef BHAMR_HPP_
#define BHAMR_HPP_

#include "AMRInterpolator.hpp"
#include "GRAMR.hpp"
#include "Lagrange.hpp"
#include <chrono>
#include <ratio>

// DISABLE_AHFINDER is used to override 'USE_AHFINDER' on specific examples
// in which you don't want to use the AHFINDER
// (add to GNUMakefile 'cxxcppflags := $(cxxcppflags) -DDISABLE_AHFINDER')
#if defined(USE_AHFINDER) && !defined(DISABLE_AHFINDER)
#include "AHInterpolation.hpp"
#include "AHSphericalCoords.hpp"
#include "ApparentHorizon.hpp"
#endif

/// A child of Chombo's AMR class to interface with tools which require
/// access to the whole AMR hierarchy, and those of GRAMR
/**
 * This object inherits from GRAMR and adds tools required for BH spacetimes
 */
class BHAMR : public GRAMR
{
  private:
    // the info for the puncture tracks
    int m_num_punctures;
    std::vector<std::array<double, CH_SPACEDIM>> m_puncture_coords;
    std::vector<std::array<double, CH_SPACEDIM>> m_puncture_shift;

  public:
    BHAMR()
    {
        m_num_punctures = 2; // default to 2 for now
        m_puncture_coords.resize(m_num_punctures);
        m_puncture_shift.resize(m_num_punctures);
    }

    ~BHAMR()
    {
#if defined(USE_AHFINDER) && !defined(DISABLE_AHFINDER)
        // destroy horizon pointers and finalize PETSc
        for (auto &ah : m_apparent_horizons)
            delete ah;
        AHFinder::finalize();
#endif
    }

#if defined(USE_AHFINDER) && !defined(DISABLE_AHFINDER)
    std::vector<ApparentHorizon<AHInterpolation<AHSphericalCoords>> *>
        m_apparent_horizons;
#endif

    // function to set punctures
    void set_puncture_data(
        std::vector<std::array<double, CH_SPACEDIM>> &a_puncture_coords,
        std::vector<std::array<double, CH_SPACEDIM>> &a_puncture_shift)
    {
        m_puncture_coords = a_puncture_coords;
        m_puncture_shift = a_puncture_shift;
    }

    // function to get punctures
    const std::vector<std::array<double, CH_SPACEDIM>>
    get_puncture_coords() const
    {
        return m_puncture_coords;
    }

    // function to get shift at puncture on previous timestep
    const std::vector<std::array<double, CH_SPACEDIM>>
    get_puncture_shift() const
    {
        return m_puncture_shift;
    }
};

#endif /* BHAMR_HPP_ */
