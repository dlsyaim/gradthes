#pragma once
/*
 * This header file holds up all the user defined message types
 */
/* This message is sent from the protocol parser to the communication test dialog */
#define COMMUNICATION_TEST_REPLY_MSG WM_USER + 300
/* This message is sent from the protocol parser to the opt test form view */
#define OPT_TEST_REPLY_MSG WM_USER + 301
/* This message is sent from the protocol parser to the IMU test form view */
#define IMU_TEST_REPLY_MSG WM_USER + 302
/* This message is sent from the protocol parser to the Path set view */
#define LOAD_POINT_REPLY_MSG WM_USER + 303
/* This message is sent from the protocol parser to the Path set view */
#define PATH_CHECK_REPLY_MSG WM_USER + 304

/* This message is sent from the protoocl parser to the Left view */
#define START_TASK_REPLY_MSG WM_USER + 305
#define STOP_TASK_REPLY_MSG WM_USER + 306
#define FLYING_STATE_DATA_MSG WM_USER + 307

/* Message indicates instruction parsering error */
#define ERROR_INSTRUCTION WM_USER + 308