/*
 * MFDI_Interface.h
 *
 *  Created on: 23-05-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef MFDI_INTERFACE_H_
#define MFDI_INTERFACE_H_

void MFDI_voidEraseSector(u8 Copy_u8SectorNum);

void MFDI_voidEraseAppSector(void);

void MFDI_voidWrite(u32 Copy_u32Address, u16 *Copy_pu16PtrToData, u8 Copy_u8Length);


#endif /* MFDI_INTERFACE_H_ */
