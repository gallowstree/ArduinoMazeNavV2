#include "TwiddleAutotune.h" 
#include <Arduino.h>
const unsigned int dimension = 3;

TwiddleAutotune::TwiddleAutotune() {

}

double sum(double nums[]) {
    double s = 0;
    for(int i = 0; i < dimension; i++) {
        s += nums[i];
    }
    return s;
}


void TwiddleAutotune::start() {
    double p[] = {0, 0, 0};
    double dp[] = {1, 0.25, 0.25};
    double best_error = iterate(p);
    double threshold = 0.001;

    while(sum(dp) > threshold) {
        Serial.print("Best error: ");
        Serial.println(best_error);
        for(int i = 0; i < dimension; i++) {
            p[i] += dp[i];
            double error = iterate(p); 

            if (error < best_error) {
                best_error = error;
                dp[i] *= 1.1;
            } else {
                p[i] -= 2 * dp[i];
                error = iterate(p);

                if (error < best_error) {
                    best_error = error;
                    dp[i] *= 1.05;
                } else {
                    p[i] += dp[i];
                    dp[i] *= 0.9;
                }
            }
        }
    }

}