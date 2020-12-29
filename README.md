# S-DIAG

This algorithm was proposed by Chessa and Santi:
https://www.scopus.com/inward/record.uri?eid=2-s2.0-0035276556&doi=10.1109%2f3468.911368&partnerID=40&md5=1a5265f3774e381bc0a35d33844206d9


The algorithm requires the fault propagation graph and the position of alarms as a starting input:

    #vertices #edges
    edges (e.g. 1 2 to represent the edge 1 -> 2)
    #alarms
    alarms

For each iteration of the sequential diagnosis algorithm S-DIAG the following input is required.
The alarm at vertex v is ringing iff at least one of v's anchestors (including v itself) is faulty. 

    #ringing alarms
    ringing alarms
 
This is an example input:

    5 7
    1 2
    1 4
    2 3
    2 4
    3 2
    3 5
    4 5

    3
    2 4 5

    2
    4 5
    
    1
    5
  
This example input represents the following graph with 5 vertices and 7 edges:

    1 ---> 2 <-------> 3
    |      |           |
    --------> 4 ----------> 5

Three vertices are equipped with an alarm: 2, 4, 5
In the first iteration the alarm at vertex 2 is silent, the alarms at vertexes 4 and 5 are ringing.
In the second iteration both the alarms at 2 and 4 are silent and the alarm at vertex 5 is ringing.

At the end of each iteration, the algorithm outputs the minimum set S of vertexes which contains at least one fault.
Checking and repairing the corresponding components in set S will stop at least one alarm from ringing. 
The next iteration requires the remaining ringing alarms as input.
