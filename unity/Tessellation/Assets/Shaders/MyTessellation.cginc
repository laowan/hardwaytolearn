#if !defined(TESSELLATION_INCLUDED)
#define TESSELLATION_INCLUDED

struct TessellationFactors {
    float edge[3] : SV_TessFactor;
    float inside : SV_InsideTessFactor;
};

TessellationFactors MyPatchConstantFunction (InputPatch<VertexData, 3> patch)
{
    TessellationFactors f;
    f.edge[0] = 1;
    f.edge[1] = 1;
    f.edge[2] = 1;
    f.inside = 1;
    return f;
}

[UNITY_domain("tri")]
[UNITY_outputcontrolpoints(3)]
[UNITY_outputtopology("triangle_cw")]
[UNITY_partitioning("integer")]
[UNITY_patchconstantfunc("MyPatchConstantFunction")]
VertexData MyHullProgram (
    InputPatch<VertexData, 3> patch,
    uint id : SV_OutputControlPointID)
{
    return patch[id];
}


[UNITY_domain("tri")]
void MyDomainProgram (
    TessellationFactors factors,
    OutputPatch<VertexData, 3> patch,
    float3 barycentricCoordinates : SV_DomainLocation)
{

}

#endif