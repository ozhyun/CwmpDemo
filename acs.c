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

	//indicate more requests to send to cpe
	soap->header->cwmp__HoldRequests = xsd__boolean__true_;

	soap_write_cwmp__DeviceIdStruct(soaptmp, DeviceId);
	soap_write_EventList(soaptmp, Event);
	soap_write_ParameterValueList(soaptmp, ParameterList);

	soap_destroy(soaptmp); 				  // delete managed and deserialized data
	soap_end(soaptmp); 					  // delete other data
	soap_free(soaptmp);					  // we're done

	response->MaxEnvelopes = 1;

	return SOAP_OK;
}

int cwmp__GetParameterValues(struct soap *soap, struct ParameterNames *ParameterNames, 
			struct ParameterValueList *ParameterList)
{

    struct soap *soaptmp = soap_new();
	char *name1 = "InternetGatewayDevice.DeviceSummary";
	char *value1 = "EOC - Home Gateway Device";
	char *name2 = "InternetGatewayDevice.LANDeviceNumberOfEntries";
	char *value2 = "4";

    if(soap->header) {
        fprintf(stderr, "%s: get header ID:%s\n", __FUNCTION__, soap->header->cwmp__ID);
    }

	soap_write_ParameterNames(soaptmp, ParameterNames);


	// prepare the response
	ParameterList->__ptrParameterValueStruct = soap_malloc(soap, sizeof(struct cwmp__ParameterValueStruct *)*2);
	struct cwmp__ParameterValueStruct * params = soap_new_cwmp__ParameterValueStruct(soap, 2);
	
	params[0].Name = soap_malloc(soap, strlen(name1)+1);
	params[0].Value = soap_malloc(soap, strlen(value1)+1);
	soap_strcpy(params[0].Name, strlen(name1)+1, name1);
	soap_strcpy(params[0].Value, strlen(value1)+1, value1);
	
	params[1].Name = soap_malloc(soap, strlen(name2)+1);
	params[1].Value = soap_malloc(soap, strlen(value2)+1);
	soap_strcpy(params[1].Name, strlen(name2)+1, name2);
	soap_strcpy(params[1].Value, strlen(value2)+1, value2);


	ParameterList->__ptrParameterValueStruct[0] = params;
	ParameterList->__ptrParameterValueStruct[1] = params+1;
	ParameterList->__size = 2;
	
    soap_destroy(soaptmp);                // delete managed and deserialized data
    soap_end(soaptmp);                    // delete other data
    soap_free(soaptmp);                   // we're done

	return SOAP_OK;
}
