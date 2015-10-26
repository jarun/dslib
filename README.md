# dslib
An under-development library of handy data structures with a circular doubly linked list in its heart. The idea is to build up on top of the base data structure and implement newer data structures. Library-internal data structures are dynamically (de)allocated.
  
`dslib` is GPLv3 licensed.  
Copyright (C) 2015 Arun Prakash Jana &lt;engineerarun@gmail.com&gt;

Building blocks
-
- dlist : Circular doubly linked list with a void pointer pointing to the data in each node. As you can guess, the library doesn't take care (de)allocating memory for the data used. A node simply points to the data plus next and previous node pointers.
- queue : Builds on top of `dlist`. Each element is a dlist node pointing to the value inserted in the queue.
- stack : Builds on top of `dlist`. Each element is a dlist node pointing to the value pushed in the stack.
- tree : A binary search tree custructed from integer values.
- BFS : Breadth-first search implemented using the `queue`.
- DFS : Depth-first search implemented using the `stack`.
  
NOTE: by the first release, the code will be well-commented.

# Compilation
The following compilation steps are tested on Ubuntu 14.04.3 x86_64:
<pre>$ git clone https://github.com/jarun/dslib/
$ cd dslib/DS
$ make</pre>
  
NOTE: By the first release, installation steps would be available along with installable shared library.

# Developers
Arun Prakash Jana &lt;engineerarun@gmail.com&gt;  
Ananya Jana &lt;ananya.jana@gmail.com&gt;
