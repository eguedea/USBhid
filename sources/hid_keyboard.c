/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_hid.h"

#include "usb_device_ch9.h"
#include "usb_device_descriptor.h"

#include "composite.h"

#include "hid_keyboard.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static usb_status_t USB_DeviceHidKeyboardAction(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static uint8_t s_KeyboardBuffer[USB_HID_KEYBOARD_REPORT_LENGTH];
static usb_device_composite_struct_t *s_UsbDeviceComposite;
static usb_device_hid_keyboard_struct_t s_UsbDeviceHidKeyboard;

/*******************************************************************************
 * Code
 ******************************************************************************/

static usb_status_t USB_DeviceHidKeyboardAction(void)
{
    static int x = 0U;
    enum
    {
    	START,
		START2,
        WINR,
		R,
		EMPTY,
        M,
		S,
		P,
		A,
		I,
		N,
		T,
		ENTER,
		UNENTER,
		WINR2,
		R2,
		EMPTY2,
		N2,
		O,
		T2,
		E,
		P2,
		A2,
		D,
		ENTER2,
		UNENTER2,
		WINR3,
		LEFTARROW,
		WINR4,
		R3,
		EMPTY3,
		N3,
		O2,
		T3,
		E2,
		P3,
		A3,
		D2,
		ENTER3,
		UNENTER3,
		WINR5,
		RIGHTARROW,
		UNGUI,
		UNARROW,
		H,
		O3,
		L,
		A4,
		SPACE,
		M2,
		U,
		N4,
		D3,
		O4,
		CTRL,
		E3,
		C,
		V
    };
    static uint8_t dir = WINR;

    s_UsbDeviceHidKeyboard.buffer[2] = 0x00U;
    switch (dir)
    {

    break;
		case START:
				  x++;
				  if (x > 500)
				  {
					  dir++;



				  }
				  break;
		case START2:
		   x--;
		   if (x < 1U)
		   {
			   dir++;
		   }
		   break;
    	case WINR:
            x++;
            if (x > 200U)
            {
                dir++;
                s_UsbDeviceHidKeyboard.buffer[7] = KEY_LEFT_GUI;


            }
            break;
        case R:
                   x--;
                   if (x < 1U)
                   {
                       dir++;
                       s_UsbDeviceHidKeyboard.buffer[2] = KEY_R;
                   }
                   break;
	   case EMPTY:
				  x++;
				  if (x > 200U)
				  {
					  dir++;



				  }
				  break;
        case M:
            x--;
            if (x < 1U)
            {
                dir++;
                s_UsbDeviceHidKeyboard.buffer[7] = 0;
                s_UsbDeviceHidKeyboard.buffer[2] = KEY_M;
            }
            break;
        case S:
                   x++;
                   if (x > 200U)
                   {
                       dir++;
                       s_UsbDeviceHidKeyboard.buffer[2] = KEY_S;



                   }
                   break;
	   case P:
		   x--;
		   if (x < 1U)
		   {
			   dir++;
			   s_UsbDeviceHidKeyboard.buffer[2] = KEY_P;
		   }
		   break;
       case A:
                  x++;
                  if (x > 200U)
                  {
                      dir++;
                      s_UsbDeviceHidKeyboard.buffer[2] = KEY_A;


                  }
                  break;
	   case I:
		   x--;
		   if (x < 1U)
		   {
			   dir++;
			   s_UsbDeviceHidKeyboard.buffer[2] = KEY_I;
		   }
		   break;
       case N:
                  x++;
                  if (x > 200U)
                  {
                      dir++;
                      s_UsbDeviceHidKeyboard.buffer[2] = KEY_N;


                  }
                  break;
	   case T:
		   x--;
		   if (x < 1U)
		   {
			   dir++;
			   s_UsbDeviceHidKeyboard.buffer[2] = KEY_T;
		   }
		   break;

        case ENTER:
                   x++;
                   if (x > 200U)
                   {
                       dir++;
                       s_UsbDeviceHidKeyboard.buffer[4] = KEY_ENTER;


                   }
                   break;
        case UNENTER:
       		   x--;
   			   s_UsbDeviceHidKeyboard.buffer[4] = 0;

       		   if (x < 1U)
       		   {
       			   dir++;
       			   s_UsbDeviceHidKeyboard.buffer[4] = 0;
       		   }
       		   break;
       //BRINCAR A MOUSE PARA DIBUJAR CUADRADO
        case WINR2:
                   x++;
                   if (x > 200U)
                   {
                       dir++;
                       s_UsbDeviceHidKeyboard.buffer[7] = KEY_LEFT_GUI;


                   }
                   break;
               case R2:
                          x--;
                          if (x < 1U)
                          {
                              dir++;
                              s_UsbDeviceHidKeyboard.buffer[2] = KEY_R;
                          }
                          break;
       	   case EMPTY2:
       				  x++;
       				  if (x > 200U)
       				  {
       					  dir++;



       				  }
       				  break;
               case N2:
                   x--;
                   if (x < 1U)
                   {
                       dir++;
                       s_UsbDeviceHidKeyboard.buffer[7] = 0;
                       s_UsbDeviceHidKeyboard.buffer[2] = KEY_N;
                   }
                   break;
               case O:
                          x++;
                          if (x > 200U)
                          {
                              dir++;
                              s_UsbDeviceHidKeyboard.buffer[2] = KEY_O;



                          }
                          break;
       	   case T2:
       		   x--;
       		   if (x < 1U)
       		   {
       			   dir++;
       			   s_UsbDeviceHidKeyboard.buffer[2] = KEY_T;
       		   }
       		   break;
              case E:
                         x++;
                         if (x > 200U)
                         {
                             dir++;
                             s_UsbDeviceHidKeyboard.buffer[2] = KEY_E;


                         }
                         break;
       	   case P2:
       		   x--;
       		   if (x < 1U)
       		   {
       			   dir++;
       			   s_UsbDeviceHidKeyboard.buffer[2] = KEY_P;
       		   }
       		   break;
              case A2:
                         x++;
                         if (x > 200U)
                         {
                             dir++;
                             s_UsbDeviceHidKeyboard.buffer[2] = KEY_A;


                         }
                         break;
       	   case D:
       		   x--;
       		   if (x < 1U)
       		   {
       			   dir++;
       			   s_UsbDeviceHidKeyboard.buffer[2] = KEY_D;
       		   }
       		   break;


               case ENTER2:
                          x++;
                          if (x > 200U)
                          {
                              dir++;
                              s_UsbDeviceHidKeyboard.buffer[4] = KEY_ENTER;


                          }
                          break;
               case UNENTER2:
              		   x--;
          			   s_UsbDeviceHidKeyboard.buffer[4] = 0;

              		   if (x < 1U)
              		   {
              			   dir++;
              			   s_UsbDeviceHidKeyboard.buffer[4] = 0;
              		   }
              		   break;
               case WINR3:
                           x++;
                           if (x > 200U)
                           {
                               dir++;
                               s_UsbDeviceHidKeyboard.buffer[7] = KEY_LEFT_GUI;


                           }
                           break;
			   case LEFTARROW:
						  x--;
						  if (x < 1U)
						  {
							  dir++;
							  s_UsbDeviceHidKeyboard.buffer[5] = KEY_LEFTARROW;
						  }
						  break;
		        case WINR4:
		                   x++;
		                   if (x > 200U)
		                   {
		                       dir++;

		                       s_UsbDeviceHidKeyboard.buffer[7] = KEY_LEFT_GUI;


		                   }
		                   break;
		               case R3:
		                          x--;
		                          if (x < 1U)
		                          {
		                              dir++;
		                              s_UsbDeviceHidKeyboard.buffer[2] = KEY_R;
		                          }
		                          break;
		       	   case EMPTY3:
		       				  x++;
		       				  if (x > 200U)
		       				  {
		       					  dir++;



		       				  }
		       				  break;
		               case N3:
		                   x--;
		                   if (x < 1U)
		                   {
		                       dir++;
		                       s_UsbDeviceHidKeyboard.buffer[7] = 0;
		                       s_UsbDeviceHidKeyboard.buffer[2] = KEY_N;
		                   }
		                   break;
		               case O2:
		                          x++;
		                          if (x > 200U)
		                          {
		                              dir++;
		                              s_UsbDeviceHidKeyboard.buffer[2] = KEY_O;



		                          }
		                          break;
		       	   case T3:
		       		   x--;
		       		   if (x < 1U)
		       		   {
		       			   dir++;
		       			   s_UsbDeviceHidKeyboard.buffer[2] = KEY_T;
		       		   }
		       		   break;
		              case E2:
		                         x++;
		                         if (x > 200U)
		                         {
		                             dir++;
		                             s_UsbDeviceHidKeyboard.buffer[2] = KEY_E;


		                         }
		                         break;
		       	   case P3:
		       		   x--;
		       		   if (x < 1U)
		       		   {
		       			   dir++;
		       			   s_UsbDeviceHidKeyboard.buffer[2] = KEY_P;
		       		   }
		       		   break;
		              case A3:
		                         x++;
		                         if (x > 200U)
		                         {
		                             dir++;
		                             s_UsbDeviceHidKeyboard.buffer[2] = KEY_A;


		                         }
		                         break;
		       	   case D2:
		       		   x--;
		       		   if (x < 1U)
		       		   {
		       			   dir++;
		       			   s_UsbDeviceHidKeyboard.buffer[2] = KEY_D;
		       		   }
		       		   break;


		               case ENTER3:
		                          x++;
		                          if (x > 200U)
		                          {
		                              dir++;
		                              s_UsbDeviceHidKeyboard.buffer[4] = KEY_ENTER;


		                          }
		                          break;
		               case UNENTER3:
		              		   x--;
	              			   s_UsbDeviceHidKeyboard.buffer[4] = 0;

		              		   if (x < 1U)
		              		   {
		              			   dir++;
		              			   s_UsbDeviceHidKeyboard.buffer[4] = 0;
		              		   }
		              		   break;
		               case WINR5:
		                           x++;
		                           if (x > 200U)
		                           {
		                               dir++;
		                               s_UsbDeviceHidKeyboard.buffer[7] = KEY_LEFT_GUI;


		                           }
		                           break;
					   case RIGHTARROW:
								  x--;
								  if (x < 1U)
								  {
									  dir++;
									  s_UsbDeviceHidKeyboard.buffer[6] = KEY_RIGHTARROW;
								  }
								  break;
					///BRINCAR A MOUSE IR A IZQUIERDA Y HACER CLICK
					   case UNGUI:
							   x++;
							   if (x > 200U)
							   {
								   dir++;
									  s_UsbDeviceHidKeyboard.buffer[6] = 0;


							   }
							   break;
					   case UNARROW:
						   x--;
						   if (x < 1U)
						   {
							   dir++;
                               s_UsbDeviceHidKeyboard.buffer[7] = 0;
						   }
						   break;
					   case H:
							   x++;
							   if (x > 200U)
							   {
								   dir++;
								   s_UsbDeviceHidKeyboard.buffer[2] = KEY_H;


							   }
							   break;
					   case O3:
						   x--;
						   if (x < 1U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_O;
						   }
						   break;
					   case L:
						   x++;
						   if (x > 200U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_L;


						   }
						   break;
					   case A4:
						   x--;
						   if (x < 1U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_A;
						   }
						   break;
					   case SPACE:
						   x++;
						   if (x > 200U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[4] = KEY_SPACEBAR;



						   }
						   break;
					   case M2:
						   x--;
						   s_UsbDeviceHidKeyboard.buffer[4] = 0;

						   if (x < 1U)
						   {
							   dir++;

							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_M;
						   }
						   break;

					   case U:
						   x++;
						   if (x > 200U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_U;


						   }
						   break;
					   case N4:
						   x--;
						   if (x < 1U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_N;
						   }
						   break;
					   case D3:
						   x++;
						   if (x > 200U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_D;


						   }
						   break;
					   case O4:
						   x--;
						   if (x < 1U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_O;
						   }
						   break;
					   case CTRL:
						   x++;
						   if (x > 200U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[7] = KEY_LEFTCONTROL;	//


						   }
						   break;
					   case E3:
						   x--;
						   if (x < 1U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_E;
						   }
						   break;
					   case C:
						   x++;
						   if (x > 200U)
						   {
							   dir++;
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_C;


						   }
						   break;
							//BRINCAR A MOUSE PARA IR A DERECHA

					   case V:
						   x--;
						   if (x < 1U)
						   {
							   s_UsbDeviceHidKeyboard.buffer[2] = KEY_V;

						   }
						   break;
    }
    return USB_DeviceHidSend(s_UsbDeviceComposite->hidKeyboardHandle, USB_HID_KEYBOARD_ENDPOINT_IN,
                             s_UsbDeviceHidKeyboard.buffer, USB_HID_KEYBOARD_REPORT_LENGTH);
}

