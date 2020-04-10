DEPENDENCIES := -lpthread
UNAME := $(shell uname)

# Assume target is Mac OS if build host is Mac OS; any other host targets Linux
ifeq ($(UNAME), Darwin)
	DEPENDENCIES += -lobjc -framework IOKit -framework CoreFoundation
else
	DEPENDENCIES += -lrt
endif

CC = gcc
CFLAGS = -Wall -Wextra

DYNAMIC_LINK_OPTIONS := -Wl,-rpath

APP = test

STATIC_APP = $(APP)-static

DYNAMIC_APP = $(APP)-dynamic

STATIC_LIB = ../../libftd2xx/release/build/libftd2xx.a

all: $(STATIC_APP) $(DYNAMIC_APP)

$(STATIC_APP): main.c
	$(CC) main.c -o $(STATIC_APP) $(STATIC_LIB) $(CFLAGS) $(DEPENDENCIES)

$(DYNAMIC_APP): main.c
	$(CC) main.c -o $(DYNAMIC_APP) $(CFLAGS) -lftd2xx $(DEPENDENCIES) $(DYNAMIC_LINK_OPTIONS)
	
clean:
	-rm -f *.o ; rm -f $(STATIC_APP); rm -f $(DYNAMIC_APP)
