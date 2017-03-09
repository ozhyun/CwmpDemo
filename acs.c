#include "soapH.h"
#include "cwmp.nsmap"

int main(int argc, char **argv)
{
	SOAP_SOCKET m, s; /* master and slave sockets */
	struct soap soap;
	soap_init1(&soap, SOAP_XML_IGNORENS|SOAP_IO_KEEPALIVE);

	if (argc < 2) {
		soap_serve(&soap); /* serve as CGI application */
	}
	else {
		m = soap_bind(&soap, NULL, atoi(argv[1]), 100);
		if (!soap_valid_socket(m)) {
			soap_print_fault(&soap, stderr);
			exit(-1);
		}
		fprintf(stderr, "Socket connection successful: master socket = %d\n", m);

		while(1) {
			s = soap_accept(&soap);
			fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);
			if (!soap_valid_socket(s)) {
				soap_print_fault(&soap, stderr);
				exit(-1);
			}
			soap_serve(&soap);
			soap_end(&soap);
		}
	}

	return 0;

}

int cwmp__Inform(struct soap *soap, struct cwmp__DeviceIdStruct *DeviceId,
	struct EventList 		*Event,
	unsigned int			MaxEnvelopes,
	time_t				CurrentTime,
	unsigned int			RetryCount,
	struct ParameterValueList	*ParameterList,
	struct cwmp__InformResponse *response)
{
	struct soap *soaptmp = soap_new();

	if(soap->header) {
		fprintf(stderr, "%s: get header ID:%s\n", __FUNCTION__, soap->header->cwmp__ID);
	}

	soap_write_cwmp__DeviceIdStruct(soaptmp, DeviceId);
	soap_write_EventList(soaptmp, Event);
	soap_write_ParameterValueList(soaptmp, ParameterList);

	soap_destroy(soaptmp); 				  // delete managed and deserialized data
	soap_end(soaptmp); 					  // delete other data
	soap_free(soaptmp);					  // we're done

	response->MaxEnvelopes = 1;

	return SOAP_OK;
}

