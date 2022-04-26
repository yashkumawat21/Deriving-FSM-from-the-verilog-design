# Deriving-FSM-from-the-verilog-design
Course Project B4:
 
The objective is Deriving Finite state machine (FSM) From Verilog descriptions in generalized manner.
We have implemented or code for 5 different verilog designs enclosed with the file.
We have used ifstream to read our verilog file .Please follow below snippet.
		ifstream file("file_name.v");



Working of code:
First of all we convert the whole code into a 2-D vector of string. In one vector of string we store the words which are in a single line.
Now  first of all we detect the case block in the formed 2-D vector.We also  ensure that this case block includes FSM as there are many case blocks present in code.
For example there are 2 case blocks in code .One for storing output after final state and second is FSM .So we find the variables in which output is stored ,so if we detect any of these variables in case block we won't run it.
Now ,as we know for each case ,we are detecting current state by colon ‘:’ if we find one in string.
Also I stored total states in a set of strings to identify when it appears in code.
I had made 3 functions in this code checkeq() ,forif(), checkcase().
checkcase() → This is the parent function which will check everyline of code between case -endcase and detects if/else/else-if condition and state changing and extracts FSM.
checkeq() will search for “=” sign in the code, used when the condition and the next state is defined in same line.(Refer to input 3 in report).
forif()-To detect condition in if/else/elseif loop.
I am storing each FSM condition in 2-D vector of string ,where each vector stored the state changing in a vector of stringand clearing it after every condition.
We print our 2-D vector in end.






Verilog design code format:

The input verilog code should not have any unnecessary indentation ,otherwise data in string would not be stored properly.The front is shown above for different cases.
The code should have proper spacing between each word for the  code to run.
We have taken the states from the parameter. So it must follow the following pattern with proper spacing.
		[parameter State0=value, State1=value, …….... ;


The outputs and FSM Design are shown in report and code and inputs are enclosed with the file.





Yash Kumawat (B19EE091)
Yogesh Nema (B19EE092)
—---------------------------------------------------------------------------------------------------------


