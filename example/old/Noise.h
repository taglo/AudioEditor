/* 
 * File:   Noise.h
 * Author: tglo
 *
 * Created on 30 janvier 2016, 06:57
 */

#ifndef NOISE_H
#define	NOISE_H
using namespace std;

class Noise {
private:
    
public:
    Noise(double amplitude);
    //Noise(const Noise& orig);
    virtual ~Noise();

    double bound;

    std::mt19937_64 rng();
    std::uniform_real_distribution<double> distribution;

    // double tick=rng(distribution);
    double tick();



};

#endif	/* NOISE_H */

