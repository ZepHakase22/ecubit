DEPENDENCIES := -lpthread
UNAME := $(shell uname)

# Assume target is Mac OS if build host is Mac OS; any other host targets Linux
ifeq ($(UNAME), Darwin)
	DEPENDENCIES += -lobjc -framework IOKit -framework CoreFoundation
else
	DEPENDENCIES += -lrt
endif

app = footboard2PC
appdll = $(app)dll
appd = $(app).d
appdlld = $(appdll).d
objects = $(app).o ftd.o ftdDevice.o EnumToString.o parseopt.o udpClient.o

apphf = $(app)hf
apphfdll = $(apphf)dll
apphfd = $(apphf).d
apphfdlld = $(apphfdll).d
objectshf = $(apphf).o ftdhf.o ftdDevicehf.o EnumToStringhf.o parseopthf.o udpClienthf.o

udp = UDPServer
udpd = $(udp).d
objectsudp = $(udp).o

CXXFLAGS = -I../libftd2xx/release
RELEASE = -O3
DEBUG = -Wall -Wextra -g
lib = ../libftd2xx.beta/release/build/libftd2xx.a

CC = arm-linux-gnueabihf-g++
libhf = ../libftd2xxhf/release/build/libftd2xx.a

DYNAMIC_LINK_OPTIONS := -Wl,-rpath

linux linuxdll raspbian raspbiandll udp : FLAGS = $(RELEASE)
linux.d linuxdll.d raspbian.d raspbiandll.d udp.d : FLAGS = $(DEBUG)

all: linux raspbian udp 
debug: linux.d raspbian.d udp.d
dll: linuxdll raspbiandll udp
dlldebug: linuxdll.d raspbiandll.d udp.d 

$(app): $(objects)
	$(CXX) $(CXXFLAGS) $(RELEASE) -o $(app) $(objects) $(lib) $(DEPENDENCIES)

$(appdll): $(objects)
	$(CXX) $(CXXFLAGS) $(RELEASE) -lftd2xx -o $(appdll) $(objects) $(DYNAMIC_LINK_OPTIONS) $(DEPENDENCIES)

$(appd): $(objects)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $(appd) $(objects) $(lib) $(DEPENDENCIES)

$(appdlld): $(objects)
	$(CXX) $(CXXFLAGS) $(DEBUG) -lftd2xx -o $(appdlld) $(objects) $(DYNAMIC_LINK_OPTIONS) $(DEPENDENCIES)

$(apphf): $(objectshf)
	$(CC) $(CXXFLAGS) $(RELEASE) -o $(apphf) $(objectshf) $(libhf) $(DEPENDENCIES)

$(apphfdll): $(objectshf)
	$(CC) $(CXXFLAGS) $(RELEASE) -lftd2xx -o $(apphfdll) $(objectshf) $(DYNAMIC_LINK_OPTIONS) $(DEPENDENCIES)

$(apphfd): $(objectshf)
	$(CC) $(CXXFLAGS) $(DEBUG) -o $(apphfd) $(objectshf) $(libhf) $(DEPENDENCIES)

$(apphfdlld): $(objectshf)
	$(CC) $(CXXFLAGS) $(DEBUG) -lftd2xx -o $(apphfdlld) $(objectshf) $(DYNAMIC_LINK_OPTIONS) $(DEPENDENCIES)

$(udp): $(objectsudp)
	$(CXX) $(CXXFLAGS) $(RELEASE) -o $(udp) $(objectsudp) $(DEPENDENCIES)

$(udpd): $(objectsudp)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $(udpd) $(objectsudp) $(DEPENDENCIES)

$(objects): 
	$(CXX) $(CXXFLAGS) $(FLAGS) -c $< -o $@

$(objectshf): 
	$(CC) $(CXXFLAGS) $(FLAGS) -c $< -o $@

$(objectsudp):
	$(CXX) -c $< -o $@

footboard2PC.o footboard2PChf.o: footboard2PC.cpp ftd.hpp ftdException.hpp enums.h Log.hpp types.h blocking_queue.hpp udpClient.hpp  
ftd.o ftdhf.o: ftd.cpp ftd.hpp ftdException.hpp enums.h Log.hpp types.h blocking_queue.hpp udpClient.hpp
ftdDevice.o ftdDevicehf.o: ftdDevice.cpp ftdDevice.hpp blocking_queue.hpp enums.h
EnumToString.o EnumToStringhf.o: EnumToString.cpp enums.h EnumToString.h
parseopt.o parseopthf.o: parseopt.cpp cppopt.hpp
udpClient.o udpClienthf.o: udpClient.cpp enums.h ftdException.hpp udpClient.hpp
UDPServer.o: UDPServer.cpp

rebuild: clean all
rebuild.d: clean debug
rebuilddll: clean dll
rebuilddll.d: clean dlldebug

linux: rmdebug rmreleasedll rmdebugdll $(app)

raspbian: rmdebughf rmreleasedllhf rmdebughdllf $(apphf)

udp: rmdebugudp $(udp)

linux.d: rmrelease rmreleasedll rmdebugdll $(appd)

raspbian.d: rmreleasehf rmreleasedllhf rmdebugdllhf $(apphfd)

udp.d: rmreleaseudp $(udpd)

linuxdll: rmdebugdll rmrelease rmdebug $(appdll)

linuxdll.d: rmreleasedll rmrelease rmdebug $(appdlld)

raspbiandll: rmdebugdllhf rmreleasehf rmdebughf $(apphfdll)

raspbiandll.d: rmreleasedllhf rmreleasehf rmdebughf $(apphfdlld)

.PHONY: clean 
clean:
	-rm -f $(app) $(objects) $(apphf) $(objectshf) $(udp) $(objectsudp) \
	$(appd) $(apphfd) $(udpd) $(appdll) $(appdlld) $(apphfdll) $(apphfdlld)

rmdebug:
	@if [ -f $(appd) ]; then rm -f $(objects); fi

rmdebugdll:
	@if [ -f $(appdlld) ]; then rm -f $(objects); fi

rmrelease:
	@if [ -f $(app) ]; then rm -f $(objects); fi

rmreleasedll:
	@if [ -f $(appdll) ]; then rm -f $(objects); fi

rmdebughf:
	@if [ -f $(apphfd) ]; then rm -f $(objectshf); fi

rmdebugdllhf:
	@if [ -f $(apphfdlld) ]; then rm -f $(objectshf); fi

rmreleasehf:
	@if [ -f $(apphf) ]; then rm -f $(objectshf); fi

rmreleasedllhf:
	@if [ -f $(apphfdll) ]; then rm -f $(objectshf); fi

rmdebugudp:
	@if [ -f $(udpd) ]; then rm -f $(objectsudp); fi

rmreleaseudp:
	@if [ -f $(udp) ]; then rm -f $(objectsudp); fi