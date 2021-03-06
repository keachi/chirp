// ======
// Errors
// ======
//
// ..todo:: Document purpose
//
// .. code-block:: cpp

#ifndef ch_libchirp_error_h
#define ch_libchirp_error_h

// .. c:type:: ch_error_t
//
//    Represents a chirp error.
//
//    .. c:member:: CH_SUCCESS
//
//       No error.
//
//    .. c:member:: CH_VALUE_ERROR
//
//       Supplied value is not allowed.
//
//    .. c:member:: CH_UV_ERROR
//
//       General libuv error.
//
//    .. c:member:: CH_PROTOCOL_ERROR
//
//       Happens when bad values are received or the remote dies unexpectedly.
//
//    .. c:member:: CH_EADDRINUSE
//
//       The chirp port is already in use.
//
//    .. c:member:: CH_FATAL
//
//       .. todo: List all fatal error cases.
//
//       * We do not have an entropy source
//
//    .. c:member:: CH_TLS_ERROR
//
//       General TLS error.
//
//    .. c:member:: CH_UNINIT
//
//       Chirp or another object is not initialized.
//
//    .. c:member:: CH_IN_PROGRESS
//
//       Action is already in progress.
//
//    .. c:member:: CH_TIMEOUT
//
//       A timeout happened during an action.
//
//    .. c:member:: CH_ENOMEM
//
//       Could not get memory. We consider this as totally fatal, but try to
//       handle it transparent for the user. We try to chain this error up to
//       the user, but often it might only be logged. In debug mode it is
//       asserted.
//
//    .. c:member:: CH_SHUTDOWN
//
//       Indicates that error occurred because chirp is shutting down. For
//       example the connection that is currently sending a message got closed.
//
//    .. c:member:: CH_CANNOT_CONNECT
//
//       Indicates that the remote has refused the connection or has timed out.
//
//    .. c:member:: CH_QUEUED
//
//       Indicates that the message as been placed in the send queue.
//
//    .. c:member:: CH_USED
//
//       Indicates that the message is already in use. The message will not be
//       sent.
//
// .. code-block:: cpp
//
typedef enum {
    CH_SUCCESS        = 0,
    CH_VALUE_ERROR    = 1,
    CH_UV_ERROR       = 2,
    CH_PROTOCOL_ERROR = 3,
    CH_EADDRINUSE     = 4,
    CH_FATAL          = 5,
    CH_TLS_ERROR      = 6,
    CH_UNINIT         = 7,
    CH_IN_PRORESS     = 8,
    CH_TIMEOUT        = 9,
    CH_ENOMEM         = 10,
    CH_SHUTDOWN       = 11,
    CH_CANNOT_CONNECT = 12,
    CH_QUEUED         = 13,
    CH_USED           = 14,
} ch_error_t;

#endif //ch_libchirp_error_h
