#include "s21_grep.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    CmdArgs* cmdargs = getFlags(argc, argv);
    if (cmdargs) {
      getFileNames(argc, argv, cmdargs);
    }
  } else {
    printf("No args\n");
  }
  return 0;
}

int getFileNames(int argc, char* argv[], CmdArgs* cmdargs) {
  int code = 1;
  for (int i = cmdargs->flagnum; i < argc; ++i) {
    FILE* file = fopen(argv[i], "r");
    if (NULL == file) {
      if (!cmdargs->s) printf("grep: %s: No such file or directory\n", argv[i]);
      code = 404;
      continue;
    } else {
      code = useFile(file, argv[i], cmdargs, argc - cmdargs->flagnum);
      fclose(file);
    }
  }
  free(cmdargs);
  return code;
}

void useFlags(char* orig_line, int* cnt_lines, int cnt_files, int* code,
              int* cnt_found, CmdArgs* cmdargs, char* filename) {
  *cnt_lines += 1;
  char* line = (char*)malloc(sizeof(char) * (strlen(orig_line) + 2));
  if (line) {
    strcpy(line, orig_line);
    *code = checkLine(&line, cmdargs);
    if (cmdargs->v) *code = !(*code);
    if (*code == 1) {
      if (cmdargs->l || cmdargs->c) {
        *cnt_found += 1;
      } else if (cmdargs->n) {
        cnt_files > 1 && !cmdargs->h
            ? printf("%s:%d:%s", filename, *cnt_lines, line)
            : printf("%d:%s", *cnt_lines, line);
      } else {
        cnt_files > 1 && !cmdargs->h ? printf("%s:%s", filename, line)
                                     : printf("%s", line);
      }
    }
    free(line);
  }
}

int useFile(FILE* file, char* filename, CmdArgs* cmdargs, int cnt_files) {
  char* orig_line = NULL;
  size_t len = 0;
  ssize_t nread;
  int code = 1;
  int cnt_found = 0;
  int cnt_lines = 0;
  while (((nread = getline(&orig_line, &len, file)) != -1) && code != 404) {
    useFlags(orig_line, &cnt_lines, cnt_files, &code, &cnt_found, cmdargs,
             filename);
  }
  free(orig_line);
  if (cmdargs->c && cmdargs->l && cnt_found) {
    cnt_files > 1 && !cmdargs->h ? printf("%s:%d\n", filename, 1)
                                 : printf("%d\n", 1);
  } else if (cmdargs->c && cmdargs->l && !cnt_found) {
    cnt_files > 1 && !cmdargs->h ? printf("%s:%d\n", filename, 0)
                                 : printf("%d\n", 0);
  } else if (cmdargs->c) {
    cnt_files > 1 && !cmdargs->h ? printf("%s:%d\n", filename, cnt_found)
                                 : printf("%d\n", cnt_found);
  }
  if (cmdargs->l && cnt_found) {
    printf("%s\n", filename);
  }
  return code;
}

int checkLine(char** orig_line, CmdArgs* cmdargs) {
  regex_t regex;
  regmatch_t match;
  int re = 0;
  int found = 0;
  int len = strlen(*orig_line) + 1;
  char line[len];
  strcpy(line, *orig_line);
  if (cmdargs->i) strlwr(line);
  for (int i = 0; i < cmdargs->patcnt && found == 0 && found != 404; ++i) {
    if (cmdargs->i) strlwr(cmdargs->patterns[i]);
    re = regcomp(&regex, cmdargs->patterns[i], 0);

    if (re) {
      found = 404;
    }
    if (found != 404) {
      *orig_line = patchLine(line, *orig_line);
      if (regexec(&regex, line, 1, &match, 0) == 0) {
        orig_line = getMatch(orig_line, match, cmdargs);
        found = 1;
      }
    }
    regfree(&regex);
  }
  return found;
}

