#  CC=g++ -Wall -pg -O3 # profile
#  CC=g++ -Wall -g # debug
CC=g++ -Wall  -O2 # release
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
DEPS=$(patsubst %.cpp,%.d,$(SRCS))

all: main

main: $(OBJS)
	$(CC) -o main $^

CFLAGS= -Wall

$(OBJS): %.o: %.cpp
	$(CC) -c -MMD -MP $(CFLAGS) $< -o $@
	@sed -i -e '1s,\($*\)\.o[ :]*,\1.o $*.d: ,' $*.d

-include $(DEPS)

clean:
	rm -f *.o *.d gmon.out


