DEPENDENCIES := -lpthread
UNAME := $(shell uname)

# Assume target is Mac OS if build host is Mac OS; any other host targets Linux
ifeq ($(UNAME), Darwin)
	DEPENDENCIES += -lobjc -framework IOKit -framework CoreFoundation
else
	DEPENDENCIES += -lrt
endif

CC = g++
CDBFLAGS = -Wall -Wextra -g
CXXFLAGS = -Wall -Wextra

app = footboard2PC
lib = ../libftd2xx/release/build/libftd2xx.agit 
objects = $(app).o ftd.o ftdException.o

$(APP): ftd.o
	$(CC) $(CDBFLAGS) -o $(app) $(objects) $(lib) $(DEPENDENCIES)

ftd.o: ftd.hpp ftdException.o
ftdException.o: enums.h ftdException.hpp

.PHONY: clean
clean:
	-rm -f $(app) $(objects)
 