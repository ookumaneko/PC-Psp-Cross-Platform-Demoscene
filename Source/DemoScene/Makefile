#
# PSP Makefile
#

SDK_TOP		= "/usr/local/psp/devkit"
INCDIR		= $(SDK_TOP)/include
LIBDIR		= $(SDK_TOP)/lib

DBGFLAG		= -g
OPTFLAG		= -Os
SECTFLAG	= -ffunction-sections -fdata-sections

CFLAGS		= -W -Wall $(DBGFLAG) -menable-vfpu=m0-m7 $(OPTFLAG) $(SECTFLAG) -I$(INCDIR)
#CFLAGS		= -W -Wall $(DBGFLAG) -DFULL_VERSION -menable-vfpu=m0-m7 $(OPTFLAG) $(SECTFLAG) -I$(INCDIR)
#CFLAGS		= -W -Wall $(DBGFLAG) -DFPS_ON -DDEBUG_MODE $(OPTFLAG) $(SECTFLAG) -I$(INCDIR)

ASFLAGS		= $(DBGFLAG)
LDFLAGS		= $(DBGFLAG) -L$(LIBDIR)
LDLIBS		= -lgum -lgu -lm
LOADLIBES	=  $(LIBDIR)/ctrl_stub.a
LOADLIBES	+= $(LIBDIR)/display_stub.a
LOADLIBES	+= $(LIBDIR)/ge_user_stub.a
LOADLIBES	+= $(LIBDIR)/libvfpu.a

TARGET	= demo
OBJS	= main.o 

all: $(TARGET).prx $(TARGET).elf
	
clean:
	rm -f $(TARGET).prx $(TARGET).elf *.sym *.o *~ *.bak

$(TARGET).prx: $(OBJS)
	$(LINK.c) $^ $(LDLIBS) $(LOADLIBES) -startfiles -zgc-sections -zv -o $@.sym
	$(STRIP) --strip-section-header -o $@ $@.sym

$(TARGET).elf: $(OBJS)
	$(LINK.c) $^ $(LDLIBS) $(LOADLIBES) -zgenelf -Wl,-gc-sections -o $@.sym
	$(STRIP) --strip-section-header -o $@ $@.sym

#----------- rules --------------
-include PathDefs
PathDefs:
	psp-path-setup > PathDefs || (rm -f PathDefs ; exit 1)