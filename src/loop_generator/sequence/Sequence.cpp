
#include "Sequence.h"

Sequence::Sequence() {
    //seq = new vector<Step*>;

}

void Sequence::setParametre(Parametre *parametreIn) {
    parametre = parametreIn;
}

void Sequence::process(vector<Step> *stepVectorIn) {
    std::cout << parametre->typeBoucle << std::endl;

    stepVector = stepVectorIn;


    stepVector->clear();

    for (double s = 0.0; s < 16.0; s += 4.0) {

        Step t; //=new Step();
       // t = new Step();

        t.position = s;


        stepVector->push_back(t);

    }

    std::cout << stepVector->size() << endl;


}