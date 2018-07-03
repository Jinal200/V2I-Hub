/*
 * PersonalSafetyMessage.hpp
 *
 *  Created on: Sep 15, 2016
 *      Author: gmb
 */

#ifndef TMX_J2735_MESSAGES_PERSONALSAFETYMESSAGE_HPP_
#define TMX_J2735_MESSAGES_PERSONALSAFETYMESSAGE_HPP_

#include <PersonalSafetyMessage.h>
#include <tmx/j2735_messages/J2735MessageTemplate.hpp>
#include <tmx/messages/TmxJ2735.hpp>

TMX_J2735_DECLARE(Psm, PersonalSafetyMessage, api::personalSafetyMessage, api::MSGSUBTYPE_PERSONALSAFETYMESSAGE_STRING)

// Specialize the unique key function
TMX_J2735_NAMESPACE_START(tmx)
TMX_J2735_NAMESPACE_START(messages)
TMX_J2735_NAMESPACE_START(j2735)

template <>
inline int get_j2735_message_key<tmx::messages::PsmMessage>(std::shared_ptr<PersonalSafetyMessage> message) {
	if (message) {
		tmx::byte_stream bytes(fmax(message->id.size, sizeof(int)));
		::memcpy(bytes.data(), message->id.buf, bytes.size());
		return *((int *)bytes.data());
	}

	return 0;
}

TMX_J2735_NAMESPACE_END(j2735)
TMX_J2735_NAMESPACE_END(messages)
TMX_J2735_NAMESPACE_END(tmx)

#endif /* TMX_J2735_MESSAGES_PERSONALSAFETYMESSAGE_HPP_ */
