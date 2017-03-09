#
#
#
PROG=acs cpe


CC = gcc
CFLAGS:=-DLINUX
CFLAGS += -g 
#CFLAGS += -DSOAP_DEBUG
LDFLAGS:= -lm

SOAP=soapcpp2
SOAPFLAGS = -ctL
SOAP_HEADERFILE=cwmp.h
TR069_H_FILE = tr069.h
SOAP_C_CORE=soapC.c

acs__SRCS = acs.c \
	stdsoap2.c \
	$(SOAP_C_CORE) \
	soapServer.c

acs__OBJS = $(acs__SRCS:.c=.o)

cpe__SRCS = cpe.c \
	stdsoap2.c \
	$(SOAP_C_CORE) \
	soapClient.c 

cpe__OBJS = $(cpe__SRCS:.c=.o)


SRCS = $(acs__SRCS) \
	$(cpe__SRCS)

DEPDIR = .deps/
dep__OBJS_T = $(SRCS:.c=.Po)
dep__OBJS = $(addprefix $(DEPDIR), $(dep__OBJS_T))


CLEANFILES = $(SOAP_HEADERFILE) \
	$(SOAP_C_CORE) \
	*.req.xml *.res.xml *.nsmap \
	soapStub.h soapH.h \
	soapC.c soap*Proxy.h soap*Proxy.cpp \
	soap*Object.h soap*Service.h \
	soap*Service.c soapClient.c soapServer.c \
	soapClientLib.c soapServerLib.c *~

.PHONY: all clean

all: PRE $(PROG)

$(SOAP_HEADERFILE): datamodels/cwmp-1-2.xsd
	wsdl2h -t gsoap/typemap.dat -c -o $@ $<

$(TR069_H_FILE): $(SOAP_HEADERFILE)
$(SOAP_C_CORE): $(TR069_H_FILE)
	$(SOAP) $(SOAPFLAGS) $^

PRE: $(SOAP_C_CORE)
	mkdir -p $(DEPDIR)

#dep: $(acs__SRCS)
#	$(CC) $(CFLAGS) -MM -MD -MP  $^

dep: PRE $(dep__OBJS)

%.Po: $(SRCS)
	$(CC) $(CFLAGS) -MM -MD -MP -MF $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

acs: $(acs__OBJS)
	$(CC) -o $@  $(CFLAGS) $(LDFLAGS) $^

cpe: $(cpe__OBJS)
	$(CC) -o $@  $(CFLAGS) $(LDFLAGS) $^ 

DD: stdsoap2.c
	$(CC) -DLINUX -g -MD -MP -MF .deps/stdsoap2.Po stdsoap2.c 

tt:acs.c
	$(CC) -E -o $@ $(CFLAGS) $^

clean:
	-rm -rf $(DEPDIR)
	-rm -f *.o $(PROG) $(CLEANFILES) *.o *.wsdl *.xsd
