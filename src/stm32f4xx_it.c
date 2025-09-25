#include "main.h"

extern UART_HandleTypeDef huart2;

void SysTick_Handler(void)
{
  HAL_IncTick();
  
  /* FreeRTOS will handle SysTick via xPortSysTickHandler - don't call it here */
}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart2);
}