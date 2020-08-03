
#ifndef __FGFDMPacket_HPP__
#define __FGFDMPacket_HPP__

#include "endian_utils.hpp"

const uint32_t FGFDMPacket_Version{24};

//------------------------------------------------------------------------
// Struct: FGFDMPacket
// Description: This structure contains all the parameters for a top level
//              flight dynamics model - it is send as a packet through the
//              network to the flightgear application to control cockpit
//              interface
//------------------------------------------------------------------------
// Original source info below:
//
// net_fdm.hxx -- defines a common net I/O interface to the flight
//                dynamics model
//
// Written by Curtis Olson - http://www.flightgear.org/~curt
// Started September 2001.
//
// This file is in the Public Domain, and comes with no warranty.
//
// NOTE: this file defines an external interface structure.  Due to
// variability between platforms and architectures, we only used fixed
// length types here.  Specifically, integer types can vary in length.
// I am not aware of any platforms that don't use 4 bytes for float
// and 8 bytes for double.
//------------------------------------------------------------------------
struct FGFDMPacket
{
   enum {
      FG_MAX_ENGINES = 4,
      FG_MAX_WHEELS = 3,
      FG_MAX_TANKS = 4
   };

   std::uint32_t version{}; // increment when data values change
   std::uint32_t padding{}; // padding

   // positions
   double longitude{};     // geodetic (radians)
   double latitude{};      // geodetic (radians)
   double altitude{};      // above sea level (meters)
   float agl{};            // above ground level (meters)
   float phi{};            // roll (radians)
   float theta{};          // pitch (radians)
   float psi{};            // yaw or true heading (radians)
   float alpha{};          // angle of attack (radians)
   float beta{};           // side slip angle (radians)

   // velocities
   float phidot{};         // roll rate (radians/sec)
   float thetadot{};       // pitch rate (radians/sec)
   float psidot{};         // yaw rate (radians/sec)
   float vcas{};           // calibrated airspeed
   float climb_rate{};     // feet per second
   float v_north{};        // north velocity in local/body frame, fps
   float v_east{};         // east velocity in local/body frame, fps
   float v_down{};         // down/vertical velocity in local/body frame, fps
   float v_body_u{};       // ECEF velocity in body frame
   float v_body_v{};       // ECEF velocity in body frame 
   float v_body_w{};       // ECEF velocity in body frame

   // accelerations
   float A_X_pilot{};      // X accel in body frame ft/sec^2
   float A_Y_pilot{};      // Y accel in body frame ft/sec^2
   float A_Z_pilot{};      // Z accel in body frame ft/sec^2

   // stall
   float stall_warning{};  // 0.0 - 1.0 indicating the amount of stall
   float slip_deg{};       // slip ball deflection

   // engine status
   std::uint32_t num_engines{};                // number of valid engines
   std::uint32_t eng_state[FG_MAX_ENGINES]{};  // engine state (off, cranking, running)
   float rpm[FG_MAX_ENGINES]{};                // engine RPM rev/min
   float fuel_flow[FG_MAX_ENGINES]{};          // fuel flow gallons/hr
   float fuel_px[FG_MAX_ENGINES]{};            // fuel pressure psi
   float egt[FG_MAX_ENGINES]{};                // exhuast gas temp deg F
   float cht[FG_MAX_ENGINES]{};                // cylinder head temp deg F
   float mp_osi[FG_MAX_ENGINES]{};             // manifold pressure
   float tit[FG_MAX_ENGINES]{};                // turbine Inlet Temperature
   float oil_temp[FG_MAX_ENGINES]{};           // oil temp deg F
   float oil_px[FG_MAX_ENGINES]{};             // oil pressure psi

   // consumables
   uint32_t num_tanks{};                  // max number of fuel tanks
   float fuel_quantity[FG_MAX_TANKS]{};

   // gear status
   uint32_t num_wheels{};
   uint32_t wow[FG_MAX_WHEELS]{};
   float gear_pos[FG_MAX_WHEELS]{};
   float gear_steer[FG_MAX_WHEELS]{};
   float gear_compression[FG_MAX_WHEELS]{};

   // environment
   std::uint32_t cur_time{};      // current unix time
                                  // FIXME: make this uint64_t before 2038
   std::int32_t warp{};           // offset in seconds to unix time
   float visibility{};            // visibility in meters (for env. effects)

   // control surface positions (normalized values)
   float elevator{};
   float elevator_trim_tab{};
   float left_flap{};
   float right_flap{};
   float left_aileron{};
   float right_aileron{};
   float rudder{};
   float nose_wheel{};
   float speedbrake{};
   float spoilers{};
};

void swapBytes(FGFDMPacket* x)
{
   swap_endian<std::uint32_t>(x->version);
   swap_endian<std::uint32_t>(x->padding);

   // positions
   swap_endian<double>(x->latitude);
   swap_endian<double>(x->longitude);
   swap_endian<double>(x->altitude);
   swap_endian<float>(x->agl);
   swap_endian<float>(x->phi);
   swap_endian<float>(x->theta);
   swap_endian<float>(x->psi);
   swap_endian<float>(x->alpha);
   swap_endian<float>(x->beta);

   // velocities
   swap_endian<float>(x->phidot);
   swap_endian<float>(x->thetadot);
   swap_endian<float>(x->psidot);
   swap_endian<float>(x->vcas);
   swap_endian<float>(x->climb_rate);
   swap_endian<float>(x->v_north);
   swap_endian<float>(x->v_east);
   swap_endian<float>(x->v_down);
   swap_endian<float>(x->v_body_u);
   swap_endian<float>(x->v_body_v);
   swap_endian<float>(x->v_body_w);

   // accelerations
   swap_endian<float>(x->A_X_pilot);
   swap_endian<float>(x->A_Y_pilot);
   swap_endian<float>(x->A_Z_pilot);

   // stall
   swap_endian<float>(x->stall_warning);
   swap_endian<float>(x->slip_deg);

   // engine status
   swap_endian<std::uint32_t>(x->num_engines);

   // consumables
   swap_endian<std::uint32_t>(x->num_tanks);
   swap_endian<float>(x->fuel_quantity[0]);

   // gear status
   swap_endian<std::uint32_t>(x->num_wheels);

   // environment
   swap_endian<std::uint32_t>(x->cur_time);
   swap_endian<std::int32_t>(x->warp);
   swap_endian<float>(x->visibility);

   // control surface positions (normalized values)
   swap_endian<float>(x->elevator);
   swap_endian<float>(x->elevator_trim_tab);
   swap_endian<float>(x->left_flap);
   swap_endian<float>(x->right_flap);
   swap_endian<float>(x->left_aileron);
   swap_endian<float>(x->right_aileron);
   swap_endian<float>(x->rudder);
   swap_endian<float>(x->nose_wheel);
   swap_endian<float>(x->speedbrake);
   swap_endian<float>(x->spoilers);
}

#endif
