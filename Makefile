#
#
#
PROG=acs cpe

prefix=/usr/local
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

CFLAGS:=-DLINUX -I${includedir}
CFLAGS += -g -DSOAP_DEBUG
LDFLAGS:=-L${libdir} -lgsoap -lm

SOAP=soapcpp2
SOAPFLAGS = -ctL
SOAP_HEADERFILE=cwmp.h
TR069_H_FILE = tr069.h
SOAP_C_CORE=soapC.c

CLEANFILES = $(SOAP_HEADERFILE) $(SOAP_C_CORE) *.req.xml *.res.xml *.nsmap soapStub.h soapH.h soapC.c soap*Proxy.h soap*Proxy.cpp soap*Object.h soap*Service.h soap*Service.c soapClient.c soapServer.c soapClientLib.c soapServerLib.c *~

.PHONY: all clean

all: $(PROG)

$(SOAP_HEADERFILE): datamodels/cwmp-1-2.xsd
	wsdl2h -t gsoap/typemap.dat -c -o $@ $<

$(TR069_H_FILE): $(SOAP_HEADERFILE)
$(SOAP_C_CORE): $(TR069_H_FILE)
	$(SOAP) $(SOAPFLAGS) $^

%.o: %.c
	gcc $(CFLAGS) -o $@ $<

acs: acs.c $(SOAP_C_CORE) soapServer.c
	gcc -o $@  $(CFLAGS) $(LDFLAGS) $^ /usr/local/lib/libgsoap.a

cpe: cpe.c $(SOAP_C_CORE) soapClient.c
	gcc -o $@  $(CFLAGS) $(LDFLAGS) $^ /usr/local/lib/libgsoap.a

tt:acs.c
	gcc -E -o $@ $(CFLAGS) $^

clean:
	-rm -f *.o $(PROG) $(CLEANFILES) *.o *.wsdl *.xsd
