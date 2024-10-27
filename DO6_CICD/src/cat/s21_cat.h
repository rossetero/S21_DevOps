#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#define OPT_NUM 7

int* getflags(int argc, char* argv[]);
int use_files(int argc, char* argv[], int* active_opts);
void modify_file(FILE* file, int* active_opts);
char generalFlagLogic(char ch, char prevch, FILE* file, int cnt_blank,
                      int cnt_lines, int* active_opts);
int* setFlags(char c, int* active_opts, int* bflag_used);

#endif