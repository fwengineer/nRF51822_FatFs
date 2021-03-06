/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#ifndef HAL_NFC_H__
#define HAL_NFC_H__

/** @file
 * @defgroup nfc_hal NFC Type 2 Tag HAL
 * @{
 * @ingroup nfc_library
 * @brief @tagAPI52 Hardware abstraction layer for the NFC Type 2 Tag library.
 *
 */

#include <stdint.h>
#include <string.h> /* Accessing the size_t type */

/** @brief Return values generated by HAL_NFC functions. */
typedef enum {
  HAL_NFC_RETVAL_OK,
  HAL_NFC_RETVAL_ERROR,
  HAL_NFC_RETVAL_INVALID_SIZE,
  HAL_NFC_RETVAL_TIMEOUT
} hal_nfc_retval;

/** @brief Events passed to upper-layer callback function. */
typedef enum {
  HAL_NFC_EVENT_FIELD_ON,
  HAL_NFC_EVENT_FIELD_OFF,
  HAL_NFC_EVENT_DATA_RECEIVED,
  HAL_NFC_EVENT_DATA_TRANSMITTED
} hal_nfc_event;

/** @brief Parameter IDs for set/get function. */
typedef enum {
  HAL_NFC_PARAM_ID_TESTING,
  HAL_NFC_PARAM_ID_UNKNOWN
} hal_nfc_param_id;


/** \brief Callback from HAL_NFC layer into upper layer.
  *
  * If event == HAL_NFC_EVENT_DATA_RECEIVED:
  * data points to the received packet. The memory belongs to the HAL_NFC layer and
  * is guaranteed to be valid only until the callback returns.
  *
  * If event == HAL_NFC_EVENT_DATA_TRANSMITTED:
  * data points to the transmitted packet. The memory belongs to the application.
  *
  * If event == \<Other event\>:
  * data definition is event-specific (to be defined).
  *
  * \param context    Context for callback execution.
  * \param event      The event that occurred.
  * \param data       Received/transmitted data or NULL.
  * \param dataLength Size of the received/transmitted packet.
  */
typedef void (*hal_nfc_callback)(void *context, hal_nfc_event event, const char *data, size_t dataLength);

/** \brief Function for initializing the NFC layer.
  *
  * This function provides a pointer to a callback function and the callback context
  * to the NFC layer.
  *
  * \param callback  Pointer to the callback function.
  * \param cbContext Context of callback.
  *
  * \retval OK If the NFC layer was initialized successfully.  If one 
  *            of the arguments was invalid, an error code is returned.
  */
hal_nfc_retval hal_nfc_setup(hal_nfc_callback callback, void *cbContext);

/** \brief Function for setting a HAL_NFC parameter.
  *
  * This function allows to set any parameter defined as available by HAL_NFC.
  *
  * \param id         ID of the parameter to set.
  * \param data       Pointer to a buffer containing the data to set.
  * \param dataLength Size of the buffer containing the data to set.
  *
  * \retval OK If the parameter was set successfully. If one of the arguments
  *            was invalid (for example, a wrong data length), an error code
  *            is returned.
  */
hal_nfc_retval hal_nfc_set_parameter(hal_nfc_param_id id, void *data, size_t dataLength);


/** \brief Function for querying a HAL_NFC parameter value.
  *
  * The queried value will be placed into the passed data buffer. If the buffer
  * is too small, maxDataLength will contain the required buffer size.
  *
  * \param id         ID of the parameter to query.
  * \param data       Pointer to a buffer receiving the queried data.
  * \param maxDataLength Size of the buffer, receives needed size if buffer is too small.
  *
  * \retval OK If the parameter was received successfully. If one of the arguments
  *            was invalid (for example, the buffer was too small), an error code
  *            is returned.
  */
hal_nfc_retval hal_nfc_get_parameter(hal_nfc_param_id id, void *data, size_t *maxDataLength);

/** \brief Function for starting the NFC subsystem.
  *
  * After this function completes, NFC readers will be able to detect the chip.
  *
  * \retval OK If the NFC subsystem was started successfully. If the NFC 
  *            subsystem could not be started, an error code is returned.
  */
hal_nfc_retval hal_nfc_start(void);


/** \brief Function for sending a packet to the connected NFC reader.
  *
  * The provided data buffer belongs to the caller and is guaranteed to be
  * valid until the HAL_NFC_EVENT_DATA_TRANSMITTED event is received by the
  * callback.
  *
  * \param data       The data packet to send.
  * \param dataLength Size of the packet in bytes.
  *
  * \retval OK If the packet was sent. Otherwise, an error code is returned.
  */
hal_nfc_retval hal_nfc_send(const char *data, size_t dataLength);

/** \brief Function for stopping the NFC subsystem.
  *
  * After this function returns, NFC readers will no longer be able to connect
  * to the chip.
  *
  * \retval OK If the NFC subsystem was stopped. Otherwise, an error code
  *            is returned.
  */
hal_nfc_retval hal_nfc_stop(void);

/** \brief Function for releasing resources.
  *
  * After this call returns, the callback is considered invalid and no more
  * events will be posted to it.
  *
  * \retval OK This function always succeeds.
  */
hal_nfc_retval hal_nfc_done(void);

/** @} */
#endif /* HAL_NFC_H__ */

