#ifndef DRIVER_UDP_RECEIVE_H
#define DRIVER_UDP_RECEIVE_H


#ifndef GENERIC_TARGET_IMPLEMENTATION
#include <cstdint>
#endif


/**
 *  @brief Create the UDP receive driver.
 *  @param [in] port The port of this UDP socket.
 *  @param [in] ipInterface The interface that should be used. If the interface is set to [0;0;0;0] then the default interface will be used.
 *  @param [in] rxBufferSize The size of the receive buffer.
 *  @param [in] prioritySocket Socket priority, range: [0, 6].
 *  @param [in] priorityThread Receiver thread priority, range: [0, 99].
 *  @param [in] numBuffers Number of receive buffers to be used.
 *  @param [in] bufferStrategy Either 0 (DISCARD_OLDEST) or 1 (DISCARD_RECEIVED). Unknown values are ignored.
 */
extern void CreateDriverUDPReceive(uint16_t port, uint8_t* ipInterface, uint32_t rxBufferSize, int32_t prioritySocket, int32_t priorityThread, const uint32_t numBuffers, const uint32_t bufferStrategy);

/**
 *  @brief Delete the UDP receive driver.
 */
extern void DeleteDriverUDPReceive(void);

/**
 *  @brief Fetch all messages from the receive buffer of a socket.
 *  @param [in] port The local port of the UDP socket that should be used.
 *  @param [in] rxBufferSize The maximum length for one message that can be stored in the output.
 *  @param [in] maxNumMessages The maximum number of messages that can be stored in the output.
 *  @param [out] sources The sources of dimension [5*NUM_BUFFER], where indices [offset,offset+1,offset+2,offset+3] indicate the source IPv4 address and index [offset+4] indicates the source port.
 *  @param [out] bytes Array where to store the bytes. The array must be of dimension (maxMessageSize * maxNumMessages).
 *  @param [out] lengths Length for each received message.
 *  @param [out] timestamps The timestamps for each message (seconds) when the corresponding message has been received.
 *  @param [out] numMessagesReceived The number of messages that have been received/written to the output.
 *  @param [out] numMessagesDiscarded The number of messages that have been discarded.
 *  @details After this operations the whole FIFO is cleared, that is the index lists are cleared and the lengths are reset to zero, however the bytes of the buffer, timestamps, sources are not reset (the length indicates a valid message).
 */
extern void OutputDriverUDPReceive(uint16_t port, uint32_t rxBufferSize, uint32_t maxNumMessages, uint16_t* sources, uint8_t* bytes, uint32_t* lengths, double* timestamps, uint32_t* numMessagesReceived, uint32_t* numMessagesDiscarded);


#endif /* DRIVER_UDP_RECEIVE_H */

