#include <string>
#ifndef STATISTICS_H
#define STATISTICS_H


void pick(double* stcs, int max, int size);
void pick_n_best(double* stcs, int size, int n);
void pick_kvantil(double* stcs, int size, double p);
void pick_mnt_crl(double* stcs, int size, int n);
int prepare_sum(char* fname, std::string mapName, double* stcs, int size);
int prepare_w_sum(char* fname, std::string mapName, double* stcs, int size, int w1, int wm1);
void prepare_mov_avg(char* fname, std::string mapName, double* stcs, int size);
#endif
