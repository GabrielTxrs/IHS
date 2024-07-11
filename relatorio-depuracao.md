<div align="center">
<img src="logo ufs.png" alt="logo ufs" width="100"/>


### Universidade Federal de Sergipe<br>
Interface Hardware Software
Turma 03


Gabriel Teixeira Silveira





### Relatório sobre depuração de código em C



Professor: <br>
Calebe Micael de Oliveira Conceição




São Cristóvão<br>
Julho de 2024


Abaixo, segue o código utilizado para compilação e depuração.

</div>

```
#include <stdio.h>

void trocar(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int lomutoPartition(int inicio, int fim, int *vetor) {
	int pivot = vetor[inicio];
	int mediana = inicio;// indice do ultimo elemento do primeiro segmento
	for(int i = inicio + 1; i < fim; i++) {
		if(vetor[i] < pivot) {
			mediana++;
			trocar(&vetor[mediana],&vetor[i]);
		}
	}
	trocar(&vetor[inicio],&vetor[mediana]);
	return mediana;
}

void QuickSort(int inicio, int fim, int *vetor) {
	int particao;
	if(inicio < fim) {
		particao = lomutoPartition(inicio, fim, vetor);
		QuickSort(inicio, particao, vetor);
		QuickSort(particao+1, fim, vetor);
	}
}

int main() {
	int vetor[12] = {4, 5, 6, 9, 2, 3, 1, 8, 7, 10};

	for(int i = 0 ; i < 10 ;i++) {
		printf("%d ", vetor[i]);
	}
	printf("\n");
	QuickSort(0, 10, vetor);
	for(int i = 0 ; i < 10 ;i++) {
		printf("%d ", vetor[i]);
	}
	printf("\n");
	return 0;
}
```
Primeiramente, compilei o código e testei seu funcionamento

```
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ gcc QuickSort.c -o QuickSort
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ ls
 QuickSort   QuickSort.c   
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ ./QuickSort
4 5 6 9 2 3 1 8 7 10
1 2 3 4 5 6 7 8 9 10
```

<details>

<summary>Em seguida, gerei a Árvore Sintática Abstrata (LLVM)

