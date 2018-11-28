#ifndef _BTREE_H_
#define _BTREE_H_

void addIdxEntry_Btree(LIBRARY *, IDXENTRY );
int searchEntry_Btree(LIBRARY *, char []);
void printAllBooks_Btree(LIBRARY *);
void buildStartingLibrary_Btree(LIBRARY *);

#endif
