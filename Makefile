SYSCONF_LINK = gcc
CFLAGS     = -Wall -g
LDFLAGS      =
LIBS         = -lm -lc

DESTDIR = ./
TARGET  = tinyrenderer

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) $(CFLAGS) $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.c
	$(SYSCONF_LINK) $(CFLAGS)   -c $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f *.tga

fclean: clean
	-rm -f $(TARGET)

re:	fclean all
