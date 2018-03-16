/** @file
 *  @brief PPRZLink message header for ACINFO_LLA in class datalink
 *
 *  
 *  @see http://paparazziuav.org
 */

#ifndef _VAR_MESSAGES_datalink_ACINFO_LLA_H_
#define _VAR_MESSAGES_datalink_ACINFO_LLA_H_


#include "pprzlink/pprzlink_device.h"
#include "pprzlink/pprzlink_transport.h"
#include "pprzlink/pprzlink_utils.h"
#include "pprzlink/pprzlink_message.h"


#ifdef __cplusplus
extern "C" {
#endif

#if DOWNLINK

#define DL_ACINFO_LLA 14
#define PPRZ_MSG_ID_ACINFO_LLA 14

/**
 * Macro that redirect calls to the default version of pprzlink API
 * Used for compatibility between versions.
 */
#define pprzlink_msg_send_ACINFO_LLA _send_msg(ACINFO_LLA,PPRZLINK_DEFAULT_VER)

/**
 * Sends a ACINFO_LLA message (API V2.0 version)
 *
 * @param msg the pprzlink_msg structure for this message
 * @param _course 
 * @param _lat 
 * @param _lon 
 * @param _alt Height above ellipsoid
 * @param _itow 
 * @param _speed ground speed
 * @param _climb 
 * @param _ac_id 
 */
static inline void pprzlink_msg_v2_send_ACINFO_LLA(struct pprzlink_msg * msg, int16_t *_course, int32_t *_lat, int32_t *_lon, int32_t *_alt, uint32_t *_itow, uint16_t *_speed, int16_t *_climb, uint8_t *_ac_id) {
#if PPRZLINK_ENABLE_FD
  long _FD = 0; /* can be an address, an index, a file descriptor, ... */
#endif
  const uint8_t size = msg->trans->size_of(msg, /* msg header overhead */4+2+4+4+4+4+2+2+1);
  if (msg->trans->check_available_space(msg, _FD_ADDR, size)) {
    msg->trans->count_bytes(msg, size);
    msg->trans->start_message(msg, _FD, /* msg header overhead */4+2+4+4+4+4+2+2+1);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, &(msg->sender_id), 1);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, msg->receiver_id, NULL);
    uint8_t comp_class = (msg->component_id & 0x0F) << 4 | (2 & 0x0F);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, comp_class, NULL);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, DL_ACINFO_LLA, "ACINFO_LLA");
    msg->trans->put_bytes(msg, _FD, DL_TYPE_INT16, DL_FORMAT_SCALAR, (void *) _course, 2);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_INT32, DL_FORMAT_SCALAR, (void *) _lat, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_INT32, DL_FORMAT_SCALAR, (void *) _lon, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_INT32, DL_FORMAT_SCALAR, (void *) _alt, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT32, DL_FORMAT_SCALAR, (void *) _itow, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT16, DL_FORMAT_SCALAR, (void *) _speed, 2);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_INT16, DL_FORMAT_SCALAR, (void *) _climb, 2);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, (void *) _ac_id, 1);
    msg->trans->end_message(msg, _FD);
  } else
        msg->trans->overrun(msg);
}

// Compatibility with the protocol v1.0 API
#define pprzlink_msg_v1_send_ACINFO_LLA pprz_msg_send_ACINFO_LLA
#define DOWNLINK_SEND_ACINFO_LLA(_trans, _dev, course, lat, lon, alt, itow, speed, climb, ac_id) pprz_msg_send_ACINFO_LLA(&((_trans).trans_tx), &((_dev).device), AC_ID, course, lat, lon, alt, itow, speed, climb, ac_id)
/**
 * Sends a ACINFO_LLA message (API V1.0 version)
 *
 * @param trans A pointer to the transport_tx structure used for sending the message
 * @param dev A pointer to the link_device structure through which the message will be sent
 * @param ac_id The id of the sender of the message
 * @param _course 
 * @param _lat 
 * @param _lon 
 * @param _alt Height above ellipsoid
 * @param _itow 
 * @param _speed ground speed
 * @param _climb 
 * @param _ac_id 
 */
static inline void pprz_msg_send_ACINFO_LLA(struct transport_tx *trans, struct link_device *dev, uint8_t ac_id, int16_t *_course, int32_t *_lat, int32_t *_lon, int32_t *_alt, uint32_t *_itow, uint16_t *_speed, int16_t *_climb, uint8_t *_ac_id) {
    struct pprzlink_msg msg;
    msg.trans = trans;
    msg.dev = dev;
    msg.sender_id = ac_id;
    msg.receiver_id = 0;
    msg.component_id = 0;
    pprzlink_msg_v2_send_ACINFO_LLA(&msg,_course,_lat,_lon,_alt,_itow,_speed,_climb,_ac_id);
}


