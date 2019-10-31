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
	vec3 direction;//定向光源
    float cutOff;//
    float outerCutOff;

	vec3 ambient;//环境光
	vec3 diffuse;//反射光
	vec3 specular;//镜面光
	//冯氏光照

	//衰减系数
	float constant;
    float linear;
    float quadratic;
};
uniform Light light;

void main()
{
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction)); 
	if (theta > light.cutOff)
	{
	//环境光照
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	//漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + 
                light.quadratic * (distance * distance));

	// vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * light.diffuse * texture(material.diffuse, TexCoords).rgb);

	//镜面光
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0); 		
	}
	else
	{
		FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
	}


}