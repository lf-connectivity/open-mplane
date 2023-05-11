APP = tunctl

# Add any other object files to this list below
APP_OBJS = tunctl.o

all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS)

clean:
	-rm $(APP) *.o
	