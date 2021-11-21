#ifndef __AW9364_H
#define __AW9364_H

#define AW9364_BRIGHTNESS_MIN  (1)
#define AW9364_BRIGHTNESS_MAX  (16)

void AW9364_on(int brightness);
void AW9364_adjust(int brightness);
void AW9364_off(void);

#endif //__AW9364_H