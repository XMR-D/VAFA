#ifndef VIGENERE_H
#define VIGENERE_H

void Vigenere2_0(char plaintext[], char key[]);

void extend(int size, char key[], char returned[]);

sfText * SetText(char str[], int x, int y, sfFont *f, sfColor col, int size);

char * c_to_s(char c);


#endif
