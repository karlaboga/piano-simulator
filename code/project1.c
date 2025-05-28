#include <16F874.h>
#include <string.h> 

#fuses NOWDT,HS, NOPUT, NOPROTECT, NODEBUG, NOLVP, NOCPD, NOWRT, BROWNOUT

#use delay(clock=20000000)
#define RS     PIN_E0
#define ENABLE PIN_E1


int8 caracter; // Variable used for transmiting characters to LCD
int8 instrucao; // Vriable used for transmiting instructions to LCD
int16 i;
char cuv[20];  // Variable used for notes (DO, RE...)

void activa()   // Enable LCD
{
  output_high(ENABLE);
  delay_ms(10);
  output_low(ENABLE);
}


void transfere_carac(int8 carac)  // Function for character to be sent to the data pins
{
  output_high(RS);
  output_d(carac);
  activa();
}


void transfere_inst(int8 inst)  // Function for instruction to be sent to the data pins
{
  output_low(RS);
  output_d(inst);
  activa();
}


void init_LCD()  // Function for LCD initialization 
{
   instrucao=56;  // Sets the LCD to operate in 8-bit mode with 2 lines.
   transfere_inst(instrucao);   
   instrucao=1;  // Clears the display and rests the cursor the initial position (top left)
   transfere_inst(instrucao);
   instrucao=12;  // Turns on the display without a visible cursor
   transfere_inst(instrucao);
   instrucao=2;   // Moves the cursor to the initial position without clearing the display              
   transfere_inst(instrucao);
}

void write_word(char word[])  // Display a word on the LCD, character by character
{
   for(i=0; i<strlen(word); i++)
      {
         caracter = word[i];
         transfere_carac(caracter);
      }
      delay_ms(250);
}


void nota(int note)  // Generates musical notes based on the input note parameter
{
  switch (note)  // To determine the corresponding note frequency
  {
    case 1: // Do
      output_high(PIN_B0);  // Set the buzzer pin high to generate sound
      delay_us(1953);       // Delay for half the period of the DO note (1953 microseconds)
      output_low(PIN_B0);   // Set the buzzer pin low
      delay_us(1953);       // Delay for the remaining half of the period
      break;

    case 2: // Re
      output_high(PIN_B0);  // Set the buzzer pin high
      delay_us(1709);       // Delay for half the period of the RE note
      output_low(PIN_B0);   // Set the buzzer pin low
      delay_us(1709);       // Delay for the remaining half of the period
      break;

    case 3: // Mi
      output_high(PIN_B0);  // Set the buzzer pin high
      delay_us(1519);       // Delay for half the period of the MI note
      output_low(PIN_B0);   // Set the buzzer pin low
      delay_us(1519);       // Delay for the remaining half of the period
      break;

    case 4: // Fa
      output_high(PIN_B0);  // Set the buzzer pin high
      delay_us(1367);       // Delay for half the period of the FA note
      output_low(PIN_B0);   // Set the buzzer pin low
      delay_us(1367);       // Delay for the remaining half of the period
      break;

    case 5: // Sol
      output_high(PIN_B0);  // Set the buzzer pin high
      delay_us(1243);       // Delay for half the period of the SOL note
      output_low(PIN_B0);   // Set the buzzer pin low
      delay_us(1243);       // Delay for the remaining half of the period
      break;

    case 6: // La
      output_high(PIN_B0);  // Set the buzzer pin high
      delay_us(1139);       // Delay for half the period of the LA note
      output_low(PIN_B0);   // Set the buzzer pin low
      delay_us(1139);       // Delay for the remaining half of the period
      break;

    case 7: // Si
      output_high(PIN_B0);  // Set the buzzer pin high
      delay_us(1052);       // Delay for half the period of the SI note
      output_low(PIN_B0);   // Set the buzzer pin low
      delay_us(1052);       // Delay for the remaining half of the period
      break;

    case 8: // Do2
      output_high(PIN_B0);  // Set the buzzer pin high
      delay_us(947);        // Delay for half the period of the DO2 note
      output_low(PIN_B0);   // Set the buzzer pin low
      delay_us(947);        // Delay for the remaining half of the period
      break;

    case 9: // La#
      output_high(PIN_B0);  // Set the buzzer pin high
      delay_us(1064);       // Delay for half the period of the LA# note
      output_low(PIN_B0);   // Set the buzzer pin low
      delay_us(1064);       // Delay for the remaining half of the period
      break;

    default:  // Handle invalid input
      // Invalid note - No action taken
      break;
  }
}