```
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ clang -S -Xclang -ast-dump QuickSort.c
TranslationUnitDecl 0x131aa28 <<invalid sloc>> <invalid sloc>
|-TypedefDecl 0x131b250 <<invalid sloc>> <invalid sloc> implicit __int128_t '__int128'
| `-BuiltinType 0x131aff0 '__int128'
|-TypedefDecl 0x131b2c0 <<invalid sloc>> <invalid sloc> implicit __uint128_t 'unsigned __int128'
| `-BuiltinType 0x131b010 'unsigned __int128'
|-TypedefDecl 0x131b5c8 <<invalid sloc>> <invalid sloc> implicit __NSConstantString 'struct __NSConstantString_tag'
| `-RecordType 0x131b3a0 'struct __NSConstantString_tag'
|   `-Record 0x131b318 '__NSConstantString_tag'
|-TypedefDecl 0x131b660 <<invalid sloc>> <invalid sloc> implicit __builtin_ms_va_list 'char *'
| `-PointerType 0x131b620 'char *'
|   `-BuiltinType 0x131aad0 'char'
|-TypedefDecl 0x131b958 <<invalid sloc>> <invalid sloc> implicit referenced __builtin_va_list 'struct __va_list_tag[1]'     
| `-ConstantArrayType 0x131b900 'struct __va_list_tag[1]' 1
|   `-RecordType 0x131b740 'struct __va_list_tag'
|     `-Record 0x131b6b8 '__va_list_tag'
```
</summary>

```
|-TypedefDecl 0x131b9c8 </usr/lib/llvm-14/lib/clang/14.0.0/include/stddef.h:46:1, col:23> col:23 referenced size_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a4210 </usr/lib/llvm-14/lib/clang/14.0.0/include/stdarg.h:14:1, col:27> col:27 va_list '__builtin_va_list':'struct __va_list_tag[1]'
| `-TypedefType 0x13a41e0 '__builtin_va_list' sugar
|   |-Typedef 0x131b958 '__builtin_va_list'
|   `-ConstantArrayType 0x131b900 'struct __va_list_tag[1]' 1
|     `-RecordType 0x131b740 'struct __va_list_tag'
|       `-Record 0x131b6b8 '__va_list_tag'
|-TypedefDecl 0x13a4278 <line:32:1, col:27> col:27 referenced __gnuc_va_list '__builtin_va_list':'struct __va_list_tag[1]'  
| `-TypedefType 0x13a41e0 '__builtin_va_list' sugar
|   |-Typedef 0x131b958 '__builtin_va_list'
|   `-ConstantArrayType 0x131b900 'struct __va_list_tag[1]' 1
|     `-RecordType 0x131b740 'struct __va_list_tag'
|       `-Record 0x131b6b8 '__va_list_tag'
|-TypedefDecl 0x13a42e8 </usr/include/x86_64-linux-gnu/bits/types.h:31:1, col:23> col:23 __u_char 'unsigned char'
| `-BuiltinType 0x131ab90 'unsigned char'
|-TypedefDecl 0x13a4358 <line:32:1, col:28> col:28 __u_short 'unsigned short'
| `-BuiltinType 0x131abb0 'unsigned short'
|-TypedefDecl 0x13a43c8 <line:33:1, col:22> col:22 __u_int 'unsigned int'
| `-BuiltinType 0x131abd0 'unsigned int'
|-TypedefDecl 0x13a4438 <line:34:1, col:27> col:27 __u_long 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a44a8 <line:37:1, col:21> col:21 referenced __int8_t 'signed char'
| `-BuiltinType 0x131aaf0 'signed char'
|-TypedefDecl 0x13a4518 <line:38:1, col:23> col:23 referenced __uint8_t 'unsigned char'
| `-BuiltinType 0x131ab90 'unsigned char'
|-TypedefDecl 0x13a4588 <line:39:1, col:26> col:26 referenced __int16_t 'short'
| `-BuiltinType 0x131ab10 'short'
|-TypedefDecl 0x13a45f8 <line:40:1, col:28> col:28 referenced __uint16_t 'unsigned short'
| `-BuiltinType 0x131abb0 'unsigned short'
|-TypedefDecl 0x13a4668 <line:41:1, col:20> col:20 referenced __int32_t 'int'
| `-BuiltinType 0x131ab30 'int'
|-TypedefDecl 0x13a46d8 <line:42:1, col:22> col:22 referenced __uint32_t 'unsigned int'
| `-BuiltinType 0x131abd0 'unsigned int'
|-TypedefDecl 0x13a4748 <line:44:1, col:25> col:25 referenced __int64_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13a47b8 <line:45:1, col:27> col:27 referenced __uint64_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a4840 <line:52:1, col:18> col:18 __int_least8_t '__int8_t':'signed char'
| `-TypedefType 0x13a4810 '__int8_t' sugar
|   |-Typedef 0x13a44a8 '__int8_t'
|   `-BuiltinType 0x131aaf0 'signed char'
|-TypedefDecl 0x13a48d0 <line:53:1, col:19> col:19 __uint_least8_t '__uint8_t':'unsigned char'
| `-TypedefType 0x13a48a0 '__uint8_t' sugar
|   |-Typedef 0x13a4518 '__uint8_t'
|   `-BuiltinType 0x131ab90 'unsigned char'
|-TypedefDecl 0x13a4960 <line:54:1, col:19> col:19 __int_least16_t '__int16_t':'short'
| `-TypedefType 0x13a4930 '__int16_t' sugar
|   |-Typedef 0x13a4588 '__int16_t'
|   `-BuiltinType 0x131ab10 'short'
|-TypedefDecl 0x13a49f0 <line:55:1, col:20> col:20 __uint_least16_t '__uint16_t':'unsigned short'
| `-TypedefType 0x13a49c0 '__uint16_t' sugar
|   |-Typedef 0x13a45f8 '__uint16_t'
|   `-BuiltinType 0x131abb0 'unsigned short'
|-TypedefDecl 0x13a4a80 <line:56:1, col:19> col:19 __int_least32_t '__int32_t':'int'
| `-TypedefType 0x13a4a50 '__int32_t' sugar
|   |-Typedef 0x13a4668 '__int32_t'
|   `-BuiltinType 0x131ab30 'int'
|-TypedefDecl 0x13a4b10 <line:57:1, col:20> col:20 __uint_least32_t '__uint32_t':'unsigned int'
| `-TypedefType 0x13a4ae0 '__uint32_t' sugar
|   |-Typedef 0x13a46d8 '__uint32_t'
|   `-BuiltinType 0x131abd0 'unsigned int'
|-TypedefDecl 0x13a4ba0 <line:58:1, col:19> col:19 __int_least64_t '__int64_t':'long'
| `-TypedefType 0x13a4b70 '__int64_t' sugar
|   |-Typedef 0x13a4748 '__int64_t'
|   `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13a4c30 <line:59:1, col:20> col:20 __uint_least64_t '__uint64_t':'unsigned long'
| `-TypedefType 0x13a4c00 '__uint64_t' sugar
|   |-Typedef 0x13a47b8 '__uint64_t'
|   `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a4ca0 <line:63:1, col:18> col:18 __quad_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13a4d10 <line:64:1, col:27> col:27 __u_quad_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a4d80 <line:72:1, col:18> col:18 __intmax_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13a4df0 <line:73:1, col:27> col:27 __uintmax_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a4e60 <line:137:22, line:145:25> col:25 __dev_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a4ed0 <line:137:22, line:146:25> col:25 __uid_t 'unsigned int'
| `-BuiltinType 0x131abd0 'unsigned int'
|-TypedefDecl 0x13a4f40 <line:137:22, line:147:25> col:25 __gid_t 'unsigned int'
| `-BuiltinType 0x131abd0 'unsigned int'
|-TypedefDecl 0x13a4fb0 <line:137:22, line:148:25> col:25 __ino_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a5020 <line:137:22, line:149:27> col:27 __ino64_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a5090 <line:137:22, line:150:26> col:26 __mode_t 'unsigned int'
| `-BuiltinType 0x131abd0 'unsigned int'
|-TypedefDecl 0x13a5100 <line:137:22, line:151:27> col:27 __nlink_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13a5170 <line:137:22, line:152:25> col:25 referenced __off_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b1f50 <line:137:22, line:153:27> col:27 referenced __off64_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b1fc0 <line:137:22, line:154:25> col:25 __pid_t 'int'
| `-BuiltinType 0x131ab30 'int'
|-RecordDecl 0x13b2018 </usr/include/x86_64-linux-gnu/bits/typesizes.h:73:24, col:47> col:24 struct definition
| `-FieldDecl 0x13b2160 <col:33, col:44> col:37 __val 'int[2]'
|-TypedefDecl 0x13b2208 </usr/include/x86_64-linux-gnu/bits/types.h:137:22, line:155:26> col:26 __fsid_t 'struct __fsid_t':'__fsid_t'
| `-ElaboratedType 0x13b21b0 'struct __fsid_t' sugar
|   `-RecordType 0x13b20a0 '__fsid_t'
|     `-Record 0x13b2018 ''
|-TypedefDecl 0x13b2290 <line:137:22, line:156:27> col:27 __clock_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b2300 <line:137:22, line:157:26> col:26 __rlim_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13b2370 <line:137:22, line:158:28> col:28 __rlim64_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13b23e0 <line:137:22, line:159:24> col:24 __id_t 'unsigned int'
| `-BuiltinType 0x131abd0 'unsigned int'
|-TypedefDecl 0x13b2450 <line:137:22, line:160:26> col:26 __time_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b24c0 <line:137:22, line:161:30> col:30 __useconds_t 'unsigned int'
| `-BuiltinType 0x131abd0 'unsigned int'
|-TypedefDecl 0x13b2530 <line:137:22, line:162:31> col:31 __suseconds_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b25a0 <line:137:22, line:163:33> col:33 __suseconds64_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b2610 <line:137:22, line:165:27> col:27 __daddr_t 'int'
| `-BuiltinType 0x131ab30 'int'
|-TypedefDecl 0x13b2680 <line:137:22, line:166:25> col:25 __key_t 'int'
| `-BuiltinType 0x131ab30 'int'
|-TypedefDecl 0x13b26f0 <line:137:22, line:169:29> col:29 __clockid_t 'int'
| `-BuiltinType 0x131ab30 'int'
|-TypedefDecl 0x13b2760 <line:137:22, line:172:27> col:27 __timer_t 'void *'
| `-PointerType 0x131b1b0 'void *'
|   `-BuiltinType 0x131aa90 'void'
|-TypedefDecl 0x13b27d0 <line:137:22, line:175:29> col:29 __blksize_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b2840 <line:137:22, line:180:28> col:28 __blkcnt_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b28b0 <line:137:22, line:181:30> col:30 __blkcnt64_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b2920 <line:137:22, line:184:30> col:30 __fsblkcnt_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13b2990 <line:137:22, line:185:32> col:32 __fsblkcnt64_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13b2a00 <line:137:22, line:188:30> col:30 __fsfilcnt_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13b2a70 <line:137:22, line:189:32> col:32 __fsfilcnt64_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13b2ae0 <line:137:22, line:192:28> col:28 __fsword_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b2b50 <line:137:22, line:194:27> col:27 referenced __ssize_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b2bc0 <line:137:22, line:197:33> col:33 __syscall_slong_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b2c30 <line:137:22, line:199:33> col:33 __syscall_ulong_t 'unsigned long'
| `-BuiltinType 0x131abf0 'unsigned long'
|-TypedefDecl 0x13b2cc0 <line:203:1, col:19> col:19 __loff_t '__off64_t':'long'
| `-TypedefType 0x13b2c90 '__off64_t' sugar
|   |-Typedef 0x13b1f50 '__off64_t'
|   `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b2d30 <line:204:1, col:15> col:15 __caddr_t 'char *'
| `-PointerType 0x131b620 'char *'
|   `-BuiltinType 0x131aad0 'char'
|-TypedefDecl 0x13b2da0 <line:137:22, line:207:25> col:25 __intptr_t 'long'
| `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13b2e10 <line:137:22, line:210:23> col:23 __socklen_t 'unsigned int'
| `-BuiltinType 0x131abd0 'unsigned int'
|-TypedefDecl 0x13b2e80 <line:215:1, col:13> col:13 __sig_atomic_t 'int'
| `-BuiltinType 0x131ab30 'int'
|-RecordDecl 0x13b3f70 </usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h:13:9, line:21:1> line:13:9 struct definition 
| |-FieldDecl 0x13b4028 <line:15:3, col:7> col:7 __count 'int'
| |-RecordDecl 0x13b4078 <line:16:3, line:20:3> line:16:3 union definition
| | |-FieldDecl 0x13b4138 <<built-in>:98:23, /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h:18:19> col:19 __wch 'unsigned int'
| | `-FieldDecl 0x13b4228 <line:19:5, col:18> col:10 __wchb 'char[4]'
| `-FieldDecl 0x13b42d8 <line:16:3, line:20:5> col:5 __value 'union (unnamed union at /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h:16:3)':'union __mbstate_t::(unnamed at /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h:16:3)'       
|-TypedefDecl 0x13b4388 <line:13:1, line:21:3> col:3 referenced __mbstate_t 'struct __mbstate_t':'__mbstate_t'
| `-ElaboratedType 0x13b4330 'struct __mbstate_t' sugar
|   `-RecordType 0x13b3ff0 '__mbstate_t'
|     `-Record 0x13b3f70 ''
|-RecordDecl 0x13b43f8 </usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h:10:9, line:14:1> line:10:16 struct _G_fpos_t definition
| |-FieldDecl 0x13b44d0 <line:12:3, col:11> col:11 __pos '__off_t':'long'
| `-FieldDecl 0x13b4550 <line:13:3, col:15> col:15 __state '__mbstate_t':'__mbstate_t'
|-TypedefDecl 0x13b45f8 <line:10:1, line:14:3> col:3 referenced __fpos_t 'struct _G_fpos_t':'struct _G_fpos_t'
| `-ElaboratedType 0x13b45a0 'struct _G_fpos_t' sugar
|   `-RecordType 0x13b4480 'struct _G_fpos_t'
|     `-Record 0x13b43f8 '_G_fpos_t'
|-RecordDecl 0x13b4668 </usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h:10:9, line:14:1> line:10:16 struct _G_fpos64_t definition
| |-FieldDecl 0x13b4720 <line:12:3, col:13> col:13 __pos '__off64_t':'long'
| `-FieldDecl 0x13b4780 <line:13:3, col:15> col:15 __state '__mbstate_t':'__mbstate_t'
|-TypedefDecl 0x13b4828 <line:10:1, line:14:3> col:3 __fpos64_t 'struct _G_fpos64_t':'struct _G_fpos64_t'
| `-ElaboratedType 0x13b47d0 'struct _G_fpos64_t' sugar
|   `-RecordType 0x13b46f0 'struct _G_fpos64_t'
|     `-Record 0x13b4668 '_G_fpos64_t'
|-RecordDecl 0x13b4898 </usr/include/x86_64-linux-gnu/bits/types/__FILE.h:4:1, col:8> col:8 struct _IO_FILE
|-TypedefDecl 0x13b4990 <line:5:1, col:25> col:25 __FILE 'struct _IO_FILE':'struct _IO_FILE'
| `-ElaboratedType 0x13b4940 'struct _IO_FILE' sugar
|   `-RecordType 0x13b4920 'struct _IO_FILE'
|     `-Record 0x13b4da8 '_IO_FILE'
|-RecordDecl 0x13b49e8 prev 0x13b4898 </usr/include/x86_64-linux-gnu/bits/types/FILE.h:4:1, col:8> col:8 struct _IO_FILE    
|-TypedefDecl 0x13b4a88 <line:7:1, col:25> col:25 referenced FILE 'struct _IO_FILE':'struct _IO_FILE'
| `-ElaboratedType 0x13b4940 'struct _IO_FILE' sugar
|   `-RecordType 0x13b4920 'struct _IO_FILE'
|     `-Record 0x13b4da8 '_IO_FILE'
|-RecordDecl 0x13b4ae0 prev 0x13b49e8 </usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h:35:1, col:8> col:8 struct _IO_FILE
|-RecordDecl 0x13b4b60 <line:36:1, col:8> col:8 struct _IO_marker
|-RecordDecl 0x13b4c00 <line:37:1, col:8> col:8 struct _IO_codecvt
|-RecordDecl 0x13b4ca0 <line:38:1, col:8> col:8 struct _IO_wide_data
|-TypedefDecl 0x13b4d50 <line:43:1, col:14> col:14 referenced _IO_lock_t 'void'
| `-BuiltinType 0x131aa90 'void'
|-RecordDecl 0x13b4da8 prev 0x13b4ae0 <line:49:1, line:99:1> line:49:8 struct _IO_FILE definition
| |-FieldDecl 0x13b4e40 <line:51:3, col:7> col:7 _flags 'int'
| |-FieldDecl 0x13b4ea8 <line:54:3, col:9> col:9 _IO_read_ptr 'char *'
| |-FieldDecl 0x13b4f10 <line:55:3, col:9> col:9 _IO_read_end 'char *'
| |-FieldDecl 0x13b8028 <line:56:3, col:9> col:9 _IO_read_base 'char *'
| |-FieldDecl 0x13b8090 <line:57:3, col:9> col:9 _IO_write_base 'char *'
| |-FieldDecl 0x13b80f8 <line:58:3, col:9> col:9 _IO_write_ptr 'char *'
| |-FieldDecl 0x13b8160 <line:59:3, col:9> col:9 _IO_write_end 'char *'
| |-FieldDecl 0x13b81c8 <line:60:3, col:9> col:9 _IO_buf_base 'char *'
| |-FieldDecl 0x13b8230 <line:61:3, col:9> col:9 _IO_buf_end 'char *'
| |-FieldDecl 0x13b8298 <line:64:3, col:9> col:9 _IO_save_base 'char *'
| |-FieldDecl 0x13b8300 <line:65:3, col:9> col:9 _IO_backup_base 'char *'
| |-FieldDecl 0x13b8368 <line:66:3, col:9> col:9 _IO_save_end 'char *'
| |-FieldDecl 0x13b8470 <line:68:3, col:22> col:22 _markers 'struct _IO_marker *'
| |-FieldDecl 0x13b8540 <line:70:3, col:20> col:20 _chain 'struct _IO_FILE *'
| |-FieldDecl 0x13b85a8 <line:72:3, col:7> col:7 _fileno 'int'
| |-FieldDecl 0x13b8610 <line:73:3, col:7> col:7 _flags2 'int'
| |-FieldDecl 0x13b8670 <line:74:3, col:11> col:11 _old_offset '__off_t':'long'
| |-FieldDecl 0x13b86d8 <line:77:3, col:18> col:18 _cur_column 'unsigned short'
| |-FieldDecl 0x13b8740 <line:78:3, col:15> col:15 _vtable_offset 'signed char'
| |-FieldDecl 0x13b8828 <line:79:3, col:19> col:8 _shortbuf 'char[1]'
| |-FieldDecl 0x13b88d8 <line:81:3, col:15> col:15 _lock '_IO_lock_t *'
| |-FieldDecl 0x13b8938 <line:89:3, col:13> col:13 _offset '__off64_t':'long'
| |-FieldDecl 0x13b8a40 <line:91:3, col:23> col:23 _codecvt 'struct _IO_codecvt *'
| |-FieldDecl 0x13b8b40 <line:92:3, col:25> col:25 _wide_data 'struct _IO_wide_data *'
| |-FieldDecl 0x13b8bb8 <line:93:3, col:20> col:20 _freeres_list 'struct _IO_FILE *'
| |-FieldDecl 0x13b8c20 <line:94:3, col:9> col:9 _freeres_buf 'void *'
| |-FieldDecl 0x13b8ca0 <line:95:3, col:10> col:10 __pad5 'size_t':'unsigned long'
| |-FieldDecl 0x13b8d08 <line:96:3, col:7> col:7 _mode 'int'
| `-FieldDecl 0x13b8f68 <line:98:3, col:74> col:8 _unused2 'char[20]'
|-TypedefDecl 0x13bad70 prev 0x13a4210 </usr/include/stdio.h:52:1, col:24> col:24 va_list '__gnuc_va_list':'struct __va_list_tag[1]'
| `-TypedefType 0x13b8fc0 '__gnuc_va_list' sugar
|   |-Typedef 0x13a4278 '__gnuc_va_list'
|   `-TypedefType 0x13a41e0 '__builtin_va_list' sugar
|     |-Typedef 0x131b958 '__builtin_va_list'
|     `-ConstantArrayType 0x131b900 'struct __va_list_tag[1]' 1
|       `-RecordType 0x131b740 'struct __va_list_tag'
|         `-Record 0x131b6b8 '__va_list_tag'
|-TypedefDecl 0x13badd8 <line:63:1, col:17> col:17 off_t '__off_t':'long'
| `-TypedefType 0x13b44a0 '__off_t' sugar
|   |-Typedef 0x13a5170 '__off_t'
|   `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13bae60 <line:77:1, col:19> col:19 ssize_t '__ssize_t':'long'
| `-TypedefType 0x13bae30 '__ssize_t' sugar
|   |-Typedef 0x13b2b50 '__ssize_t'
|   `-BuiltinType 0x131ab50 'long'
|-TypedefDecl 0x13baef0 <line:84:1, col:18> col:18 referenced fpos_t '__fpos_t':'struct _G_fpos_t'
| `-TypedefType 0x13baec0 '__fpos_t' sugar
|   |-Typedef 0x13b45f8 '__fpos_t'
|   `-ElaboratedType 0x13b45a0 'struct _G_fpos_t' sugar
|     `-RecordType 0x13b4480 'struct _G_fpos_t'
|       `-Record 0x13b43f8 '_G_fpos_t'
|-VarDecl 0x13bafa8 <line:143:1, col:14> col:14 stdin 'FILE *' extern
|-VarDecl 0x13bb068 <line:144:1, col:14> col:14 stdout 'FILE *' extern
|-VarDecl 0x13bb0e0 <line:145:1, col:14> col:14 stderr 'FILE *' extern
|-FunctionDecl 0x13bb230 <line:152:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:152:12 remove 'int (const char *)' extern
| |-ParmVarDecl 0x13bb160 <col:20, col:32> col:32 __filename 'const char *'
| `-NoThrowAttr 0x13bb2d8 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13bb4a0 </usr/include/stdio.h:154:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:154:12 rename 'int (const char *, const char *)' extern
| |-ParmVarDecl 0x13bb348 <col:20, col:32> col:32 __old 'const char *'
| |-ParmVarDecl 0x13bb3c8 <col:39, col:51> col:51 __new 'const char *'
| `-NoThrowAttr 0x13bb550 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13bb840 </usr/include/stdio.h:158:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:158:12 renameat 'int (int, const char *, int, const char *)' extern
| |-ParmVarDecl 0x13bb5c0 <col:22, col:26> col:26 __oldfd 'int'
| |-ParmVarDecl 0x13bb640 <col:35, col:47> col:47 __old 'const char *'
| |-ParmVarDecl 0x13bb6c0 <col:54, col:58> col:58 __newfd 'int'
| |-ParmVarDecl 0x13bb740 <line:159:8, col:20> col:20 __new 'const char *'
| `-NoThrowAttr 0x13bb900 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13bba60 </usr/include/stdio.h:178:1, col:34> col:12 fclose 'int (FILE *)' extern
| `-ParmVarDecl 0x13bb968 <col:20, col:26> col:26 __stream 'FILE *'
|-FunctionDecl 0x13bbbf8 <line:188:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:281:58> /usr/include/stdio.h:188:14 tmpfile 
'FILE *(void)' extern
| `-RestrictAttr 0x13bbc98 </usr/include/x86_64-linux-gnu/sys/cdefs.h:281:47> malloc
|-FunctionDecl 0x13c0450 </usr/include/stdio.h:205:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:205:14 tmpnam 'char *(char *)' extern
| |-ParmVarDecl 0x13c0350 <col:22, col:35> col:26 'char *':'char *'
| `-NoThrowAttr 0x13c04f8 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13c0648 </usr/include/stdio.h:210:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:210:14 tmpnam_r 'char *(char *)' extern
| |-ParmVarDecl 0x13c05b0 <col:24, col:41> col:29 __s 'char *':'char *'
| `-NoThrowAttr 0x13c06f0 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13c08c0 </usr/include/stdio.h:222:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:281:58> /usr/include/stdio.h:222:14 tempnam 'char *(const char *, const char *)' extern
| |-ParmVarDecl 0x13c0760 <col:23, col:35> col:35 __dir 'const char *'
| |-ParmVarDecl 0x13c07e0 <col:42, col:54> col:54 __pfx 'const char *'
| |-NoThrowAttr 0x13c0970 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
| `-RestrictAttr 0x13c09c8 <line:281:47> malloc
|-FunctionDecl 0x13c0a98 </usr/include/stdio.h:230:1, col:34> col:12 fflush 'int (FILE *)' extern
| `-ParmVarDecl 0x13c0a00 <col:20, col:26> col:26 __stream 'FILE *'
|-FunctionDecl 0x13c0be8 <line:239:1, col:43> col:12 fflush_unlocked 'int (FILE *)' extern
| `-ParmVarDecl 0x13c0b50 <col:29, col:35> col:35 __stream 'FILE *'
|-FunctionDecl 0x13c0e78 <line:258:14> col:14 implicit fopen 'FILE *(const char *, const char *)' extern
| |-ParmVarDecl 0x13c0f70 <<invalid sloc>> <invalid sloc> 'const char *'
| |-ParmVarDecl 0x13c0fd8 <<invalid sloc>> <invalid sloc> 'const char *'
| `-BuiltinAttr 0x13c0f18 <<invalid sloc>> Implicit 838
|-FunctionDecl 0x13c1050 prev 0x13c0e78 <col:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:281:58> /usr/include/stdio.h:258:14 fopen 'FILE *(const char *, const char *)' extern
| |-ParmVarDecl 0x13c0ca8 <col:21, col:44> col:44 __filename 'const char *restrict'
| |-ParmVarDecl 0x13c0d28 <line:259:7, col:30> col:30 __modes 'const char *restrict'
| |-BuiltinAttr 0x13c1158 <<invalid sloc>> Inherited Implicit 838
| `-RestrictAttr 0x13c1100 </usr/include/x86_64-linux-gnu/sys/cdefs.h:281:47> malloc
|-FunctionDecl 0x13c3458 </usr/include/stdio.h:265:1, line:267:34> line:265:14 freopen 'FILE *(const char *restrict, const char *restrict, FILE *restrict)' extern
| |-ParmVarDecl 0x13c1198 <col:23, col:46> col:46 __filename 'const char *restrict'
| |-ParmVarDecl 0x13c1218 <line:266:9, col:32> col:32 __modes 'const char *restrict'
| `-ParmVarDecl 0x13c1290 <line:267:9, col:26> col:26 __stream 'FILE *restrict'
|-FunctionDecl 0x13c36b8 <line:293:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:281:58> /usr/include/stdio.h:293:14 fdopen 'FILE *(int, const char *)' extern
| |-ParmVarDecl 0x13c3528 <col:22, col:26> col:26 __fd 'int'
| |-ParmVarDecl 0x13c35a8 <col:32, col:44> col:44 __modes 'const char *'
| |-NoThrowAttr 0x13c3768 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
| `-RestrictAttr 0x13c37c0 <line:281:47> malloc
|-FunctionDecl 0x13c3a18 </usr/include/stdio.h:308:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:281:58> /usr/include/stdio.h:308:14 fmemopen 'FILE *(void *, size_t, const char *)' extern
| |-ParmVarDecl 0x13c3800 <col:24, col:30> col:30 __s 'void *'
| |-ParmVarDecl 0x13c3878 <col:35, col:42> col:42 __len 'size_t':'unsigned long'
| |-ParmVarDecl 0x13c38f8 <col:49, col:61> col:61 __modes 'const char *'
| |-NoThrowAttr 0x13c3ad0 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
| `-RestrictAttr 0x13c3b28 <line:281:47> malloc
|-FunctionDecl 0x13c3d78 </usr/include/stdio.h:314:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:281:58> /usr/include/stdio.h:314:14 open_memstream 'FILE *(char **, size_t *)' extern
| |-ParmVarDecl 0x13c3b90 <col:30, col:37> col:37 __bufloc 'char **'
| |-ParmVarDecl 0x13c3c68 <col:47, col:55> col:55 __sizeloc 'size_t *'
| |-NoThrowAttr 0x13c3e28 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
| `-RestrictAttr 0x13c3e80 <line:281:47> malloc
|-FunctionDecl 0x13c4048 </usr/include/stdio.h:328:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:328:13 setbuf 'void (FILE *restrict, char *restrict)' extern
| |-ParmVarDecl 0x13c3eb8 <col:21, col:38> col:38 __stream 'FILE *restrict'
| |-ParmVarDecl 0x13c3f38 <col:48, col:65> col:65 __buf 'char *restrict'
| `-NoThrowAttr 0x13c40f8 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13c4440 </usr/include/stdio.h:332:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:332:12 setvbuf 'int (FILE *restrict, char *restrict, int, size_t)' extern
| |-ParmVarDecl 0x13c4160 <col:21, col:38> col:38 __stream 'FILE *restrict'
| |-ParmVarDecl 0x13c41e0 <col:48, col:65> col:65 __buf 'char *restrict'
| |-ParmVarDecl 0x13c4260 <line:333:7, col:11> col:11 __modes 'int'
| |-ParmVarDecl 0x13c42d8 <col:20, col:27> col:27 __n 'size_t':'unsigned long'
| `-NoThrowAttr 0x13c4500 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13c4788 </usr/include/stdio.h:338:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:338:13 setbuffer 'void (FILE *restrict, char *restrict, size_t)' extern
| |-ParmVarDecl 0x13c4568 <col:24, col:41> col:41 __stream 'FILE *restrict'
| |-ParmVarDecl 0x13c45e8 <col:51, col:68> col:68 __buf 'char *restrict'
| |-ParmVarDecl 0x13c4660 <line:339:10, col:17> col:17 __size 'size_t':'unsigned long'
| `-NoThrowAttr 0x13c4840 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13c4998 </usr/include/stdio.h:342:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:342:13 setlinebuf 'void (FILE *)' extern
| |-ParmVarDecl 0x13c48a8 <col:25, col:31> col:31 __stream 'FILE *'
| `-NoThrowAttr 0x13c4a40 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13c4c90 </usr/include/stdio.h:350:12> col:12 implicit fprintf 'int (FILE *, const char *, ...)' extern     
| |-ParmVarDecl 0x13c4d88 <<invalid sloc>> <invalid sloc> 'FILE *'
| |-ParmVarDecl 0x13c4df0 <<invalid sloc>> <invalid sloc> 'const char *'
| |-BuiltinAttr 0x13c4d30 <<invalid sloc>> Implicit 825
| `-FormatAttr 0x13c4e68 <col:12> Implicit printf 2 3
|-FunctionDecl 0x13c4ea0 prev 0x13c4c90 <col:1, line:351:43> line:350:12 fprintf 'int (FILE *, const char *, ...)' extern   
| |-ParmVarDecl 0x13c4aa8 <col:21, col:38> col:38 __stream 'FILE *restrict'
| |-ParmVarDecl 0x13c4b28 <line:351:7, col:30> col:30 __format 'const char *restrict'
| |-BuiltinAttr 0x13c4f80 <<invalid sloc>> Inherited Implicit 825
| `-FormatAttr 0x13c4fa8 <line:350:12> Inherited printf 2 3
|-FunctionDecl 0x13c5108 <line:356:12> col:12 implicit used printf 'int (const char *, ...)' extern
| |-ParmVarDecl 0x13c5200 <<invalid sloc>> <invalid sloc> 'const char *'
| |-BuiltinAttr 0x13c51a8 <<invalid sloc>> Implicit 824
| `-FormatAttr 0x13c5270 <col:12> Implicit printf 1 2
|-FunctionDecl 0x13c52a8 prev 0x13c5108 <col:1, col:56> col:12 used printf 'int (const char *, ...)' extern
| |-ParmVarDecl 0x13c4ff8 <col:20, col:43> col:43 __format 'const char *restrict'
| |-BuiltinAttr 0x13c5380 <<invalid sloc>> Inherited Implicit 824
| `-FormatAttr 0x13c53c0 <col:12> Inherited printf 1 2
|-FunctionDecl 0x13c55b8 <line:358:12> col:12 implicit sprintf 'int (char *, const char *, ...)' extern
| |-ParmVarDecl 0x13c56b0 <<invalid sloc>> <invalid sloc> 'char *'
| |-ParmVarDecl 0x13c5718 <<invalid sloc>> <invalid sloc> 'const char *'
| |-BuiltinAttr 0x13c5658 <<invalid sloc>> Implicit 827
| `-FormatAttr 0x13c5790 <col:12> Implicit printf 2 3
|-FunctionDecl 0x13c57c8 prev 0x13c55b8 <col:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:80:49> /usr/include/stdio.h:358:12 sprintf 'int (char *, const char *, ...)' extern
| |-ParmVarDecl 0x13c5410 <col:21, col:38> col:38 __s 'char *restrict'
| |-ParmVarDecl 0x13c5490 <line:359:7, col:30> col:30 __format 'const char *restrict'
| |-BuiltinAttr 0x13c58d0 <<invalid sloc>> Inherited Implicit 827
| |-FormatAttr 0x13c58f8 <line:358:12> Inherited printf 2 3
| `-NoThrowAttr 0x13c5878 </usr/include/x86_64-linux-gnu/sys/cdefs.h:80:37>
|-FunctionDecl 0x13c5c10 </usr/include/stdio.h:365:12> col:12 implicit vfprintf 'int (FILE *, const char *, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13c5d08 <<invalid sloc>> <invalid sloc> 'FILE *'
| |-ParmVarDecl 0x13c5d70 <<invalid sloc>> <invalid sloc> 'const char *'
| |-ParmVarDecl 0x13c5dd8 <<invalid sloc>> <invalid sloc> 'struct __va_list_tag *'
| |-BuiltinAttr 0x13c5cb0 <<invalid sloc>> Implicit 829
| `-FormatAttr 0x13c5e58 <col:12> Implicit printf 2 0
|-FunctionDecl 0x13c5e90 prev 0x13c5c10 <col:1, line:366:28> line:365:12 vfprintf 'int (FILE *, const char *, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13c5940 <col:22, col:39> col:39 __s 'FILE *restrict'
| |-ParmVarDecl 0x13c59c0 <col:44, col:67> col:67 __format 'const char *restrict'
| |-ParmVarDecl 0x13c5aa0 <line:366:8, col:23> col:23 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13c5f78 <<invalid sloc>> Inherited Implicit 829
| `-FormatAttr 0x13c5fa0 <line:365:12> Inherited printf 2 0
|-FunctionDecl 0x13c6180 <line:371:12> col:12 implicit vprintf 'int (const char *, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13c6278 <<invalid sloc>> <invalid sloc> 'const char *'
| |-ParmVarDecl 0x13c62e0 <<invalid sloc>> <invalid sloc> 'struct __va_list_tag *'
| |-BuiltinAttr 0x13c6220 <<invalid sloc>> Implicit 828
| `-FormatAttr 0x13c6358 <col:12> Implicit printf 1 0
|-FunctionDecl 0x13c6470 prev 0x13c6180 <col:1, col:74> col:12 vprintf 'int (const char *, struct __va_list_tag *)' extern  
| |-ParmVarDecl 0x13c5ff0 <col:21, col:44> col:44 __format 'const char *restrict'
| |-ParmVarDecl 0x13c6068 <col:54, col:69> col:69 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13c6550 <<invalid sloc>> Inherited Implicit 828
| `-FormatAttr 0x13c6578 <col:12> Inherited printf 1 0
|-FunctionDecl 0x13c67f0 <line:373:12> col:12 implicit vsprintf 'int (char *, const char *, struct __va_list_tag *)' extern 
| |-ParmVarDecl 0x13c68e8 <<invalid sloc>> <invalid sloc> 'char *'
| |-ParmVarDecl 0x13c6950 <<invalid sloc>> <invalid sloc> 'const char *'
| |-ParmVarDecl 0x13c69b8 <<invalid sloc>> <invalid sloc> 'struct __va_list_tag *'
| |-BuiltinAttr 0x13c6890 <<invalid sloc>> Implicit 831
| `-FormatAttr 0x13c6a38 <col:12> Implicit printf 2 0
|-FunctionDecl 0x13c6a70 prev 0x13c67f0 <col:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:80:49> /usr/include/stdio.h:373:12 vsprintf 'int (char *, const char *, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13c65c8 <col:22, col:39> col:39 __s 'char *restrict'
| |-ParmVarDecl 0x13c6648 <col:44, col:67> col:67 __format 'const char *restrict'
| |-ParmVarDecl 0x13c66c0 <line:374:8, col:23> col:23 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13c6b80 <<invalid sloc>> Inherited Implicit 831
| |-FormatAttr 0x13c6ba8 <line:373:12> Inherited printf 2 0
| `-NoThrowAttr 0x13c6b28 </usr/include/x86_64-linux-gnu/sys/cdefs.h:80:37>
|-FunctionDecl 0x13c6e88 </usr/include/stdio.h:378:12> col:12 implicit snprintf 'int (char *, unsigned long, const char *, ...)' extern
| |-ParmVarDecl 0x13c6f80 <<invalid sloc>> <invalid sloc> 'char *'
| |-ParmVarDecl 0x13c6fe8 <<invalid sloc>> <invalid sloc> 'unsigned long'
| |-ParmVarDecl 0x13c7050 <<invalid sloc>> <invalid sloc> 'const char *'
| |-BuiltinAttr 0x13c6f28 <<invalid sloc>> Implicit 826
| `-FormatAttr 0x13c70d0 <col:12> Implicit printf 3 4
|-FunctionDecl 0x13c7108 prev 0x13c6e88 <col:1, line:380:62> line:378:12 snprintf 'int (char *, unsigned long, const char *, ...)' extern
| |-ParmVarDecl 0x13c6bf8 <col:22, col:39> col:39 __s 'char *restrict'
| |-ParmVarDecl 0x13c6c70 <col:44, col:51> col:51 __maxlen 'size_t':'unsigned long'
| |-ParmVarDecl 0x13c6cf0 <line:379:8, col:31> col:31 __format 'const char *restrict'
| |-BuiltinAttr 0x13c7250 <<invalid sloc>> Inherited Implicit 826
| |-NoThrowAttr 0x13c71c0 </usr/include/x86_64-linux-gnu/sys/cdefs.h:80:37>
| `-FormatAttr 0x13c7218 </usr/include/stdio.h:380:32, col:60> printf 3 4
|-FunctionDecl 0x13c75b0 <line:382:12> col:12 implicit vsnprintf 'int (char *, unsigned long, const char *, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13c76a8 <<invalid sloc>> <invalid sloc> 'char *'
| |-ParmVarDecl 0x13c7710 <<invalid sloc>> <invalid sloc> 'unsigned long'
| |-ParmVarDecl 0x13c7778 <<invalid sloc>> <invalid sloc> 'const char *'
| |-ParmVarDecl 0x13c77e0 <<invalid sloc>> <invalid sloc> 'struct __va_list_tag *'
| |-BuiltinAttr 0x13c7650 <<invalid sloc>> Implicit 830
| `-FormatAttr 0x13c7868 <col:12> Implicit printf 3 0
|-FunctionDecl 0x13c78a0 prev 0x13c75b0 <col:1, line:384:62> line:382:12 vsnprintf 'int (char *, unsigned long, const char *, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13c7290 <col:23, col:40> col:40 __s 'char *restrict'
| |-ParmVarDecl 0x13c7308 <col:45, col:52> col:52 __maxlen 'size_t':'unsigned long'
| |-ParmVarDecl 0x13c7388 <line:383:9, col:32> col:32 __format 'const char *restrict'
| |-ParmVarDecl 0x13c7400 <col:42, col:57> col:57 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13c79f0 <<invalid sloc>> Inherited Implicit 830
| |-NoThrowAttr 0x13c7960 </usr/include/x86_64-linux-gnu/sys/cdefs.h:80:37>
| `-FormatAttr 0x13c79b8 </usr/include/stdio.h:384:32, col:60> printf 3 0
|-FunctionDecl 0x13c7ca0 <line:403:1, line:405:52> line:403:12 vdprintf 'int (int, const char *restrict, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13c7a30 <col:22, col:26> col:26 __fd 'int'
| |-ParmVarDecl 0x13c7ab0 <col:32, col:55> col:55 __fmt 'const char *restrict'
| |-ParmVarDecl 0x13c7b28 <line:404:8, col:23> col:23 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| `-FormatAttr 0x13c7d58 <line:405:22, col:50> printf 2 0
|-FunctionDecl 0x13c7fc8 <line:406:1, line:407:52> line:406:12 dprintf 'int (int, const char *restrict, ...)' extern        
| |-ParmVarDecl 0x13c7dd8 <col:21, col:25> col:25 __fd 'int'
| |-ParmVarDecl 0x13c7e58 <col:31, col:54> col:54 __fmt 'const char *restrict'
| `-FormatAttr 0x13c8078 <line:407:22, col:50> printf 2 3
|-FunctionDecl 0x13c8210 <line:415:12> col:12 implicit fscanf 'int (FILE *restrict, const char *restrict, ...)' extern      
| |-ParmVarDecl 0x13c8308 <<invalid sloc>> <invalid sloc> 'FILE *restrict'
| |-ParmVarDecl 0x13c8370 <<invalid sloc>> <invalid sloc> 'const char *restrict'
| |-BuiltinAttr 0x13c82b0 <<invalid sloc>> Implicit 833
| `-FormatAttr 0x13c83e8 <col:12> Implicit scanf 2 3
|-FunctionDecl 0x13c94b0 prev 0x13c8210 <col:1, line:416:42> line:415:12 fscanf 'int (FILE *restrict, const char *restrict, 
...)' extern
| |-ParmVarDecl 0x13c80f0 <col:20, col:37> col:37 __stream 'FILE *restrict'
| |-ParmVarDecl 0x13c8170 <line:416:6, col:29> col:29 __format 'const char *restrict'
| |-BuiltinAttr 0x13c9590 <<invalid sloc>> Inherited Implicit 833
| `-FormatAttr 0x13c95b8 <line:415:12> Inherited scanf 2 3
|-FunctionDecl 0x13c96a0 <line:421:12> col:12 implicit scanf 'int (const char *restrict, ...)' extern
| |-ParmVarDecl 0x13c9798 <<invalid sloc>> <invalid sloc> 'const char *restrict'
| |-BuiltinAttr 0x13c9740 <<invalid sloc>> Implicit 832
| `-FormatAttr 0x13c9808 <col:12> Implicit scanf 1 2
|-FunctionDecl 0x13c9840 prev 0x13c96a0 <col:1, col:55> col:12 scanf 'int (const char *restrict, ...)' extern
| |-ParmVarDecl 0x13c9608 <col:19, col:42> col:42 __format 'const char *restrict'
| |-BuiltinAttr 0x13c9918 <<invalid sloc>> Inherited Implicit 832
| `-FormatAttr 0x13c9940 <col:12> Inherited scanf 1 2
|-FunctionDecl 0x13c9b38 <line:423:12> col:12 implicit sscanf 'int (const char *restrict, const char *restrict, ...)' extern| |-ParmVarDecl 0x13c9c30 <<invalid sloc>> <invalid sloc> 'const char *restrict'
| |-ParmVarDecl 0x13c9c98 <<invalid sloc>> <invalid sloc> 'const char *restrict'
| |-BuiltinAttr 0x13c9bd8 <<invalid sloc>> Implicit 834
| `-FormatAttr 0x13c9d10 <col:12> Implicit scanf 2 3
|-FunctionDecl 0x13c9d48 prev 0x13c9b38 <col:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:423:12 sscanf 'int (const char *restrict, const char *restrict, ...)' extern
| |-ParmVarDecl 0x13c9990 <col:20, col:43> col:43 __s 'const char *restrict'
| |-ParmVarDecl 0x13c9a10 <line:424:6, col:29> col:29 __format 'const char *restrict'
| |-BuiltinAttr 0x13c9e50 <<invalid sloc>> Inherited Implicit 834
| |-FormatAttr 0x13c9e78 <line:423:12> Inherited scanf 2 3
| `-NoThrowAttr 0x13c9df8 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-TypedefDecl 0x13c9ec8 </usr/include/x86_64-linux-gnu/bits/floatn-common.h:214:1, col:15> col:15 _Float32 'float'
| `-BuiltinType 0x131ac30 'float'
|-TypedefDecl 0x13c9f38 <line:251:1, col:16> col:16 _Float64 'double'
| `-BuiltinType 0x131ac50 'double'
|-TypedefDecl 0x13c9fa8 <line:268:1, col:16> col:16 _Float32x 'double'
| `-BuiltinType 0x131ac50 'double'
|-TypedefDecl 0x13ca018 <line:285:1, col:21> col:21 _Float64x 'long double'
| `-BuiltinType 0x131ac70 'long double'
|-FunctionDecl 0x13ca210 prev 0x13c94b0 </usr/include/stdio.h:434:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:247:79> /usr/include/stdio.h:434:24 fscanf 'int (FILE *restrict, const char *restrict, ...)' extern
| |-ParmVarDecl 0x13ca080 <col:33, col:50> col:50 __stream 'FILE *restrict'
| |-ParmVarDecl 0x13ca100 <line:435:5, col:28> col:28 __format 'const char *restrict'
| |-BuiltinAttr 0x13ca338 <<invalid sloc>> Inherited Implicit 833
| |-FormatAttr 0x13ca360 <line:415:12> Inherited scanf 2 3
| `-AsmLabelAttr 0x13ca2b0 <<scratch space>:32:1> "__isoc99_fscanf" IsLiteralLabel
|-FunctionDecl 0x13d58f0 prev 0x13c9840 </usr/include/stdio.h:437:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:247:79> /usr/include/stdio.h:437:24 scanf 'int (const char *restrict, ...)' extern
| |-ParmVarDecl 0x13ca3b0 <col:32, col:55> col:55 __format 'const char *restrict'
| |-BuiltinAttr 0x13d5a10 <<invalid sloc>> Inherited Implicit 832
| |-FormatAttr 0x13d5a38 <line:421:12> Inherited scanf 1 2
| `-AsmLabelAttr 0x13d5990 <<scratch space>:34:1> "__isoc99_scanf" IsLiteralLabel
|-FunctionDecl 0x13d5bd8 prev 0x13c9d48 </usr/include/stdio.h:439:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:439:28 sscanf 'int (const char *restrict, const char *restrict, ...)' extern
| |-ParmVarDecl 0x13d5a88 <col:37, col:60> col:60 __s 'const char *restrict'
| |-ParmVarDecl 0x13d5b08 <line:440:9, col:32> col:32 __format 'const char *restrict'
| |-BuiltinAttr 0x13d5d28 <<invalid sloc>> Inherited Implicit 834
| |-FormatAttr 0x13d5d50 <line:423:12> Inherited scanf 2 3
| |-AsmLabelAttr 0x13d5c78 <<scratch space>:36:1> "__isoc99_sscanf" IsLiteralLabel
| `-NoThrowAttr 0x13d5d00 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13d5fd0 </usr/include/stdio.h:459:12> col:12 implicit vfscanf 'int (FILE *restrict, const char *restrict, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13d60c8 <<invalid sloc>> <invalid sloc> 'FILE *restrict'
| |-ParmVarDecl 0x13d6130 <<invalid sloc>> <invalid sloc> 'const char *restrict'
| |-ParmVarDecl 0x13d6198 <<invalid sloc>> <invalid sloc> 'struct __va_list_tag *'
| |-BuiltinAttr 0x13d6070 <<invalid sloc>> Implicit 836
| `-FormatAttr 0x13d6218 <col:12> Implicit scanf 2 0
|-FunctionDecl 0x13d6250 prev 0x13d5fd0 <col:1, line:461:51> line:459:12 vfscanf 'int (FILE *restrict, const char *restrict, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13d5d98 <col:21, col:38> col:38 __s 'FILE *restrict'
| |-ParmVarDecl 0x13d5e18 <col:43, col:66> col:66 __format 'const char *restrict'
| |-ParmVarDecl 0x13d5e90 <line:460:7, col:22> col:22 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13d6370 <<invalid sloc>> Inherited Implicit 836
| `-FormatAttr 0x13d6308 <line:461:22, col:49> scanf 2 0
|-FunctionDecl 0x13d6558 <line:467:12> col:12 implicit vscanf 'int (const char *restrict, struct __va_list_tag *)' extern   
| |-ParmVarDecl 0x13d6650 <<invalid sloc>> <invalid sloc> 'const char *restrict'
| |-ParmVarDecl 0x13d66b8 <<invalid sloc>> <invalid sloc> 'struct __va_list_tag *'
| |-BuiltinAttr 0x13d65f8 <<invalid sloc>> Implicit 835
| `-FormatAttr 0x13d6730 <col:12> Implicit scanf 1 0
|-FunctionDecl 0x13d6768 prev 0x13d6558 <col:1, line:468:51> line:467:12 vscanf 'int (const char *restrict, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13d63b0 <col:20, col:43> col:43 __format 'const char *restrict'
| |-ParmVarDecl 0x13d6428 <col:53, col:68> col:68 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13d6880 <<invalid sloc>> Inherited Implicit 835
| `-FormatAttr 0x13d6818 <line:468:22, col:49> scanf 1 0
|-FunctionDecl 0x13d79e0 <line:471:12> col:12 implicit vsscanf 'int (const char *restrict, const char *restrict, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13d7ad8 <<invalid sloc>> <invalid sloc> 'const char *restrict'
| |-ParmVarDecl 0x13d7b40 <<invalid sloc>> <invalid sloc> 'const char *restrict'
| |-ParmVarDecl 0x13d7ba8 <<invalid sloc>> <invalid sloc> 'struct __va_list_tag *'
| |-BuiltinAttr 0x13d7a80 <<invalid sloc>> Implicit 837
| `-FormatAttr 0x13d7c28 <col:12> Implicit scanf 2 0
|-FunctionDecl 0x13d7c60 prev 0x13d79e0 <col:1, line:473:59> line:471:12 vsscanf 'int (const char *restrict, const char *restrict, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13d7730 <col:21, col:44> col:44 __s 'const char *restrict'
| |-ParmVarDecl 0x13d77b0 <line:472:7, col:30> col:30 __format 'const char *restrict'
| |-ParmVarDecl 0x13d7828 <col:40, col:55> col:55 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13d7da8 <<invalid sloc>> Inherited Implicit 837
| |-NoThrowAttr 0x13d7d18 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
| `-FormatAttr 0x13d7d70 </usr/include/stdio.h:473:30, col:57> scanf 2 0
|-FunctionDecl 0x13d8038 prev 0x13d6250 <line:479:1, line:483:51> line:479:24 vfscanf 'int (FILE *restrict, const char *restrict, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13d7de0 <line:480:11, col:28> col:28 __s 'FILE *restrict'
| |-ParmVarDecl 0x13d7e60 <line:481:4, col:27> col:27 __format 'const char *restrict'
| |-ParmVarDecl 0x13d7ed8 <col:37, col:52> col:52 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13d81a0 <<invalid sloc>> Inherited Implicit 836
| |-AsmLabelAttr 0x13d80d8 <<scratch space>:39:1> "__isoc99_vfscanf" IsLiteralLabel
| `-FormatAttr 0x13d8168 </usr/include/stdio.h:483:22, col:49> scanf 2 0
|-FunctionDecl 0x13d8378 prev 0x13d6768 <line:484:1, line:486:51> line:484:24 vscanf 'int (const char *restrict, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13d81e0 <col:33, col:56> col:56 __format 'const char *restrict'
| |-ParmVarDecl 0x13d8258 <line:485:5, col:20> col:20 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13d84d8 <<invalid sloc>> Inherited Implicit 835
| |-AsmLabelAttr 0x13d8418 <<scratch space>:41:1> "__isoc99_vscanf" IsLiteralLabel
| `-FormatAttr 0x13d84a0 </usr/include/stdio.h:486:22, col:49> scanf 1 0
|-FunctionDecl 0x13d8780 prev 0x13d7c60 <line:487:1, line:491:51> line:487:28 vsscanf 'int (const char *restrict, const char *restrict, struct __va_list_tag *)' extern
| |-ParmVarDecl 0x13d8518 <line:488:8, col:31> col:31 __s 'const char *restrict'
| |-ParmVarDecl 0x13d8598 <line:489:8, col:31> col:31 __format 'const char *restrict'
| |-ParmVarDecl 0x13d8610 <line:490:8, col:23> col:23 __arg 'struct __va_list_tag *':'struct __va_list_tag *'
| |-BuiltinAttr 0x13d8910 <<invalid sloc>> Inherited Implicit 837
| |-AsmLabelAttr 0x13d8820 <<scratch space>:43:1> "__isoc99_vsscanf" IsLiteralLabel
| |-NoThrowAttr 0x13d88b0 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
| `-FormatAttr 0x13d88d8 </usr/include/stdio.h:491:22, col:49> scanf 2 0
|-FunctionDecl 0x13d89e0 <line:513:1, col:33> col:12 fgetc 'int (FILE *)' extern
| `-ParmVarDecl 0x13d8948 <col:19, col:25> col:25 __stream 'FILE *'
|-FunctionDecl 0x13d8b30 <line:514:1, col:32> col:12 getc 'int (FILE *)' extern
| `-ParmVarDecl 0x13d8a98 <col:18, col:24> col:24 __stream 'FILE *'
|-FunctionDecl 0x13d8ca0 <line:520:1, col:25> col:12 getchar 'int (void)' extern
|-FunctionDecl 0x13d8de8 <line:527:1, col:41> col:12 getc_unlocked 'int (FILE *)' extern
| `-ParmVarDecl 0x13d8d50 <col:27, col:33> col:33 __stream 'FILE *'
|-FunctionDecl 0x13d8f30 <line:528:1, col:34> col:12 getchar_unlocked 'int (void)' extern
|-FunctionDecl 0x13d9078 <line:538:1, col:42> col:12 fgetc_unlocked 'int (FILE *)' extern
| `-ParmVarDecl 0x13d8fe0 <col:28, col:34> col:34 __stream 'FILE *'
|-FunctionDecl 0x13d92d0 <line:549:1, col:42> col:12 fputc 'int (int, FILE *)' extern
| |-ParmVarDecl 0x13d9138 <col:19, col:23> col:23 __c 'int'
| `-ParmVarDecl 0x13d91b0 <col:28, col:34> col:34 __stream 'FILE *'
|-FunctionDecl 0x13d94b0 <line:550:1, col:41> col:12 putc 'int (int, FILE *)' extern
| |-ParmVarDecl 0x13d9398 <col:18, col:22> col:22 __c 'int'
| `-ParmVarDecl 0x13d9410 <col:27, col:33> col:33 __stream 'FILE *'
|-FunctionDecl 0x13d9640 <line:556:1, col:28> col:12 putchar 'int (int)' extern
| `-ParmVarDecl 0x13d9578 <col:21, col:25> col:25 __c 'int'
|-FunctionDecl 0x13d9868 <line:565:1, col:51> col:12 fputc_unlocked 'int (int, FILE *)' extern
| |-ParmVarDecl 0x13d9750 <col:28, col:32> col:32 __c 'int'
| `-ParmVarDecl 0x13d97c8 <col:37, col:43> col:43 __stream 'FILE *'
|-FunctionDecl 0x13d9a48 <line:573:1, col:50> col:12 putc_unlocked 'int (int, FILE *)' extern
| |-ParmVarDecl 0x13d9930 <col:27, col:31> col:31 __c 'int'
| `-ParmVarDecl 0x13d99a8 <col:36, col:42> col:42 __stream 'FILE *'
|-FunctionDecl 0x13d9ba8 <line:574:1, col:37> col:12 putchar_unlocked 'int (int)' extern
| `-ParmVarDecl 0x13d9b10 <col:30, col:34> col:34 __c 'int'
|-FunctionDecl 0x13d9cf8 <line:581:1, col:32> col:12 getw 'int (FILE *)' extern
| `-ParmVarDecl 0x13d9c60 <col:18, col:24> col:24 __stream 'FILE *'
|-FunctionDecl 0x13d9ed0 <line:584:1, col:41> col:12 putw 'int (int, FILE *)' extern
| |-ParmVarDecl 0x13d9db8 <col:18, col:22> col:22 __w 'int'
| `-ParmVarDecl 0x13d9e30 <col:27, col:33> col:33 __stream 'FILE *'
|-FunctionDecl 0x13da1c0 <line:592:1, col:77> col:14 fgets 'char *(char *restrict, int, FILE *restrict)' extern
| |-ParmVarDecl 0x13d9f98 <col:21, col:38> col:38 __s 'char *restrict'
| |-ParmVarDecl 0x13da018 <col:43, col:47> col:47 __n 'int'
| `-ParmVarDecl 0x13da090 <col:52, col:69> col:69 __stream 'FILE *restrict'
|-FunctionDecl 0x13da548 <line:632:1, line:634:55> line:632:18 __getdelim '__ssize_t (char **restrict, size_t *restrict, int, FILE *restrict)' extern
| |-ParmVarDecl 0x13da290 <col:30, col:48> col:48 __lineptr 'char **restrict'
| |-ParmVarDecl 0x13da308 <line:633:30, col:49> col:49 __n 'size_t *restrict'
| |-ParmVarDecl 0x13da388 <col:54, col:58> col:58 __delimiter 'int'
| `-ParmVarDecl 0x13da400 <line:634:30, col:47> col:47 __stream 'FILE *restrict'
|-FunctionDecl 0x13da880 <line:635:1, line:637:53> line:635:18 getdelim '__ssize_t (char **restrict, size_t *restrict, int, 
FILE *restrict)' extern
| |-ParmVarDecl 0x13da620 <col:28, col:46> col:46 __lineptr 'char **restrict'
| |-ParmVarDecl 0x13da698 <line:636:28, col:47> col:47 __n 'size_t *restrict'
| |-ParmVarDecl 0x13da760 <col:52, col:56> col:56 __delimiter 'int'
| `-ParmVarDecl 0x13da7d8 <line:637:28, col:45> col:45 __stream 'FILE *restrict'
|-FunctionDecl 0x13dab68 <line:645:1, line:647:52> line:645:18 getline '__ssize_t (char **restrict, size_t *restrict, FILE *restrict)' extern
| |-ParmVarDecl 0x13da958 <col:27, col:45> col:45 __lineptr 'char **restrict'
| |-ParmVarDecl 0x13da9d0 <line:646:27, col:46> col:46 __n 'size_t *restrict'
| `-ParmVarDecl 0x13daa48 <line:647:27, col:44> col:44 __stream 'FILE *restrict'
|-FunctionDecl 0x13dadd0 <line:655:1, col:72> col:12 fputs 'int (const char *restrict, FILE *restrict)' extern
| |-ParmVarDecl 0x13dac38 <col:19, col:42> col:42 __s 'const char *restrict'
| `-ParmVarDecl 0x13dacb0 <col:47, col:64> col:64 __stream 'FILE *restrict'
|-FunctionDecl 0x13daf30 <line:661:1, col:33> col:12 puts 'int (const char *)' extern
| `-ParmVarDecl 0x13dae98 <col:18, col:30> col:30 __s 'const char *'
|-FunctionDecl 0x13db108 <line:668:1, col:43> col:12 ungetc 'int (int, FILE *)' extern
| |-ParmVarDecl 0x13daff0 <col:20, col:24> col:24 __c 'int'
| `-ParmVarDecl 0x13db068 <col:29, col:35> col:35 __stream 'FILE *'
|-FunctionDecl 0x13db4c8 <line:675:15> col:15 implicit fread 'unsigned long (void *, unsigned long, unsigned long, FILE *)' 
extern
| |-ParmVarDecl 0x13db5c0 <<invalid sloc>> <invalid sloc> 'void *'
| |-ParmVarDecl 0x13db628 <<invalid sloc>> <invalid sloc> 'unsigned long'
| |-ParmVarDecl 0x13db690 <<invalid sloc>> <invalid sloc> 'unsigned long'
| |-ParmVarDecl 0x13db6f8 <<invalid sloc>> <invalid sloc> 'FILE *'
| `-BuiltinAttr 0x13db568 <<invalid sloc>> Implicit 839
|-FunctionDecl 0x13db790 prev 0x13db4c8 <col:1, line:676:45> line:675:15 fread 'unsigned long (void *, unsigned long, unsigned long, FILE *)' extern
| |-ParmVarDecl 0x13db1d0 <col:22, col:39> col:39 __ptr 'void *restrict'
| |-ParmVarDecl 0x13db248 <col:46, col:53> col:53 __size 'size_t':'unsigned long'
| |-ParmVarDecl 0x13db2c0 <line:676:8, col:15> col:15 __n 'size_t':'unsigned long'
| |-ParmVarDecl 0x13db338 <col:20, col:37> col:37 __stream 'FILE *restrict'
| `-BuiltinAttr 0x13db880 <<invalid sloc>> Inherited Implicit 839
|-FunctionDecl 0x13dbbe8 <line:681:15> col:15 implicit fwrite 'unsigned long (const void *, unsigned long, unsigned long, FILE *)' extern
| |-ParmVarDecl 0x13dbce0 <<invalid sloc>> <invalid sloc> 'const void *'
| |-ParmVarDecl 0x13dbd48 <<invalid sloc>> <invalid sloc> 'unsigned long'
| |-ParmVarDecl 0x13dbdb0 <<invalid sloc>> <invalid sloc> 'unsigned long'
| |-ParmVarDecl 0x13dbe18 <<invalid sloc>> <invalid sloc> 'FILE *'
| `-BuiltinAttr 0x13dbc88 <<invalid sloc>> Implicit 840
|-FunctionDecl 0x13dbea0 prev 0x13dbbe8 <col:1, line:682:41> line:681:15 fwrite 'unsigned long (const void *, unsigned long, unsigned long, FILE *)' extern
| |-ParmVarDecl 0x13db8f0 <col:23, col:46> col:46 __ptr 'const void *restrict'
| |-ParmVarDecl 0x13db968 <col:53, col:60> col:60 __size 'size_t':'unsigned long'
| |-ParmVarDecl 0x13db9e0 <line:682:9, col:16> col:16 __n 'size_t':'unsigned long'
| |-ParmVarDecl 0x13dba58 <col:21, col:38> col:38 __s 'FILE *restrict'
| `-BuiltinAttr 0x13dbf90 <<invalid sloc>> Inherited Implicit 840
|-FunctionDecl 0x13dc1e0 <line:702:1, line:703:47> line:702:15 fread_unlocked 'size_t (void *restrict, size_t, size_t, FILE 
*restrict)' extern
| |-ParmVarDecl 0x13dbfd0 <col:31, col:48> col:48 __ptr 'void *restrict'
| |-ParmVarDecl 0x13dc048 <col:55, col:62> col:62 __size 'size_t':'unsigned long'
| |-ParmVarDecl 0x13dc0c0 <line:703:10, col:17> col:17 __n 'size_t':'unsigned long'
| `-ParmVarDecl 0x13dc138 <col:22, col:39> col:39 __stream 'FILE *restrict'
|-FunctionDecl 0x13dc4c8 <line:704:1, line:705:48> line:704:15 fwrite_unlocked 'size_t (const void *restrict, size_t, size_t, FILE *restrict)' extern
| |-ParmVarDecl 0x13dc2b8 <col:32, col:55> col:55 __ptr 'const void *restrict'
| |-ParmVarDecl 0x13dc330 <col:62, col:69> col:69 __size 'size_t':'unsigned long'
| |-ParmVarDecl 0x13dc3a8 <line:705:11, col:18> col:18 __n 'size_t':'unsigned long'
| `-ParmVarDecl 0x13dc420 <col:23, col:40> col:40 __stream 'FILE *restrict'
|-FunctionDecl 0x13dc800 <line:713:1, col:63> col:12 fseek 'int (FILE *, long, int)' extern
| |-ParmVarDecl 0x13dc598 <col:19, col:25> col:25 __stream 'FILE *'
| |-ParmVarDecl 0x13dc618 <col:35, col:44> col:44 __off 'long'
| `-ParmVarDecl 0x13dc698 <col:51, col:55> col:55 __whence 'int'
|-FunctionDecl 0x13dc9c0 <line:718:1, col:38> col:17 ftell 'long (FILE *)' extern
| `-ParmVarDecl 0x13dc8c8 <col:24, col:30> col:30 __stream 'FILE *'
|-FunctionDecl 0x13dcb08 <line:723:1, col:35> col:13 rewind 'void (FILE *)' extern
| `-ParmVarDecl 0x13dca78 <col:21, col:27> col:27 __stream 'FILE *'
|-FunctionDecl 0x13dcda0 <line:736:1, col:63> col:12 fseeko 'int (FILE *, __off_t, int)' extern
| |-ParmVarDecl 0x13dcbc0 <col:20, col:26> col:26 __stream 'FILE *'
| |-ParmVarDecl 0x13dcc38 <col:36, col:44> col:44 __off '__off_t':'long'
| `-ParmVarDecl 0x13dccb8 <col:51, col:55> col:55 __whence 'int'
|-FunctionDecl 0x13dcf28 <line:741:1, col:38> col:16 ftello '__off_t (FILE *)' extern
| `-ParmVarDecl 0x13dce68 <col:24, col:30> col:30 __stream 'FILE *'
|-FunctionDecl 0x13dd1f0 <line:760:1, col:72> col:12 fgetpos 'int (FILE *restrict, fpos_t *restrict)' extern
| |-ParmVarDecl 0x13dcfe0 <col:21, col:38> col:38 __stream 'FILE *restrict'
| `-ParmVarDecl 0x13dd0d8 <col:48, col:67> col:67 __pos 'fpos_t *restrict'
|-FunctionDecl 0x13dd4a0 <line:765:1, col:56> col:12 fsetpos 'int (FILE *, const fpos_t *)' extern
| |-ParmVarDecl 0x13dd2b0 <col:21, col:27> col:27 __stream 'FILE *'
| `-ParmVarDecl 0x13dd388 <col:37, col:51> col:51 __pos 'const fpos_t *'
|-FunctionDecl 0x13dd5f0 <line:786:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:786:13 clearerr 
'void (FILE *)' extern
| |-ParmVarDecl 0x13dd560 <col:23, col:29> col:29 __stream 'FILE *'
| `-NoThrowAttr 0x13dd698 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13dd7c0 </usr/include/stdio.h:788:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:788:12 feof 'int (FILE *)' extern
| |-ParmVarDecl 0x13dd700 <col:18, col:24> col:24 __stream 'FILE *'
| `-NoThrowAttr 0x13dd868 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13dd968 </usr/include/stdio.h:790:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:790:12 ferror 'int (FILE *)' extern
| |-ParmVarDecl 0x13dd8d0 <col:20, col:26> col:26 __stream 'FILE *'
| `-NoThrowAttr 0x13dda10 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13ddb08 </usr/include/stdio.h:794:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:794:13 clearerr_unlocked 'void (FILE *)' extern
| |-ParmVarDecl 0x13dda78 <col:32, col:38> col:38 __stream 'FILE *'
| `-NoThrowAttr 0x13ddbb0 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13ddcb0 </usr/include/stdio.h:795:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:795:12 feof_unlocked 'int (FILE *)' extern
| |-ParmVarDecl 0x13ddc18 <col:27, col:33> col:33 __stream 'FILE *'
| `-NoThrowAttr 0x13ddd58 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13dde58 </usr/include/stdio.h:796:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:796:12 ferror_unlocked 'int (FILE *)' extern
| |-ParmVarDecl 0x13dddc0 <col:29, col:35> col:35 __stream 'FILE *'
| `-NoThrowAttr 0x13ddf00 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13de038 </usr/include/stdio.h:804:1, col:36> col:13 perror 'void (const char *)' extern
| `-ParmVarDecl 0x13ddf70 <col:21, col:33> col:33 __s 'const char *'
|-FunctionDecl 0x13de188 <line:809:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:809:12 fileno 'int (FILE *)' extern
| |-ParmVarDecl 0x13de0f0 <col:20, col:26> col:26 __stream 'FILE *'
| `-NoThrowAttr 0x13de230 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13de330 </usr/include/stdio.h:814:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:814:12 fileno_unlocked 'int (FILE *)' extern
| |-ParmVarDecl 0x13de298 <col:29, col:35> col:35 __stream 'FILE *'
| `-NoThrowAttr 0x13de3d8 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13de4d8 </usr/include/stdio.h:823:1, col:34> col:12 pclose 'int (FILE *)' extern
| `-ParmVarDecl 0x13de440 <col:20, col:26> col:26 __stream 'FILE *'
|-FunctionDecl 0x13de6b0 <line:829:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:281:58> /usr/include/stdio.h:829:14 popen 'FILE *(const char *, const char *)' extern
| |-ParmVarDecl 0x13de598 <col:21, col:33> col:33 __command 'const char *'
| |-ParmVarDecl 0x13de618 <col:44, col:56> col:56 __modes 'const char *'
| `-RestrictAttr 0x13de760 </usr/include/x86_64-linux-gnu/sys/cdefs.h:281:47> malloc
|-FunctionDecl 0x13df890 </usr/include/stdio.h:837:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:837:14 ctermid 'char *(char *)' extern
| |-ParmVarDecl 0x13df7f8 <col:23, col:29> col:29 __s 'char *'
| `-NoThrowAttr 0x13df938 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13dfa30 </usr/include/stdio.h:867:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:867:13 flockfile 'void (FILE *)' extern
| |-ParmVarDecl 0x13df9a0 <col:24, col:30> col:30 __stream 'FILE *'
| `-NoThrowAttr 0x13dfad8 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13dfbd8 </usr/include/stdio.h:871:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:871:12 ftrylockfile 'int (FILE *)' extern
| |-ParmVarDecl 0x13dfb40 <col:26, col:32> col:32 __stream 'FILE *'
| `-NoThrowAttr 0x13dfc80 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13dfd78 </usr/include/stdio.h:874:1, /usr/include/x86_64-linux-gnu/sys/cdefs.h:79:54> /usr/include/stdio.h:874:13 funlockfile 'void (FILE *)' extern
| |-ParmVarDecl 0x13dfce8 <col:26, col:32> col:32 __stream 'FILE *'
| `-NoThrowAttr 0x13dfe20 </usr/include/x86_64-linux-gnu/sys/cdefs.h:79:35>
|-FunctionDecl 0x13dff20 </usr/include/stdio.h:885:1, col:27> col:12 __uflow 'int (FILE *)' extern
| `-ParmVarDecl 0x13dfe88 <col:21, col:26> col:27 'FILE *'
|-FunctionDecl 0x13e0170 <line:886:1, col:35> col:12 __overflow 'int (FILE *, int)' extern
| |-ParmVarDecl 0x13dffd8 <col:24, col:29> col:30 'FILE *'
| `-ParmVarDecl 0x13e0058 <col:32> col:35 'int'
|-FunctionDecl 0x13e03b8 <QuickSort.c:3:1, line:7:1> line:3:6 used trocar 'void (int *, int *)'
| |-ParmVarDecl 0x13e0260 <col:13, col:18> col:18 used a 'int *'
| |-ParmVarDecl 0x13e02e0 <col:21, col:26> col:26 used b 'int *'
| `-CompoundStmt 0x13e06e8 <col:29, line:7:1>
|   |-DeclStmt 0x13e0550 <line:4:2, col:15>
|   | `-VarDecl 0x13e0480 <col:2, col:14> col:6 used temp 'int' cinit
|   |   `-ImplicitCastExpr 0x13e0538 <col:13, col:14> 'int' <LValueToRValue>
|   |     `-UnaryOperator 0x13e0520 <col:13, col:14> 'int' lvalue prefix '*' cannot overflow
|   |       `-ImplicitCastExpr 0x13e0508 <col:14> 'int *' <LValueToRValue>
|   |         `-DeclRefExpr 0x13e04e8 <col:14> 'int *' lvalue ParmVar 0x13e0260 'a' 'int *'
|   |-BinaryOperator 0x13e0620 <line:5:2, col:8> 'int' '='
|   | |-UnaryOperator 0x13e05a0 <col:2, col:3> 'int' lvalue prefix '*' cannot overflow
|   | | `-ImplicitCastExpr 0x13e0588 <col:3> 'int *' <LValueToRValue>
|   | |   `-DeclRefExpr 0x13e0568 <col:3> 'int *' lvalue ParmVar 0x13e0260 'a' 'int *'
|   | `-ImplicitCastExpr 0x13e0608 <col:7, col:8> 'int' <LValueToRValue>
|   |   `-UnaryOperator 0x13e05f0 <col:7, col:8> 'int' lvalue prefix '*' cannot overflow
|   |     `-ImplicitCastExpr 0x13e05d8 <col:8> 'int *' <LValueToRValue>
|   |       `-DeclRefExpr 0x13e05b8 <col:8> 'int *' lvalue ParmVar 0x13e02e0 'b' 'int *'
|   `-BinaryOperator 0x13e06c8 <line:6:2, col:7> 'int' '='
|     |-UnaryOperator 0x13e0678 <col:2, col:3> 'int' lvalue prefix '*' cannot overflow
|     | `-ImplicitCastExpr 0x13e0660 <col:3> 'int *' <LValueToRValue>
|     |   `-DeclRefExpr 0x13e0640 <col:3> 'int *' lvalue ParmVar 0x13e02e0 'b' 'int *'
|     `-ImplicitCastExpr 0x13e06b0 <col:7> 'int' <LValueToRValue>
|       `-DeclRefExpr 0x13e0690 <col:7> 'int' lvalue Var 0x13e0480 'temp' 'int'
|-FunctionDecl 0x13e0e00 <line:9:1, line:20:1> line:9:5 used lomutoPartition 'int (int, int, int *)'
| |-ParmVarDecl 0x13e0728 <col:21, col:25> col:25 used inicio 'int'
| |-ParmVarDecl 0x13e0c90 <col:33, col:37> col:37 used fim 'int'
| |-ParmVarDecl 0x13e0d10 <col:42, col:47> col:47 used vetor 'int *'
| `-CompoundStmt 0x13e1850 <col:54, line:20:1>
|   |-DeclStmt 0x13e0fe0 <line:10:2, col:27>
|   | `-VarDecl 0x13e0ed0 <col:2, col:26> col:6 used pivot 'int' cinit
|   |   `-ImplicitCastExpr 0x13e0fc8 <col:14, col:26> 'int' <LValueToRValue>
|   |     `-ArraySubscriptExpr 0x13e0fa8 <col:14, col:26> 'int' lvalue
|   |       |-ImplicitCastExpr 0x13e0f78 <col:14> 'int *' <LValueToRValue>
|   |       | `-DeclRefExpr 0x13e0f38 <col:14> 'int *' lvalue ParmVar 0x13e0d10 'vetor' 'int *'
|   |       `-ImplicitCastExpr 0x13e0f90 <col:20> 'int' <LValueToRValue>
|   |         `-DeclRefExpr 0x13e0f58 <col:20> 'int' lvalue ParmVar 0x13e0728 'inicio' 'int'
|   |-DeclStmt 0x13e10b0 <line:11:2, col:22>
|   | `-VarDecl 0x13e1010 <col:2, col:16> col:6 used mediana 'int' cinit
|   |   `-ImplicitCastExpr 0x13e1098 <col:16> 'int' <LValueToRValue>
|   |     `-DeclRefExpr 0x13e1078 <col:16> 'int' lvalue ParmVar 0x13e0728 'inicio' 'int'
|   |-ForStmt 0x13e1618 <line:12:2, line:17:2>
|   | |-DeclStmt 0x13e11c0 <line:12:6, col:24>
|   | | `-VarDecl 0x13e10e0 <col:6, col:23> col:10 used i 'int' cinit
|   | |   `-BinaryOperator 0x13e11a0 <col:14, col:23> 'int' '+'
|   | |     |-ImplicitCastExpr 0x13e1188 <col:14> 'int' <LValueToRValue>
|   | |     | `-DeclRefExpr 0x13e1148 <col:14> 'int' lvalue ParmVar 0x13e0728 'inicio' 'int'
|   | |     `-IntegerLiteral 0x13e1168 <col:23> 'int' 1
|   | |-<<<NULL>>>
|   | |-BinaryOperator 0x13e1248 <col:26, col:30> 'int' '<'
|   | | |-ImplicitCastExpr 0x13e1218 <col:26> 'int' <LValueToRValue>
|   | | | `-DeclRefExpr 0x13e11d8 <col:26> 'int' lvalue Var 0x13e10e0 'i' 'int'
|   | | `-ImplicitCastExpr 0x13e1230 <col:30> 'int' <LValueToRValue>
|   | |   `-DeclRefExpr 0x13e11f8 <col:30> 'int' lvalue ParmVar 0x13e0c90 'fim' 'int'
|   | |-UnaryOperator 0x13e1288 <col:35, col:36> 'int' postfix '++'
|   | | `-DeclRefExpr 0x13e1268 <col:35> 'int' lvalue Var 0x13e10e0 'i' 'int'
|   | `-CompoundStmt 0x13e1600 <col:40, line:17:2>
|   |   `-IfStmt 0x13e15e0 <line:13:3, line:16:3>
|   |     |-BinaryOperator 0x13e1380 <line:13:6, col:17> 'int' '<'
|   |     | |-ImplicitCastExpr 0x13e1350 <col:6, col:13> 'int' <LValueToRValue>
|   |     | | `-ArraySubscriptExpr 0x13e1310 <col:6, col:13> 'int' lvalue
|   |     | |   |-ImplicitCastExpr 0x13e12e0 <col:6> 'int *' <LValueToRValue>
|   |     | |   | `-DeclRefExpr 0x13e12a0 <col:6> 'int *' lvalue ParmVar 0x13e0d10 'vetor' 'int *'
|   |     | |   `-ImplicitCastExpr 0x13e12f8 <col:12> 'int' <LValueToRValue>
|   |     | |     `-DeclRefExpr 0x13e12c0 <col:12> 'int' lvalue Var 0x13e10e0 'i' 'int'
|   |     | `-ImplicitCastExpr 0x13e1368 <col:17> 'int' <LValueToRValue>
|   |     |   `-DeclRefExpr 0x13e1330 <col:17> 'int' lvalue Var 0x13e0ed0 'pivot' 'int'
|   |     `-CompoundStmt 0x13e15c0 <col:24, line:16:3>
|   |       |-UnaryOperator 0x13e13c0 <line:14:4, col:11> 'int' postfix '++'
|   |       | `-DeclRefExpr 0x13e13a0 <col:4> 'int' lvalue Var 0x13e1010 'mediana' 'int'
|   |       `-CallExpr 0x13e1590 <line:15:4, col:36> 'void'
|   |         |-ImplicitCastExpr 0x13e1578 <col:4> 'void (*)(int *, int *)' <FunctionToPointerDecay>
|   |         | `-DeclRefExpr 0x13e13d8 <col:4> 'void (int *, int *)' Function 0x13e03b8 'trocar' 'void (int *, int *)'     
|   |         |-UnaryOperator 0x13e1488 <col:11, col:25> 'int *' prefix '&' cannot overflow
|   |         | `-ArraySubscriptExpr 0x13e1468 <col:12, col:25> 'int' lvalue
|   |         |   |-ImplicitCastExpr 0x13e1438 <col:12> 'int *' <LValueToRValue>
|   |         |   | `-DeclRefExpr 0x13e13f8 <col:12> 'int *' lvalue ParmVar 0x13e0d10 'vetor' 'int *'
|   |         |   `-ImplicitCastExpr 0x13e1450 <col:18> 'int' <LValueToRValue>
|   |         |     `-DeclRefExpr 0x13e1418 <col:18> 'int' lvalue Var 0x13e1010 'mediana' 'int'
|   |         `-UnaryOperator 0x13e1530 <col:27, col:35> 'int *' prefix '&' cannot overflow
|   |           `-ArraySubscriptExpr 0x13e1510 <col:28, col:35> 'int' lvalue
|   |             |-ImplicitCastExpr 0x13e14e0 <col:28> 'int *' <LValueToRValue>
|   |             | `-DeclRefExpr 0x13e14a0 <col:28> 'int *' lvalue ParmVar 0x13e0d10 'vetor' 'int *'
|   |             `-ImplicitCastExpr 0x13e14f8 <col:34> 'int' <LValueToRValue>
|   |               `-DeclRefExpr 0x13e14c0 <col:34> 'int' lvalue Var 0x13e10e0 'i' 'int'
|   |-CallExpr 0x13e17d8 <line:18:2, col:39> 'void'
|   | |-ImplicitCastExpr 0x13e17c0 <col:2> 'void (*)(int *, int *)' <FunctionToPointerDecay>
|   | | `-DeclRefExpr 0x13e1650 <col:2> 'void (int *, int *)' Function 0x13e03b8 'trocar' 'void (int *, int *)'
|   | |-UnaryOperator 0x13e1700 <col:9, col:22> 'int *' prefix '&' cannot overflow
|   | | `-ArraySubscriptExpr 0x13e16e0 <col:10, col:22> 'int' lvalue
|   | |   |-ImplicitCastExpr 0x13e16b0 <col:10> 'int *' <LValueToRValue>
|   | |   | `-DeclRefExpr 0x13e1670 <col:10> 'int *' lvalue ParmVar 0x13e0d10 'vetor' 'int *'
|   | |   `-ImplicitCastExpr 0x13e16c8 <col:16> 'int' <LValueToRValue>
|   | |     `-DeclRefExpr 0x13e1690 <col:16> 'int' lvalue ParmVar 0x13e0728 'inicio' 'int'
|   | `-UnaryOperator 0x13e17a8 <col:24, col:38> 'int *' prefix '&' cannot overflow
|   |   `-ArraySubscriptExpr 0x13e1788 <col:25, col:38> 'int' lvalue
|   |     |-ImplicitCastExpr 0x13e1758 <col:25> 'int *' <LValueToRValue>
|   |     | `-DeclRefExpr 0x13e1718 <col:25> 'int *' lvalue ParmVar 0x13e0d10 'vetor' 'int *'
|   |     `-ImplicitCastExpr 0x13e1770 <col:31> 'int' <LValueToRValue>
|   |       `-DeclRefExpr 0x13e1738 <col:31> 'int' lvalue Var 0x13e1010 'mediana' 'int'
|   `-ReturnStmt 0x13e1840 <line:19:2, col:9>
|     `-ImplicitCastExpr 0x13e1828 <col:9> 'int' <LValueToRValue>
|       `-DeclRefExpr 0x13e1808 <col:9> 'int' lvalue Var 0x13e1010 'mediana' 'int'
|-FunctionDecl 0x13e1a88 <line:21:1, line:28:1> line:21:6 used QuickSort 'void (int, int, int *)'
| |-ParmVarDecl 0x13e18a0 <col:16, col:20> col:20 used inicio 'int'
| |-ParmVarDecl 0x13e1920 <col:28, col:32> col:32 used fim 'int'
| |-ParmVarDecl 0x13e19a0 <col:37, col:42> col:42 used vetor 'int *'
| `-CompoundStmt 0x13e2660 <col:49, line:28:1>
|   |-DeclStmt 0x13e1bc0 <line:22:2, col:14>
|   | `-VarDecl 0x13e1b58 <col:2, col:6> col:6 used particao 'int'
|   `-IfStmt 0x13e2640 <line:23:2, line:27:2>
|     |-BinaryOperator 0x13e1c48 <line:23:5, col:14> 'int' '<'
|     | |-ImplicitCastExpr 0x13e1c18 <col:5> 'int' <LValueToRValue>
|     | | `-DeclRefExpr 0x13e1bd8 <col:5> 'int' lvalue ParmVar 0x13e18a0 'inicio' 'int'
|     | `-ImplicitCastExpr 0x13e1c30 <col:14> 'int' <LValueToRValue>
|     |   `-DeclRefExpr 0x13e1bf8 <col:14> 'int' lvalue ParmVar 0x13e1920 'fim' 'int'
|     `-CompoundStmt 0x13e2618 <col:19, line:27:2>
|       |-BinaryOperator 0x13e2360 <line:24:3, col:48> 'int' '='
|       | |-DeclRefExpr 0x13e1c68 <col:3> 'int' lvalue Var 0x13e1b58 'particao' 'int'
|       | `-CallExpr 0x13e22e0 <col:14, col:48> 'int'
|       |   |-ImplicitCastExpr 0x13e22c8 <col:14> 'int (*)(int, int, int *)' <FunctionToPointerDecay>
|       |   | `-DeclRefExpr 0x13e2220 <col:14> 'int (int, int, int *)' Function 0x13e0e00 'lomutoPartition' 'int (int, int, 
int *)'
|       |   |-ImplicitCastExpr 0x13e2318 <col:30> 'int' <LValueToRValue>
|       |   | `-DeclRefExpr 0x13e2240 <col:30> 'int' lvalue ParmVar 0x13e18a0 'inicio' 'int'
|       |   |-ImplicitCastExpr 0x13e2330 <col:38> 'int' <LValueToRValue>
|       |   | `-DeclRefExpr 0x13e2260 <col:38> 'int' lvalue ParmVar 0x13e1920 'fim' 'int'
|       |   `-ImplicitCastExpr 0x13e2348 <col:43> 'int *' <LValueToRValue>
|       |     `-DeclRefExpr 0x13e2280 <col:43> 'int *' lvalue ParmVar 0x13e19a0 'vetor' 'int *'
|       |-CallExpr 0x13e2440 <line:25:3, col:36> 'void'
|       | |-ImplicitCastExpr 0x13e2428 <col:3> 'void (*)(int, int, int *)' <FunctionToPointerDecay>
|       | | `-DeclRefExpr 0x13e2380 <col:3> 'void (int, int, int *)' Function 0x13e1a88 'QuickSort' 'void (int, int, int *)'|       | |-ImplicitCastExpr 0x13e2478 <col:13> 'int' <LValueToRValue>
|       | | `-DeclRefExpr 0x13e23a0 <col:13> 'int' lvalue ParmVar 0x13e18a0 'inicio' 'int'
|       | |-ImplicitCastExpr 0x13e2490 <col:21> 'int' <LValueToRValue>
|       | | `-DeclRefExpr 0x13e23c0 <col:21> 'int' lvalue Var 0x13e1b58 'particao' 'int'
|       | `-ImplicitCastExpr 0x13e24a8 <col:31> 'int *' <LValueToRValue>
|       |   `-DeclRefExpr 0x13e23e0 <col:31> 'int *' lvalue ParmVar 0x13e19a0 'vetor' 'int *'
|       `-CallExpr 0x13e25b0 <line:26:3, col:35> 'void'
|         |-ImplicitCastExpr 0x13e2598 <col:3> 'void (*)(int, int, int *)' <FunctionToPointerDecay>
|         | `-DeclRefExpr 0x13e24c0 <col:3> 'void (int, int, int *)' Function 0x13e1a88 'QuickSort' 'void (int, int, int *)'|         |-BinaryOperator 0x13e2538 <col:13, col:22> 'int' '+'
|         | |-ImplicitCastExpr 0x13e2520 <col:13> 'int' <LValueToRValue>
|         | | `-DeclRefExpr 0x13e24e0 <col:13> 'int' lvalue Var 0x13e1b58 'particao' 'int'
|         | `-IntegerLiteral 0x13e2500 <col:22> 'int' 1
|         |-ImplicitCastExpr 0x13e25e8 <col:25> 'int' <LValueToRValue>
|         | `-DeclRefExpr 0x13e2558 <col:25> 'int' lvalue ParmVar 0x13e1920 'fim' 'int'
|         `-ImplicitCastExpr 0x13e2600 <col:30> 'int *' <LValueToRValue>
|           `-DeclRefExpr 0x13e2578 <col:30> 'int *' lvalue ParmVar 0x13e19a0 'vetor' 'int *'
`-FunctionDecl 0x13e26d0 <line:30:1, line:43:1> line:30:5 main 'int ()'
  `-CompoundStmt 0x13e3648 <col:12, line:43:1>
    |-DeclStmt 0x13e2ba0 <line:31:2, col:49>
    | `-VarDecl 0x13e2810 <col:2, col:48> col:6 used vetor 'int[12]' cinit
    |   `-InitListExpr 0x13e2a58 <col:18, col:48> 'int[12]'
    |     |-array_filler: ImplicitValueInitExpr 0x13e2b90 <<invalid sloc>> 'int'
    |     |-IntegerLiteral 0x13e2878 <col:19> 'int' 4
    |     |-IntegerLiteral 0x13e2898 <col:22> 'int' 5
    |     |-IntegerLiteral 0x13e28b8 <col:25> 'int' 6
    |     |-IntegerLiteral 0x13e28d8 <col:28> 'int' 9
    |     |-IntegerLiteral 0x13e28f8 <col:31> 'int' 2
    |     |-IntegerLiteral 0x13e2918 <col:34> 'int' 3
    |     |-IntegerLiteral 0x13e2938 <col:37> 'int' 1
    |     |-IntegerLiteral 0x13e2958 <col:40> 'int' 8
    |     |-IntegerLiteral 0x13e2978 <col:43> 'int' 7
    |     `-IntegerLiteral 0x13e2998 <col:46> 'int' 10
    |-ForStmt 0x13e2ee0 <line:33:2, line:35:2>
    | |-DeclStmt 0x13e2c58 <line:33:6, col:16>
    | | `-VarDecl 0x13e2bd0 <col:6, col:14> col:10 used i 'int' cinit
    | |   `-IntegerLiteral 0x13e2c38 <col:14> 'int' 0
    | |-<<<NULL>>>
    | |-BinaryOperator 0x13e2cc8 <col:18, col:22> 'int' '<'
    | | |-ImplicitCastExpr 0x13e2cb0 <col:18> 'int' <LValueToRValue>
    | | | `-DeclRefExpr 0x13e2c70 <col:18> 'int' lvalue Var 0x13e2bd0 'i' 'int'
    | | `-IntegerLiteral 0x13e2c90 <col:22> 'int' 10
    | |-UnaryOperator 0x13e2d08 <col:26, col:27> 'int' postfix '++'
    | | `-DeclRefExpr 0x13e2ce8 <col:26> 'int' lvalue Var 0x13e2bd0 'i' 'int'
    | `-CompoundStmt 0x13e2ec8 <col:31, line:35:2>
    |   `-CallExpr 0x13e2e50 <line:34:3, col:25> 'int'
    |     |-ImplicitCastExpr 0x13e2e38 <col:3> 'int (*)(const char *, ...)' <FunctionToPointerDecay>
    |     | `-DeclRefExpr 0x13e2d20 <col:3> 'int (const char *, ...)' Function 0x13c52a8 'printf' 'int (const char *, ...)' 
    |     |-ImplicitCastExpr 0x13e2e98 <col:10> 'const char *' <NoOp>
    |     | `-ImplicitCastExpr 0x13e2e80 <col:10> 'char *' <ArrayToPointerDecay>
    |     |   `-StringLiteral 0x13e2d40 <col:10> 'char[4]' lvalue "%d "
    |     `-ImplicitCastExpr 0x13e2eb0 <col:17, col:24> 'int' <LValueToRValue>
    |       `-ArraySubscriptExpr 0x13e2dd0 <col:17, col:24> 'int' lvalue
    |         |-ImplicitCastExpr 0x13e2da0 <col:17> 'int *' <ArrayToPointerDecay>
    |         | `-DeclRefExpr 0x13e2d60 <col:17> 'int[12]' lvalue Var 0x13e2810 'vetor' 'int[12]'
    |         `-ImplicitCastExpr 0x13e2db8 <col:23> 'int' <LValueToRValue>
    |           `-DeclRefExpr 0x13e2d80 <col:23> 'int' lvalue Var 0x13e2bd0 'i' 'int'
    |-CallExpr 0x13e2fc8 <line:36:2, col:13> 'int'
    | |-ImplicitCastExpr 0x13e2fb0 <col:2> 'int (*)(const char *, ...)' <FunctionToPointerDecay>
    | | `-DeclRefExpr 0x13e2f18 <col:2> 'int (const char *, ...)' Function 0x13c52a8 'printf' 'int (const char *, ...)'     
    | `-ImplicitCastExpr 0x13e3008 <col:9> 'const char *' <NoOp>
    |   `-ImplicitCastExpr 0x13e2ff0 <col:9> 'char *' <ArrayToPointerDecay>
    |     `-StringLiteral 0x13e2f78 <col:9> 'char[2]' lvalue "\n"
    |-CallExpr 0x13e30b8 <line:37:2, col:24> 'void'
    | |-ImplicitCastExpr 0x13e30a0 <col:2> 'void (*)(int, int, int *)' <FunctionToPointerDecay>
    | | `-DeclRefExpr 0x13e3020 <col:2> 'void (int, int, int *)' Function 0x13e1a88 'QuickSort' 'void (int, int, int *)'    
    | |-IntegerLiteral 0x13e3040 <col:12> 'int' 0
    | |-IntegerLiteral 0x13e3060 <col:15> 'int' 10
    | `-ImplicitCastExpr 0x13e30f0 <col:19> 'int *' <ArrayToPointerDecay>
    |   `-DeclRefExpr 0x13e3080 <col:19> 'int[12]' lvalue Var 0x13e2810 'vetor' 'int[12]'
    |-ForStmt 0x13e3518 <line:38:2, line:40:2>
    | |-DeclStmt 0x13e31a8 <line:38:6, col:16>
    | | `-VarDecl 0x13e3120 <col:6, col:14> col:10 used i 'int' cinit
    | |   `-IntegerLiteral 0x13e3188 <col:14> 'int' 0
    | |-<<<NULL>>>
    | |-BinaryOperator 0x13e3330 <col:18, col:22> 'int' '<'
    | | |-ImplicitCastExpr 0x13e3200 <col:18> 'int' <LValueToRValue>
    | | | `-DeclRefExpr 0x13e31c0 <col:18> 'int' lvalue Var 0x13e3120 'i' 'int'
    | | `-IntegerLiteral 0x13e31e0 <col:22> 'int' 10
    | |-UnaryOperator 0x13e3370 <col:26, col:27> 'int' postfix '++'
    | | `-DeclRefExpr 0x13e3350 <col:26> 'int' lvalue Var 0x13e3120 'i' 'int'
    | `-CompoundStmt 0x13e3500 <col:31, line:40:2>
    |   `-CallExpr 0x13e3488 <line:39:3, col:25> 'int'
    |     |-ImplicitCastExpr 0x13e3470 <col:3> 'int (*)(const char *, ...)' <FunctionToPointerDecay>
    |     | `-DeclRefExpr 0x13e3388 <col:3> 'int (const char *, ...)' Function 0x13c52a8 'printf' 'int (const char *, ...)' 
    |     |-ImplicitCastExpr 0x13e34d0 <col:10> 'const char *' <NoOp>
    |     | `-ImplicitCastExpr 0x13e34b8 <col:10> 'char *' <ArrayToPointerDecay>
    |     |   `-StringLiteral 0x13e33a8 <col:10> 'char[4]' lvalue "%d "
    |     `-ImplicitCastExpr 0x13e34e8 <col:17, col:24> 'int' <LValueToRValue>
    |       `-ArraySubscriptExpr 0x13e3438 <col:17, col:24> 'int' lvalue
    |         |-ImplicitCastExpr 0x13e3408 <col:17> 'int *' <ArrayToPointerDecay>
    |         | `-DeclRefExpr 0x13e33c8 <col:17> 'int[12]' lvalue Var 0x13e2810 'vetor' 'int[12]'
    |         `-ImplicitCastExpr 0x13e3420 <col:23> 'int' <LValueToRValue>
    |           `-DeclRefExpr 0x13e33e8 <col:23> 'int' lvalue Var 0x13e3120 'i' 'int'
    |-CallExpr 0x13e35c0 <line:41:2, col:13> 'int'
    | |-ImplicitCastExpr 0x13e35a8 <col:2> 'int (*)(const char *, ...)' <FunctionToPointerDecay>
    | | `-DeclRefExpr 0x13e3550 <col:2> 'int (const char *, ...)' Function 0x13c52a8 'printf' 'int (const char *, ...)'     
    | `-ImplicitCastExpr 0x13e3600 <col:9> 'const char *' <NoOp>
    |   `-ImplicitCastExpr 0x13e35e8 <col:9> 'char *' <ArrayToPointerDecay>
    |     `-StringLiteral 0x13e3570 <col:9> 'char[2]' lvalue "\n"
    `-ReturnStmt 0x13e3638 <line:42:2, col:9>
      `-IntegerLiteral 0x13e3618 <col:9> 'int' 0
```

