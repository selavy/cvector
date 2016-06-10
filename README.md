# cvector
C dynamic sized array

gen_cvector.py --type=[ <typename> ]

`typename` must be a single word.  If you want a "multi-word" type (e.g. long long *) then you will
need to typedef that type (e.g. typedef long long * mylong_ptr_t) then use that type.
