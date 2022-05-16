#include <stdafx.h>

static const char* ms_szShaderSrc = R"SRC(
Texture2D HDRSampler : register(t5);
SamplerState g_samLinear : register(s5)
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

float4 main(float4 position	: SV_POSITION, float3 texcoord : TEXCOORD0, float4 color : COLOR0) : SV_Target0
{
    texcoord.x = (texcoord.x * 5.) % 1.0;
    texcoord.y = (texcoord.y * 5.) % 1.0;
    return HDRSampler.Sample(g_samLinear, texcoord);
}
)SRC";

static void OnStart()
{
    Hooks::OverrideScreenShader(ms_szShaderSrc);
}

static void OnStop()
{
    Hooks::ResetScreenShader();
}

static RegisterEffect registerEffect(EFFECT_MISC_LOCALCOOP, OnStart, OnStop, EffectInfo
	{
		.Name = "Split Screen Co-op",
		.Id = "misc_localcoop",
		.IsTimed = true,
        .IsShortDuration = true,
		.EffectCategory = EEffectCategory::Shader,
        .EffectGroupType = EEffectGroupType::Shader
	}
);