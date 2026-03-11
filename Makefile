
CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude/

SRCDIR=src/
OBJDIR=obj/
TARGETDIR=build/

STATIC_TARGET=$(TARGETDIR)libslogger.a
SHARED_TARGET=$(TARGETDIR)libslogger.so

SOURCES=$(SRCDIR)main.c $(SRCDIR)first.c $(SRCDIR)second.c
OBJECTS=$(OBJDIR)main.o $(OBJDIR)first.o $(OBJDIR)second.o


ifeq ($(LIBTYPE), shared)
$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@
else
$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
endif


.PHONY: static shared clean


static: $(OBJECTS)
	ar rcs $(STATIC_TARGET) $^

shared: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $(SHARED_TARGET) $^


clean:
	-rm $(STATIC_TARGET) $(SHARED_TARGET)
	-rm -r $(OBJDIR)*

