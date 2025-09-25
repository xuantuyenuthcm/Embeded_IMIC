#include "main.h"

// System Clock Configuration
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

// Pseudo-RTOS Task Functions
void GreenLED_Task(void);
void OrangeLED_Task(void);
void RedLED_Task(void);
void UART_Task(void);
void Button_Task(void);

// Hardware handles
UART_HandleTypeDef huart2;

// Pseudo-RTOS Task Control Blocks
typedef struct {
    uint32_t period;        // Task period in ms
    uint32_t last_run;      // Last execution time
    void (*task_func)(void); // Task function pointer
    uint8_t enabled;        // Task enable flag
} TaskControlBlock_t;

// Message Queue (simple array)
#define QUEUE_SIZE 10
char message_queue[QUEUE_SIZE][50];
uint8_t queue_head = 0;
uint8_t queue_tail = 0;
uint8_t queue_count = 0;

// UART Mutex (simple flag)
uint8_t uart_busy = 0;

// Simple string length function
int string_length(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Queue functions
uint8_t queue_send(const char* msg) {
    if(queue_count < QUEUE_SIZE) {
        for(int i = 0; i < 50 && msg[i] != '\0'; i++) {
            message_queue[queue_head][i] = msg[i];
        }
        queue_head = (queue_head + 1) % QUEUE_SIZE;
        queue_count++;
        return 1;
    }
    return 0;
}

uint8_t queue_receive(char* msg) {
    if(queue_count > 0) {
        for(int i = 0; i < 50; i++) {
            msg[i] = message_queue[queue_tail][i];
        }
        queue_tail = (queue_tail + 1) % QUEUE_SIZE;
        queue_count--;
        return 1;
    }
    return 0;
}

int main(void)
{
    // Reset of all peripherals, Initializes the Flash interface and the Systick
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize all configured peripherals
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    // Initialize Pseudo-RTOS Task Control Blocks
    TaskControlBlock_t tasks[] = {
        {1000, 0, GreenLED_Task, 1},   // Green LED - 1000ms period
        {1500, 0, OrangeLED_Task, 1},  // Orange LED - 1500ms period  
        {2000, 0, RedLED_Task, 1},     // Red LED - 2000ms period
        {100, 0, UART_Task, 1},        // UART Task - 100ms period
        {50, 0, Button_Task, 1}        // Button Task - 50ms period
    };
    
    uint8_t num_tasks = sizeof(tasks) / sizeof(TaskControlBlock_t);

    // Send startup message to queue
    queue_send("Pseudo-RTOS Started on STM32F411E-DISCO!\r\n");

    // Main Scheduler Loop
    while (1)
    {
        uint32_t current_time = HAL_GetTick();
        
        // Execute tasks based on their periods
        for(uint8_t i = 0; i < num_tasks; i++)
        {
            if(tasks[i].enabled && 
               (current_time - tasks[i].last_run >= tasks[i].period))
            {
                tasks[i].task_func();  // Execute task
                tasks[i].last_run = current_time;
            }
        }
        
        HAL_Delay(1);  // Small delay for system stability
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level - STM32F411E-DISCO LEDs */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); // LD4 Green
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET); // LD3 Orange  
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); // LD5 Red
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET); // LD6 Blue

    /*Configure GPIO pins : PD12 PD13 PD14 PD15 - STM32F411E-DISCO LEDs */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    /*Configure GPIO pin : PA0 - User Button */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PA2 PA3 */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}



/**
  * @brief Green LED Task - Toggles LD4 (PD12)
  */
void GreenLED_Task(void)
{
    static uint8_t led_state = 0;
    
    led_state = !led_state;
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, led_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    
    if(led_state) {
        queue_send("Green LED ON\r\n");
    }
}

/**
  * @brief Orange LED Task - Toggles LD3 (PD13)
  */
void OrangeLED_Task(void)
{
    static uint8_t led_state = 0;
    
    led_state = !led_state;
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, led_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    
    if(led_state) {
        queue_send("Orange LED ON\r\n");
    }
}

/**
  * @brief Red LED Task - Toggles LD5 (PD14)
  */
void RedLED_Task(void)
{
    static uint8_t led_state = 0;
    
    led_state = !led_state;
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, led_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    
    if(led_state) {
        queue_send("Red LED ON\r\n");
    }
}

/**
  * @brief UART Task - Handles message transmission
  */
void UART_Task(void)
{
    char msg[50];
    
    if(!uart_busy && queue_receive(msg))
    {
        uart_busy = 1;  // Take mutex
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, string_length(msg), 100);
        uart_busy = 0;  // Release mutex
    }
}

/**
  * @brief Button Task - Monitors user button
  */
void Button_Task(void)
{
    static uint8_t last_button_state = 0;
    uint8_t button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    
    if(button_state && !last_button_state) // Rising edge
    {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15); // Toggle Blue LED
        queue_send("Button Pressed - Blue LED Toggled\r\n");
    }
    
    last_button_state = button_state;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}





#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
