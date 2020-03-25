#target: prerequisites 
#	command
####################################################
# Author      : longbin
# Created date: 2020-03-25 10:39:42
####################################################

TARGET := a.out
SRC := template.cpp
SRC += template.test.cpp

NEEDED_CXXFLAGS += -std=c++11
NEEDED_CXXFLAGS += -pthread
NEEDED_CXXFLAGS += -D_GLIBCXX_USE_NANOSLEEP
CFLAGS = $(NEEDED_CXXFLAGS)

all:
	g++ $(CFLAGS) -o $(TARGET) $(SRC)

.phony: clean
clean:
	-rm -v $(TARGET)