</details>

<details>

<summary>Em seguida, gerei a representação intermediária (LLVM)

```
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ clang -S -emit-llvm QuickSort.c
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ ls
 QuickSort   QuickSort.c   QuickSort.ll   exemplo.c  'logo ufs.png'   relatorio-depuracao.md
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ cat QuickSort.ll
; ModuleID = 'QuickSort.c'
source_filename = "QuickSort.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@__const.main.vetor = private unnamed_addr constant [12 x i32] [i32 4, i32 5, i32 6, i32 9, i32 2, i32 3, i32 1, i32 8, i32 
7, i32 10, i32 0, i32 0], align 16
@.str = private unnamed_addr constant [4 x i8] c"%d \00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @trocar(i32* noundef %0, i32* noundef %1) #0 {
  %3 = alloca i32*, align 8
  %4 = alloca i32*, align 8
  %5 = alloca i32, align 4
  store i32* %0, i32** %3, align 8
  store i32* %1, i32** %4, align 8
  %6 = load i32*, i32** %3, align 8
  %7 = load i32, i32* %6, align 4
  store i32 %7, i32* %5, align 4
  %8 = load i32*, i32** %4, align 8
  %9 = load i32, i32* %8, align 4
  %10 = load i32*, i32** %3, align 8
  store i32 %9, i32* %10, align 4
  %11 = load i32, i32* %5, align 4
  %12 = load i32*, i32** %4, align 8
  store i32 %11, i32* %12, align 4
  ret void
}
```
</summary>

