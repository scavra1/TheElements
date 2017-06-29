uniform sampler2D texture;
uniform float loadRatio;
uniform int barSize;

void main()
{
	vec4 pos = gl_FragCoord;
	vec4 color;
	if(pos.x < loadRatio * barSize)
	{
		color = vec4(0.0, (0.5 * (pos.x/barSize)) + 0.1, 1.0, 1.0);
	}
	else
	{
		color = gl_FragColor;
		color.w = 0.0;
	}
	
	gl_FragColor = color;
}