#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE
#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OPT_NUM 6
#define PAT_NUM 100

typedef struct СmdArgs {
  int e, i, v, c, l, n, s, h, o, f;
  char patterns[PAT_NUM][PAT_NUM];
  int flagnum;
  int patcnt;
} CmdArgs;

void initCmdArgs(CmdArgs* cmdargs);
CmdArgs* createCmdArgs();
CmdArgs* getFlags(int argc, char* argv[]);
int checkLine(char** line, CmdArgs* cmdargs);
int getFileNames(int argc, char* argv[], CmdArgs* cmdargs);
int useFile(FILE* file, char* filename, CmdArgs* cmdargs, int cnt_files);
char* strlwr(char* s);
CmdArgs* setFlags(char ch, CmdArgs* cmdargs);
char* patchLine(char* line, char* orig_line);
char** getMatch(char** orig_line, regmatch_t match, CmdArgs* cmdargs);
int getRegexFromFile(CmdArgs* cmdargs, char* filename);
void useFlags(char* orig_line, int* cnt_lines, int cnt_files, int* code,
              int* cnt_found, CmdArgs* cmdargs, char* filename);

#endif