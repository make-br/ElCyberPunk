
int small_delay = 10;

int medium_delay = 200;
int xmedium_delay = 300;
int large_delay = 800;
int xlarge_delay = 3000;
int epic_delay = 5000;
//int program_delay = 100;
 int program_delay = 4000;

// tops are even
// bottoms are odd
int blue_top = 2;
int blue_bottom = 3;
int green_top = 4;
int green_bottom = 5;
int red_top = 6;
int red_bottom = 7;
int pink_top = 8;
int pink_bottom = 9;

int blue[] = {blue_top, blue_bottom};
int green[] = {green_top, green_bottom};
int red[] = {red_top, red_bottom};
int pink[] = {pink_top, pink_bottom};

int right[] = {red_top, blue_top,  red_bottom, blue_bottom};
int left[] = {green_top, pink_top, green_bottom, pink_bottom};

int top_colors[] = {red_top, blue_top, green_top, pink_top};
int bottom_colors[] = {red_bottom, blue_bottom, green_bottom, pink_bottom};
int all[] = {red_top, blue_top, green_top, pink_top,red_bottom, blue_bottom, green_bottom, pink_bottom};
// define a type function pointer that accepts a param
typedef void (* Strand_op)(int);
typedef void (* Program_op)(void);


void setup() {                
  // The EL channels are on pins 2 through 9
  // Initialize the pins as outputs
  pinMode(2, OUTPUT);  // channel A  
  pinMode(3, OUTPUT);  // channel B   
  pinMode(4, OUTPUT);  // channel C
  pinMode(5, OUTPUT);  // channel D    
  pinMode(6, OUTPUT);  // channel E
  pinMode(7, OUTPUT);  // channel F
  pinMode(8, OUTPUT);  // channel G
  pinMode(9, OUTPUT);  // channel H
  // We also have two status LEDs, pin 10 on the Escudo, 
  // and pin 13 on the Arduino itself
  pinMode(10, OUTPUT);     
  pinMode(13, OUTPUT);    
}



void loop_strands(void (*do_this)(int))
{
  int x;
   for (x=2; x<=9; x++)
  {
   do_this(x);
  }
}

void all_off()
{

  loop_strands(off);
}

void toggle_delay(int strand, int time)
{
  toggle(strand);
  safe_delay(time);
}

void blink(int strand, int time)
{
  on(strand);
  safe_delay(time);
  off(strand);
}

void blink_group(int strands[], int count, int time, int loops)
{
  int i, j;
  for (j=0; j<loops; j++)
  {
    for (i=0; i<count; i++)
    {
       on(strands[i]);
    }
    safe_delay(time);
     for (i=0; i<count; i++)
    {
       off(strands[i]);
    }
    safe_delay(time);
  }
}


void toggle(int strand)
{
  int state;
  state = digitalRead(strand);  
  digitalWrite(strand, !state);

}

void toggle_group(int strands[], int count)
{
  int i;
    for (i=0; i<count; i++)
    {
      toggle(strands[i]);
    }
}

/** set helpers */
void toggle_red()
{
  toggle_color_pair(red_top);
}
void toggle_pink()
{
  toggle_color_pair(pink_top);
}
void toggle_blue()
{
  toggle_color_pair(blue_top);
}
void toggle_green()
{
  toggle_color_pair(green_top);
}


void toggle_color_pair(int top_strand)
{
  toggle(top_strand);
  toggle(sibling(top_strand));
}


void on(int strand)
{
  digitalWrite(strand, HIGH);
}

void off(int strand)
{
  digitalWrite(strand, LOW);
}
// given the strand find the other strand of the same color;
// if it's odd subtract one, even, add one
int sibling(int strand)
{
  // start with a safe value
  int target = 2;
  if (strand % 2 == 0) 
  {
    target = strand + 1;
  }
  else 
  {
    target = strand - 1;
  }
 return target; 
}

void blink_vertical(int loops)
{
   blink_group(top_colors, 4, medium_delay, loops);
   blink_group(bottom_colors, 4, medium_delay, loops);
  
}

void blink_horizontal(int loops)
{
   blink_group(left, 4, medium_delay, loops);
   blink_group(right, 4, medium_delay, loops);
  
}


int random_strand()
{
  return random(blue_top, pink_bottom + 1);
}

// modified delay so we don't care about negatives
void safe_delay(int ms)
{
  if (ms < 0 )
  {    
    ms = 0;
  }
 delay (ms);
}

