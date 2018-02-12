#include "i8042.h"

.intel_syntax

.global _M_ASM_IH

_M_ASM_IH:

out_empty:
	xor %eax, %eax
	inb STAT_REG
	mov %dl, %al & OBF
	cmp %dl, OBF
	jc out_empty

	mov %dl, %al & PARITY
	cmp %dl, PARITY
	jnc end

	mov %dl, %al & TIMEOUT
	cmp %dl, TIMEOUT
	jnc end


end:

	ret
	.end _M_ASM_IH

