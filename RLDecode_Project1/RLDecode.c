#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * Title:
 * Programming Assignment 0 Decoding RLE Strings
 *
 * Due:
 * September 4, 2025
 *
 * Creator:
 * Ariel Sosa, 50400671
 *
 * Sources:
 * The additional code provided in this file is created by me and me alone,
 * I used my knowledge in c and resources provided to me by this course.
 * This includes, the textbook "The C Programming Language" by Brian K.,
 * lab notes and handouts, lecture notes and slides provided in class,
 * and additional information provided by the handout and the git repository
 * for this assignment. - Ariel Sosa
 **/


/*
 * The isnumber() function examines the character given as its first
 * argument and returns true if and only if the character represents
 * an number.  This helper function should be relatively short.
 *
 * Returns true if the given character represents an number, false
 * otherwise.
 */
bool isnumber(char c);

/*
 * The decode() function takes a run-length encoded string as its
 * argument, parses every integer n preceding every character in
 * the string, and prints each character n times.  For example, if
 * the string passed to decode() is "1a3b", decode() will print
 * "abbb".  It returns an integer that represents the summed value
 * of the amount of characters printed; in this example, decode()
 * would return the integer 4.
 *
 * This function must also handle malformed run-length encoded strings.
 * A malformed string is any string which does not adhere to the RLE
 * implementation described in the handout. If a malformed string is
 * encountered, it should cease printing the decoded string, print an
 * error message, and return -1.
 *
 * Returns the integer value of the total amount of characters printed,
 * or -1 if the run-length encoded string is malformed.
 */
int decode(char *str);

/*
 * The numConverter() function is a helper function that takes a string
 * as its paramter. The main purpose of this function is to convert numbers
 * as a string into an integer. It does this by a series of multiplication
 * and addition to get the proper value of the string number as an integer. 
 *
 * Returns the converted string as an integer 
 */ 
int numConverter(char *str);

/*
 * The main function is where C programs begin.
 *
 * This function parses its arguments and returns the value they
 * represent.  In this assignment, the only valid argument is a
 * run-length encoded string.  Any extra arguments in excess of
 * this single valid argument make the invocation of your program
 * invalid.
 *
 * Remember that the argument in argv[0] is the name of the program, so
 * a program passed exactly one argument on the command line will
 * receive _two_ arguments: its name in argv[0] and the provided
 * argument in argv[1].
 *
 * Arguments:
 * argc - The number of arguments received
 * argv - The arguments received as an array of C strings
 *
 * Returns 0 if the argument is well-formed and the string could
 * be decoded, non-zero otherwise.
 */
int main(int argc, char *argv[]) {
    /* Your main program logic should go here, with helper logic in the
     * functions isnumber() and decode(), which you can place below
     * the closing brace of main() */

  if(argc != 2){
    fprintf(stderr, "Error: Invalid Arguments\n");
    return -1;
  }

  int returnVal = decode(argv[1]);
  if(returnVal == -1){
    return -1;
  }
  
  return 0;
}

/* You should implement isnumber() and decode() here */

/**
 * isnumber() Function:
 *
 * Since we are not able to use any parse int functions, I decided to
 * check if the character is a number by using the ascii library. In the
 * library 57 - 48 represent numbers 0-9, and that is why I use an if statement
 * checking if char c is between 57 - 48 in the library, indicating a number.
 **/
bool isnumber(char c){
  if(c <= 57 && c >= 48)
    return true;
  return false;
}

/**
 * decode() Funtion:
 *
 * numbers[] string: is meant to hold the parsed numbers from the provided string, then
 * this string is used with my helper function numConverter to properly get the letterCt.
 *
 * lettFlag Var: is meant to be used as a flag in order to check for ' Malformed String'.
 * It does this by keeping count of letters being used in the string and resets when a
 * number is encountered.
 *
 * letterCt Var: Is meant to hold the number given before a letter, it is used in the inner
 * for loop to print out the amount of times the procedding letter should be printed.
 *
 * outputLength Var: Is meant to hold the count of the final string printed out. This variable is
 * returned after the provided string was decoded.
 *
 * wIndex Var: Is meant to hold the index of numbers when iterating through str.
 *
 * As a note, I implemented many checks for "Malformed String", I made sure to check for
 * "All Numbers", "Two Letters back to back", and "No starting number or starting zero"
 **/
