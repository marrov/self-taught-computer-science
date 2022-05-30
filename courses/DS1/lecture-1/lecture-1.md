# Lecture 1: Introduction

Lecture notes for lecture 1 of MIT's 6.824: Distributed Systems ([lecture recording](https://www.youtube.com/watch?v=cQP8WApzIQQ)) 

## Motivation and challenges

What is meant "distributed system" (aka distsys): A group of computers cooperating to provide a service

Reasons for distsys?:
- Increase capacity via parallel processing
- Tolerate faults via replication
- Match distribution of physical devices e.g. sensors
- Achieve security via isolation

Challenges:
- Many concurrent parts, complex interactions
- Must cope with partial failure
- Tricky to realize performance potential

Types of applications/infrasturucture:
- Storage: main focus bc it is well defined and known
- Communication: less, mainly as a tool required for distsys
- Computation: some (like MapReduce)

## Abstractions

**Main goal**: discover abstractions that hide complexity (robust, fault tolerance, etc) to make building applications easy.

Topics that appear in these simplifying abstractions:
- Implementation details/tools:
	- RPC (remote procedure call): mask unrealiable network 
	- Threads: tool to structure concurrent operations
	- Concurrency controls (i.e. locks): 
- Performance: goal of distsys is (ideal/perfect) scalability
- Fault tolerance: on a highly scalable system (i.e. thousands of computers) very rare per-computer failures become increasingly frequent. In distsys there is always something broken. Concepts:
	- Availability: operation of a system despite failures (e.g. a replicated system into two and only one fails)
	- Recoverability: the system is able to work after it is repaired/recovered from an error (e.g. can save states to which it can revoer after a power failure). Weaker requirement than availablity. Note: a good available system is also recoverable. Tools required:
		- Non-volatile storage is usually required for this purpose.
		- Replication (management): how to ensure replication do not get out of sync.
- Consistency: example what does a Put/Get pair commands do in a distsys? These commands may do different things or more complex things in a distsys as compared to in a single computer. More complex laws that take into account errors/replication/communication etc. The rquirement is to ensure that command outputs are consistent.

## MapReduce

Based on 2004 paper by Google's engineers (must read!).

### Motivation

Find a solution to run a 'sort' operation to index all websites efficiently on a distsys. 

Google required a framework to abstract away the details of more complex computations to allow for a simple interface to flexibly solve many problem by a non-specialist vs having tailor-made solutions for every problem written by distsys specialists.

### Abstract view of MapReduce

Starts by assuming an input that is split up into many files/chunks. Then runs a map function on each input file (allows for parallelism) and produces a key/value (aka k/v) output for this fractional input.

---

Simple example: Word count  

1. Make a Map of each fractional input (key is the word and the value is 1):  
Input1 -> Map -> a,1 b,1  
Input2 -> Map ->     b,1  
Input3 -> Map -> a,1     c,1
2. Run the reduces by collecting all instances for all maps of each keyword:  
Reduce1 -> a,1 a,1 -> a,2  
Reduce2 -> b,1 b,1 -> b,2  
Reduce3 -> c,1     -> c,1  

So, generally the pseudo-code for the `Map` function for this example is:

`Map(k,v)`: `k` is input file name (not relevant here) and `v` is the content of the file `k`
1. Split `v` into words
2. For each word `w`:
	- `emit(w,"1")`

Similarly, the pseudo-code for the `Reduce` function in this example will be:

`Reduce(k,v)`: `k` is the word and `v` will be a vector of 1's, so we care about `len(v)`:
1. `emit(len(v))`

---

Disadvantages from this example:
1. Functions must be expresable in a Map function
2. Maps have to be independent

Google File System (GFS): splits up large files evenly into small chunks (64kb) distributed among all Google servers. Allows for parallel read as the file is already stored in the "correct" fractional way.

Due to restrictions on the newtwork speed at the time of the paper, the fraction input defined by the GFS and the Map worker for that input lived in the same machine (to avoid network communication of the fractional input to the map worker). Currently, there is not such limitation and so storage and running the map tasks are executed separately. Similarly, the outputs of the maps are stored locally. Then the reduce task does require network communication.