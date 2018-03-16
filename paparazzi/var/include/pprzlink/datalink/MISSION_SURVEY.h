/** @file
 *  @brief PPRZLink message header for MISSION_SURVEY in class datalink
 *
 *  
 *  @see http://paparazziuav.org
 */

#ifndef _VAR_MESSAGES_datalink_MISSION_SURVEY_H_
#define _VAR_MESSAGES_datalink_MISSION_SURVEY_H_


#include "pprzlink/pprzlink_device.h"
#include "pprzlink/pprzlink_transport.h"
#include "pprzlink/pprzlink_utils.h"
#include "pprzlink/pprzlink_message.h"


#ifdef __cplusplus
extern "C" {
#endif

#if DOWNLINK

#define DL_MISSION_SURVEY 28
#define PPRZ_MSG_ID_MISSION_SURVEY 28

/**
 * Macro that redirect calls to the default version of pprzlink API
 * Used for compatibility between versions.
 */
#define pprzlink_msg_send_MISSION_SURVEY _send_msg(MISSION_SURVEY,PPRZLINK_DEFAULT_VER)

/**
 * Sends a MISSION_SURVEY message (API V2.0 version)
 *
 * @param msg the pprzlink_msg structure for this message
 * @param _ac_id 
 * @param _insert 
 * @param _survey_east_1 
 * @param _survey_north_1 
 * @param _survey_east_2 
 * @param _survey_north_2 
 * @param _survey_alt altitude above geoid (MSL)
 * @param _duration 
 * @param _index 
 */
static inline void pprzlink_msg_v2_send_MISSION_SURVEY(struct pprzlink_msg * msg, uint8_t *_ac_id, uint8_t *_insert, float *_survey_east_1, float *_survey_north_1, float *_survey_east_2, float *_survey_north_2, float *_survey_alt, float *_duration, uint8_t *_index) {
#if PPRZLINK_ENABLE_FD
  long _FD = 0; /* can be an address, an index, a file descriptor, ... */
#endif
  const uint8_t size = msg->trans->size_of(msg, /* msg header overhead */4+1+1+4+4+4+4+4+4+1);
  if (msg->trans->check_available_space(msg, _FD_ADDR, size)) {
    msg->trans->count_bytes(msg, size);
    msg->trans->start_message(msg, _FD, /* msg header overhead */4+1+1+4+4+4+4+4+4+1);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, &(msg->sender_id), 1);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, msg->receiver_id, NULL);
    uint8_t comp_class = (msg->component_id & 0x0F) << 4 | (2 & 0x0F);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, comp_class, NULL);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, DL_MISSION_SURVEY, "MISSION_SURVEY");
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, (void *) _ac_id, 1);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, (void *) _insert, 1);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _survey_east_1, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _survey_north_1, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _survey_east_2, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _survey_north_2, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _survey_alt, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _duration, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, (void *) _index, 1);
    msg->trans->end_message(msg, _FD);
  } else
        msg->trans->overrun(msg);
}

// Compatibility with the protocol v1.0 API
#define pprzlink_msg_v1_send_MISSION_SURVEY pprz_msg_send_MISSION_SURVEY
#define DOWNLINK_SEND_MISSION_SURVEY(_trans, _dev, ac_id, insert, survey_east_1, survey_north_1, survey_east_2, survey_north_2, survey_alt, duration, index) pprz_msg_send_MISSION_SURVEY(&((_trans).trans_tx), &((_dev).device), AC_ID, ac_id, insert, survey_east_1, survey_north_1, survey_east_2, survey_north_2, survey_alt, duration, index)
/**
 * Sends a MISSION_SURVEY message (API V1.0 version)
 *
 * @param trans A pointer to the transport_tx structure used for sending the message
 * @param dev A pointer to the link_device structure through which the message will be sent
 * @param ac_id The id of the sender of the message
 * @param _ac_id 
 * @param _insert 
 * @param _survey_east_1 
 * @param _survey_north_1 
 * @param _survey_east_2 
 * @param _survey_north_2 
 * @param _survey_alt altitude above geoid (MSL)
 * @param _duration 
 * @param _index 
 */
static inline void pprz_msg_send_MISSION_SURVEY(struct transport_tx *trans, struct link_device *dev, uint8_t ac_id, uint8_t *_ac_id, uint8_t *_insert, float *_survey_east_1, float *_survey_north_1, float *_survey_east_2, float *_survey_north_2, float *_survey_alt, float *_duration, uint8_t *_index) {
    struct pprzlink_msg msg;
    msg.trans = trans;
    msg.dev = dev;
    msg.sender_id = ac_id;
    msg.receiver_id = 0;
    msg.component_id = 0;
    pprzlink_msg_v2_send_MISSION_SURVEY(&msg,_ac_id,_insert,_survey_east_1,_survey_north_1,_survey_east_2,_survey_north_2,_survey_alt,_duration,_index);
}


