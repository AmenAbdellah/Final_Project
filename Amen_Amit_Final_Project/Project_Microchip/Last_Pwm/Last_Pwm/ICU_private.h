/****************************************/
/*          Author: Amen Abdellah       */        
/*          Version: 1.0                */
/*          Module: ICU                 */
/****************************************/

#ifndef ICU_PRIVATE_H_
#define ICU_PRIVATE_H_


#define TIMSK  *((volatile u8 *)0x59)
#define ACSR   *((volatile u8 *)0x28)
#define TCCR1A *((volatile u8 *)0x4F)
#define TCCR1B *((volatile u8 *)0x4E)
#define ICR1L   *((volatile u8 *)0x46)
#define ICR1H   *((volatile u8 *)0x47)

#endif