TARGET=miniclr

OBJS=src/main.o src/pe/pe.o src/pe/metadata.o src/btree.o src/list.o src/runtime/runtime.o src/platform/platform.o

CFLAGS= -g -std=c11 -Iinclude

LDFLAGS=
LIBS=

.phony:all

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(LDFLAGS) $(LIBS) $(OBJS) -o $(TARGET)

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)