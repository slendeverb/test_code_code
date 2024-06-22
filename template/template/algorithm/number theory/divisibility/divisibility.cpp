__int128 divDn(__int128 a, __int128 b)
{
    if (b < 0)
        return divDn(-a, -b);
    if (a >= 0 || a % b == 0)
        return a / b;
    else
        return a / b - 1;
}

__int128 divUp(__int128 a, __int128 b)
{
    if (b < 0)
        return divUp(-a, -b);
    if (a <= 0 || a % b == 0)
        return a / b;
    else
        return a / b + 1;
}