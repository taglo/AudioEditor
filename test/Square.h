/* 
 * File:   Square.h
 * Author: tglo
 *
 * Created on 11 septembre 2016, 11:08
 */

#ifndef SQUARE_H
#define	SQUARE_H


class Square{
    
public :
    Square(){
        w=rand()%100;
        h=rand()%100;
    }
    void debug() {
        std::cout << "w:" << w << " h:" << h << std::endl;
    }
private:
    int w;
    int h;
};

#endif	/* SQUARE_H */

