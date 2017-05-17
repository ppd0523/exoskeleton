/*---------------------------- Inlcude ---------------------------------------*/
#include <CoOS.h>			              /*!< CoOS header file	         */
#include "usart_rxtx.h"
#include "gpio_led.h"
/*---------------------------- Symbol Define -------------------------------*/
#define STACK_SIZE_TASKA 128              /*!< Define "taskA" task size */
#define STACK_SIZE_TASKB 128              /*!< Define "taskB" task size */
#define STACK_SIZE_TASKC 128              /*!< Define "taskC" task size */

/*---------------------------- Variable Define -------------------------------*/
OS_STK taskA_stk[STACK_SIZE_TASKA]; /*!< Define "taskA" task stack */
OS_STK taskB_stk[STACK_SIZE_TASKB]; /*!< Define "taskB" task stack */
OS_STK taskC_stk[STACK_SIZE_TASKC]; /*!< Define "taskC" task stack */

OS_FlagID flagID;

/**
 *******************************************************************************
 * @brief       "taskA" task code
 * @param[in]   None
 * @param[out]  None
 * @retval      None
 * @par Description
 * @details    This task use to crate mutex and flags,print message "taskA running".
 *             Indicate "taskA" had been executed.
 *******************************************************************************
 */

void taskA(void* pdata) {
	flagID = CoCreateFlag(0, 0);
	for (;;) {

		UARTSend("BBB\r\n", 5);
		CoTickDelay(50);
	}
}

/**
 *******************************************************************************
 * @brief       "taskB" task code
 * @param[in]   None
 * @param[out]  None
 * @retval      None
 * @par Description
 * @details    This task use to print message "taskB running". Indicate "taskB"
 *             had been executed.
 *******************************************************************************
 */
void taskB(void* pdata) {
	StatusType result;
	for (;;) {

		led_toggle();
		CoTickDelay(100);
	}
}

/**
 *******************************************************************************
 * @brief       "led" task code
 * @param[in]   None
 * @param[out]  None
 * @retval      None
 * @par Description
 * @details    This function use to blink led,and set flag for "taskA" and "taskB".
 *******************************************************************************
 */
void taskC(void* pdata) {


	for (;;) {
		CoTickDelay(100);
	}
}

/**
 *******************************************************************************
 * @brief		main function
 * @param[in] 	None
 * @param[out] 	None
 * @retval		None
 *******************************************************************************
 */
int main() {
	CoInitOS(); /*!< Initial CooCox CoOS          */
	usart_init();
	gpio_init();

	UARTSend("Hello world\r\n", 13);

	/*!< Create three tasks	*/
	CoCreateTask(taskA, 0, 0, &taskA_stk[STACK_SIZE_TASKA-1], STACK_SIZE_TASKA);
	CoCreateTask(taskB, 0, 1, &taskB_stk[STACK_SIZE_TASKB-1], STACK_SIZE_TASKB);
	//CoCreateTask(taskC, 0, 2, &taskC_stk[STACK_SIZE_TASKC-1], STACK_SIZE_TASKC);
	CoStartOS(); /*!< Start multitask	           */

	while (1)
		; /*!< The code don''t reach here	   */
}
