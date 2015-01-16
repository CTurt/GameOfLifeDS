#include "memory.h"

	.global _start
_start:
	mov r0, #IO								@ I/O space offset
	mov r1, #0x3							@ Both screens on
	
	mov r2, #MODE_FB0						@ Use VRAM_A as framebuffer
	mov r3, #(VRAM_ENABLE | VRAM_A_LCD)		@ VRAM bank A enabled in LCD mode
	
	str r1, [r0, #0x304]					@ Set POWERCNT
	str r2, [r0]							@		DISPCNT
	str r3, [r0, #0x240]					@		VRAMCNT_A
	
	bl setupState
	
	flushState:
	mov r0, #VRAM_A							@ VRAM A offset, framebuffer
	mov r2, #(256 * 192)					@ Pixel count
	ldr r3, =nextState						@ Next framebuffer
	
	writePixel:
	ldrh r1, [r3], #2
	strh r1, [r0], #2						@ Write a pixel
	subs r2, r2, #1							@ Move along one
	bne writePixel							@ Fill whole screen
	
	swi 0x05
	
	bl emulate
	
	b flushState
