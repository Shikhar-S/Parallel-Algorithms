__kernel void test(__global const int *in, __global int *out,__local int* aux)
{
    int i=get_global_id(0);
    int wg=get_local_size(0);
    int offset=get_group_id(0)*wg;
    in+=offset;
    out+=offset;
    aux[i]=in[i];
    barrier(CLK_LOCAL_MEM_FENCE);
    
    for(int length=1;length<wg;length<<=1)
    {
        int direction=((i&(length<<1))!=0);
        for(int inc=length;inc>0;inc>>=1)
        {
            int j=i^inc;
            int idata=aux[i];
            int jdata=aux[j];
            int smaller=(jdata<idata);
            int swap=smaller^(j<i)^direction;
            barrier(CLK_LOCAL_MEM_FENCE);
            aux[i]=(swap)?jdata:idata;
            barrier(CLK_LOCAL_MEM_FENCE);
        }
    }
    out[i]=aux[i];
}
