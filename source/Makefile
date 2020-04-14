DEPENDENCIES := -lpthread
UNAME := $(shell uname)

# Assume target is Mac OS if build host is Mac OS; any other host targets Linux
ifeq ($(UNAME), Darwin)
	DEPENDENCIES += -lobjc -framework IOKit -framework CoreFoundation
else
	DEPENDENCIES += -lrt
endif

CC = g++
CXXFLAGS = -Wall -Wextra -g -I../libftd2xx/release 

app = footboard2PC
lib = ../libftd2xx/release/build/libftd2xx.a
objects = $(app).o ftd.o ftdDevice.o EnumToString.o parseopt.o

$(app): $(objects)
	$(CC) $(CDBFLAGS) -o $(app) $(objects) $(lib) $(DEPENDENCIES)

$(app).o ftd.o: ftd.hpp ftdException.hpp enums.h Log.hpp types.h blocking_queue.hpp
ftdDevice.o: ftdDevice.hpp blocking_queue.hpp
EnumToString.o: enums.h EnumToString.h
parseopt.o: cppopt.hpp

rebuild: clean $(app)

.PHONY: clean
clean:
	-rm -f $(app) $(objects)
 