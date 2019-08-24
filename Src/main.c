/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SM_Control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void DRC(void);
void APF(void);
void ASV(void);
void Aswitch(char*,int8_t*);
void PRS(void);
int16_t ReadNum(char*,int8_t*);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  
  /* USER CODE END 2 */
  
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(1)
  {
    
    Write("To start, print one from the following commands:\n\r1) DRC for direct control\n\r2) APF for performing algorithm\n\r");
    //Write("3) ASV for saving algorithm in memory\n4) PRS for performing algorithm in memory\n");
    HAL_Delay(2000);
      
    //COM("DRC");
    
    if(strncmp((char*)UserRxBufferFS,"DRC",3)==0)
    {
        Debug("DRCbegin\n\r");
        
        UserRxBufferFS[0]=(uint8_t)'\0';
        DRC();
        
        Debug("DRCend\n\r");
    }
    else if(strncmp((char*)UserRxBufferFS,"APF",3)==0)
    {
        Debug("APFbegin\n\r");
        
        UserRxBufferFS[0]=(uint8_t)'\0';
        APF();
        
        Debug("APFend\n\r");
    }
    /*
    else if(strncmp((char*)UserRxBufferFS,"ASV",3)==0)
    {
        UserRxBufferFS[0]=(uint8_t)'\0';
        ASV();
    }
    else if(strncmp((char*)UserRxBufferFS,"PRS",3)==0)
    {
        UserRxBufferFS[0]=(uint8_t)'\0';
        PRS();
    }
    */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        
      
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */


void DRC()
{
    char str[1000];
    int8_t k;
    
    Write("\nInput command:\n");
    
    while(1)
    {
        HAL_Delay(100);
        //COM("MV1000");
        if(UserRxBufferFS[0]!=(uint8_t)'\0')
            break;
    }
    
    while(1)
    {
        strcpy(str,(char*)UserRxBufferFS);
        UserRxBufferFS[0]=(uint8_t)'\0';
        Write(str);
        switch(str[0])
        {
            case 'S':
                switch(str[1])
                {
                    case 'P':
                        SPdc(ReadNum(str,0));
                        break;
                }
                break;
            case 'M':
                switch(str[1])
                {
                    case 'V':
                        k=0;
                        while('0'<str[2+k]&&str[2+k]<'9')
                            k++;
                        if(k==0)
                        {
                            MV();
                            break;
                        }
                        MVXdc(ReadNum(str,0));
                        break;
                    case 'H':
                        MHdc();
                        break;
                    case 'L':
                        MLdc();
                        break;
                }
                break;
            case 'H':
                switch(str[1])
                {
                    case 'M':
                        HMdc();
                        break;
                }
                break;
            //For parameter changing, LL-JP functions and WL/WH
            default:
                Aswitch(str,0);
                break;
        }
    }
}

void APF()
{
    char str[1000];
    
    Write("\nInput your algorithm:\n");
    while(1)
    {
        HAL_Delay(100);
        if(UserRxBufferFS[0]!=(uint8_t)'\0')
            break;
    }
    
    strcpy(str,(char*)UserRxBufferFS);
    for(int8_t i=0;i<strlen(str)-1;i+=2)
        Aswitch(str,&i);

}
void ASV()
{
    //SAVING ALGORITHM IN FLASH-MEMORY
}

void PRS()
{
    //READING ALGORITHM FROM FLASH-MEMORY
}

void Aswitch(char* str,int8_t* i)
{
    int8_t k=0,j;
    switch(str[*i])
        {
            case 'D':
                switch(str[*i+1])
                {
                    case 'L':
                        DL();
                        break;
                    case 'R':
                        DR();
                        break;
                }
                break;
            case 'R':
                switch(str[*i+1])
                {
                    case 'S':
                        RS();
                        break;
                }
                break;
           case 'A':
                switch(str[*i+1])
                {
                    case 'L':
                        AL(ReadNum(str,i));
                        break;
                }
                break;
            case 'S':
                switch(str[*i+1])
                {
                    case 'D':
                        SD(ReadNum(str,i));
                        break;
                    case 'S':
                        SS(ReadNum(str,i));
                        break;
                    case 'P':
                        SP(ReadNum(str,i));
                        break;
                }
                break;
            case 'M':
                switch(str[*i+1])
                {
                    case 'V':
                        k=0;
                        while('0'<str[*i+2+k]&&str[*i+2+k]<'9')
                            k++;
                        if(k==0)
                        {
                            MV();
                            break;
                        }
                        MVX(ReadNum(str,i));
                        break;
                    case 'H':
                        MH();
                        break;
                    case 'L':
                        ML();
                        break;
                }
                break;
            case 'H':
                switch(str[*i+1])
                {
                    case 'M':
                        HM();
                        break;
                }
                break;
            case 'L':
                switch(str[*i+1])
                {
                    case 'L':
                        j=*i+2;
                        while(!(str[j]=='J'&&str[j+1]=='P'))
                            j+=2;
                        int8_t temp=j;
                        temp=ReadNum(str,&temp);
                        for(int8_t t=0;t<temp;t++)
                            for(int8_t p=*i+2;p<j;p+=2)
                                Aswitch(str,&p);
                        break;
                }
                break;
        }
}

extern void NoInterrupt(){
    char str[12];
    strncpy(str,(char*)UserRxBufferFS,12);
   
     switch(str[0])
        {
            case 'S':
                switch(str[1])
                {
                    case 'P':
                        SPdc(ReadNum(str,0));
                        break;
                }
                break;
            //For parameter changing functions
            default:
                Aswitch(str,0);
            break;
        }
}

int16_t ReadNum(char* str,int8_t* i){
    int8_t k=0;
    char temp[10];
    while(('0'<str[*i+2+k]&&str[*i+2+k]<'9')||str[*i+2+k]=='-'||str[*i+2+k]=='+')
        k++;
    for(int8_t j=0;j<k;j++)
        temp[j]=str[*i+2+j];
    *i+=k;
    return atoi(temp);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
