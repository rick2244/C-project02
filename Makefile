PROG = project02

OBJS = project02.o

%.o: %.c
	gcc -c -g -o $@ $<

$(PROG): $(OBJS)
	gcc -g -o $@ $^
	
clean:
	rm -rf $(PROG) $(OBJS)
