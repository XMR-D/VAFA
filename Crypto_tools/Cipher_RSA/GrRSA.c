#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>

#define FILEP "./Crypto_tools/Cipher_RSA/primes.txt"

char buffer[1024];
const int MAX_DIGITS = 50;
int i,j = 0;

struct public_key_class{
  long long modulus;
  long long exponent;
};

struct private_key_class{
  long long modulus;
  long long exponent;
};


// This should totally be in the math library.
long long gcd(long long a, long long b)
{
  long long c;
  while ( a != 0 ) {
    c = a; a = b%a;  b = c;
  }
  return b;
}


long long ExtEuclid(long long a, long long b)
{
 long long x = 0, y = 1, u = 1, v = 0, gcd = b, m, n, q, r;
 while (a!=0) {
   q = gcd/a; r = gcd % a;
   m = x-u*q; n = y-v*q;
   gcd = a; a = r; x = u; y = v; u = m; v = n;
   }
   return y;
}
static inline long long modmult(long long a,long long b,long long mod)
{
   // this is necessary since we will be dividing by a
   if (a == 0 ){
         return 0;
   }
   register long long product = a * b;
    //if multiplication does not overflow, we can use it
   if (product / a == b){
          return product % mod;
   }
   // if a % 2 == 1 i. e. a >> 1 is not a / 2
   if ( a & 1 ) {
         product = modmult((a>>1), b, mod);
         if ((product << 1) > product ){
         return ((( product << 1 ) % mod ) + b) % mod;
      }
   }
   //implicit else
   product = modmult((a >> 1), b, mod);
   if ((product << 1) > product){
         return (product << 1) % mod ;
         }
   //implicit else: this is about 10x slower than the code above, but it will not overflow
    long long sum;
    sum = 0;
    while(b>0)
    {
        if(b&1)
            sum = (sum + a) % mod;
        a = (2*a) % mod;
        b>>=1;
    }
    return sum;
}
long long rsa_modExp(long long b, long long e, long long m)
{
      long long product;
      product = 1;
      if (b < 0 || e < 0 || m <= 0){
            return -1;
      }
      b = b % m;
      while ( e > 0){
            if (e & 1){
                  product = modmult(product, b, m);
            }
            b = modmult(b, b, m);
            e >>= 1;
      }
      return product;
}
// Calling this function will generate a public and private key and store them in the pointers
// it is given.
void rsa_gen_keys(struct public_key_class *pub, struct private_key_class *priv, char *PRIME_SOURCE_FILE)
{
  FILE * primes_list;
  if(!(primes_list = fopen(PRIME_SOURCE_FILE, "r"))){
    fprintf(stderr, "Problem reading %s\n", PRIME_SOURCE_FILE);
    exit(1);
  }

  // count number of primes in the list
  long long prime_count = 0;
  do{
    int bytes_read = fread(buffer,1,sizeof(buffer)-1, primes_list);
    buffer[bytes_read] = '\0';
    for (i=0 ; buffer[i]; i++){
      if (buffer[i] == '\n'){
	prime_count++;
      }
    }
  }
  while(feof(primes_list) == 0);


  // choose random primes from the list, store them as p,q

  long long p = 0;
  long long q = 0;

//values of e should be sufficiently large to protect against naive attacks
  long long e = (2 << 16) +1;
  long long d = 0;
  char prime_buffer[MAX_DIGITS];
  long long max = 0;
  long long phi_max = 0;

  srand(time(NULL));

  do{
    // a and b are the positions of p and q in the list
    int a =  (double)rand() * (prime_count+1) / (RAND_MAX+1.0);
    int b =  (double)rand() * (prime_count+1) / (RAND_MAX+1.0);

    // here we find the prime at position a, store it as p
    rewind(primes_list);
    for(i=0; i < a + 1; i++)
    {
    //  for(j=0; j < MAX_DIGITS; j++){
    //	prime_buffer[j] = 0;
    //  }
      if(fgets(prime_buffer,sizeof(prime_buffer)-1, primes_list)==NULL)
          exit(0);
    }
    p = atol(prime_buffer);

    // here we find the prime at position b, store it as q
    rewind(primes_list);
    for(i=0; i < b + 1; i++)
    {
      for(j=0; j < MAX_DIGITS; j++)
      {
	        prime_buffer[j] = 0;
      }
      if(fgets(prime_buffer,sizeof(prime_buffer)-1, primes_list) == NULL)
          exit(0);
    }
    q = atol(prime_buffer);

    max = p*q;
    phi_max = (p-1)*(q-1);
  }
  while(!(p && q) || (p == q) || (gcd(phi_max, e) != 1));

  // Next, we need to choose a,b, so that a*max+b*e = gcd(max,e). We actually only need b
  // here, and in keeping with the usual notation of RSA we'll call it d. We'd also like
  // to make sure we get a representation of d as positive, hence the while loop.
  d = ExtEuclid(phi_max,e);
  while(d < 0){
    d = d+phi_max;
  }

  //printf("primes are %lld and %lld\n",(long long)p, (long long )q);
  // We now store the public / private keys in the appropriate structs
  pub->modulus = max;
  pub->exponent = e;

  priv->modulus = max;
  priv->exponent = d;
}