#else // DOWNLINK

#define DOWNLINK_SEND_ACINFO_LLA(_trans, _dev, course, lat, lon, alt, itow, speed, climb, ac_id) {}
static inline void pprz_send_msg_ACINFO_LLA(struct transport_tx *trans __attribute__((unused)), struct link_device *dev __attribute__((unused)), uint8_t ac_id __attribute__((unused)), int16_t *_course __attribute__((unused)), int32_t *_lat __attribute__((unused)), int32_t *_lon __attribute__((unused)), int32_t *_alt __attribute__((unused)), uint32_t *_itow __attribute__((unused)), uint16_t *_speed __attribute__((unused)), int16_t *_climb __attribute__((unused)), uint8_t *_ac_id __attribute__((unused))) {}

#endif // DOWNLINK


/** Getter for field course in message ACINFO_LLA
  *
  * @param _payload : a pointer to the ACINFO_LLA message
  * @return 
  */
static inline int16_t pprzlink_get_DL_ACINFO_LLA_course(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_int16_t(_payload, 4);
}


/** Getter for field lat in message ACINFO_LLA
  *
  * @param _payload : a pointer to the ACINFO_LLA message
  * @return 
  */
static inline int32_t pprzlink_get_DL_ACINFO_LLA_lat(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_int32_t(_payload, 6);
}


/** Getter for field lon in message ACINFO_LLA
  *
  * @param _payload : a pointer to the ACINFO_LLA message
  * @return 
  */
static inline int32_t pprzlink_get_DL_ACINFO_LLA_lon(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_int32_t(_payload, 10);
}


/** Getter for field alt in message ACINFO_LLA
  *
  * @param _payload : a pointer to the ACINFO_LLA message
  * @return Height above ellipsoid
  */
static inline int32_t pprzlink_get_DL_ACINFO_LLA_alt(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_int32_t(_payload, 14);
}


/** Getter for field itow in message ACINFO_LLA
  *
  * @param _payload : a pointer to the ACINFO_LLA message
  * @return 
  */
static inline uint32_t pprzlink_get_DL_ACINFO_LLA_itow(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_uint32_t(_payload, 18);
}


/** Getter for field speed in message ACINFO_LLA
  *
  * @param _payload : a pointer to the ACINFO_LLA message
  * @return ground speed
  */
static inline uint16_t pprzlink_get_DL_ACINFO_LLA_speed(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_uint16_t(_payload, 22);
}


/** Getter for field climb in message ACINFO_LLA
  *
  * @param _payload : a pointer to the ACINFO_LLA message
  * @return 
  */
static inline int16_t pprzlink_get_DL_ACINFO_LLA_climb(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_int16_t(_payload, 24);
}


/** Getter for field ac_id in message ACINFO_LLA
  *
  * @param _payload : a pointer to the ACINFO_LLA message
  * @return 
  */
static inline uint8_t pprzlink_get_DL_ACINFO_LLA_ac_id(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_uint8_t(_payload, 26);
}


/* Compatibility macros */
#define DL_ACINFO_LLA_course(_payload) pprzlink_get_DL_ACINFO_LLA_course(_payload)
#define DL_ACINFO_LLA_lat(_payload) pprzlink_get_DL_ACINFO_LLA_lat(_payload)
#define DL_ACINFO_LLA_lon(_payload) pprzlink_get_DL_ACINFO_LLA_lon(_payload)
#define DL_ACINFO_LLA_alt(_payload) pprzlink_get_DL_ACINFO_LLA_alt(_payload)
#define DL_ACINFO_LLA_itow(_payload) pprzlink_get_DL_ACINFO_LLA_itow(_payload)
#define DL_ACINFO_LLA_speed(_payload) pprzlink_get_DL_ACINFO_LLA_speed(_payload)
#define DL_ACINFO_LLA_climb(_payload) pprzlink_get_DL_ACINFO_LLA_climb(_payload)
#define DL_ACINFO_LLA_ac_id(_payload) pprzlink_get_DL_ACINFO_LLA_ac_id(_payload)



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _VAR_MESSAGES_datalink_ACINFO_LLA_H_
