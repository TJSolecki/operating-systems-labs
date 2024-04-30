## Step 1

When the program is run, it starts by creating 10 threads and executing each concurrently. Each thread reaches a print
statement where they print the value of the loop iteration variable i in the main function (0-9) that they were created
on. Then the program slows down as each thread reaches its critical section. Due to the use of a sempahore here, each
thread needs to take turns in this critical section. I noticed that the order that each thread enters the critical
section is exactly the same order in which the threads were started. So in the case first 3 threads to start executing
were threads 0, 4, and 3, I observed that those threads entered the ciritcal section in the same order as well
consistantly upon mutiple exeuctions. Though, the ordering of which the threads were created intialy changed per
execution.
