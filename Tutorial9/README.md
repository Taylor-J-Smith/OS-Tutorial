#Tutorial 7 - Wed Nov 4

##Application Questions

1. DONE
2. DONE
3. DONE
4. DONE
5. <OPEN>


##Conceptual Questions
**1. Explain what OpenMP is, what are it’s benefits?**

OpenMp is an api that simplifies thread creation, data sharing, synchronization, and other parallelism routines and directives.

**2. What are the #pragma ​definitions, what do they do?**

pragma definitions provide the compilier with additional information from another source, such as an api, outside of the C language. The meaning of each part of a pragma defintion is defined in the outside source. 

pragmas:
omp : This pragma indicates to the compilier that we are going to be using the openmp api. The following directives in the pragma will be definied in OpenMP

parallel: This indicates that the section of code will be executed by multiple threads

critical: This indicates that the following section will be a critical section, and this section should only be accessed by one thread at a time.

for: This indicates that the following line will contain a for loop, and OpenMP will then use the program's threads to optimize the execution of the for loop.

private: This declaration will make a variable that is private to each thread, and will not be shared amongst multiple threads

reduction: This creates a copy of the list variable per thread, and at the end of all the threads execution it performs the reduction operation on each copy of the list variables, effectively "merging" them into one single global variable.

**3. Write the OpenMP #pragma definition to execute a loop in parallel.**

\#pragma omp parallel for

**4. What does the reduction​do in the #pragma definition in OpenMP?**

This creates a copy of the list variable per thread, and at the end of all the threads execution it performs the reduction operation on each copy of the list variables, effectively "merging" them into one single global variable.

**5. Explain the critical ​and private()​declarations used in OpenMP.**

critical: This indicates that the following section will be a critical section, and this section should only be accessed by one thread at a time.
private: This declaration will make a variable that is private to each thread, and will not be shared amongst multiple threads
