```
; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @lomutoPartition(i32 noundef %0, i32 noundef %1, i32* noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32* %2, i32** %6, align 8
  %10 = load i32*, i32** %6, align 8
  %11 = load i32, i32* %4, align 4
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds i32, i32* %10, i64 %12
  %14 = load i32, i32* %13, align 4
  store i32 %14, i32* %7, align 4
  %15 = load i32, i32* %4, align 4
  store i32 %15, i32* %8, align 4
  %16 = load i32, i32* %4, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, i32* %9, align 4
  br label %18

18:                                               ; preds = %42, %3
  %19 = load i32, i32* %9, align 4
  %20 = load i32, i32* %5, align 4
  %21 = icmp slt i32 %19, %20
  br i1 %21, label %22, label %45

22:                                               ; preds = %18
  %23 = load i32*, i32** %6, align 8
  %24 = load i32, i32* %9, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i32, i32* %23, i64 %25
  %27 = load i32, i32* %26, align 4
  %28 = load i32, i32* %7, align 4
  %29 = icmp slt i32 %27, %28
  br i1 %29, label %30, label %41

30:                                               ; preds = %22
  %31 = load i32, i32* %8, align 4
  %32 = add nsw i32 %31, 1
  store i32 %32, i32* %8, align 4
  %33 = load i32*, i32** %6, align 8
  %34 = load i32, i32* %8, align 4
  %35 = sext i32 %34 to i64
  %36 = getelementptr inbounds i32, i32* %33, i64 %35
  %37 = load i32*, i32** %6, align 8
  %38 = load i32, i32* %9, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds i32, i32* %37, i64 %39
  call void @trocar(i32* noundef %36, i32* noundef %40)
  br label %41

41:                                               ; preds = %30, %22
  br label %42

42:                                               ; preds = %41
  %43 = load i32, i32* %9, align 4
  %44 = add nsw i32 %43, 1
  store i32 %44, i32* %9, align 4
  br label %18, !llvm.loop !6

45:                                               ; preds = %18
  %46 = load i32*, i32** %6, align 8
  %47 = load i32, i32* %4, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds i32, i32* %46, i64 %48
  %50 = load i32*, i32** %6, align 8
  %51 = load i32, i32* %8, align 4
  %52 = sext i32 %51 to i64
  %53 = getelementptr inbounds i32, i32* %50, i64 %52
  call void @trocar(i32* noundef %49, i32* noundef %53)
  %54 = load i32, i32* %8, align 4
  ret i32 %54
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @QuickSort(i32 noundef %0, i32 noundef %1, i32* noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32*, align 8
  %7 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32* %2, i32** %6, align 8
  %8 = load i32, i32* %4, align 4
  %9 = load i32, i32* %5, align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %23

11:                                               ; preds = %3
  %12 = load i32, i32* %4, align 4
  %13 = load i32, i32* %5, align 4
  %14 = load i32*, i32** %6, align 8
  %15 = call i32 @lomutoPartition(i32 noundef %12, i32 noundef %13, i32* noundef %14)
  store i32 %15, i32* %7, align 4
  %16 = load i32, i32* %4, align 4
  %17 = load i32, i32* %7, align 4
  %18 = load i32*, i32** %6, align 8
  call void @QuickSort(i32 noundef %16, i32 noundef %17, i32* noundef %18)
  %19 = load i32, i32* %7, align 4
  %20 = add nsw i32 %19, 1
  %21 = load i32, i32* %5, align 4
  %22 = load i32*, i32** %6, align 8
  call void @QuickSort(i32 noundef %20, i32 noundef %21, i32* noundef %22)
  br label %23

23:                                               ; preds = %11, %3
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [12 x i32], align 16
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %5 = bitcast [12 x i32]* %2 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %5, i8* align 16 bitcast ([12 x i32]* @__const.main.vetor to i8*), i64 48, i1 false)
  store i32 0, i32* %3, align 4
  br label %6

6:                                                ; preds = %15, %0
  %7 = load i32, i32* %3, align 4
  %8 = icmp slt i32 %7, 10
  br i1 %8, label %9, label %18

9:                                                ; preds = %6
  %10 = load i32, i32* %3, align 4
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds [12 x i32], [12 x i32]* %2, i64 0, i64 %11
  %13 = load i32, i32* %12, align 4
  %14 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %13)
  br label %15

15:                                               ; preds = %9
  %16 = load i32, i32* %3, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, i32* %3, align 4
  br label %6, !llvm.loop !8

18:                                               ; preds = %6
  %19 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i64 0, i64 0))
  %20 = getelementptr inbounds [12 x i32], [12 x i32]* %2, i64 0, i64 0
  call void @QuickSort(i32 noundef 0, i32 noundef 10, i32* noundef %20)
  store i32 0, i32* %4, align 4
  br label %21

21:                                               ; preds = %30, %18
  %22 = load i32, i32* %4, align 4
  %23 = icmp slt i32 %22, 10
  br i1 %23, label %24, label %33

24:                                               ; preds = %21
  %25 = load i32, i32* %4, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [12 x i32], [12 x i32]* %2, i64 0, i64 %26
  %28 = load i32, i32* %27, align 4
  %29 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %28)
  br label %30

30:                                               ; preds = %24
  %31 = load i32, i32* %4, align 4
  %32 = add nsw i32 %31, 1
  store i32 %32, i32* %4, align 4
  br label %21, !llvm.loop !9

33:                                               ; preds = %21
  %34 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i64 0, i64 0))
  ret i32 0
}

; Function Attrs: argmemonly nofree nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #1 

declare i32 @printf(i8* noundef, ...) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly nofree nounwind willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
```

