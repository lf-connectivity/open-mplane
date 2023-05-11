APP = i2cdetect
TARGETS = $(APP) i2cdump i2cget i2cset

# Add any other object files to this list below
APP_OBJS = i2cbusses.o smbus.o util.o

all: build

build: $(TARGETS)

$(APP): $(APP).o $(APP_OBJS)
	echo $@
	$(CC) $(LDFLAGS) -o $@ $@.o $(APP_OBJS) $(LDLIBS)

i2cdump: i2cdump.o $(APP_OBJS)
	echo $@
	$(CC) $(LDFLAGS) -o $@ $@.o $(APP_OBJS) $(LDLIBS)

i2cget: i2cget.o $(APP_OBJS)
	echo $@
	$(CC) $(LDFLAGS) -o $@ $@.o $(APP_OBJS) $(LDLIBS)

i2cset: i2cset.o $(APP_OBJS)
	echo $@
	$(CC) $(LDFLAGS) -o $@ $@.o $(APP_OBJS) $(LDLIBS)

clean:
	-rm *.o $(TARGETS)

