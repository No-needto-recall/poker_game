SRCS:=$(wildcard *.cc)
OBJECT:=$(patsubst %.cc, %.o, $(SRCS))
ALL:=a.out

a.out:$(OBJECT)
	g++ $(OBJECT) -o a.out

%.o:%.cc
	g++ -c $^ -o $@


.PHONY:
	clean rebuild print
clean:
	rm -rf $(ALL) $(OBJECT)
rebuild: clean $(ALL)
print:
	echo $(OBJECT)
