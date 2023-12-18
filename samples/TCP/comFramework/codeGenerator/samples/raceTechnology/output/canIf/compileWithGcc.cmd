:: A simple test of the compilability of the generated interface code. An installation of
:: GCC is assumed.
gcc -c -DCRT_UNCONDITIONALLY_GENERATE_PACK_FCTS -DCRT_UNCONDITIONALLY_GENERATE_UNPACK_FCTS crt_canRT.c
