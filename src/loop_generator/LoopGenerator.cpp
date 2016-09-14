
#include "LoopGenerator.h"

LoopGenerator::LoopGenerator() {


}


void LoopGenerator::process() {


    initParametre();
    
    //Effet *cEffet;
    int nEffet;

    soundVector = new vector<Sound>;
    effetVector = new vector<Effet*>;

    nEffet = 10 + rand() % 20;

    while (effetVector->size() < nEffet) {
        effetFactory.setNew(effetVector, soundVector);
    }

    std::cout << soundVector->size() << endl;

    soundVector->clear();

    for (int i = 0; i < effetVector->size(); i++) {
        (*effetVector)[i]->setSoundVector(soundVector);
        (*effetVector)[i]->process();
    }

    std::cout << soundVector->size() << endl;

    std::stringstream filename;


    for (int i = 0; i < soundVector->size(); i++) {

        filename.str("");
        filename << "test_loop_" << i;

        (*soundVector)[i].saveToFile(filename.str());
    }
}

void LoopGenerator::initParametre() {
    
    srand (time(NULL));
    
    parametre.typeBoucle=Parametre::arrTypeBoucle[rand()%Parametre::nTypeBoucle];
    
    std::cout<<parametre.typeBoucle<<endl;
    
}