void Manual()
{
  if(input(PIN_C0))  // Check if the button connected to PIN_C0 is pressed
  { 
    cuv = " DO";        // Set the note name to "DO"
    write_word(cuv);    // Display "DO" on the LCD
  }
  while (input(PIN_C0)) // While the button is pressed
  {
    nota(1);            // Play the "DO" note
  }

  if(input(PIN_C1))     // Check if the button connected to PIN_C1 is pressed
  { 
    cuv = " RE";        // Set the note name to "RE"
    write_word(cuv);    // Display "RE" on the LCD
  }
  while (input(PIN_C1)) 
  {
    nota(2);            // Play the "RE" note
  }

  // Repeat the same logic for other buttons and notes
  if(input(PIN_C2)) 
  { 
    cuv = " MI";
    write_word(cuv);
  }
  while(input(PIN_C2)) 
  {
    nota(3);            // Play the "MI" note
  }

  if(input(PIN_C3))
  { 
    cuv = " FA";
    write_word(cuv);
  }
  while(input(PIN_C3)) 
  {
    nota(4);            // Play the "FA" note
  }

  if(input(PIN_C4)) 
  { 
    cuv = " SOL";
    write_word(cuv);
  }
  while(input(PIN_C4)) 
  {
    nota(5);            // Play the "SOL" note
  }

  if(input(PIN_C5)) 
  { 
    cuv = " LA";
    write_word(cuv);
  }
  while(input(PIN_C5)) 
  {
    nota(6);            // Play the "LA" note
  }

  if(input(PIN_B6)) 
  { 
    cuv = " SI";
    write_word(cuv);
  }
  while(input(PIN_B6)) 
  {
    nota(7);            // Play the "SI" note
  }
}

void HappyBirthday()
{
  for(i = 1; i <= 64; i++) // Repeat 64 times for the "DO" note (k=64) 
    nota(1); // Play "DO"
  delay_us(100000);  // Delay for rhythm

  for(i = 1; i <= 64; i++) 
    nota(1); // Play "DO" again
  delay_us(100000);

  for(i = 1; i <= 73*2; i++) // Repeat k times multiplied by 2 (tempos)
    nota(2); // Play "RE"
  delay_us(100000);

  for(i = 1; i <= 64; i++) 
    nota(1); // Play "DO"
  delay_us(100000);

  for(i = 1; i <= 91; i++) 
    nota(4); // Play "FA"
  delay_us(100000);

  for(i = 1; i <= 82*3; i++) 
    nota(3); // Play "MI"
  delay_us(100000);

  if(input(PIN_B7) == 0) // Check if the switch is turned off
    goto sss;            // Exit the melody if the switch is off

  // Repeat similar logic for the rest of the melody
  for(i = 1; i <= 64; i++) 
    nota(1); // Play "DO"
  delay_us(100000);

  for(i = 1; i <= 64; i++) 
    nota(1); // Play "DO"
  delay_us(100000);

  for(i = 1; i <= 132*2; i++) 
    nota(8); // Play "DO2"
  delay_us(100000);

  // Add additional repetitions for the "Happy Birthday" tune
  for(i = 1; i <= 110; i++) 
    nota(6); // Play "LA"
  delay_us(100000);

sss:
  delay_us(100000); // Exit point for stopping the melody
}
 
void main()
{
  set_tris_d(0x00);      // Set all PORTD pins as output
  init_LCD();            // Initialize the LCD

  char wordHB[20] = "Happy Birthday!!";
  char wordMM[20] = "Manual";
  char user[20] = "Choose SW1-HB";
  char user2[20] = "Or SW0-Manual";

  // Display the user prompt
  instrucao = 128;      
  transfere_inst(instrucao);  
  write_word(user);

  instrucao = 192;        
  transfere_inst(instrucao);
  write_word(user2);

  delay_ms(5000);         // Allow the user time to decide

  while(1)                
  {
    instrucao = 128;      
    transfere_inst(instrucao);  

    instrucao = 1;        
    transfere_inst(instrucao);  // Clear the LCD

    if(input(PIN_B7))     // Check the state of the switch
    {
      write_word(wordHB); // Display "Happy Birthday!!"
      HappyBirthday();    // Play the "Happy Birthday" melody
    }
    else
    {
      write_word(wordMM); // Display "Manual Mode"
      Manual();           // Enable manual note play
    }
  }
}
