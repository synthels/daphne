;;
; Copyright (C) 2020 synthels <synthels.me@gmail.com>
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
; GNU General Public License for more details.
;
; GDT
;;

[bits 64]

global gdt_flush

gdt_flush:
	mov rdi, [rdi + 8]
	lgdt [rdi]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov gs, ax
	mov ss, ax
	ret
