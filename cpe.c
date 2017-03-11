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

	if (argc < 2)
	{
		fprintf(stderr, "Usage: [Inform|GetParameterValues|Reboot] \n");
		exit(0);
	}

	soap_init1(&soap, SOAP_XML_INDENT|SOAP_IO_KEEPALIVE);
	soap.header = &header;

	switch (*argv[1])
	{
	case 'I':
	{
		struct cwmp__InformResponse response;
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
		if (soap.error)	{
			soap_print_fault(&soap, stderr);
			exit(1);
		}
		else {
			printf("result = %ld\n", response.MaxEnvelopes);
		}

		break;
	}

	case 'S':
	{
		printf("Not support now\n");

		break;
	}

	case 'G':
	{
		struct ParameterNames params;
		struct ParameterValueList response;

		char *nameList[3] = {
			"InternetGatewayDevice.DeviceInfo.ProvisioningCode",
			"InternetGatewayDevice.ManagementServer.ConnectionRequestURL",
			"InternetGatewayDevice.ManagementServer.Username",
		};

		params.__ptrstring = nameList;
		params.__size = 3;

		soap_call_cwmp__GetParameterValues(&soap, server, "", &params, &response);
		if (soap.error)	{
			soap_print_fault(&soap, stderr);
			exit(1);
		}
		else {
			printf("result = %ld\n", response.__size);
		}

		break;
	}
	case 'R':
	{
		struct cwmp__RebootResponse response;
		soap_call_cwmp__Reboot(&soap, server, "", "REBOOT", &response);
		if (soap.error)	{
			soap_print_fault(&soap, stderr);
			exit(1);
		}
		else {
			printf("call reboot success.\n");
		}

		break;
	}
	default:
		fprintf(stderr, "Unknown command\n");
		exit(0);
	}

	soap_destroy(&soap);
	soap_end(&soap);
	soap_done(&soap);

	return 0;
}