int  decode(char *str){

  int lettFlag= 0;
  int letterCt = 0;
  int outputLength = 0;
  char numbers[] = "oooooooooo";
  int wIndex;
 
  if(isnumber(str[0]) == false || str[0] == 48){
    fprintf(stderr, "Error: Malformed String\n");
    return -1;
  }

  for(int i = 0; i < strlen(str); ++i){
    if(isnumber(str[i])){
      lettFlag = 0;
      if(isnumber(str[i+1])){
	wIndex = 0;
	while(isnumber(str[i])){ // Parsing Numbers in str
	  numbers[wIndex] = str[i];
	  ++wIndex;
	  ++i;
	}
	letterCt = numConverter(numbers);
	--i;
      }else{
	letterCt = str[i] - '0';
      }
    }else{
      lettFlag += 1;
      if(lettFlag == 2){
	fprintf(stderr, "Error: Malformed String\n");
	return -1;
      }

      for(int j = 0; j < letterCt; j++){
	putchar(str[i]);
	outputLength += 1;
      }
    }
  }
  if(lettFlag == 0){
    fprintf(stderr, "Error: Malformed String\n");
    return -1;
  }
  putchar(10); // Newline placed after display
  return outputLength;
}

/**
 * numConverter() Funtion:
 *
 * This function can only do numbers up to the one billions, as mentioned in the handout,
 * "An integer in our RLE encoding can range from 1 to 2147483647 (that is, 1 to 2^31 −1)".
 * So in order to account for that I decided to use a series of if-else statements to be able
 * to multiply and add numbers up to 9,999,999,999.
 * 
 * numOutput Var: is meant to be used as the final integer to be returned at the end of this
 * function. It will hold the final converted integer.
 *
 * size Var: is meant to hold the size of the given number string, in the for loop, as you will
 * see, size is decremented, as the purpose of this variable is to represent each integers
 * 10s placement. This is important to be able to properly convert the number string to an int.
 *
 * curr Var: is meant to represent the decimal value of c[i], as c[i] would originally be in
 * Ascii form at first. This variable will hold the current number in the string.
 *
 **/
int numConverter(char *c){
  
  int numOutput = 0;
  int size = 0;
  int curr = 0;

  for(int a = 0; a < strlen(c); ++a){
    if(isnumber(c[a])){
      size++;
    }
  }
  
  for(int i = 0; c[i] != 'o'; ++i){
    curr = c[i] - '0'; // Sourced from handout to find true int value of c[i]
    
    if(size == 10){
      numOutput += curr * 1000000000; // One Billions
      c[i] = 'o';
    }else if(size == 9){
      numOutput += curr * 100000000; // Hundred Millions
      c[i] = 'o';
    }else if(size == 8){
      numOutput += curr * 10000000; // Ten Millions
      c[i] = 'o';
    }else if(size == 7){
      numOutput += curr * 1000000; // One Millions
      c[i] = 'o';
    }else if(size == 6){
      numOutput += curr * 100000; // Hundred Thousands
      c[i] = 'o';
    }else if(size == 5){
      numOutput += curr * 10000; // Ten Thousands
      c[i] = 'o';
    }else if(size == 4){
      numOutput += curr * 1000; // One Thousands
      c[i] = 'o';
    }else if(size == 3){
      numOutput += curr * 100; // Hundreds
      c[i] = 'o';
    }else if(size == 2){
      numOutput += curr * 10; // Tens
      c[i] = 'o';
    }else if(size == 1){
      numOutput += curr * 1; // Ones
      c[i] = 'o';
    }

    --size;
  }

  return numOutput;
}