long long *rsa_encrypt(const char *message, const unsigned long message_size,
                     const struct public_key_class *pub)
{
  long long *encrypted = malloc(sizeof(long long)*message_size);
  memset(encrypted, '\0', message_size);
  if(encrypted == NULL){
    fprintf(stderr,
     "Error: Heap allocation failed.\n");
    return NULL;
  }
  long long i = 0;
  for(i=0; i < message_size; i++){
    if ((encrypted[i] = rsa_modExp(message[i], pub->exponent, pub->modulus)) == -1)
    return NULL;
  }
  return encrypted;
}

int llarrlen(long long * n)
{
    int i = 0;
    while(n[i] != '\0')
        i++;
    return i;
}

//CHANGELOG : CHANGE THE POSITION OF THE SETTING AND DRAW THEM; ADD THE RSA.BMP FILE

char * rev(char * src)
{
    char * dest = malloc(sizeof(char)*20);
    char tmp = 'a';
    int j = strlen(src)-1;
    for(int i = 0; i <= strlen(src); i++)
    {
        tmp = src[j];
        dest[i] = tmp;
        j--;
    }
    return dest;
}

char * lltostring(long long n)
{
    char * array = malloc(sizeof(char) * 10);
    memset(array, '\0', 10);
    char c = 'a';
    int i = 0;
    while(n > 0)
    {
        c = 48+(n%10);
        n/=10;
        array[i] = c;
        i++;
    }
    // ADD STRREV
    array = rev(array);
    return array;
}


