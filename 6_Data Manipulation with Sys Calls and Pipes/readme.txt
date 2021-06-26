	ECE362 Assignment #2	(three programs: twist, xor and tx)
      	Author: Abdullah Almarzouq     (an36@pdx.edu)


- Twist:
      Description: This program takes an input from an input file (or stdin)
                   then it twists the content of that file (or stdin) according to
                   the number of characters to twist (b).  Finally the program
                   writes the twisted output back to an output file (or stdout).


      @argument -i   the name of the input file (default: stdin)
      @argument -o   the name of the output file (default: stdout)
      @argument -b   the number of characters to be twisted (default: 10)

	Ex: ./twist -b 2 -i inputFile -o outputFile           (let inputFile contain: "abcd")
	output> badc		(outputFile)

	*Notes:
		- The program can also work without input files and/or output files
		  as it can take input from stdin and redirect output to stdout.
		- The order of arguments doesn't matter, they can be written/called in any order.

=============================================================================================================================================================================================

- Xor:
      Description: This program takes an input from an input file (or stdin)
                   then it performs and XOR operation the string/content of that
                   file (or stdin) with a mask value that is specified by the user.
                   Finally the program writes the XORed output back to an output
                   file (or stdout).


      @argument -i           the name of the input file (default: stdin)
      @argument -o           the name of the output file (default: stdout)
      @argument <string>     the mask which must be provided (must be less than 10 characters)

	Ex: ./xor -i inputFile -o outputFile 12			(let inputFile contain: "abcd")
	output> PPRV		(outputFile)

	*Notes:
		- The program can also work without input files and/or output files
		  as it can take input from stdin and redirect output to stdout.
		- The order of arguments doesn't matter, they can be written/called in any order. However,
		  anything written after -i or -o will be always be treated as a file name.  If you do not
		  want to use an input/output file then do not use -i/-o .
		- The mask must be proveided, otherwise the program will print an error.
		- The program prints the XORed string as ASCII characters.  Therefore, be cautious as some
		  ASCII characters are not printable.
		- When XORing the same character (i.g. "a"^"a") the results will be 0 bytes which will act
		  as NULL.  When this NULL occurs it terminates the rest of the string. See the example below:

		  Ex: NULL terminates
		  >./xor "abcd"		(mask)
		  >"1b23"		(input)
		  >"P"			(output)
		
		  As it can be seen from the example, when input "b" XORed with mask "b" the result is 0 bytes
		  which is NULL.  When NULL is stored within the output buffer it terminates the rest of the
		  string that follows it.  Hence, only "P" was printed ("1" XORed with "a" is "P") and the res
		  got terminated.

=============================================================================================================================================================================================

- Tx:
      Description: This program creates two process (parent and child) by using fork().
                  The child process will execute the twist program and redirect the output (using pipes) to
                  the parent process which executes xor.  Xor takes its input from the redirected
                  output by twist.


      @argument -i         the name of the input file (default: stdin)
      @argument -o         the name of the output file (default: stdout)
      @argument -b         the number of characters to be twisted (default: 10)
      @argument <string>   the mask which must be provided (must be less than 10 characters)

	Ex: ./tx -i inputFile -o outputFile -b 2 "12"		(Let inputFile contain: abcd)
	output> SSUQ		(outputFile)

	*Notes:
		- The program can also work without input files and/or output files
		  as it can take input from stdin and redirect output to stdout.
		- The order of arguments doesn't matter, they can be written/called in any order. However,
		  anything written after -i or -o will be always be treated as a file name.  If you do not
		  want to use an input/output file then do not use -i/-o .
		- The mask must be proveided, otherwise the program will print an error.
		- The program prints the XORed string as ASCII characters.  Therefore, be cautious as some
		  ASCII characters are not printable.
		- When XORing the same character (i.g. "a"^"a") the results will be 0 bytes which will act
		  as NULL.  When this NULL occurs it terminates the rest of the string. Just as mentioned above
		  in the example of Xor.