void alpha() 
{
   
  on(green_top);
  delay(medium_delay);
  on(green_bottom);
  delay(medium_delay);
  on(red_top);
  delay(medium_delay);
  on(red_bottom);
  // stage two
  delay(xmedium_delay);
  off(green_top);
  on(pink_top);
  delay(medium_delay);  
  on(pink_bottom);
  off(green_bottom);
  delay(medium_delay);  
  off(red_top);
  on(blue_top);
  delay(medium_delay);
  off(red_bottom);
  on(blue_bottom);
  delay(xmedium_delay);
  all_off();
}
void beta() 
{

  on(green_top);
  on(red_top);
  delay(medium_delay);
  on(green_bottom);
  on(red_bottom);

  // stage two
  delay(xmedium_delay);
  off(green_top);
  off(red_top);
  on(pink_top);
  on(blue_top);
  delay(medium_delay);  
  on(pink_bottom);
  off(green_bottom);
  off(red_bottom);
  on(blue_bottom);
  delay(xmedium_delay);
  all_off();
}

void delta() 
{
  toggle_red();
  toggle_green();
  delay(medium_delay);
  toggle_blue();
  toggle_pink();
  delay(medium_delay);
  toggle_blue();
  toggle_pink();
  delay(medium_delay);
  toggle_red();
  toggle_green();
  delay(medium_delay);
}

void gamma ()
{

  blink(blue_top, medium_delay);
  blink(green_top, medium_delay);
  blink(red_top, medium_delay);
  blink(pink_top, medium_delay);
  blink(blue_bottom, medium_delay);
  blink(green_bottom, medium_delay);
  blink(red_bottom, medium_delay);
  blink(pink_bottom, medium_delay);
}

void epsilon()
{
 blink(random_strand(), 50);
}

void iota()
{
 toggle_delay(random_strand(), 50);
}

void rho()
{
  int  group_blink_loops = 1;
  int  single_blink_loops = 4;
  
 blink_group(red, 2, medium_delay, single_blink_loops); 
 blink_vertical(group_blink_loops);
 blink_group(blue, 2, medium_delay, single_blink_loops);
 blink_vertical(group_blink_loops);
 blink_group(pink, 2, medium_delay, single_blink_loops); 
 blink_vertical(group_blink_loops);
 blink_group(green, 2, medium_delay, single_blink_loops); 
 blink_vertical(group_blink_loops);


}
void sigma()
{
  
  int  group_blink_loops = 1;
  blink_vertical(group_blink_loops);
  blink_horizontal(group_blink_loops);
}

void psy()
{
   int  single_blink_loops = 4;
   int group_delay = 200;
   int times = 4;
   int decay = 40;
   int x;
   for (x=0; x<=times; x++)
  {
    blink_group(green, 2, group_delay, single_blink_loops); 
    blink_group(red, 2, group_delay, single_blink_loops); 
    blink_group(pink, 2, group_delay, single_blink_loops); 
    blink_group(blue, 2, group_delay, single_blink_loops); 
    group_delay -= decay;
  }
  toggle_group(all, 8);


}

void omega() 
{
 toggle_group(red, 2);
 delay(150);
 toggle_group(blue, 2);
 delay(150);
 toggle_group(green, 2);
 delay(150);
 toggle_group(pink, 2);
 delay(150);
 toggle_group(pink, 2);
 delay(150);
 toggle_group(green, 2);
 delay(150);
 toggle_group(blue, 2);
 delay(150);
 toggle_group(red, 2);
 delay(150);

}

void pi()
{
  toggle_group(red, 2);
 delay(150);
 toggle_group(blue, 2);
 delay(150);
 toggle_group(green, 2);
 delay(150);
 toggle_group(pink, 2);
 delay(150);
 toggle_group(red, 2);
 delay(150);
 toggle_group(blue, 2);
 delay(150);
 toggle_group(green, 2);
 delay(150);
 toggle_group(pink, 2);
 delay(150);
  
}

void loop_program(int times, void (*program)(void))
{
  all_off();
  int i;
  for (i=0; i < times; i++)
  {
    program();
  }
  delay(program_delay);
}

void loop() 
{
  int steps = 5;
  

 loop_program(steps, alpha);
 loop_program(100  , iota);
 loop_program(steps, beta);
 loop_program(steps, rho);
 loop_program(steps, gamma);
 loop_program(steps, pi);
 loop_program(1, psy);
 loop_program(steps, delta);
 loop_program(100  , epsilon);
 loop_program(steps, gamma);
 loop_program(steps, rho);
 loop_program(steps, sigma);
 loop_program(1, psy);
 loop_program(100  , epsilon);
 loop_program(steps, omega); 

}