</details>

<details>
<summary>Em seguida, compilei o código para um arquivo .elf e usei o comando objdump

```
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ gcc -Wall QuickSort.c -o QuickSort.elf
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ ls
 QuickSort   QuickSort.c   QuickSort.elf   QuickSort.ll
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ objdump --disassemble -M amd QuickSort.elf

QuickSort.elf:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:       f3 0f 1e fa             endbr64
    1004:       48 83 ec 08             sub    $0x8,%rsp
    1008:       48 8b 05 d9 2f 00 00    mov    0x2fd9(%rip),%rax        #
    100f:       48 85 c0                test   %rax,%rax
    1012:       74 02                   je     1016 <_init+0x16>
    1014:       ff d0                   call   *%rax
    1016:       48 83 c4 08             add    $0x8,%rsp
    101a:       c3                      ret
```

</summary>

```
Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:       ff 35 8a 2f 00 00       push   0x2f8a(%rip)        # 3fb0
    1026:       f2 ff 25 8b 2f 00 00    bnd jmp *0x2f8b(%rip)        # 3f
    102d:       0f 1f 00                nopl   (%rax)
    1030:       f3 0f 1e fa             endbr64
    1034:       68 00 00 00 00          push   $0x0
    1039:       f2 e9 e1 ff ff ff       bnd jmp 1020 <_init+0x20>
    103f:       90                      nop
    1040:       f3 0f 1e fa             endbr64
    1044:       68 01 00 00 00          push   $0x1
    1049:       f2 e9 d1 ff ff ff       bnd jmp 1020 <_init+0x20>
    104f:       90                      nop
    1050:       f3 0f 1e fa             endbr64
    1054:       68 02 00 00 00          push   $0x2
    1059:       f2 e9 c1 ff ff ff       bnd jmp 1020 <_init+0x20>
    105f:       90                      nop

Disassembly of section .plt.got:

0000000000001060 <__cxa_finalize@plt>:
    1060:       f3 0f 1e fa             endbr64
    1064:       f2 ff 25 8d 2f 00 00    bnd jmp *0x2f8d(%rip)        # 3f
    106b:       0f 1f 44 00 00          nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001070 <putchar@plt>:
    1070:       f3 0f 1e fa             endbr64
    1074:       f2 ff 25 45 2f 00 00    bnd jmp *0x2f45(%rip)        # 3f
    107b:       0f 1f 44 00 00          nopl   0x0(%rax,%rax,1)

0000000000001080 <__stack_chk_fail@plt>:
    1080:       f3 0f 1e fa             endbr64
    1084:       f2 ff 25 3d 2f 00 00    bnd jmp *0x2f3d(%rip)        # 3f
    108b:       0f 1f 44 00 00          nopl   0x0(%rax,%rax,1)

0000000000001090 <printf@plt>:
    1090:       f3 0f 1e fa             endbr64
    1094:       f2 ff 25 35 2f 00 00    bnd jmp *0x2f35(%rip)        # 3f
    109b:       0f 1f 44 00 00          nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010a0 <_start>:
    10a0:       f3 0f 1e fa             endbr64
    10a4:       31 ed                   xor    %ebp,%ebp
    10a6:       49 89 d1                mov    %rdx,%r9
    10a9:       5e                      pop    %rsi
    10aa:       48 89 e2                mov    %rsp,%rdx
    10ad:       48 83 e4 f0             and    $0xfffffffffffffff0,%rsp
    10b1:       50                      push   %rax
    10b2:       54                      push   %rsp
    10b3:       45 31 c0                xor    %r8d,%r8d
    10b6:       31 c9                   xor    %ecx,%ecx
    10b8:       48 8d 3d 31 02 00 00    lea    0x231(%rip),%rdi        # 
    10bf:       ff 15 13 2f 00 00       call   *0x2f13(%rip)        # 3fd
    10c5:       f4                      hlt
    10c6:       66 2e 0f 1f 84 00 00    cs nopw 0x0(%rax,%rax,1)
    10cd:       00 00 00

00000000000010d0 <deregister_tm_clones>:
    10d0:       48 8d 3d 39 2f 00 00    lea    0x2f39(%rip),%rdi        #
    10d7:       48 8d 05 32 2f 00 00    lea    0x2f32(%rip),%rax        #
    10de:       48 39 f8                cmp    %rdi,%rax
    10e1:       74 15                   je     10f8 <deregister_tm_clones
    10e3:       48 8b 05 f6 2e 00 00    mov    0x2ef6(%rip),%rax        #
    10ea:       48 85 c0                test   %rax,%rax
    10ed:       74 09                   je     10f8 <deregister_tm_clones
    10ef:       ff e0                   jmp    *%rax
    10f1:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)
    10f8:       c3                      ret
    10f9:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)

0000000000001100 <register_tm_clones>:
    1100:       48 8d 3d 09 2f 00 00    lea    0x2f09(%rip),%rdi        #
    1107:       48 8d 35 02 2f 00 00    lea    0x2f02(%rip),%rsi        #
    110e:       48 29 fe                sub    %rdi,%rsi
    1111:       48 89 f0                mov    %rsi,%rax
    1114:       48 c1 ee 3f             shr    $0x3f,%rsi
    1118:       48 c1 f8 03             sar    $0x3,%rax
    111c:       48 01 c6                add    %rax,%rsi
    111f:       48 d1 fe                sar    %rsi
    1122:       74 14                   je     1138 <register_tm_clones+0
    1124:       48 8b 05 c5 2e 00 00    mov    0x2ec5(%rip),%rax        #
    112b:       48 85 c0                test   %rax,%rax
    112e:       74 08                   je     1138 <register_tm_clones+0
    1130:       ff e0                   jmp    *%rax
    1132:       66 0f 1f 44 00 00       nopw   0x0(%rax,%rax,1)
    1138:       c3                      ret
    1139:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)

0000000000001140 <__do_global_dtors_aux>:
    1140:       f3 0f 1e fa             endbr64
    1144:       80 3d c5 2e 00 00 00    cmpb   $0x0,0x2ec5(%rip)        #
    114b:       75 2b                   jne    1178 <__do_global_dtors_au
    114d:       55                      push   %rbp
    114e:       48 83 3d a2 2e 00 00    cmpq   $0x0,0x2ea2(%rip)        #
    1155:       00
    1156:       48 89 e5                mov    %rsp,%rbp
    1159:       74 0c                   je     1167 <__do_global_dtors_au
    115b:       48 8b 3d a6 2e 00 00    mov    0x2ea6(%rip),%rdi        #
    1162:       e8 f9 fe ff ff          call   1060 <__cxa_finalize@plt>
    1167:       e8 64 ff ff ff          call   10d0 <deregister_tm_clones
    116c:       c6 05 9d 2e 00 00 01    movb   $0x1,0x2e9d(%rip)        #
    1173:       5d                      pop    %rbp
    1174:       c3                      ret
    1175:       0f 1f 00                nopl   (%rax)
    1178:       c3                      ret
    1179:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)

0000000000001180 <frame_dummy>:
    1180:       f3 0f 1e fa             endbr64
    1184:       e9 77 ff ff ff          jmp    1100 <register_tm_clones>

0000000000001189 <trocar>:
    1189:       f3 0f 1e fa             endbr64
    118d:       55                      push   %rbp
    118e:       48 89 e5                mov    %rsp,%rbp
    1191:       48 89 7d e8             mov    %rdi,-0x18(%rbp)
    1195:       48 89 75 e0             mov    %rsi,-0x20(%rbp)
    1199:       48 8b 45 e8             mov    -0x18(%rbp),%rax
    119d:       8b 00                   mov    (%rax),%eax
    119f:       89 45 fc                mov    %eax,-0x4(%rbp)
    11a2:       48 8b 45 e0             mov    -0x20(%rbp),%rax
    11a6:       8b 10                   mov    (%rax),%edx
    11a8:       48 8b 45 e8             mov    -0x18(%rbp),%rax
    11ac:       89 10                   mov    %edx,(%rax)
    11ae:       48 8b 45 e0             mov    -0x20(%rbp),%rax
    11b2:       8b 55 fc                mov    -0x4(%rbp),%edx
    11b5:       89 10                   mov    %edx,(%rax)
    11b7:       90                      nop
    11b8:       5d                      pop    %rbp
    11b9:       c3                      ret

00000000000011ba <lomutoPartition>:
    11ba:       f3 0f 1e fa             endbr64
    11be:       55                      push   %rbp
    11bf:       48 89 e5                mov    %rsp,%rbp
    11c2:       48 83 ec 20             sub    $0x20,%rsp
    11c6:       89 7d ec                mov    %edi,-0x14(%rbp)
    11c9:       89 75 e8                mov    %esi,-0x18(%rbp)
    11cc:       48 89 55 e0             mov    %rdx,-0x20(%rbp)
    11d0:       8b 45 ec                mov    -0x14(%rbp),%eax
    11d3:       48 98                   cltq
    11d5:       48 8d 14 85 00 00 00    lea    0x0(,%rax,4),%rdx
    11dc:       00
    11dd:       48 8b 45 e0             mov    -0x20(%rbp),%rax
    11e1:       48 01 d0                add    %rdx,%rax
    11e4:       8b 00                   mov    (%rax),%eax
    11e6:       89 45 fc                mov    %eax,-0x4(%rbp)
    11e9:       8b 45 ec                mov    -0x14(%rbp),%eax
    11ec:       89 45 f4                mov    %eax,-0xc(%rbp)
    11ef:       8b 45 ec                mov    -0x14(%rbp),%eax
    11f2:       83 c0 01                add    $0x1,%eax
    11f5:       89 45 f8                mov    %eax,-0x8(%rbp)
    11f8:       eb 56                   jmp    1250 <lomutoPartition+0x96
    11fa:       8b 45 f8                mov    -0x8(%rbp),%eax
    11fd:       48 98                   cltq
    11ff:       48 8d 14 85 00 00 00    lea    0x0(,%rax,4),%rdx
    1206:       00
    1207:       48 8b 45 e0             mov    -0x20(%rbp),%rax
    120b:       48 01 d0                add    %rdx,%rax
    120e:       8b 00                   mov    (%rax),%eax
    1210:       39 45 fc                cmp    %eax,-0x4(%rbp)
    1213:       7e 37                   jle    124c <lomutoPartition+0x92
    1215:       83 45 f4 01             addl   $0x1,-0xc(%rbp)
    1219:       8b 45 f8                mov    -0x8(%rbp),%eax
    121c:       48 98                   cltq
    121e:       48 8d 14 85 00 00 00    lea    0x0(,%rax,4),%rdx
    1225:       00
    1226:       48 8b 45 e0             mov    -0x20(%rbp),%rax
    122a:       48 01 c2                add    %rax,%rdx
    122d:       8b 45 f4                mov    -0xc(%rbp),%eax
    1230:       48 98                   cltq
    1232:       48 8d 0c 85 00 00 00    lea    0x0(,%rax,4),%rcx
    1239:       00
    123a:       48 8b 45 e0             mov    -0x20(%rbp),%rax
    123e:       48 01 c8                add    %rcx,%rax
    1241:       48 89 d6                mov    %rdx,%rsi
    1244:       48 89 c7                mov    %rax,%rdi
    1247:       e8 3d ff ff ff          call   1189 <trocar>
    124c:       83 45 f8 01             addl   $0x1,-0x8(%rbp)
    1250:       8b 45 f8                mov    -0x8(%rbp),%eax
    1253:       3b 45 e8                cmp    -0x18(%rbp),%eax
    1256:       7c a2                   jl     11fa <lomutoPartition+0x40
    1258:       8b 45 f4                mov    -0xc(%rbp),%eax
    125b:       48 98                   cltq
    125d:       48 8d 14 85 00 00 00    lea    0x0(,%rax,4),%rdx
    1264:       00
    1265:       48 8b 45 e0             mov    -0x20(%rbp),%rax
    1269:       48 01 c2                add    %rax,%rdx
    126c:       8b 45 ec                mov    -0x14(%rbp),%eax
    126f:       48 98                   cltq
    1271:       48 8d 0c 85 00 00 00    lea    0x0(,%rax,4),%rcx
    1278:       00
    1279:       48 8b 45 e0             mov    -0x20(%rbp),%rax
    127d:       48 01 c8                add    %rcx,%rax
    1280:       48 89 d6                mov    %rdx,%rsi
    1283:       48 89 c7                mov    %rax,%rdi
    1286:       e8 fe fe ff ff          call   1189 <trocar>
    128b:       8b 45 f4                mov    -0xc(%rbp),%eax
    128e:       c9                      leave
    128f:       c3                      ret

0000000000001290 <QuickSort>:
    1290:       f3 0f 1e fa             endbr64
    1294:       55                      push   %rbp
    1295:       48 89 e5                mov    %rsp,%rbp
    1298:       48 83 ec 20             sub    $0x20,%rsp
    129c:       89 7d ec                mov    %edi,-0x14(%rbp)
    129f:       89 75 e8                mov    %esi,-0x18(%rbp)
    12a2:       48 89 55 e0             mov    %rdx,-0x20(%rbp)
    12a6:       8b 45 ec                mov    -0x14(%rbp),%eax
    12a9:       3b 45 e8                cmp    -0x18(%rbp),%eax
    12ac:       7d 3f                   jge    12ed <QuickSort+0x5d>
    12ae:       48 8b 55 e0             mov    -0x20(%rbp),%rdx
    12b2:       8b 4d e8                mov    -0x18(%rbp),%ecx
    12b5:       8b 45 ec                mov    -0x14(%rbp),%eax
    12b8:       89 ce                   mov    %ecx,%esi
    12ba:       89 c7                   mov    %eax,%edi
    12bc:       e8 f9 fe ff ff          call   11ba <lomutoPartition>
    12c1:       89 45 fc                mov    %eax,-0x4(%rbp)
    12c4:       48 8b 55 e0             mov    -0x20(%rbp),%rdx
    12c8:       8b 4d fc                mov    -0x4(%rbp),%ecx
    12cb:       8b 45 ec                mov    -0x14(%rbp),%eax
    12ce:       89 ce                   mov    %ecx,%esi
    12d0:       89 c7                   mov    %eax,%edi
    12d2:       e8 b9 ff ff ff          call   1290 <QuickSort>
    12d7:       8b 45 fc                mov    -0x4(%rbp),%eax
    12da:       8d 48 01                lea    0x1(%rax),%ecx
    12dd:       48 8b 55 e0             mov    -0x20(%rbp),%rdx
    12e1:       8b 45 e8                mov    -0x18(%rbp),%eax
    12e4:       89 c6                   mov    %eax,%esi
    12e6:       89 cf                   mov    %ecx,%edi
    12e8:       e8 a3 ff ff ff          call   1290 <QuickSort>
    12ed:       90                      nop
    12ee:       c9                      leave
    12ef:       c3                      ret

00000000000012f0 <main>:
    12f0:       f3 0f 1e fa             endbr64
    12f4:       55                      push   %rbp
    12f5:       48 89 e5                mov    %rsp,%rbp
    12f8:       48 83 ec 50             sub    $0x50,%rsp
    12fc:       64 48 8b 04 25 28 00    mov    %fs:0x28,%rax
    1303:       00 00
    1305:       48 89 45 f8             mov    %rax,-0x8(%rbp)
    1309:       31 c0                   xor    %eax,%eax
    130b:       48 c7 45 c0 00 00 00    movq   $0x0,-0x40(%rbp)
    1312:       00
    1313:       48 c7 45 c8 00 00 00    movq   $0x0,-0x38(%rbp)
    131a:       00
    131b:       48 c7 45 d0 00 00 00    movq   $0x0,-0x30(%rbp)
    1322:       00
    1323:       48 c7 45 d8 00 00 00    movq   $0x0,-0x28(%rbp)
    132a:       00
    132b:       48 c7 45 e0 00 00 00    movq   $0x0,-0x20(%rbp)
    1332:       00
    1333:       48 c7 45 e8 00 00 00    movq   $0x0,-0x18(%rbp)
    133a:       00
    133b:       c7 45 c0 04 00 00 00    movl   $0x4,-0x40(%rbp)
    1342:       c7 45 c4 05 00 00 00    movl   $0x5,-0x3c(%rbp)
    1349:       c7 45 c8 06 00 00 00    movl   $0x6,-0x38(%rbp)
    1350:       c7 45 cc 09 00 00 00    movl   $0x9,-0x34(%rbp)
    1357:       c7 45 d0 02 00 00 00    movl   $0x2,-0x30(%rbp)
    135e:       c7 45 d4 03 00 00 00    movl   $0x3,-0x2c(%rbp)
    1365:       c7 45 d8 01 00 00 00    movl   $0x1,-0x28(%rbp)
    136c:       c7 45 dc 08 00 00 00    movl   $0x8,-0x24(%rbp)
    1373:       c7 45 e0 07 00 00 00    movl   $0x7,-0x20(%rbp)
    137a:       c7 45 e4 0a 00 00 00    movl   $0xa,-0x1c(%rbp)
    1381:       c7 45 b8 00 00 00 00    movl   $0x0,-0x48(%rbp)
    1388:       eb 23                   jmp    13ad <main+0xbd>
    138a:       8b 45 b8                mov    -0x48(%rbp),%eax
    138d:       48 98                   cltq
    138f:       8b 44 85 c0             mov    -0x40(%rbp,%rax,4),%eax
    1393:       89 c6                   mov    %eax,%esi
    1395:       48 8d 05 68 0c 00 00    lea    0xc68(%rip),%rax        # 
    139c:       48 89 c7                mov    %rax,%rdi
    139f:       b8 00 00 00 00          mov    $0x0,%eax
    13a4:       e8 e7 fc ff ff          call   1090 <printf@plt>
    13a9:       83 45 b8 01             addl   $0x1,-0x48(%rbp)
    13ad:       83 7d b8 09             cmpl   $0x9,-0x48(%rbp)
    13b1:       7e d7                   jle    138a <main+0x9a>
    13b3:       bf 0a 00 00 00          mov    $0xa,%edi
0,%eax                                            0 <putchar@plt>
    13f6:       e8 95 fc ff ff          call   1090 <printf@plt>
    13fb:       83 45 bc 01             addl   $0x1,-0x44(%rbp)
    13ff:       83 7d bc 09             cmpl   $0x9,-0x44(%rbp)
    1403:       7e d7                   jle    13dc <main+0xec>
    1405:       bf 0a 00 00 00          mov    $0xa,%edi
    140a:       e8 61 fc ff ff          call   1070 <putchar@plt>
    140f:       b8 00 00 00 00          mov    $0x0,%eax
    1414:       48 8b 55 f8             mov    -0x8(%rbp),%rdx
    1418:       64 48 2b 14 25 28 00    sub    %fs:0x28,%rdx
    141f:       00 00
    1421:       74 05                   je     1428 <main+0x138>
    1423:       e8 58 fc ff ff          call   1080 <__stack_chk_fail@plt>
    1428:       c9                      leave
    1429:       c3                      ret

Disassembly of section .fini:

000000000000142c <_fini>:
    142c:       f3 0f 1e fa             endbr64
    1430:       48 83 ec 08             sub    $0x8,%rsp
    1434:       48 83 c4 08             add    $0x8,%rsp
    1438:       c3                      ret
```
</details>


