/*
    Copyright (C) 2011 Fredrik Johansson

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "fmpz_mat.h"
#include "perm.h"

#define E(j,k) fmpz_mat_entry(B,j,k)

slong
fmpz_mat_fflu(fmpz_mat_t B, fmpz_t den, slong * perm,
                            const fmpz_mat_t A, int rank_check)
{
    slong m, n, j, k, rank, r, pivot_row, pivot_col;

    if (fmpz_mat_is_empty(A))
    {
        fmpz_one(den);
        return 0;
    }

    fmpz_mat_set(B, A);
    m = B->r;
    n = B->c;
    rank = pivot_row = pivot_col = 0;

    while (pivot_row < m && pivot_col < n)
    {
        r = fmpz_mat_find_pivot_any(B, pivot_row, m, pivot_col);

        if (r == -1)
        {
            if (rank_check)
            {
                fmpz_zero(den);
                rank = 0;
                break;
            }
            pivot_col++;
            continue;
        }
        else if (r != pivot_row)
            fmpz_mat_swap_rows(B, perm, pivot_row, r);

        rank++;

        for (j = pivot_row + 1; j < m; j++)
        {
            for (k = pivot_col + 1; k < n; k++)
            {
                fmpz_mul(E(j, k), E(j, k), E(pivot_row, pivot_col));
                fmpz_submul(E(j, k), E(j, pivot_col), E(pivot_row, k));

                if (pivot_row > 0)
                    fmpz_divexact(E(j, k), E(j, k), den);
            }
        }

        fmpz_set(den, E(pivot_row, pivot_col));
        pivot_row++;
        pivot_col++;
    }

    return rank;
}
