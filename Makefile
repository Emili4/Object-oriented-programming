CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC_FILES = Course.cpp Person.cpp Professor.cpp Secretary.cpp Student.cpp main.cpp
HEADER_FILES = Course.h Period.h PeriodData.h Person.h Professor.h Secretary.h SignUp.h Student.h
DATA_FILES = assignments.csv courses.csv professors.csv signups.csv students.csv

all: main

main: $(SRC_FILES) $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o main

run: main
	./main

clean:
	rm -f main

.PHONY: all run clean