char** getMatch(char** orig_line, regmatch_t match, CmdArgs* cmdargs) {
  if (cmdargs->o) {
    int start = match.rm_so;
    int end = match.rm_eo;
    int length = end - start;
    char* matched_string = (char*)malloc(sizeof(char) * (length + 3));
    if (matched_string) {
      strncpy(matched_string, *orig_line + start, length);
      matched_string[length] = '\n';
      matched_string[length + 1] = '\0';
      free(*orig_line);
      *orig_line = matched_string;
    }
  }
  return orig_line;
}

char* patchLine(char* line, char* orig_line) {
  int orig_len = strlen(orig_line);
  int len = strlen(line);
  if (line[len - 1] == '\n') {
    line[len - 1] = '\0';
  }
  if (orig_line[orig_len - 1] != '\n') {
    orig_line[orig_len] = '\n';
    orig_line[orig_len + 1] = '\0';
  }
  return orig_line;
}

char* strlwr(char* s) {
  for (size_t i = 0; i < strlen(s); ++i)
    if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 'a' - 'A';
  return s;
}

void initCmdArgs(CmdArgs* cmdargs) {
  cmdargs->e = 0;
  cmdargs->o = 0;
  cmdargs->h = 0;
  cmdargs->s = 0;
  cmdargs->n = 0;
  cmdargs->l = 0;
  cmdargs->c = 0;
  cmdargs->v = 0;
  cmdargs->i = 0;
  cmdargs->f = 0;
  for (int i = 0; i < PAT_NUM; i++) {
    for (int j = 0; j < PAT_NUM; j++) {
      cmdargs->patterns[i][j] = '\0';
    }
  }
  cmdargs->flagnum = 0;
  cmdargs->patcnt = 0;
}

CmdArgs* getFlags(int argc, char* argv[]) {
  CmdArgs* cmdargs = malloc(sizeof(CmdArgs));
  if (cmdargs == NULL) {
    printf("No memory\n");
  } else {
    initCmdArgs(cmdargs);
    char c = '*';
    cmdargs->patcnt = 0;
    while (((c = getopt(argc, argv, "+e:ivclnshof:")) != -1) && cmdargs) {
      cmdargs = setFlags(c, cmdargs);
    }
    if (cmdargs) cmdargs->flagnum = optind;
    if (cmdargs && !cmdargs->e && !cmdargs->f) {
      strcpy(cmdargs->patterns[0], argv[optind]);
      cmdargs->patcnt++;
      cmdargs->flagnum++;
    }
  }
  return cmdargs;
}

int getRegexFromFile(CmdArgs* cmdargs, char* filename) {
  FILE* regfile = fopen(filename, "r");
  if (NULL == regfile) {
    printf("grep: %s: No such file or directory\n", filename);
    return 0;
  } else {
    char* line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, regfile)) != -1) {
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
      strcpy(cmdargs->patterns[cmdargs->patcnt], line);
      cmdargs->patcnt++;
    }
    free(line);
    fclose(regfile);
  }
  return 1;
}

CmdArgs* setFlags(char ch, CmdArgs* cmdargs) {
  switch (ch) {
    case 'e':
      cmdargs->e = 1;
      strcpy(cmdargs->patterns[cmdargs->patcnt], optarg);
      cmdargs->patcnt++;
      break;
    case 'f':
      cmdargs->f = 1;
      if (!getRegexFromFile(cmdargs, optarg)) {
        free(cmdargs);
        cmdargs = NULL;
      }
      break;
    case 'i':
      cmdargs->i = 1;
      break;
    case 'v':
      cmdargs->v = 1;
      break;
    case 'c':
      cmdargs->c = 1;
      break;
    case 'l':
      cmdargs->l = 1;
      break;
    case 'n':
      cmdargs->n = 1;
      break;
    case 's':
      cmdargs->s = 1;
      break;
    case 'h':
      cmdargs->h = 1;
      break;
    case 'o':
      cmdargs->o = 1;
      break;
    default:
      printf("Unknown option\n");
      free(cmdargs);
      cmdargs = NULL;
      break;
  }
  return cmdargs;
}
