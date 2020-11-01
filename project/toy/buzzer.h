#ifndef buzzer_included
#define buzzer_included

#define a 4545
#define A 4290
#define c 3822
#define f 5726
#define g 5102
#define e 3033

static short cSong[242]={
  c,0,c,0,c,0,c,0,e,0,c,0,c,0,c,0,c,0,c,0,A,0,g,0,f,0,f,0,
  a,0,a,0,a,0,a,0,A,0,g,0,g,0,g,0,g,0,g,0,f,0,f,0,g,0,a,0,
  a,0,0,0,0,0,a,0,a,0,a,0,a,0,A,0,g,0,g,0,g,0,g,0,g,0,f,0,
  g,0,a,0,a,0,0,0,0,0,c,0,c,0,c,0,c,0,e,0,c,0,c,0,c,0,c,0,
  c,0,A,0,g,0,f,0,f,0,0,0,0,0,a,0,a,0,a,0,a,0,A,0,g,0,g,0,
  g,0,g,0,g,0,f,0,g,0,a,0,a,0,0,0,0,0,a,0,a,0,a,0,a,0,A,0,
  g,0,g,0,g,0,g,0,g,0,f,0,g,0,a,0,a,0,0,0,0,0,c,0,c,0,c,0,
  c,0,0,0,0,0,0,0,0,0,e,0,c,0,0,0,c,0,c,0,0,0,c,0,c,0,0,0,
  A,0,g,0,0,0,f,0,0,0,0,0,0,0,0,0,0,0
};
  
void buzzer_init();
void buzzer_set_period(short cycles);

#endif // included
