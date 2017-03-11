//gsoap cwmp service name:        cwmp demo service
//gsoap cwmp service protocol:    SOAP1.1
//gsoap cwmp service method-protocol:    SOAP1.1
//gsoap cwmp service style:       rpc
//gsoap cwmp service encoding:    encoded
//gsoap cwmp service namespace:   http://127.0.0.1:7547/cwmp.wsdl
//gsoap cwmp service location:    http://127.0.0.1:7547/cwmpserver.cgi
//
//gsoap cwmp schema namespace:    urn:dslforum-org:cwmp-1-2
//


#import "cwmp.h"


struct SOAP_ENV__Header {
	mustUnderstand char* cwmp__ID;
	mustUnderstand enum xsd__boolean cwmp__HoldRequests;	
};


struct cwmp__InformResponse {
	unsigned int MaxEnvelopes;
};

/**
 *	impliment in ACS for CPE calling
 *
 */
//int cwmp__Inform(struct _cwmp__Inform *inform, struct _cwmp__InformResponse *response);
int cwmp__Inform(struct cwmp__DeviceIdStruct *DeviceId,
	struct EventList 		*Event,
	unsigned int			MaxEnvelopes,
	time_t				CurrentTime,
	unsigned int			RetryCount,
	struct ParameterValueList	*ParameterList,
	struct cwmp__InformResponse *response);

/**
 * can imliment in both ACS and CPE, mainly impliment in CPE
 *
 */
//int cwmp__GetRPCMethods();

/**
 * impliment in CPE for ACS calling
 *
 */
int cwmp__GetParameterValues(struct ParameterNames *ParameterNames, struct ParameterValueList *ParameterList);


/**
 * impliment in CPE for ACS calling
 *
 */
//int cwmp__SetParameterValues(struct ParameterValueList *values, char *ParamterKey);


