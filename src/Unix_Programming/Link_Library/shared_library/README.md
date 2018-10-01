## Shared Lybrary

We would like to create a shared link library containing the object code of the 
sum() and mul() functions written into mymath.c source file, which can be 
called from different C programs.

1. Compile Position Independent Code (PIC) mymath.o: 
```
gcc -c -fPIC mymath.c
```

2. Create shared link library libmymath.a from mymath.o: 
```
gcc -shared -o libmymath.so mymath.o
```

3. Generate the executable a.out using libmymath.so: 
```
gcc main.c -L. -lmymath
```

4. Export the current path
```
export LD_LIBRARY_PATH=./
```

5. Now the executable is ready to be executed:
```
./a.out
```