/****************************************/
/*          Author: Amen Abdellah       */        
/*          Version: 1.0                */
/*          Module: ICU                 */
/****************************************/

#ifndef ICU_INT_H_
#define ICU_INT_H_

void ICU_voidInit(void);
void ICU_voidSetICUCallBack(void (*Copy_ptr) (void) ) ;
void ICU_IntEnable(void);
void ICU_IntDisable(void);


#endif