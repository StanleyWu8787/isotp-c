#include <isotp.h>
#include "gtest/gtest.h"

#define ISOTP_BUFSIZE 1024

/* ==================== Mock function and variable start ==================== */

/* Alloc IsoTpLink statically in RAM */
static IsoTpLink g_link;

/* Alloc send and receive buffer statically in RAM */
static uint8_t g_isotpRecvBuf[ISOTP_BUFSIZE];
static uint8_t g_isotpSendBuf[ISOTP_BUFSIZE];


/* 
 * required, this must send a single CAN message with the given arbitration
 * ID (i.e. the CAN message ID) and data. The size will never be more than 8
 * bytes. Should return ISOTP_RET_OK if frame sent successfully.
 * May return ISOTP_RET_NOSPACE if the frame could not be sent but may be
 * retried later. Should return ISOTP_RET_ERROR in case frame could not be sent.
 */
int  isotp_user_send_can(const uint32_t arbitration_id,
                            const uint8_t* data, const uint8_t size) {
    return 0;
}

/* required, return system tick, unit is micro-second */
uint32_t isotp_user_get_us(void) {
    static uint32_t time = 0;
    time += 1;
    return time;
}

/* optional, provide to receive debugging log messages */
void isotp_user_debug(const char* message, ...) {
    printf("%s\n", message);
}

/* ==================== Mock function and variable end ==================== */


class IsotpTest : public testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  IsotpTest() {
     // You can do set-up work for each test here.
  }

  ~IsotpTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
     isotp_init_link(&g_link, 0x7,
                    g_isotpSendBuf, sizeof(g_isotpSendBuf), 
                    g_isotpRecvBuf, sizeof(g_isotpRecvBuf));
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
     memset(g_isotpSendBuf, 0, sizeof(g_isotpSendBuf));
     memset(g_isotpRecvBuf, 0, sizeof(g_isotpRecvBuf));
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests factorial of 0.
TEST(IsotpTest, HandlesZeroInput) {
  EXPECT_EQ(1, 1);
}

// Tests factorial of positive numbers.
TEST(IsotpTest, HandlesPositiveInput) {
  EXPECT_EQ(1, 1);
  EXPECT_EQ(2, 2);
  EXPECT_EQ(3, 3);
  EXPECT_EQ(8, 8);
}


// Example code:
// int main(void) {
//     /* Initialize CAN and other peripherals */
//     int ret;
    
//     /* Initialize link, 0x7TT is the CAN ID you send with */
//     isotp_init_link(&g_link, 0x7,
//                     g_isotpSendBuf, sizeof(g_isotpSendBuf), 
//                     g_isotpRecvBuf, sizeof(g_isotpRecvBuf));
    
//     while(1) {
    
//         /* If receive any interested can message, call isotp_on_can_message to handle message */
//         ret = can_receive(&id, &data, &len);
        
//         /* 0x7RR is CAN ID you want to receive */
//         if (RET_OK == ret && 0x7 == id) {
//             isotp_on_can_message(&g_link, data, len);
//         }
        
//         /* Poll link to handle multiple frame transmition */
//         isotp_poll(&g_link);
        
//         /* You can receive message with isotp_receive.
//             payload is upper layer message buffer, usually UDS;
//             payload_size is payload buffer size;
//             out_size is the actuall read size;
//             */
//         ret = isotp_receive(&g_link, payload, payload_size, &out_size);
//         if (ISOTP_RET_OK == ret) {
//             /* Handle received message */
//         }
        
//         /* And send message with isotp_send */
//         ret = isotp_send(&g_link, payload, payload_size);
//         if (ISOTP_RET_OK == ret) {
//             /* Send ok */
//         } else {
//             /* An error occured */
//         }
        
//         /* In case you want to send data w/ functional addressing, use isotp_send_with_id */
//         ret = isotp_send_with_id(&g_link, 0x7df, payload, payload_size);
//         if (ISOTP_RET_OK == ret) {
//             /* Send ok */
//         } else {
//             /* Error occur */
//         }
//     }

//     return;
// }