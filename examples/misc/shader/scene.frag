/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
*/

varying vec2 vClip;
varying vec4 vColor;

uniform sampler2D OriginalTexture;
uniform sampler2D OriginalNMap;
uniform sampler2D SpecularMap;
uniform vec2 WindowSize;
uniform vec4 SurfaceSpecular;
uniform float SurfaceShininess;

uniform vec3 LightPos;
uniform vec4 LightColor;
uniform vec4 AmbientColor;
uniform float AmbientIntensity;
uniform vec4 LightSpecularColor;
uniform vec3 Falloff;
uniform float Active;

void main()
{
  vec3 ViewDirection = vec3(0.0, 0.0, 1.0);
  vec4 DiffuseColor = texture2D(OriginalTexture, gl_TexCoord[0].xy);
  vec3 NormalMap = texture2D(OriginalNMap, gl_TexCoord[0].xy).rgb;
  vec4 SpecMap = texture2D(SpecularMap, gl_TexCoord[0].xy);
  vec3 Normal = normalize(NormalMap * 2.0 - 1.0);
  vec3 DeltaPos;
  vec3 LightDir;
  float Lambert;
  float D;
  float Att;
  vec3 Tmp;
  vec4 Specular;
  vec3 Result = vec3(0, 0, 0);

  DeltaPos = vec3((LightPos.xy - gl_FragCoord.xy) / WindowSize.xy, LightPos.z);
  LightDir = normalize(DeltaPos);
  Lambert = clamp(dot(Normal, LightDir), 0.0, 1.0);
  D = length(DeltaPos);
  Att = 1.0 / (Falloff.x + Falloff.y * D + Falloff.z * D * D);

  if (dot(Normal, LightDir) <= 0.0)
    Specular = vec4(0.0, 0.0, 0.0, 0.0);
  else
    {
      Tmp =
	Att * vec3(LightSpecularColor) * vec3(SpecMap.rgb)
	* pow(max(0.0, dot(reflect(-LightDir, Normal), ViewDirection)),
	      16.0 - SpecMap.a / 256.0);
      Specular = vec4(Tmp, SpecMap.a);
    }

  Tmp = (AmbientColor * AmbientIntensity * Att).rgb + (LightColor.rgb * Lambert) * DiffuseColor.rgb;
  Tmp += vec3(Specular);

  Result += Tmp;
  gl_FragColor = gl_Color * vec4(Result, DiffuseColor.a);
}
