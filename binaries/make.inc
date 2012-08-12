CFLAGS+=-DNDEBUG -DLINUX -O2 -fno-strict-aliasing -Wall -ffloat-store -pipe -g -MF .depends/$*.d -MMD
CFLAGS+=-I/usr/local/include -I/usr/X11R6/include
LDFLAGS+=-L/usr/local/lib -L/usr/X11R6/lib
ALLOBJ:=$(ALLSRC:.c=.o)

.PHONY: clean distclean

clean:
	-rm -f $(ALLOBJ) $(TARGETS)

DEPENDS=$(foreach file, $(ALLSRC:.c=.d), .depends/$(file))

distclean: clean
	-rm -f $(DEPENDS)

-include $(DEPENDS)

