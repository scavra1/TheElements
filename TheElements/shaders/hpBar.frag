uniform sampler2D texture;
uniform float loadRatio;
uniform int barSize;

void main()
{
	vec4 color;
	vec4 pos = gl_FragCoord;
	if(pos.x < loadRatio * barSize)
	{
		if(pos.x/barSize > 0.7 && pos.x/barSize < 1.0)
		{
			color = vec4(0.8 * (1.5 - (pos.x/barSize)), 1.0, 0.14, 1.0);
		}
		else if(pos.x/barSize > 0.8 && pos.x/barSize < 0.9)
		{
			
		}
		else if(pos.x/barSize < 0.1)
		{
			color = vec4((pos.x / barSize) + 0.9, 0.0, 0.0, 1.0);
		}
		else
		{
			color = vec4(1.0, pos.x/barSize/0.6, 0.0, 1.0);
		}
	}
	else
	{
		color = vec4(0.0, 0.0, 0.0, 1.0);
	}
	
	
	gl_FragColor = color;
}