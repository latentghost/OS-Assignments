cmd_twodmemcpy/built-in.a := rm -f twodmemcpy/built-in.a; echo twodmemcpy.o | sed -E 's:([^ ]+):twodmemcpy/\1:g' | xargs ar cDPrST twodmemcpy/built-in.a
