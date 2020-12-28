cc = g++
prom = test
deps = str_int.h code_test.cpp
obj = code_test.o
 
$(prom): $(obj)
	$(cc) -o $(prom) $(obj)
 
%.o: %.c $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)