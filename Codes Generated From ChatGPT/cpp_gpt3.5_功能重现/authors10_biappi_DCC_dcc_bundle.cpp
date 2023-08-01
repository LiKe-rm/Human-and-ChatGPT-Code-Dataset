#include "dcc.h"
#include <stdarg.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#define deltaProcLines 20
const int lineSize = 1024;

typedef struct {
    char **str;
    int numLines, allocLines;
} strTable;

typedef struct {
    strTable decl, code;
} bundle;

void newBundle(bundle *procCode) {
    procCode->decl.str = NULL;
    procCode->decl.numLines = 0;
    procCode->decl.allocLines = 0;
    procCode->code.str = NULL;
    procCode->code.numLines = 0;
    procCode->code.allocLines = 0;
}

void appendStrTab(strTable *strTab, const char *format, ...) {
    if (strTab->numLines >= strTab->allocLines) {
        incTableSize(strTab);
    }

    char *line = strTab->str[strTab->numLines];
    va_list argptr;
    va_start(argptr, format);
    vsnprintf(line, lineSize, format, argptr);
    va_end(argptr);

    strTab->numLines++;
}

int nextBundleIdx(strTable *strTab) {
    return strTab->numLines;
}

void addLabelBundle(strTable *strTab, int idx, int label) {
    char *line = strTab->str[idx];
    char *tabPos = strchr(line, '\t');
    *tabPos++ = ' ';
    snprintf(line, lineSize, "%d:\t%s", label, tabPos);
}

void writeBundle(FILE *fp, bundle procCode) {
    writeStrTab(fp, procCode.decl);
    writeStrTab(fp, procCode.code);
}

void freeBundle(bundle *procCode) {
    freeStrTab(&procCode->decl);
    freeStrTab(&procCode->code);
}

static void incTableSize(strTable *strTab) {
    int newAllocLines = strTab->allocLines + deltaProcLines;
    char **newStr = (char **) realloc(strTab->str, sizeof(char *) * newAllocLines);
    if (!newStr) {
        perror("realloc failed");
        exit(1);
    }

    strTab->str = newStr;
    for (int i = strTab->allocLines; i < newAllocLines; i++) {
        strTab->str[i] = (char *) malloc(lineSize);
        memset(strTab->str[i], 0, lineSize);
    }

    strTab->allocLines = newAllocLines;
}

static void writeStrTab(FILE *fp, strTable strTab) {
    for (int i = 0; i < strTab.numLines; i++) {
        fprintf(fp, "%s\n", strTab.str[i]);
    }
}

static void freeStrTab(strTable *strTab) {
    if (strTab->str) {
        for (int i = 0; i < strTab->allocLines; i++) {
            if (strTab->str[i]) {
                free(strTab->str[i]);
            }
        }
        free(strTab->str);
    }

    strTab->str = NULL;
    strTab->numLines = 0;
    strTab->allocLines = 0;
}
