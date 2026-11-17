#include "udf.h"

/*
References:
[1] D.M. Hargreaves, N.G. Wright / J. Wind Eng. Ind. Aerodyn. 95 (2007) 355–369, doi:10.1016/j.jweia.2006.08.002
[2] Batistic, Ivan, et al. "Steady RANS Modeling of the Atmospheric Boundary Layer:\
    A Systematic Review and Some Practical Guidelines." OpenFOAM® Journal 6 (2026): 60-78.
*/

// Reference velocity
#define UREF 10.0
// Turbulence model constant
#define CMU 0.09
// Von karman constant
#define VKC 0.4
// Reference height
#define ZREF 6.0
// Reference roughness
#define Z0 0.01

DEFINE_PROFILE(velocity_profile, thread, position)
{
        real x[ND_ND];
        real z;
        real u, u_star;
        face_t f;


        u_star = UREF*VKC/log((ZREF+Z0)/Z0) ;

        begin_f_loop(f, thread)
        {
                F_CENTROID(x,f,thread);
                z=x[2];
                u = u_star/VKC*log((z+Z0)/Z0);
                F_PROFILE(f,thread,position) = u;
        }
        end_f_loop(f, thread)
}


DEFINE_PROFILE(k_profile, thread, position)
{
        real x[ND_ND];
        face_t f;

        real u_star ;

        u_star = UREF*VKC/log((ZREF+Z0)/Z0) ;


        begin_f_loop(f, thread)
        {
                F_CENTROID(x,f,thread);

                F_PROFILE(f,thread,position)=u_star*u_star/sqrt(CMU);

        }
        end_f_loop(f, thread)
}


DEFINE_PROFILE(dissip_profile, thread, position)
{
        real x[ND_ND];
        face_t f;
        real u_star, z ;

        u_star = UREF*VKC/log((ZREF+Z0)/Z0) ;

        begin_f_loop(f, thread)
        {
                F_CENTROID(x,f,thread);
                z=x[2];
                F_PROFILE(f,thread,position)=pow(u_star,3.)/(VKC*(z+Z0));
        }
        end_f_loop(f,thread)
}


DEFINE_PROFILE(omega_profile, thread, position)
{
    real x[ND_ND];
    real z, u_star;
    face_t f;

    u_star = UREF*VKC/log((ZREF + Z0)/Z0);

    begin_f_loop(f, thread)
    {
        F_CENTROID(x, f, thread);
        z = x[2];

        F_PROFILE(f, thread, position) =
            u_star/(sqrt(CMU)*VKC*(z+Z0));
    }
    end_f_loop(f, thread)
}
