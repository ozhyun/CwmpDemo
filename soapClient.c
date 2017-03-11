/* soapClient.c
   Generated by gSOAP 2.8.44 for tr069.h

gSOAP XML Web services tools
Copyright (C) 2000-2017, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"
#ifdef __cplusplus
extern "C" {
#endif

SOAP_SOURCE_STAMP("@(#) soapClient.c ver 2.8.44 2017-03-11 09:23:32 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_cwmp__Inform(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct cwmp__DeviceIdStruct *DeviceId, struct EventList *Event, unsigned int MaxEnvelopes, time_t CurrentTime, unsigned int RetryCount, struct ParameterValueList *ParameterList, struct cwmp__InformResponse *response)
{	struct cwmp__Inform soap_tmp_cwmp__Inform;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://127.0.0.1:7547/cwmpserver.cgi";
	soap_tmp_cwmp__Inform.DeviceId = DeviceId;
	soap_tmp_cwmp__Inform.Event = Event;
	soap_tmp_cwmp__Inform.MaxEnvelopes = MaxEnvelopes;
	soap_tmp_cwmp__Inform.CurrentTime = CurrentTime;
	soap_tmp_cwmp__Inform.RetryCount = RetryCount;
	soap_tmp_cwmp__Inform.ParameterList = ParameterList;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_cwmp__Inform(soap, &soap_tmp_cwmp__Inform);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_cwmp__Inform(soap, &soap_tmp_cwmp__Inform, "cwmp:Inform", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_cwmp__Inform(soap, &soap_tmp_cwmp__Inform, "cwmp:Inform", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!response)
		return soap_closesock(soap);
	soap_default_cwmp__InformResponse(soap, response);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_cwmp__InformResponse(soap, response, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_cwmp__GetParameterValues(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct ParameterNames *ParameterNames, struct ParameterValueList *ParameterList)
{	struct cwmp__GetParameterValues soap_tmp_cwmp__GetParameterValues;
	struct cwmp__GetParameterValuesResponse *soap_tmp_cwmp__GetParameterValuesResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://127.0.0.1:7547/cwmpserver.cgi";
	soap_tmp_cwmp__GetParameterValues.ParameterNames = ParameterNames;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_cwmp__GetParameterValues(soap, &soap_tmp_cwmp__GetParameterValues);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_cwmp__GetParameterValues(soap, &soap_tmp_cwmp__GetParameterValues, "cwmp:GetParameterValues", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_cwmp__GetParameterValues(soap, &soap_tmp_cwmp__GetParameterValues, "cwmp:GetParameterValues", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ParameterList)
		return soap_closesock(soap);
	soap_default_ParameterValueList(soap, ParameterList);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_cwmp__GetParameterValuesResponse = soap_get_cwmp__GetParameterValuesResponse(soap, NULL, "", NULL);
	if (!soap_tmp_cwmp__GetParameterValuesResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (ParameterList && soap_tmp_cwmp__GetParameterValuesResponse->ParameterList)
		*ParameterList = *soap_tmp_cwmp__GetParameterValuesResponse->ParameterList;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_cwmp__Reboot(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *Commandkey, struct cwmp__RebootResponse *res)
{	struct cwmp__Reboot soap_tmp_cwmp__Reboot;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://127.0.0.1:7547/cwmpserver.cgi";
	soap_tmp_cwmp__Reboot.Commandkey = Commandkey;
	soap_begin(soap);
	soap_set_version(soap, 1); /* SOAP1.1 */
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_cwmp__Reboot(soap, &soap_tmp_cwmp__Reboot);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_cwmp__Reboot(soap, &soap_tmp_cwmp__Reboot, "cwmp:Reboot", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_cwmp__Reboot(soap, &soap_tmp_cwmp__Reboot, "cwmp:Reboot", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!res)
		return soap_closesock(soap);
	soap_default_cwmp__RebootResponse(soap, res);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_cwmp__RebootResponse(soap, res, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

#ifdef __cplusplus
}
#endif

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.c */
