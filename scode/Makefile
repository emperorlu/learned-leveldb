cc = g++
prom = test
deps = str_int.h str_int.cpp code_test.cpp
obj = str_int.o code_test.o
 
$(prom): $(obj)
    $(cc) -o $(prom) $(obj)
 
%.o: %.c $(deps)
    $(cc) -c $< -o $@
 
clean:
    rm -rf $(obj) $(prom)