#else // DOWNLINK

#define DOWNLINK_SEND_MISSION_SURVEY(_trans, _dev, ac_id, insert, survey_east_1, survey_north_1, survey_east_2, survey_north_2, survey_alt, duration, index) {}
static inline void pprz_send_msg_MISSION_SURVEY(struct transport_tx *trans __attribute__((unused)), struct link_device *dev __attribute__((unused)), uint8_t ac_id __attribute__((unused)), uint8_t *_ac_id __attribute__((unused)), uint8_t *_insert __attribute__((unused)), float *_survey_east_1 __attribute__((unused)), float *_survey_north_1 __attribute__((unused)), float *_survey_east_2 __attribute__((unused)), float *_survey_north_2 __attribute__((unused)), float *_survey_alt __attribute__((unused)), float *_duration __attribute__((unused)), uint8_t *_index __attribute__((unused))) {}

#endif // DOWNLINK


/** Getter for field ac_id in message MISSION_SURVEY
  *
  * @param _payload : a pointer to the MISSION_SURVEY message
  * @return 
  */
static inline uint8_t pprzlink_get_DL_MISSION_SURVEY_ac_id(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_uint8_t(_payload, 4);
}


/** Getter for field insert in message MISSION_SURVEY
  *
  * @param _payload : a pointer to the MISSION_SURVEY message
  * @return 
  */
static inline uint8_t pprzlink_get_DL_MISSION_SURVEY_insert(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_uint8_t(_payload, 5);
}


/** Getter for field survey_east_1 in message MISSION_SURVEY
  *
  * @param _payload : a pointer to the MISSION_SURVEY message
  * @return 
  */
static inline float pprzlink_get_DL_MISSION_SURVEY_survey_east_1(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 6);
}


/** Getter for field survey_north_1 in message MISSION_SURVEY
  *
  * @param _payload : a pointer to the MISSION_SURVEY message
  * @return 
  */
static inline float pprzlink_get_DL_MISSION_SURVEY_survey_north_1(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 10);
}


/** Getter for field survey_east_2 in message MISSION_SURVEY
  *
  * @param _payload : a pointer to the MISSION_SURVEY message
  * @return 
  */
static inline float pprzlink_get_DL_MISSION_SURVEY_survey_east_2(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 14);
}


/** Getter for field survey_north_2 in message MISSION_SURVEY
  *
  * @param _payload : a pointer to the MISSION_SURVEY message
  * @return 
  */
static inline float pprzlink_get_DL_MISSION_SURVEY_survey_north_2(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 18);
}


/** Getter for field survey_alt in message MISSION_SURVEY
  *
  * @param _payload : a pointer to the MISSION_SURVEY message
  * @return altitude above geoid (MSL)
  */
static inline float pprzlink_get_DL_MISSION_SURVEY_survey_alt(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 22);
}


/** Getter for field duration in message MISSION_SURVEY
  *
  * @param _payload : a pointer to the MISSION_SURVEY message
  * @return 
  */
static inline float pprzlink_get_DL_MISSION_SURVEY_duration(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 26);
}


/** Getter for field index in message MISSION_SURVEY
  *
  * @param _payload : a pointer to the MISSION_SURVEY message
  * @return 
  */
static inline uint8_t pprzlink_get_DL_MISSION_SURVEY_index(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_uint8_t(_payload, 30);
}


/* Compatibility macros */
#define DL_MISSION_SURVEY_ac_id(_payload) pprzlink_get_DL_MISSION_SURVEY_ac_id(_payload)
#define DL_MISSION_SURVEY_insert(_payload) pprzlink_get_DL_MISSION_SURVEY_insert(_payload)
#define DL_MISSION_SURVEY_survey_east_1(_payload) pprzlink_get_DL_MISSION_SURVEY_survey_east_1(_payload)
#define DL_MISSION_SURVEY_survey_north_1(_payload) pprzlink_get_DL_MISSION_SURVEY_survey_north_1(_payload)
#define DL_MISSION_SURVEY_survey_east_2(_payload) pprzlink_get_DL_MISSION_SURVEY_survey_east_2(_payload)
#define DL_MISSION_SURVEY_survey_north_2(_payload) pprzlink_get_DL_MISSION_SURVEY_survey_north_2(_payload)
#define DL_MISSION_SURVEY_survey_alt(_payload) pprzlink_get_DL_MISSION_SURVEY_survey_alt(_payload)
#define DL_MISSION_SURVEY_duration(_payload) pprzlink_get_DL_MISSION_SURVEY_duration(_payload)
#define DL_MISSION_SURVEY_index(_payload) pprzlink_get_DL_MISSION_SURVEY_index(_payload)



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _VAR_MESSAGES_datalink_MISSION_SURVEY_H_
