
        mul=mul*s[i]->b
    for (i = 0; i < count; i++)
        s[i]->a=s[i]->a*(mul/s[i]->b)
    for ( i = 0; i < count; i++)
        printf("%d/%d+",s[i]->a,s[i]->b);

} 