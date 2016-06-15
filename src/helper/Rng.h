#include <random>
using namespace std;
/*
 * todo : corriger, génère toujours les mêmes nombres
 */

class Rng {
private:
    // Types
    //mt19937_64 re;
    //uniform_real_distribution<double> unif;
    //typedef variate_generator <Engine, Distribution> Generator;

    // To hold the generator
    //Generator* _gen;
        uniform_real_distribution<double> unif;//(120.0, 530.0);
        mt19937_64 re;//(666777);
        
public:

    Rng(int seed, double minVal, double maxVal) {
        // _gen = new Generator( Engine( seed ), Distribution( minVal, maxVal ) );
        uniform_real_distribution<double> unif( minVal, maxVal );
        mt19937_64 re(seed);

    }


    float next() {
        return unif(re) ;
    }
};

/*
 Sample& Sample::genWhiteNoise(double amplitude,int seed) {

    double lower_bound = -amplitude;
    double upper_bound = amplitude;

    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::mt19937_64 re(seed);

    for (int i = fxIStart; i < fxIEnd; i++) {
        Sample::data[i] += unif(re);
    }
    return *this;
}
 */