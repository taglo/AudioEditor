#include "RbjFilter.h"


    RbjFilter::RbjFilter() {
        // reset filter coeffs
        b0a0 = 0.0;
        b1a0 = 0.0;
        b2a0 = 0.0;
        a1a0 = 0.0;
        a2a0 = 0.0;

        // reset in/out history
        ou1L = 0.0;
        ou2L = 0.0;
        in1L = 0.0;
        in2L = 0.0;

        ou1R = 0.0;
        ou2R = 0.0;
        in1R = 0.0;
        in2R = 0.0;

    };

    void RbjFilter::filter(double in0L, double in0R, double &outL, double &outR) {
        // filter
        double ynL = b0a0 * in0L + b1a0 * in1L + b2a0 * in2L - a1a0 * ou1L - a2a0*ou2L;

        // push in/out buffers
        in2L = in1L;
        in1L = in0L;
        ou2L = ou1L;
        ou1L = ynL;

        // return output
        outL= ynL;
        
        // filter
        double ynR = b0a0 * in0R + b1a0 * in1R + b2a0 * in2R - a1a0 * ou1R - a2a0*ou2R;

        // push in/out buffers
        in2R = in1R;
        in1R = in0R;
        ou2R = ou1R;
        ou1R = ynR;

        // return output
        outR= ynR;
        
    };

    void RbjFilter::copy_filter_coeffs(RbjFilter filterIn) {
        b0a0 = filterIn.b0a0;
        b1a0 = filterIn.b1a0;
        b2a0 = filterIn.b2a0;
        a1a0 = filterIn.a1a0;
        a2a0 = filterIn.a2a0;
    }

    void RbjFilter::calc_filter_coeffs(int type, double frequency, double sample_rate, double q, double db_gain, bool q_is_bandwidth) {
        // temp pi
        double temp_pi = 3.1415926535897932384626433832795;

        // temp coef vars
        double alpha, a0, a1, a2, b0, b1, b2;

        // peaking, lowshelf and hishelf
        if (type >= 6) {
            double A = pow(10.0, (db_gain / 40.0));
            double omega = 2.0 * temp_pi * frequency / sample_rate;
            double tsin = sin(omega);
            double tcos = cos(omega);

            if (q_is_bandwidth)
                alpha = tsin * sinh(log(2.0) / 2.0 * q * omega / tsin);
            else
                alpha = tsin / (2.0 * q);

            double beta = sqrt(A) / q;

            // peaking
            if (type == 6) {
                b0 = float(1.0 + alpha * A);
                b1 = float(-2.0 * tcos);
                b2 = float(1.0 - alpha * A);
                a0 = float(1.0 + alpha / A);
                a1 = float(-2.0 * tcos);
                a2 = float(1.0 - alpha / A);
            }

            // lowshelf
            if (type == 7) {
                b0 = float(A * ((A + 1.0)-(A - 1.0) * tcos + beta * tsin));
                b1 = float(2.0 * A * ((A - 1.0)-(A + 1.0) * tcos));
                b2 = float(A * ((A + 1.0)-(A - 1.0) * tcos - beta * tsin));
                a0 = float((A + 1.0)+(A - 1.0) * tcos + beta * tsin);
                a1 = float(-2.0 * ((A - 1.0)+(A + 1.0) * tcos));
                a2 = float((A + 1.0)+(A - 1.0) * tcos - beta * tsin);
            }

            // hishelf
            if (type == 8) {
                b0 = float(A * ((A + 1.0)+(A - 1.0) * tcos + beta * tsin));
                b1 = float(-2.0 * A * ((A - 1.0)+(A + 1.0) * tcos));
                b2 = float(A * ((A + 1.0)+(A - 1.0) * tcos - beta * tsin));
                a0 = float((A + 1.0)-(A - 1.0) * tcos + beta * tsin);
                a1 = float(2.0 * ((A - 1.0)-(A + 1.0) * tcos));
                a2 = float((A + 1.0)-(A - 1.0) * tcos - beta * tsin);
            }
        } else {
            // other filters
            double omega = 2.0 * temp_pi * frequency / sample_rate;
            double tsin = sin(omega);
            double tcos = cos(omega);

            if (q_is_bandwidth)
                alpha = tsin * sinh(log(2.0) / 2.0 * q * omega / tsin);
            else
                alpha = tsin / (2.0 * q);


            // lowpass
            if (type == 0) {
                b0 = (1.0 - tcos) / 2.0;
                b1 = 1.0 - tcos;
                b2 = (1.0 - tcos) / 2.0;
                a0 = 1.0 + alpha;
                a1 = -2.0 * tcos;
                a2 = 1.0 - alpha;
            }

            // hipass
            if (type == 1) {
                b0 = (1.0 + tcos) / 2.0;
                b1 = -(1.0 + tcos);
                b2 = (1.0 + tcos) / 2.0;
                a0 = 1.0 + alpha;
                a1 = -2.0 * tcos;
                a2 = 1.0 - alpha;
            }

            // bandpass csg
            if (type == 2) {
                b0 = tsin / 2.0;
                b1 = 0.0;
                b2 = -tsin / 2;
                a0 = 1.0 + alpha;
                a1 = -2.0 * tcos;
                a2 = 1.0 - alpha;
            }

            // bandpass czpg
            if (type == 3) {
                b0 = alpha;
                b1 = 0.0;
                b2 = -alpha;
                a0 = 1.0 + alpha;
                a1 = -2.0 * tcos;
                a2 = 1.0 - alpha;
            }

            // notch
            if (type == 4) {
                b0 = 1.0;
                b1 = -2.0 * tcos;
                b2 = 1.0;
                a0 = 1.0 + alpha;
                a1 = -2.0 * tcos;
                a2 = 1.0 - alpha;
            }

            // allpass
            if (type == 5) {
                b0 = 1.0 - alpha;
                b1 = -2.0 * tcos;
                b2 = 1.0 + alpha;
                a0 = 1.0 + alpha;
                a1 = -2.0 * tcos;
                a2 = 1.0 - alpha;
            }
        }

        // set filter coeffs
        b0a0 = b0 / a0;
        b1a0 = b1 / a0;
        b2a0 = b2 / a0;
        a1a0 = a1 / a0;
        a2a0 = a2 / a0;
    };

