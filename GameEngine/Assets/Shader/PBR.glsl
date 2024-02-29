#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;

struct VertexOutput {
    vec3 Normal;
    vec3 WorldPos;
    vec2 TexCoord;
};
layout(location = 0) out VertexOutput Output;

uniform mat3 normalMatrix;
uniform mat4 model;
uniform mat4 u_ViewProjection;

void main() {
    Output.TexCoord = a_TexCoord;
    Output.WorldPos = vec3(model * vec4(a_Position, 1.0));
    Output.Normal = normalMatrix * a_Normal;
    gl_Position = u_ViewProjection * vec4(Output.WorldPos, 1.0);
}

// -----------------------------------------------------------

#type fragment
#version 330 core

out vec4 FragColor;
out int color2;

struct VertexOutput {
	vec3 Normal;
	vec3 WorldPos;
	vec2 TexCoord;
};

layout(location = 0) in VertexOutput Input;

// material
uniform bool b_UseMetallicMap;
uniform bool b_UseRoughnessMap;
uniform float u_metallic;
uniform float u_roughness;
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

// IBL
uniform samplerCube irradianceMap;

// light and camera information(compute N, V, L)
uniform int lightCount;
uniform vec3 lightPositions[2];
uniform vec3 lightColors[2];
uniform vec3 cameraPos;
// TODO: add directional light

// HDR tonemapping
uniform float exposure;
uniform float intensity;

const float F0_NON_METAL = 0.04f;
const float PI = 3.14159265359;

// Noraml
vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(normalMap, Input.TexCoord).xyz * 2.0 - 1.0;

    vec3 Q1 = dFdx(Input.WorldPos);
    vec3 Q2 = dFdy(Input.WorldPos);
    vec2 st1 = dFdx(Input.TexCoord);
    vec2 st2 = dFdy(Input.TexCoord);

    vec3 N = normalize(Input.Normal);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

// PBR Function
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 LambertDiffuse(vec3 Ks, vec3 albedo, float metallic)
{
    vec3 Kd = (vec3(1.0f, 1.0f, 1.0f) - Ks) * (1 - metallic);
    return (Kd * albedo / PI);
}

vec3 CookTorrance(vec3 n, vec3 l, vec3 v, float roughness, float metalness, vec3 f0, out vec3 kS)
{
    vec3 h = normalize(v + l);

    float D = DistributionGGX(n, h, roughness);
    float G = GeometrySmith(n, v, l, roughness);
    vec3 F = fresnelSchlick(max(dot(h, v), 0.0), f0);

    kS = F;

    float NdotV = max(dot(n, v), 0.0f);
    float NdotL = max(dot(n, l), 0.0f);
    return (D * G * F) / (4.0 * max(NdotV * NdotL, 0.01f));
}

void main() {
    // material properties
    vec3 albedo = pow(texture(albedoMap, Input.TexCoord).rgb, vec3(2.2));

    float metallic = u_metallic;
    if (b_UseMetallicMap)
        metallic = texture(metallicMap, Input.TexCoord).r;

    float roughness = u_roughness;
    if(b_UseRoughnessMap)
        roughness = texture(roughnessMap, Input.TexCoord).r;
    
    float ao = texture(aoMap, Input.TexCoord).r;

    // N V R
    // vec3 N = getNormalFromMap();
    vec3 N = normalize(Input.Normal);
    vec3 V = normalize(cameraPos - Input.WorldPos);
    vec3 R = reflect(-V, N);

    vec3 F0 = mix(vec3(F0_NON_METAL), albedo, metallic);
    vec3 Lo = vec3(0.0);

    vec3 tmp;
    // Point Light PBR
    for (int i = 0; i < lightCount; i++) {
        vec3 L = normalize(lightPositions[i] - Input.WorldPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPositions[i] - Input.WorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = min(intensity, 10.0) * lightColors[i] * attenuation;

        vec3 kS;
        vec3 specularBRDF = CookTorrance(N, L, V, roughness, metallic, F0, kS);
        vec3 diffuseBRDF = LambertDiffuse(kS, albedo, metallic);

        float NdotL = max(dot(N, L), 0.0);

        Lo += (diffuseBRDF + specularBRDF) * radiance * NdotL;
    }

    // ambient lighting       
    vec3 irradiance = texture(irradianceMap, N).rgb;
    vec3 diffuse = irradiance * albedo;

    vec3 ambient = diffuse;  // TODO:add specular to ambient

    vec3 color = ambient + 0.8 * Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // color = vec3(1.0) - exp(-color * exposure);
    // gamma correct
    color = pow(color, vec3(1.0 / 2.2));
    FragColor = vec4(color, 1.0);
}