uniform sampler2D texture;
uniform float cooldown;
uniform float beginPosition;
uniform int sheathSize;

void main()
{
	vec4 color = texture2D(texture, gl_TexCoord[0].xy);
	vec4 pos = gl_FragCoord;
	float cool;
	if(cooldown > 1.0)
	{
		cool = 1.0;
	}
	else
	{
		cool = cooldown;
	}
	
	if(color.x > 0.9 && color.y < 0.1 && color.z > 0.9)
	{
		if(pos.x < beginPosition + cool * sheathSize)
		{
			color = vec4(0.0, 1.0, 0.0, 1.0);
		}
		else
		{
			color = vec4(0.5, 0.5, 0.5, 1.0);
		}
	}
	else
	{
		color.w = 0.0;
	}
	gl_FragColor = color;
}