void GrRSA(char * message) //working, now to adapt to CSFML.
{
  //key gen 
  struct public_key_class pub[1];
  struct private_key_class priv[1];
  rsa_gen_keys(pub, priv, FILEP);

  char * pub_exponent = lltostring((long long) pub->exponent);
  pub_exponent[strlen(pub_exponent)-1] = '\0';

  char * pub_modulo = malloc(sizeof(char) * 20);
  pub_modulo = lltostring((long long) pub->modulus);

  //getting chars
  
  char  u1 = message[0];
  char  u2 = message[1];
  char  u3 = message[2];
  char  u4 = message[3];
  char  u5 = message[4];
  char  un1 = message[strlen(message)-2];
  char  un = message[strlen(message)-1];


  //encrypt

  long long *encrypted = malloc(sizeof(char)*strlen(message));
  memset(encrypted, 0, strlen(message));
  encrypted = rsa_encrypt(message, sizeof(message), pub);

  char * cyph1 = lltostring(encrypted[0]);
  char * cyph2 = lltostring(encrypted[1]);
  char * cyph3 = lltostring(encrypted[2]);
  char * cyph4 = lltostring(encrypted[3]);
  char * cyph5 = lltostring(encrypted[4]);
  char * cyph_n_1 = lltostring(encrypted[llarrlen(encrypted)-2]);
  char * cyph_n = lltostring(encrypted[llarrlen(encrypted)-1]);

  char * cypher = malloc(sizeof(char)*55);
  memset(cypher, 0, 55);

  strcat(cypher, cyph1);
  strcat(cypher, cyph2);
  strcat(cypher, cyph3);
  strcat(cypher, "...");

  sfRenderWindow *window;
  sfVideoMode video_mode = {1401, 800, 32};
  sfEvent event;
  sfTexture * empty = sfTexture_createFromFile("./Ui_tools/CRY_RSA/RSA.bmp", NULL);


  sfSprite *img = sfSprite_create();
  sfFont * f;
  f = sfFont_createFromFile("./Ui_tools/Generals/ayar.ttf");


  //Setting strings
  //set uncipher

  sfText * uncipher = SetText(message, 62, 104, f, sfBlue, 30);

  //set uncipher chars

  sfText * u_1 = SetText(c_to_s(u1), 157, 202, f, sfBlue, 30); 
  sfText * u_2 = SetText(c_to_s(u2), 157, 246, f, sfBlue, 30);
  sfText * u_3 = SetText(c_to_s(u3), 157, 296, f, sfBlue, 30);
  sfText * u_4 = SetText(c_to_s(u4), 157, 346, f, sfBlue, 30);
  sfText * u_5 = SetText(c_to_s(u5), 157, 395, f, sfBlue, 30);
  sfText * u_n_1 = SetText(c_to_s(un1), 157, 586, f, sfBlue, 30);
  sfText * u_n = SetText(c_to_s(un), 157, 636, f, sfBlue, 30);

  //set ciphers

  sfText * c_1 = SetText(cyph1, 822, 221, f, sfRed, 30); 
  sfText * c_2 = SetText(cyph2, 822, 265, f, sfRed, 30);
  sfText * c_3 = SetText(cyph3, 822, 315, f, sfRed, 30);
  sfText * c_4 = SetText(cyph4, 822, 365, f, sfRed, 30);
  sfText * c_5 = SetText(cyph5, 822, 413, f, sfRed, 30);
  sfText * c_n_1 = SetText(cyph_n_1, 822, 605, f, sfRed, 30);
  sfText * c_n = SetText(cyph_n, 822, 655, f, sfRed, 30);

  //set public key
  
  sfText * pub_expo = SetText(pub_exponent, 836, 80, f, sfBlack, 30);
  sfText * pub_mod = SetText(pub_modulo, 836, 127, f, sfBlack, 30);

  //set cipher
  
  sfText * cyph = SetText(cypher, 85, 730, f, sfRed, 30);


  window = sfRenderWindow_create(video_mode, "Chiffrement RSA",
          sfClose | sfResize, NULL);

  sfSprite_setTexture(img, empty, sfFalse);

  while(sfRenderWindow_isOpen(window))
  {
      sfRenderWindow_display(window);
      sfRenderWindow_drawSprite(window, img, NULL);

      //draw uncipher

      sfRenderWindow_drawText(window, uncipher, NULL);
      sfRenderWindow_drawText(window, cyph, NULL);

      //draw uncipher chars

      sfRenderWindow_drawText(window, u_1, NULL);
      sfRenderWindow_drawText(window, u_2, NULL);
      sfRenderWindow_drawText(window, u_3, NULL);
      sfRenderWindow_drawText(window, u_4, NULL);
      sfRenderWindow_drawText(window, u_5, NULL);
      sfRenderWindow_drawText(window, u_n_1, NULL);
      sfRenderWindow_drawText(window, u_n, NULL);

      //draww ciphers chars

      sfRenderWindow_drawText(window, c_1, NULL);
      sfRenderWindow_drawText(window, c_2, NULL);
      sfRenderWindow_drawText(window, c_3, NULL);
      sfRenderWindow_drawText(window, c_4, NULL);
      sfRenderWindow_drawText(window, c_5, NULL);
      sfRenderWindow_drawText(window, c_n_1, NULL);
      sfRenderWindow_drawText(window, c_n, NULL);

      //draw public key couple

      sfRenderWindow_drawText(window, pub_expo, NULL);
      sfRenderWindow_drawText(window, pub_mod, NULL);

      while(sfRenderWindow_pollEvent(window, &event))
      {
          if(event.type == sfEvtClosed)
              sfRenderWindow_close(window);
      }
  }


  printf("\n");
  free(encrypted);

}
