#version 330 core
out vec4 FragColor;

uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material
{
	sampler2D diffuse;//漫反射贴图
	sampler2D specular;//镜面贴图
	float shininess;//光泽
};
uniform Material material;

struct Light
{
	vec3 position;//灯源位置

	vec3 ambient;//环境光
	vec3 diffuse;//反射光
	vec3 specular;//镜面光
	//冯氏光照
};
uniform Light light;

void main()
{
	//环境光照
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	//漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * light.diffuse * texture(material.diffuse, TexCoords).rgb);

	//镜面光
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0); 
}