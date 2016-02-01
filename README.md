# dslib
An under-development library of handy data structures with a circular doubly linked list in its heart. The idea is to build up on top of the base data structure and implement newer data structures. Library-internal data structures are dynamically (de)allocated.
 
Building blocks
-
- dlist : Circular doubly linked list with a void pointer pointing to the data in each node. As you can guess, the library doesn't take care (de)allocating memory for the data used. A node simply points to the data plus next and previous node pointers.
- queue : Builds on top of `dlist`. Each element is a dlist node pointing to the value inserted in the queue.
- stack : Builds on top of `dlist`. Each element is a dlist node pointing to the value pushed in the stack.
- tree : A binary search tree custructed from integer values.
- AVL : An AVL tree implementation, stores integer values.
- BFS : Iterative Breadth-first search for tree and AVL implemented using the `queue`.
- DFS : Iterative Depth-first search for tree and AVL implemented using the `stack`.
  
# License
`dslib` is GPLv3 licensed.  
Copyright (C) 2015 [Arun Prakash Jana](mailto:engineerarun@gmail.com)

# Compilation
The following compilation steps are tested on Ubuntu 14.04.3 x86_64:
<pre>$ git clone https://github.com/jarun/dslib/
$ cd dslib/DS
$ make</pre>
To install `dslib`, run:
<pre>$ sudo make install</pre>
To unnstall `dslib` from your system, run:
<pre>$ sudo make uninstall</pre>

# Testing
If you are not writing your own application using `dslib`, add test-cases in main.c, compile and run:
<pre>$ gcc -o ds main.c -lds
$ ./ds</pre>
A sample testcase to create tree and search a value in it is already implemented in <i>main.c</i>. Change `current_log_level` in <i>main.c</i> to DEBUG for detailed information of the sample run.

# Developers
[Arun Prakash Jana](mailto:engineerarun@gmail.com)  
[Ananya Jana](mailto:ananya.jana@gmail.com)
