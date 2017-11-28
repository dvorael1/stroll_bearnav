#include <string>
#ifndef STATISTICS_H
#define STATISTICS_H


void pick(int* stcs, int max, int size);
void pick_n_best(int* stcs, int size, int n);
void pick_kvantil(int* stcs, int size, double p);
int prepare_sum(char* fname, std::string mapName, int* stcs, int size);
int prepare_w_sum(char* fname, std::string mapName, int* stcs, int size, int w1, int wm1);
#endif