Em seguida, realizei a compilação com suporte para depuração através do gdb

```
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ gdb QuickSort.elf
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from QuickSort.elf...
(gdb) run
Starting program: /mnt/c/Users/User/Programacao/IHS/QuickSort.elf 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
4 5 6 9 2 3 1 8 7 10 
1 2 3 4 5 6 7 8 9 10 
[Inferior 1 (process 19245) exited normally]
```

Em seguida, realizei a compilação com suporte para depuração através do lldb

```
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ lldb QuickSort.elf
Traceback (most recent call last):    
  File "<string>", line 1, in <module>
ModuleNotFoundError: No module named 'lldb.embedded_interpreter'
(lldb) target create "QuickSort.elf"
Current executable set to '/mnt/c/Users/User/Programacao/IHS/QuickSort.elf' (x86_64).
(lldb) run
Process 20322 launched: '/mnt/c/Users/User/Programacao/IHS/QuickSort.elf' (x86_64)
4 5 6 9 2 3 1 8 7 10 
1 2 3 4 5 6 7 8 9 10 
Process 20322 exited with status = 0 (0x00000000) 
(lldb)
```
Após isso, alterei os algoritmos de ordenação, para testar o número de comparações e o desempenho entre eles

```
#include <stdio.h>

int SelectionSort(int tamanho, int *vetordeint) {
	int menor, temp, comparacoes = 0;
	for(int i = 0; i < tamanho-1; i++) {
	    menor = i;
		for(int j = i+1; j < tamanho; j++) {
			if(vetordeint[j] < vetordeint[menor]) {
				menor = j;
				comparacoes++;
			}
		}
		temp = vetordeint[i];
		vetordeint[i] = vetordeint[menor];
		vetordeint[menor] = temp;
	}
	return comparacoes;
}

int bubbleSort(int tamanhoLista, int *vetordeinteiros) {
	int temporario, comparacoes = 0;
	for(int i = 0; i < tamanhoLista-1; i++) {
		for(int j = 0; j < (tamanhoLista-1)-i; j++) {
			if(vetordeinteiros[j+1] < vetordeinteiros[j]) {
				temporario = vetordeinteiros[j];
				vetordeinteiros[j] = vetordeinteiros[j+1];
				vetordeinteiros[j+1] = temporario;
                comparacoes++;
			}
		}
	}
	return comparacoes;
}

int main() {
	int vetor[12] = {4, 5, 6, 9, 2, 3, 1, 8, 7, 10};
	int originalVetor[12] = {4, 5, 6, 9, 2, 3, 1, 8, 7, 10}; 
	int ss = 0, bs = 0;

    for (int i = 0; i < 10000000; i++) {
        for (int j = 0; j < 10; j++) {
            vetor[j] = originalVetor[j];
        }

        ss += SelectionSort(10, vetor); 

        for (int j = 0; j < 10; j++) {
            vetor[j] = originalVetor[j];
        }

        bs += bubbleSort(10, vetor);
    }
	printf("SelectionSort: %d BubbleSort: %d\n", ss, bs);
	return 0;
}
```

