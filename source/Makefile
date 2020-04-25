DEPENDENCIES := -lpthread
UNAME := $(shell uname)

# Assume target is Mac OS if build host is Mac OS; any other host targets Linux
ifeq ($(UNAME), Darwin)
	DEPENDENCIES += -lobjc -framework IOKit -framework CoreFoundation
else
	DEPENDENCIES += -lrt
endif

app = footboard2PC
apphf = $(app)hf
udp = UDPServer
appd = $(app).d
apphfd = $(apphf).d
udpd = $(udp).d
objects = $(app).o ftd.o ftdDevice.o EnumToString.o parseopt.o udpClient.o
objectshf = $(apphf).o ftdhf.o ftdDevicehf.o EnumToStringhf.o parseopthf.o udpClienthf.o
objectsudp = $(udp).o

CXXFLAGS = -I../libftd2xx/release
RELEASE = -O3
DEBUG = -Wall -Wextra -g
lib = ../libftd2xx.beta/release/build/libftd2xx.a

CC = arm-linux-gnueabihf-g++
libhf = ../libftd2xxhf/release/build/libftd2xx.a

linux raspbian udp : FLAGS = $(RELEASE)
linux.d raspbian.d udp.d : FLAGS = $(DEBUG)

all: linux raspbian udp 
debug: linux.d raspbian.d udp.d

$(app): $(objects)
	$(CXX) $(CXXFLAGS) $(RELEASE) -o $(app) $(objects) $(lib) $(DEPENDENCIES)

$(appd): $(objects)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $(appd) $(objects) $(lib) $(DEPENDENCIES)

$(apphf): $(objectshf)
	$(CC) $(CXXFLAGS) $(RELEASE) -o $(apphf) $(objectshf) $(libhf) $(DEPENDENCIES)

$(apphfd): $(objectshf)
	$(CC) $(CXXFLAGS) $(DEBUG) -o $(apphfd) $(objectshf) $(libhf) $(DEPENDENCIES)

$(udp): $(objectsudp)
	$(CXX) $(CXXFLAGS) $(RELEASE) -o $(udp) $(objectsudp) $(DEPENDENCIES)

$(udpd): $(objectsudpd)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $(udpd) $(objectsudp) $(DEPENDENCIES)

$(objects) $(objectsudp): 
	$(CXX) -c $(CXXFLAGS) $(FLAGS) $< -o $@

$(objectshf): 
	$(CC) -c $(CXXFLAGS) $(FLAGS) $< -o $@

footboard2PC.o footboard2PChf.o: footboard2PC.cpp ftd.hpp ftdException.hpp enums.h Log.hpp types.h blocking_queue.hpp udpClient.hpp  
ftd.o ftdhf.o: ftd.cpp ftd.hpp ftdException.hpp enums.h Log.hpp types.h blocking_queue.hpp udpClient.hpp
ftdDevice.o ftdDevicehf.o: ftdDevice.cpp ftdDevice.hpp blocking_queue.hpp enums.h
EnumToString.o EnumToStringhf.o: EnumToString.cpp enums.h EnumToString.h
parseopt.o parseopthf.o: parseopt.cpp cppopt.hpp
udpClient.o udpClienthf.o: udpClient.cpp enums.h ftdException.hpp udpClient.hpp
UDPServer.o: UDPServer.cpp

rebuild: clean all

linux: rmdebug $(app)

raspbian: rmdebughf $(apphf)

udp: rmdebugudp $(udp)

linux.d: rmrelease $(appd)

raspbian.d: rmreleasehf $(apphfd)

udp.d: rmreleaseudp $(udpd)

.PHONY: clean 
clean:
	-rm -f $(app) $(objects) $(apphf) $(objectshf) $(udp) $(objectsudp) \
	$(appd) $(objectsd) $(apphfd) $(objectshfd) $(udpd) $(objectsudpd)

rmdebug:
	@if [ -f $(appd) ]; then rm -f $(appd) $(objectsd); fi

rmrelease:
	@if [ -f $(app) ]; then rm -f $(app) $(objects); fi

rmdebughf:
	@if [ -f $(apphfd) ]; then rm -f $(apphfd) $(objectshf); fi

rmreleasehf:
	@if [ -f $(apphf) ]; then rm -f $(apphf) $(objectshf); fi

rmdebugudp:
	@if [ -f $(udpd) ]; then rm -f $(udpd) $(objectsudp); fi

rmreleaseudp:
	@if [ -f $(udp) ]; then rm -f $(udp) $(objectsudp); fi

