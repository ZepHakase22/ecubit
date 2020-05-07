DEPENDENCIES := -lpthread
UNAME := $(shell uname)
LAST := $(shell ./testLast $1)

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
objectshf = $(objects)

udp = UDPServer
udpd = $(udp).d
objectsudp = $(udp).o

CXXFLAGS = -I../libftd2xx.beta/release
DEBUG = -Wall -Wextra -g
lib = ../libftd2xx.beta/release/build/libftd2xx.a

CC = arm-linux-gnueabihf-g++
CFLAGS = -I../libftd2xxhf.beta/release
libhf = ../libftd2xxhf.beta/release/build/libftd2xx.a

DYNAMIC_LINK_OPTIONS := -Wl,-rpath /usr/local/lib

linux linuxdll udp : RELEASE = -O3 -s
raspbian raspbiandll : RELEASE = -Os -s
linux linuxdll raspbian raspbiandll udp : FLAGS = $(RELEASE)
linux.d linuxdll.d raspbian.d raspbiandll.d udp.d : FLAGS = $(DEBUG)
raspbian raspbiandll raspbian.d raspbiandll.d: CXX = $(CC)
raspbian raspbiandll raspbian.d raspbiandll.d: CXXFLAGS = $(CFLAGS)
udp udp.d: CXXFLAGS =

rebuild: clean 
	make all

rebuild.r: clean 
	make release

rebuild.d: clean
	make debug

rebuild.s: clean
	make static

rebuild.l: clean
	make dll

all: 
	make linux
	make raspbian
	make udp
	make linux.d 
	make raspbian.d 
	make udp.d
	make linuxdll
	make raspbiandll
	make linuxdll.d
	make raspbiandll.d

release:
	make linux
	make raspbian
	make udp
	make raspbiandll

debug: 
	make linux.d 
	make raspbian.d 
	make udp.d
	make raspbiandll.d

static:
	make linux
	make raspbian
	make udp
	make linux.d
	make raspbian.d
	make udp.d

dll: 
	make linuxdll 
	make raspbiandll 
	make linuxdll.d 
	make raspbiandll.d 

$(app): $(objects)
	$(CXX) $(CXXFLAGS) $(RELEASE) -o $(app) $(objects) $(lib) $(DEPENDENCIES)

$(appdll): $(objects)
	$(CXX) -o $(appdll) $(CXXFLAGS) $(RELEASE) $(objects) -lftd2xx $(DEPENDENCIES) $(DYNAMIC_LINK_OPTIONS) 

$(appd): $(objects)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $(appd) $(objects) $(lib) $(DEPENDENCIES)

$(appdlld): $(objects)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $(appdlld) $(objects) -lftd2xx $(DEPENDENCIES) $(DYNAMIC_LINK_OPTIONS)

$(apphf): $(objects)
	$(CXX) $(CFLAGS) $(RELEASE) -o $(apphf) $(objects) $(libhf) $(DEPENDENCIES)

$(apphfdll): $(objects)
	$(CXX) $(CFLAGS) $(RELEASE) -o $(apphfdll) $(objects) -L/usr/local/lib/hf -lftd2xx $(DEPENDENCIES)
	
$(apphfd): $(objectshf)
	$(CXX) $(CFLAGS) $(DEBUG) -o $(apphfd) $(objectshf) $(libhf) $(DEPENDENCIES)

$(apphfdlld): $(objectshf)
	$(CXX) $(CFLAGS) $(DEBUG) -o $(apphfdlld) $(objects) -L/usr/local/lib/hf -lftd2xx $(DEPENDENCIES)

$(udp): $(objectsudp)
	$(CXX) $(CXXFLAGS) $(RELEASE) -o $(udp) $(objectsudp) $(DEPENDENCIES)

$(udpd): $(objectsudp)
	$(CXX) $(DEBUG) -o $(udpd) $(objectsudp) $(DEPENDENCIES)

$(objects): 
	$(CXX) $(CXXFLAGS) $(FLAGS) -c $< -o $@

$(objectsudp):
	$(CXX) -c $< -o $@

footboard2PC.o: footboard2PC.cpp ftd.hpp ftdException.hpp enums.h Log.hpp types.h blocking_queue.hpp udpClient.hpp  
ftd.o: ftd.cpp ftd.hpp ftdException.hpp enums.h Log.hpp types.h blocking_queue.hpp udpClient.hpp
ftdDevice.o: ftdDevice.cpp ftdDevice.hpp blocking_queue.hpp enums.h
EnumToString.o: EnumToString.cpp enums.h EnumToString.h
parseopt.o: parseopt.cpp cppopt.hpp
udpClient.o: udpClient.cpp enums.h ftdException.hpp udpClient.hpp
UDPServer.o: UDPServer.cpp

linux: cleanlinux $(app)

linux.d: cleanlinuxd $(appd)

linuxdll: cleanlinuxdll $(appdll)

linuxdll.d: cleanlinuxdlld $(appdlld)

raspbian: cleanraspbian $(apphf)

raspbian.d: cleanraspbiand $(apphfd)

raspbiandll: cleanraspbiandll $(apphfdll)

raspbiandll.d: cleanraspbiandlld $(apphfdlld)

udp: rmdebugudp $(udp)

udp.d: rmreleaseudp $(udpd)

.PHONY: clean 
clean:
	@rm -f $(app) $(objects) $(apphf) $(udp) $(objectsudp) $(appd) $(apphfd) \
		$(udpd) $(appdll) $(appdlld) $(apphfdll) $(apphfdlld)

cleanlinux:
	@if [ $(shell ./testLast linux) = remove ]; then rm -f $(objects); fi; 
	@echo linux > lastVersion

cleanlinuxd:
	@if [ $(shell ./testLast linuxd) = remove ]; then rm -f $(objects); fi; 
	@echo linuxd > lastVersion

cleanlinuxdll:
	@if [ $(shell ./testLast linuxdll) = remove ]; then rm -f $(objects); fi; 
	@echo linuxdll > lastVersion

cleanlinuxdlld:
	@if [ $(shell ./testLast linuxdlld) = remove ]; then rm -f $(objects); fi; 
	@echo linuxdlld > lastVersion

cleanraspbian:
	@if [ $(shell ./testLast raspbian) = remove ]; then rm -f $(objects); fi; 
	@echo raspbian > lastVersion

cleanraspbiand:
	@if [ $(shell ./testLast raspbiand) = remove ]; then rm -f $(objects); fi; 
	@echo raspbiand > lastVersion

cleanraspbiandll:
	@if [ $(shell ./testLast raspbiandll) = remove ]; then rm -f $(objects); fi; 
	@echo raspbiandll > lastVersion

cleanraspbiandlld:
	@if [ $(shell ./testLast raspbiandlld) = remove ]; then rm -f $(objects); fi; 
	@echo raspbiandlld > lastVersion

rmdebugudp:
	@if [ -f $(udpd) ]; then rm -f $(objectsudp); fi

rmreleaseudp:
	@if [ -f $(udp) ]; then rm -f $(objectsudp); fi