usb_status_t USB_DeviceHidKeyboardCallback(class_handle_t handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_Error;

    switch (event)
    {
        case kUSB_DeviceHidEventSendResponse:
            if (s_UsbDeviceComposite->attach)
            {
                return USB_DeviceHidKeyboardAction();
            }
            break;
        case kUSB_DeviceHidEventGetReport:
        case kUSB_DeviceHidEventSetReport:
        case kUSB_DeviceHidEventRequestReportBuffer:
            error = kStatus_USB_InvalidRequest;
            break;
        case kUSB_DeviceHidEventGetIdle:
        case kUSB_DeviceHidEventGetProtocol:
        case kUSB_DeviceHidEventSetIdle:
        case kUSB_DeviceHidEventSetProtocol:
            break;
        default:
            break;
    }

    return error;
}

usb_status_t USB_DeviceHidKeyboardSetConfigure(class_handle_t handle, uint8_t configure)
{
    if (USB_COMPOSITE_CONFIGURE_INDEX == configure)
    {
        return USB_DeviceHidKeyboardAction(); /* run the cursor movement code */
    }
    return kStatus_USB_Error;
}

usb_status_t USB_DeviceHidKeyboardSetInterface(class_handle_t handle, uint8_t interface, uint8_t alternateSetting)
{
    if (USB_HID_KEYBOARD_INTERFACE_INDEX == interface)
    {
        return USB_DeviceHidKeyboardAction(); /* run the cursor movement code */
    }
    return kStatus_USB_Error;
}

usb_status_t USB_DeviceHidKeyboardInit(usb_device_composite_struct_t *deviceComposite)
{
    s_UsbDeviceComposite = deviceComposite;
    s_UsbDeviceHidKeyboard.buffer = s_KeyboardBuffer;
    return kStatus_USB_Success;
}
