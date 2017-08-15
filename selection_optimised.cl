__kernel void test(__global const int *in, __global int *out,__local int* aux)
{
    int i = get_global_id(0);
    int n = get_global_size(0);
    int wg = get_local_size(0);
    int iKey = in[i];
    int blockSize = 1 * wg;
    
    int pos = 0;
    
    for (int j=0;j<n;j+=blockSize)
    {
        barrier(CLK_LOCAL_MEM_FENCE);
        for (int index=get_local_id(0);index<blockSize;index+=wg)
            aux[index] = in[j+index];
        barrier(CLK_LOCAL_MEM_FENCE);
        
        for (int index=0;index<blockSize;index++)
        {
            int jKey = aux[index];
            if((jKey < iKey) || ( jKey == iKey && (j+index) < i ))
                pos++;
            
        }
    }
    out[pos] = iKey;
}