Em seguida, analisei o desempenho dos algoritmos através do comando gprof

```
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ gcc -Wall -g -pg QuickSort.c -o QuickSort.elf
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ ./QuickSort.elf
SelectionSort: 90000000 BubbleSort: 170000000
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ gprof QuickSort.elf gmon.out > analysis.txt
```

Esses foram os resultados da análise de desempenho e estão mais detalhados dentro do arquivo analysis.txt

```
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ns/call  ns/call  name    
 44.64      1.04     1.04 10000000   104.00   104.00  bubbleSort
 37.77      1.92     0.88 10000000    88.00    88.00  SelectionSort
 17.60      2.33     0.41                             main
```

Infelizmente, não foi possível comparar os resultados do gprof com o do perf, pois me deparei com diversos erros que me impossibilitaram.

```
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ perf record ./QuickSort.elf
Command 'perf' not found, but can be installed with:
sudo apt install linux-intel-iotg-tools-common        # version 5.15.0-1043.49, or
sudo apt install linux-nvidia-6.2-tools-common        # version 6.2.0-1003.3~22.04.1
sudo apt install linux-nvidia-tools-common            # version 5.15.0-1040.40
sudo apt install linux-tools-common                   # version 5.15.0-88.98
sudo apt install linux-nvidia-5.19-tools-common       # version 5.19.0-1014.14
sudo apt install linux-nvidia-tegra-igx-tools-common  # version 5.15.0-1005.5
sudo apt install linux-nvidia-tegra-tools-common      # version 5.15.0-1018.18
sudo apt install linux-xilinx-zynqmp-tools-common     # version 5.15.0-1023.27
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ sudo apt install linux-tools-common
gabriel-ubuntu-wsl-2@DESKTOP-V76KM6R:/mnt/c/Users/User/Programacao/IHS$ perf record ./QuickSort.elf
WARNING: perf not found for kernel 5.15.133.1-microsoft

  You may need to install the following packages for this specific kernel:
    linux-tools-5.15.133.1-microsoft-standard-WSL2
    linux-cloud-tools-5.15.133.1-microsoft-standard-WSL2

  You may also want to install one of the following packages to keep up to date:
    linux-tools-standard-WSL2
    linux-cloud-tools-standard-WSL2
```