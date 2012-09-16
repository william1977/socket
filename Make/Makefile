#CFLAGS+=-O1
#CXXFLAGS+=-O2
#LDFLAGS+=-static

TARGET1=main1
TARGET2=main2

#TARGETS:=$(TARGET1)
#TARGETS+=$(TARGET2)

SOURCES:=testcpp.o
SOURCES+=testc.o

TARGETSOBJ:=$(TARGET1).o
TARGETSOBJ+=$(TARGET2).o
TARGETS=`echo "$(TARGETSOBJ)" | sed 's/.o//g'`
#TARGETSOBJ=`echo "$(TARGETS)" | sed 's/ /.o /g'`

all:prep compile $(TARGETS)
$(TARGETS):$(SOURCES)
compile:$(TARGETSOBJ)

clean:
	rm $(SOURCES) $(TARGETSOBJ) $(TARGETS)

prep:
	echo $(TARGETSOBJ)
	echo $(TARGETS)
	echo "begin make ......"

