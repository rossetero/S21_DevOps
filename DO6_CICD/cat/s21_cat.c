#include "s21_cat.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    int* opts = getflags(argc, argv);
    if (opts) use_files(argc, argv, opts);
  } else {
    printf("Noargs\n");
  }
  return 0;
}

int* getflags(int argc, char* argv[]) {
  int* active_opts = (int*)calloc(OPT_NUM, sizeof(int));
  if (active_opts == NULL) {
    printf("No memory\n");
  } else {
    static struct option long_options[] = {{"squeeze-blank", 0, 0, 's'},
                                           {"number", 0, 0, 'n'},
                                           {"number-nonblank", 0, 0, 'b'},
                                           {0, 0, 0, 0}};
    int option_index = 0, bflag_used = 0, c;
    while (((c = getopt_long(argc, argv, "+snbetvTE", long_options,
                             &option_index)) != -1) &&
           active_opts) {
      active_opts = setFlags(c, active_opts, &bflag_used);
    }
    if (active_opts) active_opts[6] = optind;  // с учетом имени программы
  }
  return active_opts;  // добавить обработку NULL
}

int* setFlags(char c, int* active_opts, int* bflag_used) {
  switch (c) {
    case 'v':
      active_opts[5] = 1;
      break;
    case 's':
      active_opts[0] = 1;
      break;
    case 'n':
      active_opts[1] = !(*bflag_used) ? 1 : 0;
      break;
    case 'b':
      active_opts[2] = 1;
      active_opts[1] = 0;
      *bflag_used = 1;
      break;
    case 'e':
      active_opts[5] = 1;
      active_opts[3] = 1;
      break;
    case 'E':
      active_opts[3] = 1;
      break;
    case 't':
      active_opts[5] = 1;
      active_opts[4] = 1;
      break;
    case 'T':
      active_opts[4] = 1;
      break;
    default:
      free(active_opts);
      active_opts = NULL;
      break;
  }
  return active_opts;
}

int use_files(int argc, char* argv[], int* active_opts) {
  int code = 1;  // success
  int file_begin_ind = active_opts[6];
  for (int i = file_begin_ind; i < argc; ++i) {
    FILE* file = fopen(argv[i], "r");
    if (NULL == file) {
      printf("cat: %s: No such file or directory\n", argv[i]);
      code = 0;  // fail
    } else {
      modify_file(file, active_opts);
      fclose(file);
    }
  }
  free(active_opts);
  return code;
}

void modify_file(FILE* file, int* active_opts) {
  int cnt_blank = 0;
  int cnt_lines = 1;
  char ch = '*', prevch = '*';
  if ((prevch = fgetc(file)) != EOF) {
    if (prevch == '\n') {
      cnt_blank += 2;
    }
    if (active_opts[1]) {
      printf("%6d\t", cnt_lines++);
    }
    if (active_opts[2] && prevch != '\n') {
      printf("%6d\t", cnt_lines++);
    }
    prevch =
        generalFlagLogic(ch, prevch, file, cnt_blank, cnt_lines, active_opts);
    if (active_opts[3] && prevch == '\n') putchar('$');
    if (active_opts[4] && prevch == '\t') {
      putchar('^');
      prevch = 'I';
    }
    if (active_opts[5] && (int)prevch != 10 &&
        ((int)prevch < 32 || (int)prevch == 127)) {
      putchar('^');
      prevch += 64;
    }
    putchar(prevch);
  }
}

char generalFlagLogic(char ch, char prevch, FILE* file, int cnt_blank,
                      int cnt_lines, int* active_opts) {
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      cnt_blank++;
    } else
      cnt_blank = 0;
    if (active_opts[0] && cnt_blank > 2) {
      continue;
      cnt_lines--;
    }
    if (active_opts[5] && (int)prevch != 10 && (int)prevch != 9 &&
        ((int)prevch < 32 || (int)prevch == 127)) {
      putchar('^');
      if ((int)prevch == 127)
        prevch = '?';
      else
        prevch += 64;
    }
    if (active_opts[3] && prevch == '\n') putchar('$');
    if (active_opts[4] && prevch == '\t') {
      putchar('^');
      prevch = 'I';
    }
    putchar(prevch);
    if (active_opts[1] && prevch == '\n') {
      printf("%6d\t", (cnt_lines)++);
    }
    if (active_opts[2] && prevch == '\n' && ch != '\n')
      printf("%6d\t", (cnt_lines)++);

    prevch = ch;
  }
  return prevch;
}
