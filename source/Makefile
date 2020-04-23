DEPENDENCIES := -lpthread
UNAME := $(shell uname)

# Assume target is Mac OS if build host is Mac OS; any other host targets Linux
ifeq ($(UNAME), Darwin)
	DEPENDENCIES += -lobjc -framework IOKit -framework CoreFoundation
else
	DEPENDENCIES += -lrt
endif

CC = g++
CXXFLAGS = -Wall -Wextra -g -I../libftd2xxW

app = footboard2PC
udp = UDPServer
lib = ../libftd2xxW/Static/amd64/ftd2xx.lib
objects = $(app).o ftd.o ftdDevice.o EnumToString.o parseopt.o udpClient.o

$(app): $(objects)
	$(CC) $(CXXFLAGS) -o $(app) $(objects) $(lib) $(DEPENDENCIES)

$(app).o ftd.o: ftd.hpp ftdException.hpp enums.h Log.hpp types.h blocking_queue.hpp udpClient.hpp
ftdDevice.o: ftdDevice.hpp blocking_queue.hpp
EnumToString.o: enums.h EnumToString.h
parseopt.o: cppopt.hpp
udpClient.o: enums.h ftdException.hpp udpClient.hpp

rebuild: clean $(app)

udp: UDPServer.o
	$(CC) $(CXXFLAGS) -o $(udp) UDPServer.o $(DEPENDENCIES)

UDPServer.o:

.PHONY: clean 
clean:
	-rm -f $(app) $(udp) $(objects) UDPServer.o
 
