uniform sampler2D texture;

void main()
{
	vec4 color = texture2D(texture, gl_TexCoord[0].xy);
	if(color.x > 0.9 && color.y < 0.1 && color.z > 0.9)
	{
		color.w = 0.0;
	}
	gl_FragColor = color;
}