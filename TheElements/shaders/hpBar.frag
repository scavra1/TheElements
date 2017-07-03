uniform sampler2D texture;
uniform float loadRatio;
uniform float beginPosition;
uniform int barSize;

void main()
{
	vec4 color;
	vec4 pos = gl_FragCoord;
	if(pos.x < beginPosition + loadRatio * barSize)
	{
		if((pos.x - beginPosition)/barSize < 0.5) {
			color = vec4(1.0, 2*(pos.x - beginPosition)/barSize, 0.14, 1.0);
		} else {
			color = vec4(1.0 - 2*((pos.x - beginPosition)/barSize - 0.5), 1, 0.14, 1.0);
		}
	}
	else {
		color = vec4(0.0, 0.0, 0.0, 1.0);
	}
	gl_FragColor = color;
}