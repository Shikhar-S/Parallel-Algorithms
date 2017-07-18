__kernel void test(__global int* data,__global int* out)
{
    size_t id0=get_global_id(0);
    int x=data[id0];
    int pos=0;
    int n=get_global_size(0);
    for(int i=0;i<n;i++)
    {
        int y=data[i];
        if(x>y || (x==y && i<id0))
            pos++;
    }
    out[pos]=x;
}
