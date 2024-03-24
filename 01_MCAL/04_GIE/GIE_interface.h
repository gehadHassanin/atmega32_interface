/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   GIE_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 * Author  :  Gehad Hassanein
 * Layer   :  MCAL
 * SWC     :  GIE
 *
 */

#ifndef GIE_INTERFACE_H_
#define GIE_INTERFACE_H_


/**
*  @breif  : this function used to Enable global interrupt Enable(GIE)
*  @param  : void
*  @return : void
*/
void GIE_InterruptEnable(void);


/**
*  @breif    : this function used to Disable global interrupt Enable(GIE)
*  @param    : void
*  @return   : void
*/
void GIE_InterruptDisable(void);

#endif // GIE_INTERFACE_H_
