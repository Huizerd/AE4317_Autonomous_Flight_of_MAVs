/** @file
 *  @brief PPRZLink message header for DCF in class telemetry
 *
 *  Telemetry message for monitoring the status of the Distributed Circular Formation.
 *  @see http://paparazziuav.org
 */

#ifndef _VAR_MESSAGES_telemetry_DCF_H_
#define _VAR_MESSAGES_telemetry_DCF_H_


#include "pprzlink/pprzlink_device.h"
#include "pprzlink/pprzlink_transport.h"
#include "pprzlink/pprzlink_utils.h"
#include "pprzlink/pprzlink_message.h"


#ifdef __cplusplus
extern "C" {
#endif

#if DOWNLINK

#define DL_DCF 40
#define PPRZ_MSG_ID_DCF 40

/**
 * Macro that redirect calls to the default version of pprzlink API
 * Used for compatibility between versions.
 */
#define pprzlink_msg_send_DCF _send_msg(DCF,PPRZLINK_DEFAULT_VER)

/**
 * Sends a DCF message (API V2.0 version)
 *
 * @param msg the pprzlink_msg structure for this message
 * @param nb_table,_table  The size of the array is 4 x (maximum number of possible neighbors). The elements per each neighbor are: 1. ID of the neighbor, 2. Theta of the neighbor (degrees x 100), 3. Desired inter-vehicle angle (degrees x 100), 4. Last time in ms we received a msg from the neighbor
 * @param nb_errors,_errors  The size of the array is the maximum number of possible neighbors. Errors w.r.t. desired inter-vehicle angles (degrees x 100)
 */
static inline void pprzlink_msg_v2_send_DCF(struct pprzlink_msg * msg, uint8_t nb_table, int16_t *_table, uint8_t nb_errors, int16_t *_errors) {
#if PPRZLINK_ENABLE_FD
  long _FD = 0; /* can be an address, an index, a file descriptor, ... */
#endif
  const uint8_t size = msg->trans->size_of(msg, /* msg header overhead */4+1+nb_table*2+1+nb_errors*2);
  if (msg->trans->check_available_space(msg, _FD_ADDR, size)) {
    msg->trans->count_bytes(msg, size);
    msg->trans->start_message(msg, _FD, /* msg header overhead */4+1+nb_table*2+1+nb_errors*2);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, &(msg->sender_id), 1);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, msg->receiver_id, NULL);
    uint8_t comp_class = (msg->component_id & 0x0F) << 4 | (1 & 0x0F);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, comp_class, NULL);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, DL_DCF, "DCF");
    msg->trans->put_bytes(msg, _FD, DL_TYPE_ARRAY_LENGTH, DL_FORMAT_SCALAR, (void *) &nb_table, 1);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_INT16, DL_FORMAT_ARRAY, (void *) _table, nb_table*2);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_ARRAY_LENGTH, DL_FORMAT_SCALAR, (void *) &nb_errors, 1);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_INT16, DL_FORMAT_ARRAY, (void *) _errors, nb_errors*2);
    msg->trans->end_message(msg, _FD);
  } else
        msg->trans->overrun(msg);
}

// Compatibility with the protocol v1.0 API
#define pprzlink_msg_v1_send_DCF pprz_msg_send_DCF
#define DOWNLINK_SEND_DCF(_trans, _dev, nb_table, table, nb_errors, errors) pprz_msg_send_DCF(&((_trans).trans_tx), &((_dev).device), AC_ID, nb_table, table, nb_errors, errors)
/**
 * Sends a DCF message (API V1.0 version)
 *
 * @param trans A pointer to the transport_tx structure used for sending the message
 * @param dev A pointer to the link_device structure through which the message will be sent
 * @param ac_id The id of the sender of the message
 * @param nb_table,_table  The size of the array is 4 x (maximum number of possible neighbors). The elements per each neighbor are: 1. ID of the neighbor, 2. Theta of the neighbor (degrees x 100), 3. Desired inter-vehicle angle (degrees x 100), 4. Last time in ms we received a msg from the neighbor
 * @param nb_errors,_errors  The size of the array is the maximum number of possible neighbors. Errors w.r.t. desired inter-vehicle angles (degrees x 100)
 */
static inline void pprz_msg_send_DCF(struct transport_tx *trans, struct link_device *dev, uint8_t ac_id, uint8_t nb_table, int16_t *_table, uint8_t nb_errors, int16_t *_errors) {
    struct pprzlink_msg msg;
    msg.trans = trans;
    msg.dev = dev;
    msg.sender_id = ac_id;
    msg.receiver_id = 0;
    msg.component_id = 0;
    pprzlink_msg_v2_send_DCF(&msg,nb_table,_table,nb_errors,_errors);
}


#else // DOWNLINK

#define DOWNLINK_SEND_DCF(_trans, _dev, nb_table, table, nb_errors, errors) {}
static inline void pprz_send_msg_DCF(struct transport_tx *trans __attribute__((unused)), struct link_device *dev __attribute__((unused)), uint8_t ac_id __attribute__((unused)), uint8_t nb_table __attribute__((unused)), int16_t *_table __attribute__((unused)), uint8_t nb_errors __attribute__((unused)), int16_t *_errors __attribute__((unused))) {}

#endif // DOWNLINK

/** Getter for length of array table in message DCF
 *
 * @return table :  The size of the array is 4 x (maximum number of possible neighbors). The elements per each neighbor are: 1. ID of the neighbor, 2. Theta of the neighbor (degrees x 100), 3. Desired inter-vehicle angle (degrees x 100), 4. Last time in ms we received a msg from the neighbor
 */
 static inline uint8_t pprzlink_get_DCF_table_length(__attribute__ ((unused)) void* _payload) {
    return _PPRZ_VAL_len_aligned(_payload, 4);
}

/** Getter for field table in message DCF
  *
  * @param _payload : a pointer to the DCF message
  * @return  The size of the array is 4 x (maximum number of possible neighbors). The elements per each neighbor are: 1. ID of the neighbor, 2. Theta of the neighbor (degrees x 100), 3. Desired inter-vehicle angle (degrees x 100), 4. Last time in ms we received a msg from the neighbor
  */
static inline int16_t * pprzlink_get_DL_DCF_table(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_int16_t_array(_payload, 5);
}

/** Getter for length of array errors in message DCF
 *
 * @return errors :  The size of the array is the maximum number of possible neighbors. Errors w.r.t. desired inter-vehicle angles (degrees x 100)
 */
 static inline uint8_t pprzlink_get_DCF_errors_length(void* _payload) {
    return _PPRZ_VAL_uint8_t(_payload, 5);
}

/** Getter for field errors in message DCF
  *
  * @param _payload : a pointer to the DCF message
  * @return  The size of the array is the maximum number of possible neighbors. Errors w.r.t. desired inter-vehicle angles (degrees x 100)
  */
static inline int16_t * pprzlink_get_DL_DCF_errors(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_int16_t_array(_payload, 6);
}


/* Compatibility macros */
#define DL_DCF_table_length(_payload) pprzlink_get_DCF_table_length(_payload)
#define DL_DCF_table(_payload) pprzlink_get_DL_DCF_table(_payload)
#define DL_DCF_errors_length(_payload) pprzlink_get_DCF_errors_length(_payload)
#define DL_DCF_errors(_payload) pprzlink_get_DL_DCF_errors(_payload)



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _VAR_MESSAGES_telemetry_DCF_H_
