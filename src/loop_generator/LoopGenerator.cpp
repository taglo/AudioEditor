
#include "LoopGenerator.h"

LoopGenerator::LoopGenerator() {


}

void LoopGenerator::process() {

    
    Effet *cEffet;
    int nEffet;
    
    soundVector.clear();
    
    effetVector.clear();
    
    nEffet=10+rand()%20;
    
    
    while(effetVector.size() < nEffet) {
        cEffet=effetFactory.getNew();
        bool test=cEffet->ajoute();
        
        //std::cout<<test<<endl;
        
        if(test){
            effetVector.push_back(cEffet);
            cEffet->process();
        }
        
        //effetVector[0]->
    }
    
    for(int i=0; i<effetVector.size();i++){
        effetVector[i]->process();
    }
    
    /*
    Sound snd;
    soundVector.push_back(snd);

    std::cout << soundVector[0].info << endl;
    std::cout << soundVector.size()<< endl;

    soundVector[0].init(44100);
    
    soundVector[0].info +="test ssoundVector";
    
    std::cout << soundVector[0].info << endl;
    */
    
    
    /**
     *
     * 
     *      génère séquence : ensemble de step + notes(s) + longueur , plus ensemble de paramètres qui évoluen entre 0 et 1
     * 
     *      factory = new Factory
     * 
     *      initialise les objets qui servent aux étapes de mix
     *      while(effetVector.size()<nEffet) {
     * 
     *          cEffet=factory.getNew();
     * 
     *          if(cEffet.ajoute(paramContainer)) {
     *              efffetVector.push_back(cEffet);
     *              ceffet.process(sound,sequence);
     *          }
     *      }
     * 
     *      pour chaque partie de la séquence
     *          générateurs : synthes, samples
     * 
     *          duplique les samples de base
     *          lance des synthés
     *          lance des fx
     * 
     *          mixe / normalize
     * 
     */
}