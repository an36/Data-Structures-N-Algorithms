
	Creating 4 threads.
	
	Author: Abdullah Almarzouq      (an36@pdx.edu)
   
	Name: thread.exe or thread.out
	Description:  The program creates four threads and each thread created
		      uses the function 'thread_id' to print its own id.
		      The thread ID 'tid' gets passed to the function 'thread_id'
		      then the function prints the thread ID with the a printf instruction.
		      Once all four threads has been created and executed, the program exits
		      in main().

	Ex:
	->./thread
	->Thread ID: 140724437964176
	  Thread ID: 140724437964184
	  Thread ID: 140724437964192
	  Thread ID: 140724437964200
	
	Note: the program has no parameters. Therefore, any parameters typed after './thread' will be ignored.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	ECE362 | H.W.5 | Problem.2) Multi-threading.
	Author: Abdullah Almarzouq      (an36@pdx.edu)

	Name: mthread.exe or mthread.out
   	Description:    The program below creates a number of threads, specified by user,
			and each threads created uses the function 'thread_id' to print its own id
			and the subtotal of the summation process that the thread has computed.
			The array of values 'ary[64000]' has randomly generated values with a seed
			that should be specified by the user.  This array's values are used to for the summation
			process while each. The values inside that array are divided upon the created threads
			so that each thread can compute the subtotal of those values, then the Total is 
			computed by adding those subtotals.

	@param -t      the number of threads (1, 2, 4 or 8)
	@param -s      the value of the seed to be used in srand

	Ex:
	-> ./mthread -t 4 -s 40
	-> Expected results: 68534350915551

	   Thread ID: 140736822685824
	   Thread subtotal: 17286855369867

	   Thread ID: 140736822685832
	   Thread subtotal: 17080367199396

	   Thread ID: 140736822685840
	   Thread subtotal: 17061718031399

	   Thread ID: 140736822685848
	   Thread subtotal: 17105410314889


	   Threads Total: 68534350915551

	
	As seen from the example, the program prints the subtotal of each thread and the thread's ID. Also note that 
	the parameters must be entered by the user, otherwise, the program will prints an error message as the parameters
	must be specified.  Another note, the number of threads (-t) must be either 1, 2, 4 or 8.  Also, the order of 
	parameters doesn't matter, both (-t # -s #) and (-s # -t #) works fine.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Makefile
	
	The Makefile has two phony targets (all and clean). 'make all' compiles both program mentioned above, while 'make clean'
	removes the executable and object file created by 'make all'.





