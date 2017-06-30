uniform sampler2D texture;
uniform float loadRatio;
uniform int barSize;

void main()
{
	vec4 color;
	vec4 pos = gl_FragCoord;
	if(pos.x < loadRatio * barSize)
	{
		if(pos.x/barSize < 0.5) {
			color = vec4(1.0, 2*pos.x/barSize, 0.14, 1.0);
		} else {
			color = vec4(1.0 - 2*(pos.x/barSize - 0.5), 1, 0.14, 1.0);
		}
	}
	else {
		color = vec4(0.0, 0.0, 0.0, 1.0);
	}
	gl_FragColor = color;
}