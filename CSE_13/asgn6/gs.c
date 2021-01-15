#include "gs.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct GoodSpeak {
  char *oldspeak;
  char *newspeak;
};

GoodSpeak *gs_create(char *oldspeak, char *newspeak) {
  GoodSpeak *fresh = (GoodSpeak *)malloc(sizeof(struct GoodSpeak));
  if (!fresh || !oldspeak) {
    return NULL;
  }

  fresh->oldspeak = (char *)malloc(strlen(oldspeak) + 1);
  fresh->newspeak = (char *)malloc(strlen(newspeak) + 1);
  if(fresh->oldspeak && fresh->newspeak){
    strcpy(fresh->oldspeak, oldspeak);
    strcpy(fresh->newspeak, newspeak);
  }else{
    return NULL;
  }
  return fresh;
}

void gs_delete(GoodSpeak *g) {
  if (g) {
    free(g->oldspeak);
    free(g->newspeak);
  }
  free(g);
}

char *gs_oldspeak(GoodSpeak *g) {
  if (g) {
    return g->oldspeak;
  }
  return NULL;
}

char *gs_newspeak(GoodSpeak *g) {
  if (g) {
    return g->newspeak;
  }
  return NULL;
}
