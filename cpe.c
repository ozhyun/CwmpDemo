#include "soapH.h"
#include "cwmp.nsmap"
#include <time.h>

const char server[] = "http://127.0.0.1:7547";
/* = "http://localhost:8080"; to test against samples/webserver */

int main(int argc, char **argv)
{
	struct soap soap;
	struct SOAP_ENV__Header header = {
		"1234567",
	};

	struct _cwmp__Inform inform;
	struct cwmp__InformResponse response;
	if (argc < 2)
	{
		fprintf(stderr, "Usage: [Inform|] \n");
		exit(0);
	}

	soap_init1(&soap, SOAP_XML_INDENT);
	soap.header = &header;

	soap_default__cwmp__Inform(&soap, &inform);
	//soap_default__cwmp__InformResponse(&soap, &response);

	inform.MaxEnvelopes = 1;
	time(&inform.CurrentTime);

	switch (*argv[1])
	{
	case 'I':
	{
		//soap_call_cwmp__Inform(&soap, server, "", &inform,  &response);
		struct cwmp__DeviceIdStruct DeviceId;
		DeviceId.Manufacturer = "Abloomy";
		DeviceId.OUI = "00193b";
		DeviceId.ProductClass = "AC";
		DeviceId.SerialNumber = "A5190074KH15A2500249";
		
		struct EventList Event;
		struct cwmp__EventStruct *events_ptr[1];
		struct cwmp__EventStruct *events = soap_new_cwmp__EventStruct(&soap, 1);
		events[0].EventCode = "2 PERIODIC";
		events[0].CommandKey = "";

		events_ptr[0] = events;
		Event.__ptrEventStruct = events_ptr; 
		Event.__size = 1;

		struct ParameterValueList ParameterList;
		struct cwmp__ParameterValueStruct *params_ptr[2];
		struct cwmp__ParameterValueStruct * params = soap_new_cwmp__ParameterValueStruct(&soap, 2);
		params[0].Name = "InternetGatewayDevice.DeviceSummary";
		params[0].Value = "EOC - Home Gateway Device";
		params[1].Name = "InternetGatewayDevice.LANDeviceNumberOfEntries";
		params[1].Value = "4";
		params_ptr[0] = params;
		params_ptr[1] = params+1;
		ParameterList.__ptrParameterValueStruct = params_ptr; 
		ParameterList.__size = 2;

		soap_call_cwmp__Inform(&soap, server, "", &DeviceId, &Event, (unsigned int)1, 
						time(NULL), (unsigned int)0, &ParameterList, &response);

		break;
	}
	default:
		fprintf(stderr, "Unknown command\n");
		exit(0);
	}

	if (soap.error)	{
		soap_print_fault(&soap, stderr);
		exit(1);
	}
	else {
		printf("result = %g\n", response.MaxEnvelopes);
	}

	soap_destroy(&soap);
	soap_end(&soap);
	soap_done(&soap);
	return 0;
}
