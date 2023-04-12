main:test.cc httpconn.cc tool.cc 
	g++ $^ -o $@ -std=c++11 -g 

clean:
	rm -f main
