//
// Created by idan on 1/11/24.
//

#ifndef ROOTKIT_OPERATIONS_PROTOCOL_H
#define ROOTKIT_OPERATIONS_PROTOCOL_H

// more usages for the kernel module can be added to the protocol

#define OPER_ID short

#define OPER_EXIT_MODULE ((OPER_ID) (-1))

#define OPER_ADD_HIDDEN_PATH ((OPER_ID) 1)
#define OPER_REMOVE_HIDDEN_PATH ((OPER_ID) 2)

#define PORT int
#define OPER_ADD_HIDDEN_TCP4_PORT ((OPER_ID) 3)
#define OPER_REMOVE_HIDDEN_TCP4_PORT ((OPER_ID) 4)
#define OPER_ADD_HIDDEN_TCP6_PORT ((OPER_ID) 5)
#define OPER_REMOVE_HIDDEN_TCP6_PORT ((OPER_ID) 6)

#endif //ROOTKIT_OPERATIONS_PROTOCOL_H
