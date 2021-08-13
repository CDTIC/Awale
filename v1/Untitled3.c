for (i=0;i<12;i++)
    if (T.ligne==1)
        sum1=Tab[i];
    else
        sum2=Tab[i];
Sum=Sum1+Sum2
if (Sum<=5)
    goto fin;
else
    if (sum1==0)
    {
        for (i=6;i<12;i++)
            if (Tab[i]<12-i)
                goto fin;
    }
    else
        if (sum2==0)
        {
            for (i=0;i<6;i++)
                if (Tab[i]<6-i)
                    goto fin
        }





