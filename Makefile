
CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude/

SRCDIR=src/
OBJDIR=obj/
TARGETDIR=build/

STATIC_TARGET=$(TARGETDIR)libslogger.a
SHARED_TARGET=$(TARGETDIR)libslogger.so

SOURCES=$(SRCDIR)main.c
OBJECTS=$(OBJDIR)main.o


ifeq ($(LIBTYPE), shared)
$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@
else
$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
endif


.PHONY: static shared clean


static: $(OBJECTS) | $(TARGETDIR)
	ar rcs $(STATIC_TARGET) $^

shared: $(OBJECTS) | $(TARGETDIR)
	$(CC) $(CFLAGS) -shared -o $(SHARED_TARGET) $^


$(TARGETDIR):
	mkdir $(TARGETDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	-rm $(STATIC_TARGET) $(SHARED_TARGET)
	-rm -r $(OBJDIR)*

