/*
 * Copyright 2004-2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * XSEC
 *
 * XKMSStatusRequestImpl := Implementation of StatusRequest Messages
 *
 * $Id$
 *
 */

#include <xsec/framework/XSECDefs.hpp>
#include <xsec/framework/XSECError.hpp>
#include <xsec/framework/XSECEnv.hpp>
#include <xsec/utils/XSECDOMUtils.hpp>
#include <xsec/xkms/XKMSConstants.hpp>

#include "XKMSStatusRequestImpl.hpp"

#include <xercesc/dom/DOM.hpp>

XERCES_CPP_NAMESPACE_USE

// --------------------------------------------------------------------------------
//           Construct/Destruct
// --------------------------------------------------------------------------------

XKMSStatusRequestImpl::XKMSStatusRequestImpl(
		const XSECEnv * env) :
XKMSRequestAbstractTypeImpl(env),
mp_responseIdAttr(NULL) {
}

XKMSStatusRequestImpl::XKMSStatusRequestImpl(
		const XSECEnv * env, 
		XERCES_CPP_NAMESPACE_QUALIFIER DOMElement * node) :
XKMSRequestAbstractTypeImpl(env, node),
mp_responseIdAttr(NULL) {

}

XKMSStatusRequestImpl::~XKMSStatusRequestImpl() {

}


// --------------------------------------------------------------------------------
//           Load from DOM
// --------------------------------------------------------------------------------

// Load elements
void XKMSStatusRequestImpl::load() {

	if (mp_messageAbstractTypeElement == NULL) {

		// Attempt to load an empty element
		throw XSECException(XSECException::XKMSError,
			"XKMSStatusRequest::load - called on empty DOM");

	}

	if (!strEquals(getXKMSLocalName(mp_messageAbstractTypeElement), 
									XKMSConstants::s_tagStatusRequest)) {
	
		throw XSECException(XSECException::XKMSError,
			"XKMSStatusRequest::load - called incorrect node");
	
	}

	// Load the base message
	XKMSRequestAbstractTypeImpl::load();

	// Now check for ResponseId attribute
	mp_responseIdAttr = 
		mp_messageAbstractTypeElement->getAttributeNodeNS(NULL, XKMSConstants::s_tagResponseId);

	if (mp_responseIdAttr == NULL) {
		throw XSECException(XSECException::XKMSError,
			"XKMSStatusRequest::load - responseId not found!");
	}

}

// --------------------------------------------------------------------------------
//           Create a blank one
// --------------------------------------------------------------------------------
DOMElement * XKMSStatusRequestImpl::createBlankStatusRequest(
		const XMLCh * service,
		const XMLCh * id) {

	return XKMSRequestAbstractTypeImpl::createBlankMessageAbstractType(
		XKMSConstants::s_tagStatusRequest, service, id);
//	return XKMSRequestAbstractTypeImpl::createBlankMessageAbstractType(
//		MAKE_UNICODE_STRING("ValidateRequest"), service, id);

}

// --------------------------------------------------------------------------------
//           Get interface methods
// --------------------------------------------------------------------------------

XKMSMessageAbstractType::messageType XKMSStatusRequestImpl::getMessageType(void) {

	return XKMSMessageAbstractType::StatusRequest;

}


const XMLCh * XKMSStatusRequestImpl::getResponseId(void) const {

	if (mp_responseIdAttr == NULL) {

		// Attempt read when not initialised
		throw XSECException(XSECException::MessageAbstractTypeError,
			"XKMSStatusRequest::getResponseId - called on non-initialised structure");

	}

	return 	mp_responseIdAttr->getNodeValue();
}

// --------------------------------------------------------------------------------
//           Setter methods
// --------------------------------------------------------------------------------

void XKMSStatusRequestImpl::setResponseId(const XMLCh * responseId) {

	if (mp_messageAbstractTypeElement == NULL) {

		// Attempt update when not initialised
		throw XSECException(XSECException::MessageAbstractTypeError,
			"XKMSStatusRequest::setResponseId - called on non-initialised structure");

	}

	mp_messageAbstractTypeElement->setAttributeNS(NULL, XKMSConstants::s_tagResponseId, responseId);
	mp_responseIdAttr = 
		mp_messageAbstractTypeElement->getAttributeNodeNS(NULL, XKMSConstants::s_tagResponseId);

}

