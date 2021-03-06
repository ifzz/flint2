/*
    Copyright (C) 2009 William Hart
    Copyright (C) 2010, 2011 Sebastian Pancratz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"
#include "fmpq.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("get_str....");
    fflush(stdout);

    

    for (i = 0; i < 100000; i++)
    {
        fmpq_t a;
        mpq_t b;
        int base, j;
        char *str1, *str2;

        fmpq_init(a);
        mpq_init(b);
        fmpq_randtest(a, state, 200);
        base = (int) (n_randint(state, 31) + 2);

        fmpq_get_mpq(b, a);

        str1 = fmpq_get_str(NULL, base, a);
        str2 = mpq_get_str(NULL, base, b);
        result = (strlen(str1) == strlen(str2));
        if (result)
        {
            for (j = 0; result && j < strlen(str1); j++)
                if (str1[j] != str2[j])
                    result = 0;
        }

        if (!result)
        {
            flint_printf("FAIL:\n");
            gmp_printf("b = %Qd\n", b);
            flint_printf("base = %d\n", base);
            flint_printf("str1 = %s\n, str2 = %s\n", str1, str2);
            abort();
        }

        flint_free(str1);
        flint_free(str2);

        fmpq_clear(a);
        mpq_clear(b);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}

