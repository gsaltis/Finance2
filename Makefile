CC					= gcc
LINK					= gcc

CC_FLAGS				= -c -g -Wall -Id:/usr/local/include
LINK_FLAGS				= -g -Ld:/usr/local/lib
LIB_FLAGS				= -lutils

TARGET					= Finance
LIBS					= -lutils
OBJS					= $(sort				\
					    main.o                              \
					    NorthwestCSV.o			\
					   )

%.o					: %.c
					  @echo [CC] $@
					  @$(CC) $(CC_FLAGS) $<

.PHONY					: all
all					: $(TARGET)

$(TARGET)				: $(OBJS)
					  @echo [LD] $@
					  @$(LINK) $(LINK_FLAGS) $(LIB_FLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.PHONY					: junkclean
junkclean				:
					  rm -rf $(wildcard *~ *.bak)

.PHONY					: clean
clean					: junkclean
					  rm -rf $(wildcard $(TARGET) $(OBJS))

include					  depends.mk

