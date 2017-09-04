#ifndef MAZENAV_TWIDDLE_AUTOTUNE_H
#define MAZENAV_TWIDDLE_AUTOTUNE_H

class TwiddleAutotune {
public:
    TwiddleAutotune();
    void start();
    virtual double iterate(double p[]) = 0;
private:

};

#endif