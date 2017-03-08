//gsoap cwmp service name:        cwmp demo service
//gsoap cwmp service protocol:    SOAP1.1
//gsoap cwmp service method-protocol:    SOAP1.1
//gsoap cwmp service style:       rpc
//gsoap cwmp service encoding:    encoded
//gsoap cwmp service namespace:   http://service.qunxuehui.com:7547/cwmp.wsdl
//gsoap cwmp service location:    http://service.qunxuehui.com:7547/cwmpserver.cgi
//
//gsoap cwmp schema namespace:    urn:dslforum-org:cwmp-1-2
//


#import "cwmp.h"

struct SOAP_ENV__Header {
        mustUnderstand char *ID;
};


struct cwmp__InformResponse {
	unsigned int MaxEnvelopes;
};

//int cwmp__Inform(struct _cwmp__Inform *inform, struct _cwmp__InformResponse *response);
int cwmp__Inform(struct cwmp__DeviceIdStruct *DeviceId,
	struct EventList 		*Event,
	unsigned int			MaxEnvelopes,
	time_t				CurrentTime,
	unsigned int			RetryCount,
	struct ParameterValueList	*ParameterList,
	struct cwmp__InformResponse *response);

