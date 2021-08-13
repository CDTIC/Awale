int suivant(int i, int n, int p)
{
    if(n==2)
    {
        if(i==p)
            i=0;
        else
            i++;
    }
    else
    {
        if(i==0)
            i=p;
        else
            i--;
    }
    return i;
}
