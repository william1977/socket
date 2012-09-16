#CFLAGS+=-O1
#CXXFLAGS+=-O2
#LDFLAGS+=-static

TARGET1=main1
TARGET2=main2

TARGETS:=$(TARGET1)
TARGETS+=$(TARGET2)
TARGETOBJS=`echo "$(TARGETS) " | sed 's/ /.o /g'`

SOURCES:=testcpp.o
SOURCES+=testc.o

all:prep $(TARGETS)
$(TARGET1):$(TARGET1).o $(SOURCES)
$(TARGET2):$(TARGET2).o $(SOURCES)

clean:
	rm $(SOURCES) $(TARGETS)
	echo $(TARGETOBJS) | xargs rm

prep:
	echo $(TARGETS)
	echo $(TARGETOBJS)
	echo $(SOURCES)
	echo "begin make ......"

