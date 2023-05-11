APP = arping

# Add any other object files to this list below
APP_OBJS = arping.o

all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS)

clean:
	-rm $(APP) *.o
